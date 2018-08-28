/*
Copyright (c) 2018 Chris Chronopoulos

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "keyboard.h"

uint8_t kb_row_pins[KB_NROWS] = {KB_ROW1_PIN, KB_ROW2_PIN, KB_ROW3_PIN, KB_ROW4_PIN};

uint8_t kb_col_pins[KB_NCOLS] = {KB_COL1_PIN, KB_COL2_PIN, KB_COL3_PIN, KB_COL4_PIN,
                                KB_COL5_PIN, KB_COL6_PIN, KB_COL7_PIN, KB_COL8_PIN};

void kb_init(struct kb_data *data) {

    struct port_config config_port_pin;
    port_get_config_defaults(&config_port_pin);

    // configure matrix rows as inputs with pull-down
    config_port_pin.direction  = PORT_PIN_DIR_INPUT;
    config_port_pin.input_pull = PORT_PIN_PULL_DOWN;
    port_pin_set_config(KB_ROW1_PIN, &config_port_pin);
    port_pin_set_config(KB_ROW2_PIN, &config_port_pin);
    port_pin_set_config(KB_ROW3_PIN, &config_port_pin);
    port_pin_set_config(KB_ROW4_PIN, &config_port_pin);

    // configure matrix cols as outpus
    config_port_pin.direction  = PORT_PIN_DIR_OUTPUT;
    port_pin_set_config(KB_COL1_PIN, &config_port_pin);
    port_pin_set_config(KB_COL2_PIN, &config_port_pin);
    port_pin_set_config(KB_COL3_PIN, &config_port_pin);
    port_pin_set_config(KB_COL4_PIN, &config_port_pin);
    port_pin_set_config(KB_COL5_PIN, &config_port_pin);
    port_pin_set_config(KB_COL6_PIN, &config_port_pin);
    port_pin_set_config(KB_COL7_PIN, &config_port_pin);
    port_pin_set_config(KB_COL8_PIN, &config_port_pin);

    // initialize matrix cols low
    port_pin_set_output_level(KB_COL1_PIN, false);
    port_pin_set_output_level(KB_COL2_PIN, false);
    port_pin_set_output_level(KB_COL3_PIN, false);
    port_pin_set_output_level(KB_COL4_PIN, false);
    port_pin_set_output_level(KB_COL5_PIN, false);
    port_pin_set_output_level(KB_COL6_PIN, false);
    port_pin_set_output_level(KB_COL7_PIN, false);
    port_pin_set_output_level(KB_COL8_PIN, false);

    // now initialize the kb_data structure
    data->keyState = 0;
    data->keyState_old = 0;
    data->keyPlaying = -1;
    data->keyOnEvent = -1;
    data->keyLegatoEvent = -1;
    data->keyOffEvent = false;
    data->nKeysHeld = 0;
    for (int i=0; i<KB_NKEYS; i++) {
        data->keysHeld[i] = 0;
    }

}

void kb_update_keyState(struct kb_data *data) {

    /* this updates keyState, keyState_old, keysHeld, and nKeysHeld */

    uint32_t col, row, key;
    uint32_t keyState = 0;
    for (col=0; col<KB_NCOLS; col++) {
        port_pin_set_output_level(kb_col_pins[col], true);
        for (row=0; row<KB_NROWS; row++) {
            if (port_pin_get_input_level(kb_row_pins[row])) {
                key = KB_NCOLS - 1 + row * KB_NCOLS - col;
                keyState |= (1 << key);
            }
        }
        port_pin_set_output_level(kb_col_pins[col], false);
    }

    data->keyState_old = data->keyState;
    data->keyState = keyState;

    data->nKeysHeld = 0;
    for (key=0; key<KB_NKEYS; key++) {
        if (keyState & (1<<key)) {
            data->keysHeld[data->nKeysHeld] = key;
            data->nKeysHeld++;
        }
    }

}

void kb_update_events(struct kb_data *data) {

    /* this updates keyOnEvent, keyOffEvent, keyLegatoEvent, and keyPlaying */

    uint32_t key;
    bool state, oldState;

    data->keyOnEvent = -1;
    data->keyLegatoEvent = -1;
    data->keyOffEvent = false;

    if (data->keyState != data->keyState_old) { // do nothing unless the keystate has changed

        if (data->keyPlaying == -1) { // if nothing was playing before

            // just check for (presumably newly) pressed keys
            for (key=0; key<KB_NKEYS; key++) {
                if (data->keyState & (1 << key)) {
                    data->keyOnEvent = key;
                    data->keyPlaying = key;
                    return;
                }
            }

        } else { // if something *was* playing before

            // check for newly pressed keys
            for (key=0; key<KB_NKEYS; key++) {
                state = data->keyState & (1 << key);
                oldState = data->keyState_old & (1 << key);
                if (state && !oldState) {
                    data->keyLegatoEvent = key;
                    data->keyPlaying = key;
                    return;
                }
            }

            // otherwise check for release on keyPlaying

            if (!(data->keyState & (1 << data->keyPlaying))) { // if keyPlaying is no longer being held
                if (data->keyState == 0) { // and there's nothing else being held, then noteOff
                    data->keyOffEvent = true;
                    data->keyPlaying = -1;
                    return;
                } else { // and there are still notes being held, then legato to lowest key
                    for (key=0; key<KB_NKEYS; key++) {
                        if (data->keyState & (1 << key)) {
                            data->keyLegatoEvent = key;
                            data->keyPlaying = key;
                            return;
                        }
                    }
                }
            }

        }

    }

}

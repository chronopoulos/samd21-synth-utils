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

#include "buttons.h"

uint8_t btn_row_pins[BTN_NROWS] = {BTN_ROW1_PIN, BTN_ROW2_PIN, BTN_ROW3_PIN, BTN_ROW4_PIN};

uint8_t btn_col_pins[BTN_NCOLS] = {BTN_COL1_PIN, BTN_COL2_PIN, BTN_COL3_PIN, BTN_COL4_PIN};

void btn_init(struct btn_data *data) {

    struct port_config config_port_pin;
    port_get_config_defaults(&config_port_pin);

    // configure matrix rows as inputs with pull-down
    config_port_pin.direction  = PORT_PIN_DIR_INPUT;
    config_port_pin.input_pull = PORT_PIN_PULL_DOWN;
    port_pin_set_config(BTN_ROW1_PIN, &config_port_pin);
    port_pin_set_config(BTN_ROW2_PIN, &config_port_pin);
    port_pin_set_config(BTN_ROW3_PIN, &config_port_pin);
    port_pin_set_config(BTN_ROW4_PIN, &config_port_pin);

    // configure matrix cols as outpus
    config_port_pin.direction  = PORT_PIN_DIR_OUTPUT;
    port_pin_set_config(BTN_COL1_PIN, &config_port_pin);
    port_pin_set_config(BTN_COL2_PIN, &config_port_pin);
    port_pin_set_config(BTN_COL3_PIN, &config_port_pin);
    port_pin_set_config(BTN_COL4_PIN, &config_port_pin);

    // initialize matrix cols low
    port_pin_set_output_level(BTN_COL1_PIN, false);
    port_pin_set_output_level(BTN_COL2_PIN, false);
    port_pin_set_output_level(BTN_COL3_PIN, false);
    port_pin_set_output_level(BTN_COL4_PIN, false);

    // now initialize the btn_data structure
    data->buttonState = 0;
    data->buttonState_old = 0;
    data->pressEvent = -1;
    data->releaseEvent = -1;

}

void btn_update_buttonState(struct btn_data *data) {

    uint32_t col, row, button;
    uint16_t buttonState = 0;

    for (col=0; col<BTN_NCOLS; col++) {
        port_pin_set_output_level(btn_col_pins[col], true);
        for (row=0; row<BTN_NROWS; row++) {
            if (port_pin_get_input_level(btn_row_pins[row])) {
                button = row*BTN_NCOLS + col; // this way the buttons are in order: S8, S9..
                buttonState |= (1 << button);
            }
        }
        port_pin_set_output_level(btn_col_pins[col], false);
    }

    data->buttonState_old = data->buttonState;
    data->buttonState = buttonState;

}

void btn_update_events(struct btn_data *data) {

    uint32_t b;
    bool state, oldState;

    data->pressEvent = -1;
    data->releaseEvent = -1;

    // check for state changes
    if (data->buttonState != data->buttonState_old) {

        for (b=0; b<BTN_NBTNS; b++) {
            state = data->buttonState & (1 << b);
            oldState = data->buttonState_old & (1 << b);
            if (state && !oldState) {
                data->pressEvent = b;
            } else if (oldState && !state) {
                data->releaseEvent = b;
            }
        }

    }

}

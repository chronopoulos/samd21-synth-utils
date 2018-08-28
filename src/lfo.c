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

#include "lfo.h"

#define NCYCLES_RESET 400 // TODO tune this value

void _delay_reset(void) {

    int n = NCYCLES_RESET;

    for (;n>0; n--) {
        __asm("nop");
    }

}

void lfo_init(void) {

    struct port_config config_port_pin;
    port_get_config_defaults(&config_port_pin);
    config_port_pin.direction  = PORT_PIN_DIR_OUTPUT;
    port_pin_set_config(LFO_RESET_PIN, &config_port_pin);

}

void lfo_register_callback(const extint_callback_t cb) {

    struct extint_chan_conf config_extint_chan;
    extint_chan_get_config_defaults(&config_extint_chan);
    config_extint_chan.gpio_pin           = LFO_CLK_EXTINT_PIN;
    config_extint_chan.gpio_pin_mux       = LFO_CLK_EXTINT_MUX;
    config_extint_chan.gpio_pin_pull      = EXTINT_PULL_NONE;
    config_extint_chan.detection_criteria = EXTINT_DETECT_FALLING;
    extint_chan_set_config(LFO_EXTINT_CHAN, &config_extint_chan);
    extint_register_callback(cb, LFO_EXTINT_CHAN, EXTINT_CALLBACK_TYPE_DETECT);
    extint_chan_enable_callback(LFO_EXTINT_CHAN, EXTINT_CALLBACK_TYPE_DETECT);

}

void lfo_enable(void) {

    port_pin_set_output_level(LFO_RESET_PIN, true);

}

void lfo_disable(void) {

    port_pin_set_output_level(LFO_RESET_PIN, false);

}

void lfo_reset(void) {

    port_pin_set_output_level(LFO_RESET_PIN, false);
    _delay_reset();
    port_pin_set_output_level(LFO_RESET_PIN, true);

}

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

#include "portamento.h"

void portamento_init(void) {

    struct port_config config_port_pin;
    port_get_config_defaults(&config_port_pin);
    config_port_pin.direction  = PORT_PIN_DIR_OUTPUT;

    port_pin_set_config(PORTA1_STATE_PIN, &config_port_pin);
    port_pin_set_config(PORTA2_STATE_PIN, &config_port_pin);

    port_pin_set_output_level(PORTA1_STATE_PIN, true);
    port_pin_set_output_level(PORTA2_STATE_PIN, true);

}

void portamento_set_chan1(bool on) {

    port_pin_set_output_level(PORTA1_STATE_PIN, !on);

}

void portamento_set_chan2(bool on) {

    port_pin_set_output_level(PORTA2_STATE_PIN, !on);

}


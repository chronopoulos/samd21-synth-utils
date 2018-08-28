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

#include "range.h"

void range_init(void) {

    struct port_config config_port_pin;
    port_get_config_defaults(&config_port_pin);
    config_port_pin.direction  = PORT_PIN_DIR_INPUT;
    port_pin_set_config(RANGE1_PIN, &config_port_pin);
    port_pin_set_config(RANGE2_PIN, &config_port_pin);

}

uint8_t range_get_position(void) {

    /* returns 0,1,2,3 based on rotary switch position */

    uint8_t p1, p2;

    p1 = port_pin_get_input_level(RANGE1_PIN) ? 1 : 0;
    p2 = port_pin_get_input_level(RANGE2_PIN) ? 1 : 0;

    return 4 - 2*p1 - p2;

}

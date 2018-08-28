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

#include "mode.h"

void mode_init(struct mode_data *data) {

    data->portamento1 = PORTAMENTO_MODE_OFF;
    data->portamento2 = PORTAMENTO_MODE_OFF;
    data->arp = MODE_ARP_OFF;
    data->load = false;
    data->play = false;
    data->hold = false;
    data->transpose_tgl = 0;
    data->transpose_btn = 0;

}

void mode_set_portamento1(struct mode_data *data, int mode) {

    data->portamento1 = mode;

}

void mode_set_portamento2(struct mode_data *data, int mode) {

    data->portamento2 = mode;

}

void mode_toggle_load(struct mode_data *data) {

    data->load = !data->load;

}

void mode_toggle_play(struct mode_data *data) {

    data->play = !data->play;

}

void mode_set_arp(struct mode_data *data, int mode) {

    if (mode == data->arp) {
        data->arp = MODE_ARP_OFF;
    } else {
        data->arp = mode;
    }

}

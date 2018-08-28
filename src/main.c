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

#include <system.h> // for system_init
#include <samd21.h>

#include "lfo.h"
#include "gate.h"
#include "dacmux.h"
#include "portamento.h"
#include "keyboard.h"
#include "buttons.h"
#include "state.h"
#include "leds.h"
#include "range.h"
#include "seq.h"
#include "flash.h"
#include "arp.h"


/* global data structures */

struct dacmux_data dacmux;
struct kb_data kb;
struct btn_data btn;
struct state_data s;
struct leds_data leds;
struct seq_data seq;
struct arp_data arp;

volatile bool lfoInterruptFlag = false;

/* main */

void interrupt_callback(void) {

    lfoInterruptFlag = true;

}

int main(void) {

    // setup

    system_init(); // needed for extint

    lfo_init();
    gate_init();
    portamento_init();
    range_init();
    flash_init();

    dacmux_init(&dacmux);
    kb_init(&kb);
    btn_init(&btn);

    state_init(&s);

    leds_init(&leds);
    seq_init(&seq);
    arp_init(&arp);

    lfo_register_callback(interrupt_callback);
    system_interrupt_enable_global();
    lfo_enable();

    // loop

    while(1) {

    }

}


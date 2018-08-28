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

#include "dacmux.h"

void dacmux_init(struct dacmux_data *data) {

    // dac

    struct dac_config config_dac;
    dac_get_config_defaults(&config_dac);
    config_dac.reference = DAC_REFERENCE_AVCC;
    dac_init(&data->instance, DAC, &config_dac);

    struct dac_chan_config config_dac_chan;
    dac_chan_get_config_defaults(&config_dac_chan);
    dac_chan_set_config(&data->instance, DAC_CHANNEL_0, &config_dac_chan);
    dac_chan_enable(&data->instance, DAC_CHANNEL_0);

    dac_enable(&data->instance);

    // mux

    struct port_config config_port_pin;
    port_get_config_defaults(&config_port_pin);

    config_port_pin.direction  = PORT_PIN_DIR_OUTPUT;
    port_pin_set_config(DACMUX_SEL1_PIN, &config_port_pin);
    port_pin_set_config(DACMUX_SEL2_PIN, &config_port_pin);
    port_pin_set_config(DACMUX_SEL3_PIN, &config_port_pin);
    port_pin_set_config(DACMUX_INHB_PIN, &config_port_pin);

    port_pin_set_output_level(DACMUX_SEL1_PIN, false);
    port_pin_set_output_level(DACMUX_SEL2_PIN, false);
    port_pin_set_output_level(DACMUX_SEL3_PIN, false);
    port_pin_set_output_level(DACMUX_INHB_PIN, false);

    // channels
    data->cv1 = 0;
    data->range = 0;

}

void dacmux_set_cv1(struct dacmux_data *data, uint16_t value) {

    data->cv1 = value;

}

void dacmux_set_range(struct dacmux_data *data, uint16_t value) {

    data->range = value;

}

void dacmux_set_random(struct dacmux_data *data, uint16_t value) {

    data->random = value;

}

void dacmux_set_accel(struct dacmux_data *data, uint16_t value) {

    data->accel = value;

}

void _settle_delay(void) {

    int n;
    for (n=DAC_SETTLE_NCYCLES; n>0; n--) {
        __asm("nop");
    }

}

void dacmux_output(struct dacmux_data *data) {

    /* CV1 is channel 1 */
    port_pin_set_output_level(DACMUX_INHB_PIN, true);
    dac_chan_write(&data->instance, DAC_CHANNEL_0, data->cv1);
    port_pin_set_output_level(DACMUX_SEL1_PIN, true);
    port_pin_set_output_level(DACMUX_SEL2_PIN, false);
    port_pin_set_output_level(DACMUX_SEL3_PIN, false);
    port_pin_set_output_level(DACMUX_INHB_PIN, false);
    _settle_delay();

    /* RANGE is channel 2 */
    port_pin_set_output_level(DACMUX_INHB_PIN, true);
    dac_chan_write(&data->instance, DAC_CHANNEL_0, data->range);
    port_pin_set_output_level(DACMUX_SEL1_PIN, false);
    port_pin_set_output_level(DACMUX_SEL2_PIN, true);
    port_pin_set_output_level(DACMUX_SEL3_PIN, false);
    port_pin_set_output_level(DACMUX_INHB_PIN, false);
    _settle_delay();

    /* RANDOM is channel 3 */
    port_pin_set_output_level(DACMUX_INHB_PIN, true);
    dac_chan_write(&data->instance, DAC_CHANNEL_0, data->random);
    port_pin_set_output_level(DACMUX_SEL1_PIN, true);
    port_pin_set_output_level(DACMUX_SEL2_PIN, true);
    port_pin_set_output_level(DACMUX_SEL3_PIN, false);
    port_pin_set_output_level(DACMUX_INHB_PIN, false);
    _settle_delay();

    /* ACCEL is channel 4 */
    port_pin_set_output_level(DACMUX_INHB_PIN, true);
    dac_chan_write(&data->instance, DAC_CHANNEL_0, data->accel);
    port_pin_set_output_level(DACMUX_SEL1_PIN, false);
    port_pin_set_output_level(DACMUX_SEL2_PIN, false);
    port_pin_set_output_level(DACMUX_SEL3_PIN, true);
    port_pin_set_output_level(DACMUX_INHB_PIN, false);
    _settle_delay();

}

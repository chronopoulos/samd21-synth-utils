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

#include "leds.h"

void leds_init(struct leds_data *data) {
    /* TODO: why is this so slow? */

    struct i2c_master_config config_i2c_master;
    i2c_master_get_config_defaults(&config_i2c_master);
    i2c_master_init(&data->i2c_instance, I2C_SERCOM, &config_i2c_master);

    i2c_master_enable(&data->i2c_instance);

    data->i2c_packet.address = 0x20 | I2C_ADDR;
    data->i2c_packet.data_length = I2C_DATALEN;
    data->i2c_packet.data = data->i2c_buffer;

    // now configure the MCP23017
    data->i2c_buffer[0] = 0x00; // IODIRA
    data->i2c_buffer[1] = 0x00; // all outputs
    i2c_master_write_packet_wait(&data->i2c_instance, &data->i2c_packet);
    data->i2c_buffer[0] = 0x01; // IODIRB
    data->i2c_buffer[1] = 0x00; // all outputs
    i2c_master_write_packet_wait(&data->i2c_instance, &data->i2c_packet);

    data->iodira = 0x00;
    data->iodirb = 0x00;

}

void leds_set_load(struct leds_data *data, bool state) {

    if (state) {
        data->iodirb |= LED_LOAD;
    } else {
        data->iodirb &= ~LED_LOAD;
    }

}

void leds_set_play(struct leds_data *data, bool state) {

    if (state) {
        data->iodirb |= LED_PLAY;
    } else {
        data->iodirb &= ~LED_PLAY;
    }

}

void leds_set_down(struct leds_data *data, bool state) {

    if (state) {
        data->iodira |= LED_DOWN;
    } else {
        data->iodira &= ~LED_DOWN;
    }

}

void leds_set_updown(struct leds_data *data, bool state) {

    if (state) {
        data->iodira |= LED_UPDOWN;
    } else {
        data->iodira &= ~LED_UPDOWN;
    }

}

void leds_set_up(struct leds_data *data, bool state) {

    if (state) {
        data->iodira |= LED_UP;
    } else {
        data->iodira &= ~LED_UP;
    }

}

void leds_set_hold(struct leds_data *data, bool state) {

    if (state) {
        data->iodira |= LED_HOLD;
    } else {
        data->iodira &= ~LED_HOLD;
    }

}

void leds_set_transpose(struct leds_data *data, bool state) {

    if (state) {
        data->iodira |= LED_TRANSPOSE;
    } else {
        data->iodira &= ~LED_TRANSPOSE;
    }

}

void leds_set_internal(struct leds_data *data, bool state) {

    if (state) {
        data->iodira |= LED_INTERNAL;
    } else {
        data->iodira &= ~LED_INTERNAL;
    }

}

void leds_set_both(struct leds_data *data, bool state) {

    if (state) {
        data->iodira |= LED_BOTH;
    } else {
        data->iodira &= ~LED_BOTH;
    }

}

void leds_set_external(struct leds_data *data, bool state) {

    if (state) {
        data->iodira |= LED_EXTERNAL;
    } else {
        data->iodira &= ~LED_EXTERNAL;
    }

}

void leds_set_memory(struct leds_data *data, bool state) {

    if (state) {
        data->iodirb |= LED_MEMORY;
    } else {
        data->iodirb &= ~LED_MEMORY;
    }

}

void leds_set_shift(struct leds_data *data, bool state) {

    if (state) {
        data->iodirb |= LED_SHIFT;
    } else {
        data->iodirb &= ~LED_SHIFT;
    }

}

void leds_output(struct leds_data *data) {

    data->i2c_buffer[0] = 0x12;
    data->i2c_buffer[1] = data->iodira; 
    i2c_master_write_packet_wait(&data->i2c_instance, &data->i2c_packet);

    data->i2c_buffer[0] = 0x13;
    data->i2c_buffer[1] = data->iodirb; 
    i2c_master_write_packet_wait(&data->i2c_instance, &data->i2c_packet);

}


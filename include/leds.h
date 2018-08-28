#ifndef LEDS_H
#define LEDS_h

#include <i2c_common.h>
#include <i2c_master.h>

#define I2C_SERCOM SERCOM4
#define I2C_ADDR 0x00
#define I2C_DATALEN 2

/* iodira */
#define LED_DOWN (1 << 0)
#define LED_UPDOWN (1 << 1)
#define LED_UP (1 << 2)
#define LED_HOLD (1 << 3)
#define LED_TRANSPOSE (1 << 4)
#define LED_INTERNAL (1 << 5)
#define LED_BOTH (1 << 6)
#define LED_EXTERNAL (1 << 7)

/* iodirb */
#define LED_MEMORY (1 << 0)
#define LED_SHIFT (1 << 1)
#define LED_LOAD (1 << 2)
#define LED_PLAY (1 << 3)


struct leds_data {

    struct i2c_master_module i2c_instance;
    struct i2c_master_packet i2c_packet;
    uint8_t i2c_buffer[I2C_DATALEN];

    uint8_t iodira;
    uint8_t iodirb;

};

void leds_init(struct leds_data*);
void leds_set_load(struct leds_data*, bool);
void leds_set_play(struct leds_data*, bool);
void leds_set_down(struct leds_data*, bool);
void leds_set_updown(struct leds_data*, bool);
void leds_set_up(struct leds_data*, bool);
void leds_set_hold(struct leds_data*, bool);
void leds_set_transpose(struct leds_data*, bool);
void leds_set_internal(struct leds_data*, bool);
void leds_set_both(struct leds_data*, bool);
void leds_set_external(struct leds_data*, bool);
void leds_set_memory(struct leds_data*, bool);
void leds_set_shift(struct leds_data*, bool);
void leds_output(struct leds_data*);

#endif

#ifndef BUTTONS_H
#define BUTTONS_H

#include <port.h>

#define BTN_NROWS 4
#define BTN_NCOLS 4
#define BTN_NBTNS 16

#define BTN_ROW1_PIN PIN_PA01
#define BTN_ROW2_PIN PIN_PA03
#define BTN_ROW3_PIN PIN_PB08
#define BTN_ROW4_PIN PIN_PB09

#define BTN_COL1_PIN PIN_PB10
#define BTN_COL2_PIN PIN_PA14
#define BTN_COL3_PIN PIN_PB11
#define BTN_COL4_PIN PIN_PA00

#define BUTTON_LOAD 0
#define BUTTON_PLAY 1

#define BUTTON_DOWN 2
#define BUTTON_UPDOWN 4
#define BUTTON_UP 5

#define BUTTON_HOLD 6
#define BUTTON_TRANSPOSE 8

#define BUTTON_INTERNAL 9
#define BUTTON_BOTH 10
#define BUTTON_EXTERNAL 12
#define BUTTON_MEMORY 13
#define BUTTON_SHIFT 14

#define BUTTON_PORTAMENTO_AUTO 3
#define BUTTON_PORTAMENTO_ON 7

#define BUTTON_TRANSPOSE_DOWN 11
#define BUTTON_TRANSPOSE_UP 15


struct btn_data {

    uint16_t buttonState;       // bitfield
    uint16_t buttonState_old;   // bitfield

    int pressEvent;
    int releaseEvent;

};

void btn_init(struct btn_data*);

void btn_update_buttonState(struct btn_data*);

void btn_update_events(struct btn_data*);

#endif

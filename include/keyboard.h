#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <port.h>

#define KB_NROWS 4
#define KB_NCOLS 8
#define KB_NKEYS 32

#define KB_ROW1_PIN PIN_PA01
#define KB_ROW2_PIN PIN_PA03
#define KB_ROW3_PIN PIN_PB08
#define KB_ROW4_PIN PIN_PB09

#define KB_COL1_PIN PIN_PA04
#define KB_COL2_PIN PIN_PA05
#define KB_COL3_PIN PIN_PA06
#define KB_COL4_PIN PIN_PA07
#define KB_COL5_PIN PIN_PA08
#define KB_COL6_PIN PIN_PA09
#define KB_COL7_PIN PIN_PA10
#define KB_COL8_PIN PIN_PA11

struct kb_data {

    uint32_t keyState;      // bitfield
    uint32_t keyState_old;  // bitfield
    int keyPlaying;

    int keyOnEvent;
    int keyLegatoEvent;
    bool keyOffEvent;

    int nKeysHeld;
    int keysHeld[32];

};

void kb_init(struct kb_data*);

void kb_update_keyState(struct kb_data*);

void kb_update_events(struct kb_data*);

#endif

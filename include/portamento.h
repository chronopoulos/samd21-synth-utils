#ifndef PORTAMENTO_H
#define PORTAMENTO_H

#include <port.h>
#include <stdbool.h>

#define PORTA1_STATE_PIN PIN_PB23
#define PORTA2_STATE_PIN PIN_PA27

void portamento_init(void);

void portamento_set_chan1(bool);

void portamento_set_chan2(bool);

#endif

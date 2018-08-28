#ifndef GATE_H
#define GATE_H

#include <port.h>

#define GATE_PIN PIN_PA19

void gate_init(void);

void gate_on(void);

void gate_on_pulse(void);

void gate_off(void);

#endif

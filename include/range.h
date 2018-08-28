#ifndef RANGE_H
#define RANGE_H

#include <port.h>

#define RANGE1_PIN PIN_PB02
#define RANGE2_PIN PIN_PB03

void range_init(void);
uint8_t range_get_position(void);

#endif

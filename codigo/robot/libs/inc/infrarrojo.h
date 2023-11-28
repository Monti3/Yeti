#ifndef _INFRAROJO_H_
#define _INFRAROJO_H_

#include "hardware/gpio.h"


void infrarojo_init(uint8_t pin);
bool infrarojo_get(uint8_t pin);

#endif  /* _INFRAROJO_H_ */
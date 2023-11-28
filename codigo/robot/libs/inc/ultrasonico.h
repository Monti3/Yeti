#ifndef _ULTRASONICO_H_
#define _ULTRASONICO_H_

#include <stdio.h>
#include "pico/stdlib.h"

typedef struct{
    uint8_t trigger;
    uint8_t echo;
} ultrasonico_t;

/* Prototipos de funciones */
void ultrasonico_init(ultrasonico_t ultrasonico);
float ultrasonico_get_distance_cm(ultrasonico_t ultrasonico);

#endif /* _ULTRASONICO_H_ */


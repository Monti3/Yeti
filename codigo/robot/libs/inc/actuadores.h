#ifndef _ACTUADORES_H_
#define _ACTUADORES_H_

#include "pico/stdlib.h"
#include "hardware/adc.h"

/*prototipos para funciones*/


void actuador_init(uint8_t pin_actuador);
void potenciometro_init(uint8_t pin_potenciometro);
uint16_t leer_potenciometro(void);
void actuar(uint8_t actuador);
void no_actuar(uint8_t actuador);
void parpadear(uint8_t pin,uint delay);

#endif  /* _ACTUADORES_H_ */
#ifndef _L298_H_
#define _L298_H_

#include "pico/stdlib.h"
#include "hardware/pwm.h"


/*
 *  @param forward: numero de pin que controla la direccion de avance
 *  @param reverse: numero de pin que controla la direccion de reversa
 *  @param en: numero de pin que controla la velocidad del motor
 */

typedef struct {
    uint8_t forward;
    uint8_t reverse;
    uint8_t en;
} l298_t;




/* Prototipos para funciones de motores */
void motor_init(l298_t);
void motor_forward(l298_t l298);
void motor_reverse(l298_t l298);
void motor_forward_partial(l298_t l298, uint8_t partial);
void motor_reverse_partial(l298_t l298, uint8_t partial);
void motor_stop(l298_t l298);
/* Prototipos para funciones de movimiento */
void ir_hacia_adelante(l298_t motorIzquierdo, l298_t motorDerecho);
void ir_hacia_atras(l298_t motorIzquierdo, l298_t motorDerecho);
void girar_a_la_derecha(l298_t motorIzquierdo, l298_t motorDerecho);
void girar_a_la_izquierda(l298_t motorIzquierdo, l298_t motorDerecho);
void doblar_a_la_derecha(l298_t motorIzquierdo, l298_t motorDerecho);
void doblar_a_la_izquierda(l298_t motorIzquierdo, l298_t motorDerecho);
void atras_a_la_izquierda(l298_t motorIzquierdo, l298_t motorDerecho);
void atras_a_la_derecha(l298_t motorIzquierdo, l298_t motorDerecho);
void full_stop(l298_t motorIzquierdo, l298_t motorDerecho);




#endif  /* _L298_H */
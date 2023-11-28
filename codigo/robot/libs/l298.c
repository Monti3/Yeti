#include "l298.h"

/*
True Table de L298N  / El pin ENA/ENB es modulable por PWM
ENA | IN1 | IN2 | D                                 
0   | N/A |N/A  |OFF
1   |0    |0    |STOP
1   |0    |1    |TURN BACKWARDS
1   |1    |0    |TURN FORWARDS
1   |1    |1    |STOP
ENB | IN3 | IN4 | D
0   | N/A |N/A  |OFF
1   |0    |0    |STOP
1   |0    |1    |TURN BACKWARDS
1   |1    |0    |TURN FORWARDS
1   |1    |1    |STOP
*/

/*
*   @brief Se inicializan los pines para controlaran los motores (se usa la struct l298 con los datos dentro)
 *  @param forward: numero de pin que controla la direccion de avance
 *  @param reverse: numero de pin que controla la direccion de reversa
 *  @param en: numero de pin que controla la velocidad del motor
 */
void motor_init(l298_t l298) {
   
    gpio_init(l298.forward);
    gpio_init(l298.reverse);
    gpio_set_dir(l298.forward,1);
    gpio_set_dir(l298.reverse,1);
    gpio_put(l298.forward,0);
    gpio_put(l298.reverse,0);
    gpio_set_function(l298.en, GPIO_FUNC_PWM);
    /* Consigo los slices del pin enable */
    uint slice_pin_en = pwm_gpio_to_slice_num(l298.en);
    /* Obtengo configuracion por defecto de PWM */
    pwm_config config = pwm_get_default_config();
    /* Inicializo ambos slices */
    pwm_init(slice_pin_en, &config, true);
    /* Arranco con 0% de ancho de pulso */
    pwm_set_gpio_level(l298.en, 0);

}

/*
 *  @brief  Indica al motor de que vaya hacia adelante (se usa la struct l298 con los datos dentro)
 *  @param forward: numero de pin que controla la direccion de avance
 *  @param reverse: numero de pin que controla la direccion de reversa
 *  @param en: numero de pin que controla la velocidad del motor
 */
void motor_forward(l298_t l298) {
    gpio_put(l298.forward,1);
    gpio_put(l298.reverse,0);

    /* 100% de ancho de pulso para el pin de avance */
    pwm_set_gpio_level(l298.en, 0xffff);
}

/*
 *  @brief  Indica al motor de que vaya hacia atras (se usa la struct l298 con los datos dentro)
 *  @param forward: numero de pin que controla la direccion de avance
 *  @param reverse: numero de pin que controla la direccion de reversa
 *  @param en: numero de pin que controla la velocidad del motor
 */
void motor_reverse(l298_t l298) {
    gpio_put(l298.forward,0);
    gpio_put(l298.reverse,1);
    
    /* 100% de ancho de pulso para el pin de reversa */
    pwm_set_gpio_level(l298.en, 0xffff);
}

/*
 *  @brief  Indica al motor de que vaya hacia adelante parcialmente (se usa la struct l298 con los datos dentro)
 *  @param forward: numero de pin que controla la direccion de avance
 *  @param reverse: numero de pin que controla la direccion de reversa
 *  @param en: numero de pin que controla la velocidad del motor
 *  @param  partial: porcentaje de potencia entregada
 */
void motor_forward_partial(l298_t l298, uint8_t partial) {
    gpio_put(l298.forward,1);
    gpio_put(l298.reverse,0);
    
    /* Calculo el valor de duty necesario */
    uint16_t duty = (uint32_t)partial * 0xffff / 100.0;
    /* Porcentaje de ancho de pulso indicado para el pin de avance */
    pwm_set_gpio_level(l298.en, duty);
}

/*
 *  @brief  Indica al motor de que vaya hacia atras parcialmente (se usa la struct l298 con los datos dentro)
 *  @param forward: numero de pin que controla la direccion de avance
 *  @param reverse: numero de pin que controla la direccion de reversa
 *  @param en: numero de pin que controla la velocidad del motor
 *  @param  partial: porcentaje de potencia entregada
 */
void motor_reverse_partial(l298_t l298, uint8_t partial) {
    gpio_put(l298.forward,0);
    gpio_put(l298.reverse,1);
    /* Calculo el valor de duty necesario */
    uint16_t duty = (uint32_t)partial * 0xffff / 100.0;
    /* Porcentaje de ancho de pulso indicado para el pin de reversa */
    pwm_set_gpio_level(l298.en, duty);
}

/*
 *  @brief  Indica al motor que este completamente detenido (se usa la struct l298 con los datos dentro)
 *  @param forward: numero de pin que controla la direccion de avance
 *  @param reverse: numero de pin que controla la direccion de reversa
 *  @param en: numero de pin que controla la velocidad del motor
 */
void motor_stop(l298_t l298)
{
    motor_forward_partial(l298,0);
}

/*
 *  @brief  Se indica el giro de ambos motores en sentido horario, pudiendo ir hacia adelante (se usa la struct l298 con los datos dentro)
 *  @param forward: numero de pin que controla la direccion de avance
 *  @param reverse: numero de pin que controla la direccion de reversa
 *  @param en: numero de pin que controla la velocidad del motor
 */
void ir_hacia_adelante(l298_t motorIzquierdo, l298_t motorDerecho)
{
    motor_forward(motorIzquierdo);
    motor_forward(motorDerecho);
}

/*
 *  @brief  Se indica el giro de ambos motores en sentido antihorario , pudiendo retroceder (se usa la struct l298 con los datos dentro)
 *  @param forward: numero de pin que controla la direccion de avance
 *  @param reverse: numero de pin que controla la direccion de reversa
 *  @param en: numero de pin que controla la velocidad del motor
 */
void ir_hacia_atras(l298_t motorIzquierdo, l298_t motorDerecho)
{
    motor_reverse(motorIzquierdo);
    motor_reverse(motorDerecho);
}

/*
 *  @brief  Se indica el giro de el motor izquierdo hacia adelante y el derecho hacia atras, causando el giro hacia la derecha (se usa la struct l298 con los datos dentro)
 *  @param forward: numero de pin que controla la direccion de avance
 *  @param reverse: numero de pin que controla la direccion de reversa
 *  @param en: numero de pin que controla la velocidad del motor
 */
void girar_a_la_derecha(l298_t motorIzquierdo, l298_t motorDerecho)
{
    motor_forward(motorIzquierdo);
    motor_reverse(motorDerecho);
}

/*
 *  @brief  Se indica el giro de el motor derecho hacia adelante y el izquierdo hacia atras, causando el giro hacia la izquierda (se usa la struct l298 con los datos dentro)
 *  @param forward: numero de pin que controla la direccion de avance
 *  @param reverse: numero de pin que controla la direccion de reversa
 *  @param en: numero de pin que controla la velocidad del motor
 */
void girar_a_la_izquierda(l298_t motorIzquierdo, l298_t motorDerecho)
{
    motor_forward(motorDerecho);
    motor_reverse(motorIzquierdo);
}

/*
 *  @brief  Se indica el giro de el motor derecho hacia adelante y del motor izquierdo hacia adelante al 50%, permitiendo el doblar (se usa la struct l298 con los datos dentro)
 *  @param forward: numero de pin que controla la direccion de avance
 *  @param reverse: numero de pin que controla la direccion de reversa
 *  @param en: numero de pin que controla la velocidad del motor
 */
void doblar_a_la_derecha(l298_t motorIzquierdo, l298_t motorDerecho)
{
    motor_forward(motorIzquierdo);
    motor_forward_partial(motorDerecho, 50);
}

/*
 *  @brief  Se indica el giro de el motor izquierdo hacia adelante y del motor derecho hacia adelante al 50%, permitiendo el doblar (se usa la struct l298 con los datos dentro)
 *  @param forward: numero de pin que controla la direccion de avance
 *  @param reverse: numero de pin que controla la direccion de reversa
 *  @param en: numero de pin que controla la velocidad del motor
 */
void doblar_a_la_izquierda(l298_t motorIzquierdo, l298_t motorDerecho)
{
    motor_forward(motorDerecho);
    motor_forward_partial(motorIzquierdo, 50);
}

/*
 *  @brief  Se indica el giro de el motor izquierdo hacia atras y del motor derecho hacia atras al 50%, permitiendo el doblar a la izquierda hacia atras (se usa la struct l298 con los datos dentro)
 *  @param forward: numero de pin que controla la direccion de avance
 *  @param reverse: numero de pin que controla la direccion de reversa
 *  @param en: numero de pin que controla la velocidad del motor
 */
void atras_a_la_derecha(l298_t motorIzquierdo, l298_t motorDerecho)
{
    motor_reverse(motorIzquierdo);
    motor_reverse_partial(motorDerecho, 50);
}

/*
 *  @brief  Se indica el giro de el motor derecho hacia atras y del motor izquierdo hacia atras al 50%, permitiendo el doblar a la derecha hacia atras (se usa la struct l298 con los datos dentro)
 *  @param forward: numero de pin que controla la direccion de avance
 *  @param reverse: numero de pin que controla la direccion de reversa
 *  @param en: numero de pin que controla la velocidad del motor
 */
void atras_a_la_izquierda(l298_t motorIzquierdo, l298_t motorDerecho)
{
    motor_reverse(motorDerecho);
    motor_reverse_partial(motorIzquierdo, 50);
}

/*
 *  @brief  Se indica el giro de el motor nulo, indicando que el robot este quieto. (se usa la struct l298 con los datos dentro)
 *  @param forward: numero de pin que controla la direccion de avance
 *  @param reverse: numero de pin que controla la direccion de reversa
 *  @param en: numero de pin que controla la velocidad del motor
 */
void full_stop(l298_t motorIzquierdo, l298_t motorDerecho)
{   
    motor_stop(motorIzquierdo);
    motor_stop(motorDerecho);
    
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libs/inc/bt.h"
#include "libs/inc/infrarrojo.h"
#include "libs/inc/l298.h"
#include "libs/inc/ultrasonico.h"
#include "libs/inc/actuadores.h"

/*Prototipos para funciones de modo */

void modo_init(uint8_t led);
void modo_despejar_el_area();
void modo_sumo();
void modo_velocidad_y_control();

/*
 *  @brief  Programa principal
 */
#define BLANCO true
#define NEGRO false
const uint8_t infrarojo_izquierdo = 2;
const uint8_t infrarojo_derecho = 3;
const uint8_t infrarojo_delantero = 4;
const uint8_t motor_izquierdo_forward = 8;
const uint8_t motor_izquierdo_back = 9; // motor izquierdo
const uint8_t motor_derecho_forward = 27;
const uint8_t motor_derecho_back = 28; // motor derecho
const uint8_t ENA = 14;
const uint8_t ENB = 15;
const uint8_t ultrasonico_trigger = 12;
const uint8_t ultrasonico_echo = 13;
const uint8_t led_rojo = 16;
const uint8_t led_verde = 17;
const uint8_t led_azul = 18;
const uint8_t buzzer = 22;
const uint8_t pico_uart_tx = 0;
const uint8_t pico_uart_rx = 1;
const uint8_t sw1 = 19;
const uint8_t sw2= 20;
const uint8_t sw3 = 21;



l298_t motor_izquierdo = {
    motor_izquierdo_forward,
    motor_izquierdo_back,
    ENA};

l298_t motor_derecho = {
    motor_derecho_forward,
    motor_derecho_back,
    ENB};

ultrasonico_t ultrasonico = {

    ultrasonico_trigger,
    ultrasonico_echo

};

int main(void)
{

    stdio_init_all();
    infrarojo_init(infrarojo_izquierdo);
    infrarojo_init(infrarojo_derecho);
    infrarojo_init(infrarojo_delantero);
    motor_init(motor_izquierdo);
    motor_init(motor_derecho);
    ultrasonico_init(ultrasonico);
    actuador_init(led_rojo);
    actuador_init(25);
    actuador_init(led_verde);
    actuador_init(led_azul);
    uart_start(pico_uart_tx, pico_uart_rx);
    gpio_set_dir(sw1,false);
    gpio_set_dir(sw2,false);
    gpio_set_dir(sw3,false);

    bool lectura_sw1 = gpio_get(sw1);
    bool lectura_sw2 = gpio_get(sw2);
    bool lectura_sw3 = gpio_get(sw3);

    if (lectura_sw1){
       modo_sumo(); 
    }
   else if (lectura_sw1){
        modo_velocidad_y_control();
    }
    else if (lectura_sw1){
        modo_despejar_el_area();
    }
    else{
        gpio_put(led_azul,1);
        gpio_put(led_verde,1);
        gpio_put(led_rojo,1);
    }

}

/*
 *  @brief Modo indicado para "Tiempo de Seguridad" en el reglamento
 *  @param led: pin del led que va a indicar el modo
 */
void modo_init(uint8_t led)
{
    for (uint i; i <= 5; i++)
    {
        gpio_put(led, 1);
        sleep_ms(500);
        gpio_put(led, 0);
        sleep_ms(500);
    }
    return;
}

/*
 *   @brief modo indicado para la disciplina "Modo despejar el area"
 */
void modo_despejar_el_area()
{

    modo_init(led_rojo);
    while (1)
    {
        float dist = ultrasonico_get_distance_cm(ultrasonico);
        bool infL = infrarojo_get(infrarojo_izquierdo);
        bool infR = infrarojo_get(infrarojo_derecho);
        bool infA = infrarojo_get(infrarojo_delantero);

        if (infR == 0 && infL == 1 && dist > 1500) // si el sensor derecho se detecta fuera de la pista, se gira a la izquierda
        {
            full_stop(motor_izquierdo, motor_derecho);
            girar_a_la_izquierda(motor_izquierdo, motor_derecho);
        }

        else if (infL == 0 && infR == 1 && dist > 1500) // si el sensor izquierdo se detecta fuera de la pista, se gira a la derecha
        {
            full_stop(motor_izquierdo, motor_derecho);
            girar_a_la_derecha(motor_izquierdo, motor_derecho);
        }
        else if (infR == 0 && infL == 0) // si el los dos sensores laterales se detectan fuera de la pista, se va hacia atras
        {
            full_stop(motor_izquierdo, motor_derecho);
            ir_hacia_atras(motor_izquierdo, motor_derecho);
        }

        else if (infA == 1 && infR == 1 && infL == 1 && dist > 1500)
        {
            full_stop(motor_izquierdo, motor_derecho);
            // el robot esta sobre la pista,gira en circulos
            girar_a_la_derecha(motor_izquierdo, motor_derecho);
        }
        else
        {
            full_stop(motor_izquierdo, motor_derecho);
            ir_hacia_adelante(motor_izquierdo, motor_derecho);
        }
    }
}
/*
 *   @brief modo indicado para la disciplina "Modo velocidad y control"
 */
void modo_velocidad_y_control()
{

    modo_init(led_verde);
    /*
    primero, el robot va a buscar ir hacia la izquierda, y va tener como referencia
    la parte negra del costado; el reglamento lo permite
    */
    while (1)
    {

        bool infL = infrarojo_get(infrarojo_izquierdo);
        bool infR = infrarojo_get(infrarojo_derecho);
        // bool infA = infrarojo_get(infrarojo_delantero);

        if (infR == 0 && infL == 0)
        {

            full_stop(motor_izquierdo, motor_derecho);
            doblar_a_la_derecha(motor_izquierdo, motor_derecho);
        }
        else if (infR == 0 && infL == 1)
        {

            full_stop(motor_izquierdo, motor_derecho);
            ir_hacia_adelante(motor_izquierdo, motor_derecho);
        }
        else if (infR == 1 && infL == 0)
        {
            full_stop(motor_izquierdo, motor_derecho);
            doblar_a_la_derecha(motor_izquierdo, motor_derecho);
        }
        else if (infR == 1 && infL == 1)
        {
            full_stop(motor_izquierdo, motor_derecho);
        }
    }
}

/*if (infL == 1 && infR == 1) // si todos los sensores detectan blanco, se busca la parte negra girando a la izquierda
{
    full_stop(motor_izquierdo,motor_derecho);
    doblar_a_la_izquierda(motor_izquierdo, motor_derecho);
}


else if (infL == 0 && infR == 1) // si solo el sensor izquierdo detecta la parte negra, se avanza
{
    full_stop(motor_izquierdo,motor_derecho);
    ir_hacia_adelante(motor_izquierdo,motor_derecho);
}

else if ( infL == 1 && infA == 0 && infR == 0 ) // si el sensor delantero y derecho detectan negro, se gira a la izquierda
{
    full_stop(motor_izquierdo,motor_derecho);
    girar_a_la_izquierda(motor_izquierdo, motor_derecho);

}

else    // si detecta todo blanco, se dobla a la izquierda
{
    full_stop(motor_izquierdo,motor_derecho);
    doblar_a_la_izquierda(motor_izquierdo, motor_derecho);
}
* jua _ apaga el motor

}
}


/*
*   @brief modo indicado para la disciplina "Modo Sumo"
*/
void modo_sumo()
{
    modo_init(25);
    while (1)
    {
        char uart_input = uart_getc(uart_id);
        gpio_put(25, 1);
        switch (uart_input)
        {
        case 'F':
            ir_hacia_adelante(motor_izquierdo, motor_derecho);
            break;

        case 'B':

            ir_hacia_atras(motor_izquierdo, motor_derecho);
            break;

        case 'L':

            girar_a_la_izquierda(motor_izquierdo, motor_derecho);
            break;
        case 'R':
            girar_a_la_derecha(motor_izquierdo, motor_derecho);
            break;
        case 'I':

            doblar_a_la_derecha(motor_izquierdo, motor_derecho);
            break;

        case 'G':

            doblar_a_la_izquierda(motor_izquierdo, motor_derecho);
            break;

        case 'J':

            atras_a_la_derecha(motor_izquierdo, motor_derecho);
            break;

        case 'H':

            atras_a_la_izquierda(motor_izquierdo, motor_derecho);
            break;

        case '*':

            return;
            break;

        default:
            full_stop(motor_izquierdo, motor_derecho);
        }
    }
}
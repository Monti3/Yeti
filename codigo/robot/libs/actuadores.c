#include "actuadores.h"


/*
 *  @brief Inicializo el pin con el que voy a controlar el actuador
 *  @param pin_led: numero de pin que corresponde al actuador
 */
void actuador_init(uint8_t pin_actuador)
{
    gpio_init(pin_actuador);
    gpio_set_dir(pin_actuador, true);
}

/*
 *  @brief Inicializo el pin con el que voy a controlar el buzzer   
 *  @param pin_buzzer: numero de pin que corresponde al buzzer 
 */


/*
 *  @brief Inicializo el adc del pin que lee al pote
 *  @param pin_switch: numero de pin que corresponde al pin de adc
 */
void potenciometro_init(uint8_t pin_potenciometro){
    adc_init();
    adc_gpio_init(pin_potenciometro);
    adc_select_input(2);

    
}

/*
*   @brief Leo el canal de adc activo
*
*/
uint16_t leer_potenciometro(){
    return adc_read();
}


 /*
 *  @brief acciono el actuador mandando un 0:como ánodo común 
 *  @param pin_led: numero de pin que corresponde al actuador
 */
void actuar(uint8_t actuador)
{
    gpio_put(actuador,0);           // ánodo común
}

 /*
 *  @brief apago el actuador mandando un 1:como ánodo común 
 *  @param actuador: numero de pin que corresponde al actuador
 */
void no_actuar(uint8_t actuador)
{
    gpio_put(actuador,1);           // ánodo común
}


/*
 *  @brief acciono y apago el actuador 4 veces
 *  @param delay: tiempo total del ciclo
 */
void parpadear(uint8_t pin,uint delay)
{
    actuar(pin);
    sleep_ms(delay/4);
    no_actuar(pin);
    sleep_ms(delay/4);
    actuar(pin);
    sleep_ms(delay/4);
    no_actuar(pin);
    sleep_ms(delay/4);
}
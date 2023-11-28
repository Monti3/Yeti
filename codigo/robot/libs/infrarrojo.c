#include "infrarrojo.h"


/*
 *  @brief  Inicializa un sensor infrarojo en el pin indicado
 *  
 *  @param  pin: numero de pin conectado al infrarojo
 */

void infrarojo_init(uint8_t pin){
    gpio_init(pin);
    gpio_set_dir(pin, false);
}



/*
 *  @brief  Obtiene el valor que entregue el infrarojo
 *  
 *  @param  pin: numero de pin conectado al infrarojo
 * 
 *  @return true si la luz volvio, false si no
 */

bool infrarojo_get(uint8_t pin){
    return !gpio_get(pin);
}
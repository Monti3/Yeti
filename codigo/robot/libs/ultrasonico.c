#include "ultrasonico.h"

/*
 *  @brief  Inicializa los pines del ultrasonico
 *
 *  @param  trigger: numero de GP para usar de TRIGGER
 *  @param  echo: numero de GP para usar de ECHO
 */
void ultrasonico_init(ultrasonico_t ultrasonico) {
    /* Habilito el pin de Trigger */
    gpio_init(ultrasonico.trigger);  
    /* Configuro el Trigger como salida */
    gpio_set_dir(ultrasonico.trigger, true);
    /* Pongo un 0 en el pin de Trigger */
    gpio_put(ultrasonico.trigger, false);
    /* Habilito el pin de Echo */
    gpio_init(ultrasonico.echo);
    /* Configuro el Echo como entrada */
    gpio_set_dir(ultrasonico.echo, false);
}

/*
 *  @brief  Obtiene la distancia en cm
 *  
 *  @param  trigger: numero de GP para usar de TRIGGER
 *  @param  echo: numero de GP para usar de ECHO
 * 
 *  @return distancia en cm
 */
float ultrasonico_get_distance_cm(ultrasonico_t ultrasonico) {
    /* Escribo un 1 en el Trigger */
    gpio_put(ultrasonico.trigger, true);
    /* Espero 10 us con el pulso encendido */
    sleep_us(10);
    /* Escribo un 0 en el Trigger */
    gpio_put(ultrasonico.trigger, false);
    /* Espero a que el pulso llegue al Echo */
    while(!gpio_get(ultrasonico.echo));
    /* Mido el tiempo de cuando llega el pulso */
    absolute_time_t from = get_absolute_time();
    /* Espero a que el pulso del Echo baje a cero */
    while(gpio_get(ultrasonico.echo));
    /* Mido el tiempo cuando termina el pulso */
    absolute_time_t to = get_absolute_time();
    /* Saco la diferencia de tiempo (el ancho del pulso) en us */
    int64_t pulse_width = absolute_time_diff_us(from, to);
    /* Calculo la distancia y la devuelvo */
    return pulse_width / 59.0;
}
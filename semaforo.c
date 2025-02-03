#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

#define VERMELHO 11
#define AMARELO 12
#define VERDE 13

int estado = 0; // Estado do semáforo

// Função para configurar os pinos dos LEDs
void configurar_pinos() {
    gpio_init(VERMELHO);
    gpio_set_dir(VERMELHO, GPIO_OUT);
    gpio_init(AMARELO);
    gpio_set_dir(AMARELO, GPIO_OUT);
    gpio_init(VERDE);
    gpio_set_dir(VERDE, GPIO_OUT);
}

// Função chamada pelo timer a cada 3 segundos
bool mudar_semaforo(repeating_timer_t *t) {
    // Apaga todos os LEDs
    gpio_put(VERMELHO, 0);
    gpio_put(AMARELO, 0);
    gpio_put(VERDE, 0);

    // Acende o LED correspondente
    if (estado == 0) {
        gpio_put(VERMELHO, 1);
        estado = 1;
    } else if (estado == 1) {
        gpio_put(AMARELO, 1);
        estado = 2;
    } else {
        gpio_put(VERDE, 1);
        estado = 0;
    }
    return true; // Mantém o timer funcionando
}

int main() {
    stdio_init_all();
    configurar_pinos(); // Configura os pinos dos LEDs

    repeating_timer_t timer;
    add_repeating_timer_ms(3000, mudar_semaforo, NULL, &timer);

    while (1) {
        tight_loop_contents(); // Mantém o programa rodando
    }

    return 0;
}

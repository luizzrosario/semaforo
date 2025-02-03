#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

#define VERMELHO 11  // GPIO do LED vermelho
#define AMARELO 12   // GPIO do LED amarelo
#define VERDE 13     // GPIO do LED verde

int estado = 0; // Estado inicial do semáforo (vermelho)

// Função para configurar os pinos dos LEDs
void configurar_pinos() {
    gpio_init(VERMELHO);
    gpio_set_dir(VERMELHO, GPIO_OUT);
    gpio_init(AMARELO);
    gpio_set_dir(AMARELO, GPIO_OUT);
    gpio_init(VERDE);
    gpio_set_dir(VERDE, GPIO_OUT);

    // Começa com o LED vermelho ligado
    gpio_put(VERMELHO, 1);
}

// Callback do temporizador (muda o estado do semáforo a cada 3 segundos)
bool mudar_semaforo(repeating_timer_t *t) {
    // Apaga todos os LEDs antes de mudar o estado
    gpio_put(VERMELHO, 0);
    gpio_put(AMARELO, 0);
    gpio_put(VERDE, 0);

    // Alterna entre os estados do semáforo
    if (estado == 0) {
        gpio_put(AMARELO, 1); // Muda para amarelo
        estado = 1;
    } else if (estado == 1) {
        gpio_put(VERDE, 1); // Muda para verde
        estado = 2;
    } else {
        gpio_put(VERMELHO, 1); // Volta para vermelho
        estado = 0;
    }

    return true; // Mantém o temporizador ativo
}

int main() {
    stdio_init_all();
    configurar_pinos(); // Configura os LEDs

    repeating_timer_t timer_semaforo;
    add_repeating_timer_ms(3000, mudar_semaforo, NULL, &timer_semaforo);

    // Loop principal que imprime mensagens a cada 1 segundo
    while (1) {
        // Exibe a cor atual do semáforo no terminal
        if (estado == 0) {
            printf("Semáforo: VERMELHO\n");
        } else if (estado == 1) {
            printf("Semáforo: AMARELO\n");
        } else {
            printf("Semáforo: VERDE\n");
        }

        sleep_ms(1000); // Espera 1 segundo antes de imprimir novamente
    }

    return 0;
}

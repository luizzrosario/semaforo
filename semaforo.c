#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/timer.h"

// Definição dos pinos dos LEDs do semáforo
#define VERMELHO 11  // GPIO do LED vermelho
#define AMARELO 12   // GPIO do LED amarelo
#define VERDE 13     // GPIO do LED verde

int estado = 0; // Estado inicial do semáforo (vermelho)

// Função para configurar os pinos dos LEDs
void configurar_pinos() {
    // Inicializa os pinos dos LEDs e define como saída
    gpio_init(VERMELHO);
    gpio_set_dir(VERMELHO, GPIO_OUT);
    gpio_init(AMARELO);
    gpio_set_dir(AMARELO, GPIO_OUT);
    gpio_init(VERDE);
    gpio_set_dir(VERDE, GPIO_OUT);

    // Começa com o LED vermelho ligado, indicando o estado inicial do semáforo
    gpio_put(VERMELHO, 1);
}

// Função chamada pelo temporizador para mudar o estado do semáforo a cada 3 segundos
bool mudar_semaforo(repeating_timer_t *t) {
    // Desliga todos os LEDs antes de mudar para o próximo estado
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

    return true; // Retorna true para manter o temporizador ativo
}

int main() {
    // Inicializa a saída padrão para permitir a exibição de mensagens no terminal
    stdio_init_all();
    configurar_pinos(); // Configura os LEDs do semáforo

    // Configura um temporizador que chama a função mudar_semaforo() a cada 3 segundos
    repeating_timer_t timer_semaforo;
    add_repeating_timer_ms(3000, mudar_semaforo, NULL, &timer_semaforo);

    // Loop principal que imprime a cor atual do semáforo a cada 1 segundo
    while (1) {
        if (estado == 0) {
            printf("Semáforo: VERMELHO\n");
        } else if (estado == 1) {
            printf("Semáforo: AMARELO\n");
        } else {
            printf("Semáforo: VERDE\n");
        }

        sleep_ms(1000); // Aguarda 1 segundo antes da próxima mensagem
    }

    return 0;
}

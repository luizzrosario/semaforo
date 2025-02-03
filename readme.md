# Semáforo com Raspberry Pi Pico

Este projeto implementa um sistema de semáforo utilizando o Raspberry Pi Pico. O programa controla três LEDs representando as cores do semáforo (vermelho, amarelo e verde), alternando entre eles a cada 3 segundos. Além disso, exibe no terminal a cor atual do semáforo a cada segundo. 
Vale ressaltar que os pinos seguem as intruções do enunciado, e não necessáriamente da placa BitDogLab. Sendo necessário ficar atento ao monitor serial para identificar o estado atual.
Em acréscimo, a primeira informação de estado é dada a partir do 1º segundo, ou seja, haverá 2 prints do vermelho inicialmente. Todavia, sua duração está correta.

## Requisitos
- Placa **Raspberry Pi Pico**
- LEDs e resistores conectados aos pinos:
  - **Vermelho**: GPIO 11 (Verde na placa)
  - **Amarelo**: GPIO 12 (Azul)
  - **Verde**: GPIO 13 (Vermelho)
- Cabo USB para alimentação e comunicação serial
- Ambiente de desenvolvimento configurado com **SDK do Raspberry Pi Pico**

## Como usar

1. **Compilar o código**:
   - Certifique-se de ter o SDK do Raspberry Pi Pico configurado.
   - Compile o código utilizando CMake e GCC ARM.

2. **Transferir para o Raspberry Pi Pico**:
   - Conecte o Raspberry Pi Pico ao PC enquanto segura o botão **BOOTSEL**.
   - Monte a unidade **RPI-RP2** no computador.
   - Copie o arquivo compilado `.uf2` para a unidade montada ou aperte em Run na interface do VS Code.

## Funcionamento
- O LED **vermelho** acende primeiro, indicando parada.
- Após **3 segundos**, muda para **amarelo**.
- Depois de mais **3 segundos**, muda para **verde**.
- O ciclo continua indefinidamente.
- A cada **1 segundo**, a cor atual é impressa na porta serial.

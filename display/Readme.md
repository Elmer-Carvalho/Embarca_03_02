#  MANIPULAÇÃO DO DISPLAY SSD1306.

Este projeto implementa a manipulação do display SSD1306 para exibição de mensagens através de comunicação serial e interrupções por acionamento de botões, além do controle de uma matriz de LEDS e de um LED RGB por meio do **Raspberry Pi Pico W**. O código é desenvolvido em **C** para sistemas embarcados e foi implementado na placa voltada a aprendizagem BitDogLab.

## Estrutura do Projeto

- **display.c**: Arquivo principal do projeto com toda a lógica de instruções do Firmware.
- **ssd1306.c**: Arquivo contendo a lógica de manipulação do display SSD1306.
- **ssd1306.h**: Header com informações do display SSD1306.
- **font.h**: Possui os bitmaps para exibição dos caracteres no display.
- **framesWS2.h**: Possui a estrutura dos frames usados para compor os números na matriz de LEDS WS2812.

## Requisitos

- **Hardware**:
  - Computador pessoal.
  - Raspberry Pi Pico W (RP2040).
  - 2 Botões.
  - 1 LED RGB ou 3 LEDs de cores distintas.
  - 1 display SSD1306.
  - 1 matriz de LEDS WS2812 5x5.
  - Cabo micro-USB para USB-A.
  - Alguns resistores.

- **Software**:
  - Visual Studio Code
  - Pico SDK
  - Compilador ARM GCC
  - Plutty (Caso não consiga realizar a comunicação serial pelo VSCode)

## Vídeo demonstrativo 
[Assista aqui](https://drive.google.com/file/d/1duwJxhAqcNT8xQp2H8f_Ycheo9FF_wG5/view?usp=sharing)




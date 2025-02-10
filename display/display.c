#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <ctype.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"
#include "pio_matrix.pio.h"
#include "framesWS2.h"
#include "font.h"
#include "ssd1306.h"

#define PIN_VERDE 11
#define PIN_AZUL 12
#define PIN_WS2812 7
#define PIN_BUTTON_A 5
#define PIN_BUTTON_B 6
#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define ENDERECO 0x3C


static volatile uint32_t temp_button = 0; // Var para Debouncing 
ssd1306_t ssd; // Inicializa a estrutura do display

// Protótipos das funções
void init_pins();
uint32_t matrix_rgb();
void exibirFrame(const float frame[ALTU][LARG], PIO pio, uint sm);
void button_irq_callback(uint gpio, uint32_t events); // Função de callback da interrupção

int main() {
    // Inicializando STDIO e Pinos
    stdio_init_all();
    init_pins();

    // Configura interrupções para borda de descida (pressionamento do botão)
    gpio_set_irq_enabled_with_callback(PIN_BUTTON_A, GPIO_IRQ_EDGE_FALL, true, &button_irq_callback);
    gpio_set_irq_enabled_with_callback(PIN_BUTTON_B, GPIO_IRQ_EDGE_FALL, true, &button_irq_callback);

    // Configuração do Pio
    PIO pio = pio0;
    bool sys_clock = set_sys_clock_khz(128000, false);
    uint offset = pio_add_program(pio, &pio_matrix_program);
    uint sm = pio_claim_unused_sm(pio, true);
    pio_matrix_program_init(pio, sm, offset, PIN_WS2812);

    // I2C Initialisation. Using it at 400Khz.
    i2c_init(I2C_PORT, 400 * 1000);

    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C); // Set the GPIO pin function to I2C
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C); // Set the GPIO pin function to I2C
    gpio_pull_up(I2C_SDA); // Pull up the data line
    gpio_pull_up(I2C_SCL); // Pull up the clock line
    ssd1306_init(&ssd, WIDTH, HEIGHT, false, ENDERECO, I2C_PORT); // Inicializa o display
    ssd1306_config(&ssd); // Configura o display
    ssd1306_send_data(&ssd); // Envia os dados para o display

    // Limpa o display. O display inicia com todos os pixels apagados.
    ssd1306_fill(&ssd, false);
    ssd1306_send_data(&ssd);


    char input;
    char msg[6] = "CHAR  ";
    while (true) {
        scanf(" %c", &input);
        if (isdigit(input)) {
            uint index = input - '0';
            exibirFrame(frames[index], pio, sm); // Exibe o Número na Matriz de LEDS
        } else {
            exibirFrame(frames[10], pio, sm); // Limpa a Matriz de LEDS
        }

        msg[5] = input;

        // Atualiza o conteúdo do display com animações
        ssd1306_fill(&ssd, false); // Limpa o display
        ssd1306_draw_string(&ssd, msg, 8, 30); // Desenha uma string
        ssd1306_send_data(&ssd); // Atualiza o display
    }
}

// Inicialização dos pinos e configuração da interrupção
void init_pins() {
    // Inicializando Botão A
    gpio_init(PIN_BUTTON_A);
    gpio_set_dir(PIN_BUTTON_A, GPIO_IN);
    gpio_pull_up(PIN_BUTTON_A);
    gpio_put(PIN_BUTTON_A, true);
    
    // Inicializando Botão B
    gpio_init(PIN_BUTTON_B);
    gpio_set_dir(PIN_BUTTON_B, GPIO_IN);
    gpio_pull_up(PIN_BUTTON_B);
    gpio_put(PIN_BUTTON_B, true);

    // Inicializando LEDS
    gpio_init(PIN_VERDE);
    gpio_set_dir(PIN_VERDE, GPIO_OUT);

    gpio_init(PIN_AZUL);
    gpio_set_dir(PIN_AZUL, GPIO_OUT);

    gpio_init(PIN_WS2812);
    gpio_set_dir(PIN_WS2812, GPIO_OUT);
}

// Callback de interrupção dos botões
void button_irq_callback(uint gpio, uint32_t events) {
    if (events & GPIO_IRQ_EDGE_FALL) {

        // Debouncing
        uint32_t current_time = to_us_since_boot(get_absolute_time());
        if (current_time - temp_button> 250000) {
            temp_button = current_time;

            ssd1306_fill(&ssd, false);
            ssd1306_rect(&ssd, 3, 3, 122, 58, false, true); // Desenha um retângulo

            if (gpio == PIN_BUTTON_A) {
                gpio_put(PIN_VERDE, !gpio_get(PIN_VERDE));
                char *msg = (gpio_get(PIN_VERDE)) ? "VERDE ON" : "VERDE OFF";
                printf("%s\n", msg);
                ssd1306_draw_string(&ssd, msg, 20, 30); // Desenha uma string
            } 
            else if (gpio == PIN_BUTTON_B) {
                gpio_put(PIN_AZUL, !gpio_get(PIN_AZUL));
                char *msg = (gpio_get(PIN_AZUL)) ? "AZUL ON" : "AZUL OFF";
                printf("%s\n", msg);  
                ssd1306_draw_string(&ssd, msg, 20, 30); // Desenha uma string          
            }

            ssd1306_send_data(&ssd);
        }
    }
}

// Função para definir a cor do LED RGB
uint32_t matrix_rgb() {
    unsigned char R = 0.8 * 255;
    unsigned char G = 0.2 * 255;
    unsigned char B = 0.1 * 255;
    return (G << 24) | (R << 16) | (B << 8);
}

// Exibe um frame na matriz
void exibirFrame(const float frame[ALTU][LARG], PIO pio, uint sm) {
    uint32_t cor_led = matrix_rgb();

    for (uint linha = 0; linha < ALTU; linha++) {
        for (uint coluna = 0; coluna < LARG; coluna++) {
            uint32_t valor_cor = (linha > 0 && linha % 2 != 0) ? cor_led * frame[ALTU - linha - 1][coluna] : cor_led * frame[ALTU - linha - 1][LARG - coluna - 1];
            pio_sm_put_blocking(pio, sm, valor_cor);
        }
    }
}

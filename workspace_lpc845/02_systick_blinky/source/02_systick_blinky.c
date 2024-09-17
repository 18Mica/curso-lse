#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "fsl_debug_console.h"


// Pin para el LED azul
#define LED_BLUE	1
#define LED_D1	29
/**
 * @brief Programa principal
 */
int main(void) {

	// Inicializacion
	BOARD_BootClockFRO24M();

    // Estructura de configuracion de entrada
    gpio_pin_config_t out_config = { kGPIO_DigitalOutput, 1 };

    // Habilito el puerto 1
    GPIO_PortInit(GPIO, 1);
    // Configuro LED como salida
    GPIO_PinInit(GPIO, 0, 29, &out_config);

    // Configuro SysTick para 1 ms
    SysTick_Config(SystemCoreClock * 0.5);

    while(1);
    return 0 ;
}

/**
 * @brief Handler para interrupcion de SysTick
 */
void SysTick_Handler(void) {
	// Variable para contar interrupciones
	static uint16_t i = 0;

	// Incremento contador
	i++;
	// Verifico si el SysTick se disparo 500 veces (medio segundo)
	!GPIO_PinRead(GPIO, 0, 29);
	if(i == 3) {
		// Reinicio el contador
		i = 0;
		// Conmuto los LEDS
		GPIO_PinWrite(GPIO, 0, 29);
	}
}

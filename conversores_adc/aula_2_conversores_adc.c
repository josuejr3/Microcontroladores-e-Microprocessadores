#include "main.h"
#include "Utility.h"
#include <stdio.h>


void setup(){

	Utility_Init();
	USART1_Init();

	// Habilita o clock do GPIOA
	GPIO_Clock_Enable(GPIOA);
	// Pino PA0 e PA1 como entrada analógica
	GPIO_Pin_Mode(GPIOA, PIN_0, ANALOG);
	GPIO_Pin_Mode(GPIOA, PIN_1, ANALOG);

	// Configuração do ADC

	// Liga o Clock da Interface digital do ADC1
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	// Seleciona o PRESCALER de 4 - 21 MHz (ADCPRE)
	ADC->CCR |= 0b01 << 16;
	// Seleciona dois canais
	ADC1->SQR1 = 1 << 20;
	// Seleciona a conversão para os canais IN0 e IN1 (PA0 e PA1)
	ADC1->SQR3 = (1 << 5) | (0 << 0);
	// Habilita o modo Scan (lista com todos os canais)
	ADC1->CR1 |= ADC_CR1_SCAN;
	// Habilita o sinal EOC ao fim de cada conversão
	ADC1->CR2 |= ADC_CR2_EOCS;
	// Liga o conversor AD
	ADC1->CR2 |= ADC_CR2_ADON;



}



int main(){

	// Setup	
	// Usando a biblioteca Utility
	// ADC_Init(ADC1, MULTI_CHANNEL, ADC_RES_12BITS);
	// uint8_t canais[2] = {ADC_IN0, ADC_IN1};
	// ADC_MultiChannel(ADC1, 2, canais);

	setup();

	while(1){

		ADC1->CR2 |= ADC_CR2_SWSTART;    // Inicia a conversão
		while(!(ADC1->SR & ADC_SR_EOC)); // Aguarda o fim da primeira conversão
		uint16_t canal0 = ADC1->DR;      // Faz a leitura do valor convertido
		while(!(ADC1->SR & ADC_SR_EOC)); // Aguarda o fim da segunda conversão
		uint16_t canal1 = ADC1->DR;      // Faz a leitura do valor convertido

		printf("Valor PA0 = %d\nValor PA1 = %d\n\n", canal0, canal1);
		Delay_ms(500);


		// Usando a biblioteca utility
		// uint16_t = leitura[2];

		// O ADC que vai ser usado, a quantidade de canais e onde vão ser armazenados
		// os valores lidos
		// ADC_GetMultiConversions(ADC1, 2, leitura);

		// printf("Valor PA0 = %d\nValor PA1 = %d\n", leitura[0], leitura[1]);
		// Delay_ms(500);

	}

	return 0;
}

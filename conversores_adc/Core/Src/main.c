#include "main.h"
#include "Utility.h"
#include <stdio.h>


void setup(){

	Utility_Init();
	USART1_Init();

	// Habilita o clock do GPIOA
	GPIO_Clock_Enable(GPIOA);
	// Pino PA0 como entrada analógica
	GPIO_Pin_Mode(GPIOA, PIN_0, ANALOG);

	// Configuração do ADC

	// Liga o Clock da Interface digital do ADC1
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
	// Seleciona o PRESCALER de 4 - 21 MHz (ADCPRE)
	ADC->CCR |= 0b01 << 16;
	// Seleciona a conversão de um único canal
	ADC1->SQR1 &= (0xF << 20);
	// Seleciona o canal que vai ser convertido
	ADC1->SQR3 &= ~(0x1F);
	// Seleciona o tempo de amostragem
	ADC1->SMPR2 |= 0b111;
	// Liga o conversor
	ADC1->CR2 |= ADC_CR2_ADON;

	// Usando a biblioteca Utility
	// Informa qual ADC vai ser usado,  modo de operação e a resolução
	// ADC_Init(ADC1, SINGLE_CHANNEL, ADC_RES_12BITS);
	// A função de canal simples recebe o ADC que vai ser usado e o canal
	// ADC_Single_Channel(ADC1, ADC_IN0);



}



int main(){

	setup();

	while(1){

		// Inicia a conversão
		ADC1->CR2 |= ADC_CR2_SWSTART;
		// Aguarda o fim da conversão
		while (!(ADC1->SR & ADC_SR_EOC));

		// Faz a leitura do valor convertido
		uint16_t leitura = ADC1->DR;


		// Usando a biblioteca utility para obter a conversão
		// Aqui o valor já é convertido e passado para o canal definido
		// na função de setup
		// uint16_t leitura = ADC_GetSingleConversion(ADC1);

		printf("Valor convertido %d\n", leitura);
		Delay_ms(1000);

	}

	return 0;
}

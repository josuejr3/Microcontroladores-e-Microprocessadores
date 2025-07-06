//#include "main.h"
//#include "Utility.h"
//#include <stdio.h>
//
//
//void setup(){
//
//	// Inicialização da utility
//	Utility_Init();
//
//	// Habilita os prints
//	USART1_Init();
//
//	// Habilitando clock do GPIOA
//	GPIO_Clock_Enable(GPIOA);
//	// Configurando PA0 como entrada analógica
//	GPIO_Pin_Mode(GPIOA, PIN_0, ANALOG);
//
//	// Ligando clock do periférico
//	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
//
//	// Configurando o ADC
//	ADC->CCR |= 0b01 << 16;              // prescaler /4 (21 MHz)
//	ADC1->SQR1 &= ~(0xF << 20);          // conversão de apenas um canal
//	ADC1->SQR3 &= ~(0X1F);               // seleção do canal a ser convertido IN_0
//	ADC1->SMPR2 |= 0b111;                // seleção do tempo de amostragem
//	ADC1->CR2 |= ADC_CR2_ADON;           // liga o conversor
//
//	// Utilizando a utility
//    // ADC_Init(ADC1, SINGLE_CHANNEL, DAC_RES_12BITS);
//    // ADC_SingleChannel(ADC1, ADC_IN0);
//
//
//}
//
//int main(){
//
//	setup();
//
//	while(1){
//
//		// Usando a utility
//		// uint16_t leitura = ADC_GetSingleConversion(ADC1);
//
//
//		ADC1->CR2 |= ADC_CR2_SWSTART; // Inicia a conversão
//		while(!(ADC1->SR & ADC_SR_EOC)); // Aguarda o fim da conversão
//
//		uint16_t leitura = ADC1->DR;
//
//		printf("Valor convertido - %d\n", leitura);
//		Delay_ms(1000);
//
//	}
//	return 0;
//}

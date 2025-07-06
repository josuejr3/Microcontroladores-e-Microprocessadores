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
//	GPIO_Pin_Mode(GPIOA, PIN_1, ANALOG);
//
//	// Ligando clock do periférico
//	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
//
//	// Configurando o ADC
//	ADC->CCR |= 0b01 << 16;              // prescaler /4 (21 MHz)
//	ADC1->SQR1 = 1 << 20;                // conversão de dois canais (campo lenght do sqr1)
//	// Como eu habilitei dois canais e eu estou com potenciometros em pa0 e pa1 então
//	// eu devo escrever os números dos canais que eu desejo converter nos bits SQ1 e SQ2 do
//	// meu registrador ADC_SQR3
//	// SQ1 - IN0
//	// SQ2 - IN1
//	ADC1->SQR3 |= (1 << 5) | (0 << 0);   // Colocando os números dos canais
//
//	// Setando o bit de scan (estamos usando mais de um canal)
//	ADC1->CR1 |= ADC_CR1_SCAN;
//	// Se o bit eocs for 0 o bit eoc indica o fim da conversão apenas no fim da sequencia completa
//	// ou seja, após converter os dois canais. Se ele for um, ele vai ser setado ao final de cada
//	// conversão
//	ADC1->CR2 |= ADC_CR2_EOCS;
//	// Liga o conversor ADC1
//	ADC1->CR2 |= ADC_CR2_ADON;
//
////	// Usando a biblioteca utility
////	ADC_Init(ADC1, MULTICHANNEL, ADC_RES_12BITS);
////
////	// Array de dois valores que vão ser minhas entradas
////	uint8_t canais[2] = {ADC_IN0, ADC_IN1};
////
////	// Indico que quero fazer duas conversões no ADC1
////	ADC_MultiChannel(ADC1, 2, canais);
//
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
//		ADC1->CR2 |= ADC_CR2_SWSTART;      // Inicia a conversão
//		while (!(ADC1->SR & ADC_SR_EOC));  // Aguarde o fim da primeira conversão
//		uint16_t canal0 = ADC1->DR;        // Faz a leitura do valor convertido
//		while (!(ADC1->SR & ADC_SR_EOC));  // Aguarda o fim da segunda conversão
//		uint16_t canal1 = ADC1->DR;        // Faz a leitura do valor convertido
//
//		// Usando a biblioteca utility
//		uint16_t leitura[2];
//		ADC_GetMultiConversion(ADC1, 2, leitura);
//
//		printf("Valor PA0 - %d\nValor PA1 -%d\n", canal0, canal1);
//		Delay_ms(500);
//
//	}
//	return 0;
//}

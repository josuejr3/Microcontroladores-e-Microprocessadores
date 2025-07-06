//#include "main.h"
//#include "Utility.h"
//#include <stdio.h>
//
//
//void setup(){
//
//	// Inicialização da utility
//	Utility_Init();
//	// Habilita os prints
//	USART1_Init();
//	// Liga o cloc da interface digital do ADC1
//	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
//	// Ajusta o PreScaler /4
//	ADC->CCR |= 0b01 << 16;
//	// Conversão de apenas um canal
//	ADC1->SQR1 &= ~(0xF << 20);
//	// Seleção do canal a ser convertido (IN_16)
//	ADC1->SQR3 |= 16;
//	// Tempo de amostragem igual a 480 ciclos de ADCCLK
//	ADC1->SMPR1 |= (7 << 18);
//	// Liga o sensor de temperatura
//	ADC->CCR |= ADC_CCR_TSVREFE;
//	// Liga o conversor AD
//	ADC1->CR2 |= ADC_CR2_ADON;
//
//
//	// Cria um ponteiro para uma das posições da memória de TS_CAL1
//	uint32_t *p = (uint32_t *) 0x1FFF7A2C;
//	// Armazena e LÊ o conteúdo de parte do TS_CAL1 em Word
//	uint32_t Word = *p;
//	// Lê o valor de TS_CAL1
//	uint16_t TSCAL1 = (Word & 0x0000FFFF);
//	// Lê o valor de TS_CAL_2
//	uint16_t TSCAL2 = (Word & 0xFFFF0000);
//
//
//	// Configurando o ADC
//	ADC_Init(ADC1, SINGLE_CHANNEL, ADC_RES_12BITS);
//	ADC_SingleChannel(ADC1, ADC_IN0);
//
//	ADC1->CR2 |= 0b01 << 20;
//	ADC1->CR2 |= 0b1111 << 24;
//
//	GPIO_Clock_Enable(GPIOB);
//	GPIO_Pin_Mode(GPIOB, PIN_11, INPUT);
//	GPIO_Resistor_Enable(GPIOB, PIN_11, PULL_DOWN);
//
//	// Habilita o clock syscfg
//	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
//	// Seleciona PB11 como gatilho de EXTI11
//	SYSCFG->EXTICR[2] |= 0b0001 << 12;
//	// Seleciona a orda de subida
//	EXTI->RTSR |= 1 << 11;
//	// Habilita o evento EXTI3 no controlador EXTI
//	EXTI->EMR  |= 1 << 11;
//
//
////	// USANDO WATCHDOG
////	ADC_Init(ADC1, SINGLE_CHANNEL, ADC_RES_12BITS);
////	ADC_SingleChannel(ADC1, ADC_IN0);
////
////	// Limiar inferir
////	ADC1->LTR = 1000;
////	// Limiar superior
////	ADC1->HTR = 3000;
////	// Habilita o watchdog em um canal simples
////	ADC1->CR1 |= ADC_CR1_AWDSGL;
////	// Seleção do canal monitorado
////	ADC1->CR1 &= ~ADC_CR1_AWDCH;
////	// Habilita o watchdog
////	ADC1->CR1 |= ADC_CR1_AWDEN;
//
////	// Habilita interrupção do watchdog
////	ADC1->CR1 |= ADC_CR1_AWDIE;
////	// Habilita interrupção no NVIC
////	NVIC_EnableIRQ(ADC_IRQn);
//
//}
//
////void ADC_IRQHandler(){
////	printf("SAIDA DA REGIAO MONITORADA\n");
////	ADC1->SR &= ~ADC_SR_AWD;
////}
//
//
//int main(){
//
//	setup();
//
//	while(1){
//		// Inicia a conversão
//		ADC1->CR2 |= ADC_CR2_SWSTART;
//		// Espera a conversão finalizar
//		while(!(ADC1->SR & ADC_SR_EOC));
//		// Calcula a temperatura
//		float temperatura = ((80*(float)(ADC1->DR - TS_CAL1))/(TS_CAL2-TS_CAL1)) + 30;
//		// printa o valor
//		printf("Temperatura = %.2f\n", temperatura);
//
//
//		// Conversão com eventos
////		if (ADC1->SR & ADC_SR_EOC)
////		printf("Leitura = %d\n", (int)ADC1->DR);
////
////
////		// USANDO WATCHDOG
////		ADC1->CR2 |= ADC_CR2_SWSTART;
////		while(!(ADC1->SR & ADC_SR_EOC));
////		printf("Leitura - %d\n", (int)ADC1->DR);
////
////		if (ADC1->SR & ADC_SR_AWD)
////			printf("SAIDA DA REGIAO MONITORADA\n");
////
////		ADC1->SR &= ~ADC_SR_AWD;
////		Delay_ms(500);
//
//	}
//	return 0;
//}

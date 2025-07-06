//#include "main.h"
//#include "Utility.h"
//#include <stdio.h>
//
//
//
//int main(){
//
//	Utility_Init();
//	USART1_Init();
//
//
//	GPIO_Clock_Enable(GPIOA);
//	GPIO_Pin_Mode(GPIOA, PIN_2, ALTERNATE);
//	GPIO_Alternate_Function(GPIOA, PIN_2, AF2);
//
////	// Habilita o clock do Timer5
////	RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
////	// Define como crescente
////	TIM5->CR1 &= ~TIM_CR1_DIR;
////	// Auto reload = 99
////	TIM5->ARR = 99;
////	// Prescaler para termos pulsos a cada 5us (fpwm = 2kHz)
////	TIM5->PSC = 419;
////	// Seleciona o PWM modo 1
////	TIM5->CCMR2 |= 0b110 << 4;
////	// Habilita o pré-carregamento do registrador CCR3
////	TIM5->CCMR2 |= TIM_CCMR2_OC3PE;
////	// Hablita a saída
////	TIM5->CCER |= TIM_CCER_CC3E;
////	// Update Event para escrever o valor do prescler
////	TIM5->EGR |= TIM_EGR_UG;
////	// Habilita o Timer
////	TIM5->CR1 |= TIM_CR1_CEN;
////
////	TIM5->CCR3 = 30; // Atualiza o duty cycle
//
//
//	// Configuração para fazer um Timer3 enviar um sinal
//	// A cada 200ms e esse sinal disparar uma conversão ADC1
//	// Habilita o clock do Timer5
//	RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
//	// Define como crescente
//	TIM5->CR1 &= ~TIM_CR1_DIR;
//	// Auto reload = 39999
//	TIM5->ARR = 39999;
//	// Prescaler para termos pulsos a cada 5us
//	TIM5->PSC = 419;
//	// Colocando o timer em modo mestre
//	TIM5->CR2 = 0b010 << 4;
//	// Colocando para o overflow gerar um gatilho
//	TIM5->CR1 |= TIM_CR1_URS;
//	// Update event para escrever o valor do prescaler
//	TIM5->EGR |= TIM_EGR_UG;
//
//
//
//	ADC_Init(ADC1, SINGLE_CHANNEL, ADC_RES_12BITS);
//	ADC_SingleChannel(ADC1, ADC_IN0);
//
//	// Seleciona TIM3_TRGO como fonte de gatiho do ADC1
//	ADC1->CR2 |= 0b1000 << 24;
//	// Habilita disparo externo em rising edge no ADC1
//	ADC1->CR2 |= 0b01 << 28;
//	// Habilita interrupção de EOC
//	ADC1->CR1 |= ADC_CR1_EOCIE;
//	// Habilita a interrupção do ADC no NVIC
//	NVIC_EnableIRQ(ADC_IRQn);
//	// Habilita o timer
//	TIM3->CR1 |= TIM_CR1_CEN;
//
//
//	while(1){
//
//		for (int duty = 0; duty < 100; ++duty){
//			TIM5->CCR3 = duty;  // atualiza o duty cycle
//			Delay_ms(20);
//		}
//
//		for (int duty = 99; duty >= 0; --duty){
//			TIM5->CCR3 = duty;  // atualiza o duty cycle
//			Delay_ms(20);
//		}
//
//	}
//	return 0;
//}
//
//void ADC_IRQHandler(){
//	printf("ADC = %u\n", (unsigned int) ADC1->DR);
//}

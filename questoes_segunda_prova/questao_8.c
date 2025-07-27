//#include "main.h"
//#include "Utility.h"
//#include <stdio.h>
//
//int main()
//{
//	Utility_Init();
//	USART1_Init();
//
//	GPIO_Clock_Enable(GPIOA);
//	GPIO_Pin_Mode(GPIOA, PIN_1, ALTERNATE);
//	GPIO_Alternate_Function(GPIOA, PIN_1, AF2);
//
//	// TIM5
//	RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
//	TIM5->CR1 &= ~TIM_CR1_DIR; //Contagem crescente
//	TIM5->PSC = 8399; // Prescaler de 10 kHz
//	TIM5->ARR = 9999; // Período de 1 segundo (1 Hz)
//	TIM5->CCR2 = 5000; // Duty Cicle 50%
//	TIM5->CCMR1 |= 0b110 << 12; // Seleciona PWM modo 1
//	TIM5->CCMR1 |= TIM_CCMR1_OC2PE; // Habilita o pré carregamento do registrador CCR2
//	TIM5->CCER |= TIM_CCER_CC2E; // Habilita saída
//	TIM5->EGR = TIM_EGR_UG; // update event para escrever o valor do presca
//	TIM5->CR1 |= TIM_CR1_CEN; // Habilita o timer
//
//	while(1)
//	{
//	}
//}

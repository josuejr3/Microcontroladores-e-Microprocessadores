//#include "main.h"
//#include "Utility.h"
//#include <stdio.h>
//
//
//void TIM5_IRQHandler(){
//
//	// Limpando o bit de pendência
//	TIM5->SR &= ~TIM_SR_UIF;
//	printf("INTERROMPEU!\n");
//}
//
//int main(){
//
//	Utility_Init();
//	USART1_Init();
//
//	// Liga o clock do Timer5
////	RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
////	// Define o prescaler para pulsos a cada 500 us
////	TIM5->PSC |= 41999;
////	// Update Event para escrever o valor do prescaler (event generate register - EGR)
////	// UG - Update Generation
////	TIM5->EGR |= TIM_EGR_UG;
////	// Define a contagem como crescente (0 cresce, 1 decresce)
////	TIM5->CR1 &= ~TIM_CR1_DIR;
////	// Habilita a contagem
////	TIM5->CR1 |= TIM_CR1_CEN;
//
//
//	// Exemplo - Gerando Interrupção a cada Overflow
//	// Liga o clock do Timer5
//	RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
//	// Define o prescaler para pulsos a cada 500 us
//	TIM5->PSC |= 41999;
//	// Define a o valor máximo - 2000 (mas tem q diminuir 1)
//	TIM5->ARR = 1999;
//
//	// Update Event para escrever o valor do prescaler (event generate register - EGR)
//	// UG - Update Generation
//	TIM5->EGR |= TIM_EGR_UG;
//	// Define a contagem como crescente (0 cresce, 1 decresce)
//	TIM5->CR1 &= ~TIM_CR1_DIR;
//	// Parte de interrupções (habilita a interrupção por update)
//	TIM5->DIER |= TIM_DIER_UIE;
//	// Habilita a interrupção no NVIC
//	NVIC_EnableIRQ(TIM5_IRQn);
//	// Habilita a contagem
//	TIM5->CR1 |= TIM_CR1_CEN;
//
//	while(1){
//
//		TIM5->CNT = 0;
//		Delay_ms(1000);
//
//		printf("TIM5 = %u\n", (unsigned int)TIM5->CNT);
//
//
//	}
//	return 0;
//}

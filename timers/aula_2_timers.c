#include "main.h"
#include "Utility.h"
#include <stdio.h>


void TIM5_IRQHandler(){
	TIM5->SR &= ~TIM_SR_UIF;
	printf("INTERRUPCAO\n");
}


int main(){

	Utility_Init();
	USART1_Init();

	RCC->APB1ENR |= RCC_APB1ENR_TIM5EN; // Liga o clock do timer 5
	TIM5->PSC = 41999; // prescaler para pulsos a cada 500 us
	TIM5->ARR = 1999;
	TIM5->EGR |= TIM_EGR_UG; // update event para escrever o valor do prescaler
	// o EGR_UG aplica imediatamnte o valor do prescaler ao timer
	TIM5->CR1 &= ~TIM_CR1_DIR; // contagem crescente

	// Habilita a interrupção por update
	TIM5->DIER |= TIM_DIER_UIE;
	NVIC_EnableIRQ(TIM5_IRQn); // habilita a interrupção no NVIC

	// o bit DIR controla se é crescente (0) ou decrecente (1)
	TIM5->CR1 |= TIM_CR1_CEN;   // habilita a contagem

	while(1){


	}
	return 0;
}

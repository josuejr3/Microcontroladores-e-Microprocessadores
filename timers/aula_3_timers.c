#include "main.h"
#include "Utility.h"
#include <stdio.h>

void ADC_IRQHandler(){

	printf("ADC = %u\n", (unsigned int)ADC1->DR);

}


int main(){

	Utility_Init();
	USART1_Init();

	ADC_Init(ADC1, SINGLE_CHANNEL, ADC_RES_12BITS);
	ADC_SingleChannel(ADC1, ADC_IN0);

	// Configurações do Timer 3
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN; // Liga o clock do timer 3
	TIM3->CR1 &= ~TIM_CR1_DIR; // Contagem crescente
	TIM3->PSC = 419; // prescaler para pulsos a cada 5us
	TIM3->ARR = 39999; // estouros a cada 200ms
	TIM3->CR2 = 0b010 << 4; // master mode (TRGO a cada update)
	TIM3->CR1 |= TIM_CR1_URS; // (ativação do bit) overflow gera um gatilho em TRGO;
	TIM3->EGR = TIM_EGR_UG; // update event para escrever o valor do prescaler
	// imediatamente

	// Config do ADC
	ADC1->CR2 |= 0b1000 << 24; // seleciona a saída (TIM3 TRGO) como fonte de gatilho do ADC1
	ADC1->CR2 |= 0b01 << 28; // habilita o disparo em rising edge
	ADC1->CR1 |= ADC_CR1_EOCIE; // habilita a interrupção de EOC
	NVIC_EnableIRQ(ADC_IRQn);   // habilita a interrupção no NVIC

	TIM3->CR1 |= TIM_CR1_CEN;

	while(1){

	}
	return 0;
}

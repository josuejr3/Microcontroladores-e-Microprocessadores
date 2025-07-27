//#include "main.h"
//#include "Utility.h"
//#include <stdio.h>
//#include "amostra.h"
//
//void TIM2_IRQHandler(){
//	if (TIM2->SR & TIM_SR_UIF) {
//		TIM2->SR &= ~TIM_SR_UIF; // limpa flag
//		static int audio_index = 0;
//		if(audio_index < audio_data_len){
//			DAC_SetValue(DAC_CHANNEL1, audio_data[audio_index++], DAC_RES_8BITS);
//		}
//		else {
//			audio_index = 0;
//		}
//	}
//}
//
//
//int main(){
//
//	Utility_Init();
//	DAC_Init(DAC_CHANNEL1);
//
//	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
//	TIM2->PSC = 83;            // prescaler = 1
//	TIM2->ARR = 20;         // para 48kHz (84MHz/1750 ≈ 48kHz)
//	TIM2->DIER |= TIM_DIER_UIE; // habilita interrupção update
//	TIM2->CR1 |= TIM_CR1_CEN;   // inicia timer
//
//	NVIC_EnableIRQ(TIM2_IRQn);
//
//	while(1){
//
//	}
//
//
//}

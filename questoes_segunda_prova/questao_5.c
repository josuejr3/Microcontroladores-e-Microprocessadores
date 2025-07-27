//#include "Utility.h"
//
//	Utility_Init();
//	USART1_Init();
//
//
//	GPIO_Clock_Enable(GPIOA);
//	GPIO_Pin_Mode(GPIOA, PIN_2, ALTERNATE);
//	GPIO_Alternate_Function(GPIOA, PIN_2, AF2);
//
//	GPIO_Pin_Mode(GPIOA, PIN_0, ALTERNATE);
//	GPIO_Alternate_Function(GPIOA, PIN_0, AF2);
//
//
//	RCC->APB1ENR |= RCC_APB1ENR_TIM5EN; // Liga o clock do timer 5
//	TIM5->PSC = 83;
//	TIM5->ARR = 19999;
//	TIM5->CCMR2 |= 0b110 << 4;			// Seleciona o PWM no modo 1 (compare)
//	TIM5->CCMR1 |= 0b110 << 4;
//
//	TIM5->CCMR2 |= TIM_CCMR2_OC3PE;		// Evita glitchs
//	TIM5->CCMR1 |= TIM_CCMR1_OC1PE;		// Evita glitchs
//
//	TIM5->CCER |= TIM_CCER_CC3E;		// Habilita saída do canal 3
//	TIM5->CCER |= TIM_CCER_CC1E;		// Habilita saída do canal 1
//
//	TIM5->EGR |= TIM_EGR_UG;
//	TIM5->CR1 &= ~TIM_CR1_DIR;
//	TIM5->CR1 |= TIM_CR1_CEN;
//
//	// -----------------------------------------------------------------------
//
//
//	GPIO_Pin_Mode(GPIOA, PIN_3, ANALOG);
//	GPIO_Pin_Mode(GPIOA, PIN_4, ANALOG);
//
//	ADC_Init(ADC1, MULTI_CHANNEL, ADC_RES_12BITS);
//	uint8_t canais[2] = {ADC_IN3, ADC_IN4};
//	ADC_MultiChannel(ADC1, 2, canais);
//
//
//	//TIM5->CCR3 = 0; // Não é ideal começar com um valor padrão?
//
//int main(){
//	while(1){
//
//		uint16_t leituras[2];
//
//		ADC_GetMultiConversions(ADC1, 2, leituras);
//
//		uint16_t leiturax = leituras[0];
//		uint16_t leituray = leituras[1];
//
//		TIM5->CCR3 = (leiturax * 2000) / 4095 + 500;
//		TIM5->CCR1 = (leituray * 2000) / 4095 + 500;
//
//	}
//}

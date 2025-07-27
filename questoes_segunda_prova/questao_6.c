//void TIM4_IRQHandler(){
//	if (TIM4->SR & TIM_SR_UIF) {
//		TIM4->SR &= ~TIM_SR_UIF;
//
//		static int pwm_ativo = 0;
//
//		if (pwm_ativo) {
//			TIM5->CCER &= ~TIM_CCER_CC3E;  // Desliga canal de PWM
//		} else {
//			TIM5->CCER |= TIM_CCER_CC3E;   // Liga canal de PWM
//		}
//
//		pwm_ativo = !pwm_ativo;
//	}
//}
//
//void ADC_IRQHandler(){
//
//	if (ADC1->SR & ADC_SR_EOC){
//
//		static unsigned int cont = 0;
//		static float value = 0;
//
//		uint16_t TS_CAL1 = *((uint16_t*) 0x1FFF7A2C);
//		uint16_t TS_CAL2 = *((uint16_t*) 0x1FFF7A2E);
//
//		value += 80.0f * ((float)ADC1->DR - TS_CAL1) / (TS_CAL2 - TS_CAL1) + 30;
//		cont++;
//
//
//		if (cont == 50) {
//		    printf("Temperatura: %.2f\n\n", value/50.0f);
//
//		    if (value/50.0f <= 50){
//		    	printf("Dentro da Faixa de Operacao!\n");
//		    	GPIO_Write_Pin(GPIOA, PIN_6, HIGH);  // Desliga LED de atenção
//				GPIO_Write_Pin(GPIOA, PIN_7, HIGH);  // Desliga LED de superaquecimento
//
//				TIM4->CR1 &= ~TIM_CR1_CEN;        // Para alternância
//				TIM5->CCER &= ~TIM_CCER_CC3E;     // Garante buzzer desligado
//
//		    } else if (value/50.0f > 50 && value/50.0f <= 60){
//		    	printf("Dentro da Faixa de Atencao\n");
//		        GPIO_Write_Pin(GPIOA, PIN_6, LOW);   // Liga LED de atenção
//		        GPIO_Write_Pin(GPIOA, PIN_7, HIGH);  // Desliga superaquecimento
//
//		        TIM4->CR1 &= ~TIM_CR1_CEN;        // Para alternância
//		        TIM5->CCER &= ~TIM_CCER_CC3E;     // Garante buzzer desligado
//
//
//		    } else{
//		    	printf("Dentro da Faixa de Superaquecimento\n");
//		        GPIO_Write_Pin(GPIOA, PIN_6, LOW);  // Desliga LED de atenção
//		        GPIO_Write_Pin(GPIOA, PIN_7, LOW);   // Liga superaquecimento
//		    	TIM5->CCER |= TIM_CCER_CC3E; // Alternativamente eu poderia usar TIM5->CCER &= ~TIM_CCER_CC3E
//		    	TIM4->CR1 |= TIM_CR1_CEN;
//		    	TIM5->CR1 |= TIM_CR1_CEN;
//
//		    }
//
//		    cont = 0;
//		    value = 0;
//		}
//
//	}
//}
//
//int main(){
//
//	Utility_Init();
//	USART1_Init();
//
//	GPIO_Clock_Enable(GPIOA);
//	GPIO_Pin_Mode(GPIOA, PIN_6, OUTPUT);
//	GPIO_Pin_Mode(GPIOA, PIN_1, OUTPUT);
//	GPIO_Pin_Mode(GPIOA, PIN_7, OUTPUT);
//	GPIO_Write_Pin(GPIOA, PIN_6, HIGH);
//	GPIO_Write_Pin(GPIOA, PIN_7, HIGH);
//
//	// Configurações Base para o ADC
//	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
//	ADC->CCR |= 0b01 << 16;
//	ADC1->SQR1 &= ~(0xF << 20);
//	ADC1->SQR3 |= 16;
//	ADC1->SMPR1 |= (7 << 18);
//	ADC->CCR |= ADC_CCR_TSVREFE;
//	ADC1->CR2 |= ADC_CR2_ADON;
//
//
//	// Configurações para o Timer 3
//	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;			// Liga o Clock do Timer 3
//	TIM3->CR1 &= ~TIM_CR1_DIR;					// Define contagem crescente
//	TIM3->PSC = 8399;							// Prescaler para pulsos (incrementos) a cada 5us (TIM3 = 84MHz)
//	TIM3->ARR = 199;							// Estouros a cada 20 ms
//
//	// Configuração do TIMER para Interrupções
//	TIM3->CR2 = 0b010 << 4;						// Configuração no modo MESTRE (TRGO em Updates)
//	TIM3->CR1 |= TIM_CR1_URS;					// Ativação do bit para gatilho TRGO (Overflow);
//	TIM3->EGR = TIM_EGR_UG; 					// Update Event para escrever o valor do prescaler imediatamente
//
//	// Configuração do ADC para Interrupções
//	ADC1->CR2 |= 0b1000 << 24; 					// Seleciona a saída (TIM3 TRGO) como fonte de gatilhos
//	ADC1->CR2 |= 0b01 << 28;					// Habilita o disparo na borda de subida
//	ADC1->CR1 |= ADC_CR1_EOCIE;					// Habilita a interrupção de EOC
//	NVIC_EnableIRQ(ADC_IRQn); 					// Habilita a Interrupção do NVIC
//
//	TIM3->CR1 |= TIM_CR1_CEN;					// Habilita o Timer
//
//
//	// Timer para o Buzzer (Delay)
//	RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
//	TIM5->PSC = 83;
//	TIM5->ARR = 1999;
//	GPIO_Pin_Mode(GPIOA, PIN_2, ALTERNATE);
//	GPIO_Alternate_Function(GPIOA, PIN_2, AF2);
//	TIM5->CCMR2 |= 0b110 << 4;
//	TIM5->CCMR2 |= TIM_CCMR2_OC3PE;
//	TIM5->CCER |= TIM_CCER_CC3E;
//	TIM5->EGR |= TIM_EGR_UG;
//	TIM5->CR1 &= ~TIM_CR1_DIR;
//	TIM5->CCR3 = 1000;
//
//	// Configurar do Timer 4
//	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
//	TIM4->PSC = 8399;
//	TIM4->ARR = 2500;
//	TIM4->DIER |= TIM_DIER_UIE;
//	NVIC_EnableIRQ(TIM4_IRQn);
//
//	while(1){}
//
//}

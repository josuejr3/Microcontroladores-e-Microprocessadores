void questao08(){
	Utility_Init();
	USART1_Init();

	GPIO_Clock_Enable(GPIOA);
	GPIO_Pin_Mode(GPIOA, PIN_1, ALTERNATE);
	GPIO_Alternate_Function(GPIOA, PIN_1, AF2);

	// TIM5
	RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
	TIM5->CR1 &= ~TIM_CR1_DIR; //Contagem crescente
	TIM5->PSC = 8399; // Prescaler de 10 kHz
	TIM5->ARR = 9999; // Período de 1 segundo (1 Hz)
	TIM5->CCR2 = 5000; // Duty Cicle 50%
	TIM5->CCMR1 |= 0b110 << 12; // Seleciona PWM modo 1
	TIM5->CCMR1 |= TIM_CCMR1_OC2PE; // Habilita o pré carregamento do registrador CCR2
	TIM5->CCER |= TIM_CCER_CC2E; // Habilita saída
	TIM5->EGR = TIM_EGR_UG; // update event para escrever o valor do presca
	TIM5->CR1 |= TIM_CR1_CEN; // Habilita o timer

	while(1)
	{
	}
}

void questao09(){
	Utility_Init();
	USART1_Init();

	GPIO_Clock_Enable(GPIOA);
	GPIO_Pin_Mode(GPIOA, PIN_1, ALTERNATE);
	GPIO_Alternate_Function(GPIOA, PIN_1, AF2);

	GPIO_Clock_Enable(GPIOB);
	GPIO_Pin_Mode(GPIOB, PIN_0, INPUT);
	GPIO_Pin_Mode(GPIOB, PIN_1, INPUT);

	// TIM5 gerando sinal PWM para PA1
	RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
	TIM5->CR1 &= ~TIM_CR1_DIR; //Contagem crescente
	TIM5->PSC = 8399; // Prescaler de 10 kHz
	TIM5->ARR = 9999; // Período de 1 segundo (1 Hz)
	TIM5->CCR2 = 5000; // Duty Cicle 50%
	TIM5->CCMR1 |= 0b110 << 12; // Seleciona PWM modo 1
	TIM5->CCMR1 |= TIM_CCMR1_OC2PE; // Habilita o pré carregamento do registrador CCR2
	TIM5->CCER |= TIM_CCER_CC2E; // Habilita saída
	TIM5->EGR = TIM_EGR_UG; // update event para escrever o valor do presca
	TIM5->CR1 |= TIM_CR1_CEN; // Habilita o timer

	// Interrupções externas
	EXTI_Config(EXTI0, GPIOB, RISING_EDGE);
	NVIC_EnableIRQ(EXTI0_IRQn);
	EXTI_Config(EXTI1, GPIOB, RISING_EDGE);
	NVIC_EnableIRQ(EXTI1_IRQn);

	NVIC_SetPriority(EXTI0_IRQn, 1);
	NVIC_SetPriority(EXTI1_IRQn, 0);

	while(1){

	}
}

void questao10(){
	Utility_Init();
	USART1_Init();

	GPIO_Clock_Enable(GPIOA);
	GPIO_Pin_Mode(GPIOA, PIN_1, ALTERNATE);
	GPIO_Alternate_Function(GPIOA, PIN_1, AF2);
	GPIO_Pin_Mode(GPIOA, PIN_6, OUTPUT); // D2
	GPIO_Pin_Mode(GPIOA, PIN_7, OUTPUT); // D3
	GPIO_Write_Pin(GPIOA, PIN_6, HIGH);
	GPIO_Write_Pin(GPIOA, PIN_7, HIGH);

	GPIO_Clock_Enable(GPIOB);
	GPIO_Pin_Mode(GPIOB, PIN_0, INPUT);
	GPIO_Pin_Mode(GPIOB, PIN_1, INPUT);

	GPIO_Clock_Enable(GPIOE);
	GPIO_Pin_Mode(GPIOE, PIN_4, INPUT); // K0
	GPIO_Resistor_Enable(GPIOE, PIN_4, PULL_UP);
	GPIO_Pin_Mode(GPIOE, PIN_3, INPUT); // K1
	GPIO_Resistor_Enable(GPIOE, PIN_3, PULL_UP);

	// TIM5 gerando sinal PWM para PA1
	RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;
	TIM5->CR1 &= ~TIM_CR1_DIR; //Contagem crescente
	TIM5->PSC = 8399; // Prescaler de 10 kHz
	TIM5->ARR = 9999; // Período de 1 segundo (1 Hz)
	TIM5->CCR2 = 5000; // Duty Cicle 50%
	TIM5->CCMR1 |= 0b110 << 12; // Seleciona PWM modo 1
	TIM5->CCMR1 |= TIM_CCMR1_OC2PE; // Habilita o pré carregamento do registrador CCR2
	TIM5->CCER |= TIM_CCER_CC2E; // Habilita saída
	TIM5->EGR = TIM_EGR_UG; // update event para escrever o valor do presca
	TIM5->CR1 |= TIM_CR1_CEN; // Habilita o timer

	// Interrupções externas
	EXTI_Config(EXTI0, GPIOB, RISING_EDGE);
	NVIC_EnableIRQ(EXTI0_IRQn);
	EXTI_Config(EXTI1, GPIOB, RISING_EDGE);
	NVIC_EnableIRQ(EXTI1_IRQn);

	NVIC_SetPriority(EXTI0_IRQn, 1);
	NVIC_SetPriority(EXTI1_IRQn, 0);

	// Configurando Timer TIM3
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN; // Liga clock TIM3
	TIM3->PSC = 41999; // PS = 500 us
	TIM3->ARR = 3999;
	TIM3->EGR |= TIM_EGR_UG;  // update para escrever o valor do prescaler
	TIM3->CR1 |= TIM_CR1_OPM;
	TIM3->CR1 &= ~TIM_CR1_DIR; // contagem crescente
	// TIM4
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN; // Liga clock TIM3
	TIM4->PSC = 41999;
	TIM4->ARR = 7999;
	TIM4->EGR |= TIM_EGR_UG;  // update para escrever o valor do prescaler
	TIM4->CR1 |= TIM_CR1_OPM;
	TIM4->CR1 &= ~TIM_CR1_DIR; // contagem crescente

	// Configurando interrupções externas
	EXTI_Config(EXTI3, GPIOE, RISING_EDGE);
	NVIC_EnableIRQ(EXTI3_IRQn);
	EXTI_Config(EXTI4, GPIOE, RISING_EDGE);
	NVIC_EnableIRQ(EXTI4_IRQn);

	while(1){
		if (TIM3->SR & TIM_SR_UIF) {
			TIM3->SR &= ~TIM_SR_UIF;
			// Ação após 2 segundos
			GPIO_Write_Pin(GPIOA, PIN_6, HIGH);
		}
		if (TIM4->SR & TIM_SR_UIF) {
			TIM4->SR &= ~TIM_SR_UIF;
			// Ação após 2 segundos
			GPIO_Write_Pin(GPIOA, PIN_7, HIGH);
		}
	}

}

// Interrupções da questão 10
void EXTI4_IRQHandler(){
	TIM3->CNT = 0;
	TIM3->SR &= ~TIM_SR_UIF;
	TIM3->CR1 |= TIM_CR1_CEN; // Habilita a contagem
	GPIO_Write_Pin(GPIOA, PIN_6, LOW);
	printf("INTERRRUPÇÃO EXTERNA EM K0\n");
	EXTI_Clear_Pending(EXTI3);
}

void EXTI3_IRQHandler(){
	if(!(TIM4->CR1 & TIM_CR1_CEN))
	{
		TIM4->SR &= ~TIM_SR_UIF;
		TIM4->CNT = 0;
		TIM4->SR &= ~TIM_SR_UIF; // Garante flag limpa
		TIM4->CR1 |= TIM_CR1_CEN; // hABILITA CONTAGEM
		GPIO_Write_Pin(GPIOA, PIN_7, LOW);
		printf("INTERRRUPÇÃO EXTERNA EM K1\n");
		EXTI_Clear_Pending(EXTI4);
	}
}

// Interrupções da questão 9
void EXTI0_IRQHandler(){
	printf("INTERRUPÇÃO EXTERNA EM PB0\n");
	EXTI_Clear_Pending(EXTI0);
}

void EXTI1_IRQHandler(){
	printf("INTERRUPÇÃO EXTERNA EM PB1\n");
	EXTI_Clear_Pending(EXTI1);
}

//int questao_3(){
//
////	void ADC_IRQHandler(){
////
////		// Printa a saída padrão
////		printf("Saida da Regiao Monitorada\n");
////		// Limpando a flag da indicação de interrupção
////		ADC1->SR &= ~ADC_SR_AWD;
////
////	}
//
//
//		// Habilita a biblioteca Utility e o periférico USART1
//		Utility_Init();
//		USART1_Init();
//
//		// Iniciando ADC1 com canal simples
//		ADC_Init(ADC1, SINGLE_CHANNEL, ADC_RES_12BITS);
//		// Definindo o canal IN0
//		ADC_SingleChannel(ADC1, ADC_IN0);
//
//		// Definindo limiares superior e inferior
//		ADC1->LTR = 993;
//		ADC1->HTR = 2109;
//
//		// Habilita o WD em canal simples, seleciona o canal montiorado
//		ADC1->CR1 |= ADC_CR1_AWDSGL;
//		ADC1->CR1 &= ~ADC_CR1_AWDCH;
//
//		// Habilita o WD e coloca uma interrupção toda vez q o bit sinalizador for setado
//		ADC1->CR1 |= ADC_CR1_AWDEN;
//		ADC1->CR1 |= ADC_CR1_AWDIE;
//
//		// Habilita a interrupção no controlador NVIC
//		NVIC_EnableIRQ(ADC_IRQn);
//
//		while(1){
//
//			uint16_t leitura = ADC_GetSingleConversion(ADC1);
//			float voltage = 3.3 * (float) leitura/4095;
//			printf("Voltage = %.2f\n\n", voltage); // imoprime o valor
//			Delay_ms(500);
//
//		}
//
//		return 0;
//
//
//}

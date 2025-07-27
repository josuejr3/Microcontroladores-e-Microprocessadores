//int questao_1(){
//	Utility_Init();
//	USART1_Init();
//
//	DAC_Init(DAC_CHANNEL1);
//
//	while(1){
//
//
//		for (uint16_t valor = 0; valor <= 4095; ++valor){
//			DAC_SetValue(DAC_CHANNEL1, valor, DAC_RES_12BITS);
//			Delay_us(500);
//		}
//
//		for (uint16_t valor2 = 4095; valor2 > 0; --valor2){
//			DAC_SetValue(DAC_CHANNEL1, valor2, DAC_RES_12BITS);
//			Delay_us(500);
//		}
//
//	}
//	return 0;
//}

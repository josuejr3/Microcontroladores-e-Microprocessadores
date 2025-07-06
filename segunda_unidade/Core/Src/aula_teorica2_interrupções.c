///*
// * aula_teorica2_interrupções.c
// *
// *  Created on: May 29, 2025
// *      Author: Josue
// */
//
//
//#include "main.h"
//#include "Utility.h"
//#include <stdio.h>
//
//
//void setup(){
//
//	// Inicialização da utility
//	Utility_Init();
//
//	// Habilita os prints
//	USART1_Init();
//
//	GPIO_Pin_Mode(GPIOA, PIN_0, INPUT);
//	GPIO_Pin_Mode(GPIOA, PIN_1, INPUT);
//	GPIO_Pin_Mode(GPIOA, PIN_2, OUTPUT);
//	GPIO_Pin_Mode(GPIOA, PIN_6, OUTPUT);
//	GPIO_Pin_Mode(GPIOA, PIN_7, OUTPUT);
//
//	EXTI_Config(EXTI0, GPIOA, RISING_EDGE);
//	EXTI_Config(EXTI1, GPIOA, RISING_EDGE);
//
//	NVIC_EnableIRQ(EXTI0_IRQn);
//	NVIC_EnableIRQ(EXTI1_IRQn);
//
//	// Alterando prioridades de interrupções (nome, prioridade)
//	NVIC_SetPriority(EXTI0_IRQn, 1);
//	NVIC_SetPriority(EXTI1_IRQn, 0);
//
//	// Se os números de prioridade estão iguais, então quem decide quem
//	// executa primeiro é o CMSYS, do contrário, podemos setar prioridades diferentes
//
//
//}
//
//void EXTI0_IRQHandler(){
//	GPIO_Toggle_Pin(GPIOA, PIN_6);
//	Delay_ms(500);
//	EXTI_Clear_Pending(EXTI0);
//}
//void EXTI1_IRQHandler(){
//	GPIO_Toggle_Pin(GPIOA, PIN_7);
//	Delay_ms(500);
//	EXTI_Clear_Pending(EXTI1);
//}
//
//int main(){
//
//	setup();
//	while(1){
//		printf("Oie");
//		Delay_ms(500);
//
//
//		// Os pinos não estão acendendo e apagando ao mesmo tempo !!!
//		// Um deles liga primeiro, pois uma das ISRs está sendo executada primeiro (o microcontrolador so possui um nucleo)
//		// Dessa forma ele não consegue executar duas tarefas ao mesmo tempo
//		GPIO_Toggle_Pin(GPIOA, PIN_2);
//		Delay_ms(1000);
//	}
//	return 0;
//}

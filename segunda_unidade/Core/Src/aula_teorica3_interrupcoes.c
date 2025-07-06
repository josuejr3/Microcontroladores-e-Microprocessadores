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
//	GPIO_Clock_Enable(GPIOA);
//	GPIO_Clock_Enable(GPIOE);
//
//	GPIO_Write_Pin(GPIOA, PIN_6, HIGH);
//	GPIO_Write_Pin(GPIOA, PIN_7, HIGH);
//
//	GPIO_Pin_Mode(GPIOE, PIN_3, INPUT);
//	GPIO_Pin_Mode(GPIOE, PIN_4, INPUT);
//	GPIO_Pin_Mode(GPIOA, PIN_6, OUTPUT);
//	GPIO_Pin_Mode(GPIOA, PIN_7, OUTPUT);
//
//	GPIO_Resistor_Enable(GPIOE, PIN_3, PULL_UP);
//	GPIO_Resistor_Enable(GPIOE, PIN_4, PULL_UP);
//
//	EXTI_Config(EXTI3, GPIOE, RISING_EDGE);
//	EXTI_Config(EXTI4, GPIOE, RISING_EDGE);
//
//	NVIC_EnableIRQ(EXTI3_IRQn);
//	NVIC_EnableIRQ(EXTI4_IRQn);
//
//	// Alterando prioridades de interrupções (nome, prioridade)
//	NVIC_SetPriority(EXTI3_IRQn, 1);
//	NVIC_SetPriority(EXTI4_IRQn, 0);
//
//	// Se os números de prioridade estão iguais, então quem decide quem
//	// executa primeiro é o CMSYS, do contrário, podemos setar prioridades diferentes
//
//
//}
//
//void EXTI3_IRQHandler(){
//	GPIO_Write_Pin(GPIOA, PIN_6, LOW);
//	for (int i = 30000000; i; i--);
//	GPIO_Write_Pin(GPIOA, PIN_6, HIGH);
//	EXTI_Clear_Pending(EXTI3);
//}
//void EXTI4_IRQHandler(){
//	GPIO_Write_Pin(GPIOA, PIN_7, LOW);
//	for (int j = 30000000; j; j--);
//	GPIO_Write_Pin(GPIOA, PIN_7, HIGH);
//	EXTI_Clear_Pending(EXTI3);
//}
//
//int main(){
//
//	setup();
//	while(1){
//
//		// Os pinos não estão acendendo e apagando ao mesmo tempo !!!
//		// Um deles liga primeiro, pois uma das ISRs está sendo executada primeiro (o microcontrolador so possui um nucleo)
//		// Dessa forma ele não consegue executar duas tarefas ao mesmo tempo
////		GPIO_Toggle_Pin(GPIOA, PIN_2);
////		Delay_ms(1000);
//	}
//	return 0;
//}

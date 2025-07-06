///*
// * teste.c
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
//	// Habilitando clocks
//	GPIO_Clock_Enable(GPIOA);
//	GPIO_Clock_Enable(GPIOE);
//
//	// Configurando pino PE3 como entrada digital com resistor pullup
//	GPIO_Pin_Mode(GPIOE, PIN_3, INPUT);
//	GPIO_Resistor_Enable(GPIOE, PIN_3, PULL_UP);
//
//	// Configurando para o pino de saída PA6 começar com saída digital em nivel alto (apagado)
//	GPIO_Write_Pin(GPIOA, PIN_6, HIGH);
//	GPIO_Pin_Mode(GPIOA, PIN_6, OUTPUT);
//
//	// Configurando PA7 como saída
//	GPIO_Pin_Mode(GPIOA, PIN_7, OUTPUT);
//
//	// Configurando a interrupção
//	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN; // habilita o clock syscfgen
//	SYSCFG->EXTICR[0] |= (0b0100 << 12);  // seleciona PE3 como gatilho do EXTI3
//	EXTI->FTSR |= 1 << 3;                 // seleciona a bora de descida
//	EXTI->IMR |= 1 << 3;                  // habilita a interrupção EXTI3
//
//	NVIC_EnableIRQ(EXTI3_IRQn);           // habilita a interrupção EXTI3 no NVIC
//
//	// Observações
//	// Para selecionar PE3 como fonte de gatilho da interrupção EXTI3
//	// eu preciso fazer isso nos registradores EXTICR que está dentro do módulo SYSCFG
//	// e para acessar os registradores do módulo SYSCFG eu preciso habilitar o clock dele
//	// para isso eu usei a primeira linha de "RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN"
//	// em que APB2ENR é o barramento que liga o periférico
//
//	// Como eu ja possuo acesso aos EXTICR então eu posso ir de EXTI0 até EXTI15
//	// nesse caso como estou usando o PE3 eu devo escolher EXTI0
//	// e no campo de 4 bits de EXTI0 eu devo escolher o valor correspondente a porta que vai ser
//	// a interrupção, nesse caso o valor correspondente a GPIOE que é 0100.
//
//	// Por que deslocado de 12? SYSCFG->EXTICR[0] |= (0b0100 << 12);
//
//	// Por fim, habilito a interrupção no NVIC passando o nome da interrupção
//	// (nome das funções estão no arquivo stm32f407xx.h)
//
//	// Podemos substituir toda a configuração da interrupção usando a seguinte função
//	EXTI_Config(EXTI3, GPIOE, FALLING_EDGE);
//
//	// O arquivo para escrever as interrupções é o src/it.c
//
//	// a função HAL_GPIO_EXTI_CallBack(uint16_t GPIO_Pin) é uma função fraca
//	// e pode ser sobrescrita por qualquer outra. Além disso ela é chamada para todas
//	// as interrupções, então dessa forma para eu saber qual foi a interrupção é preciso fazer um if
//
//
//}
//
////void HAL_GPIO_EXTI_Callback(uint16_t, GPIO_Pin){
////	if (GPIO_Pin == GPIO_PIN_3){
////		GPIO_Toggle_Pin(GPIOA, PIN_6);
////	}
////}
//
//void EXTI3_IRQHandler(){
//	GPIO_Toggle_Pin(GPIOA, PIN_6); // alterna o estado de PE6
//	EXTI->PR |= 1 << 3;            // limpa a flag de pendente em EXTI0
//	// podemos substituir pela função da biblioteca utility
//	EXTI_Clear_Pending(EXTI3);
//}
//
//int main(){
//
//	setup();
//
//	while(1){
//		GPIO_Toggle_Pin(GPIOA, PIN_7);
//		Delay_ms(500);
//	}
//	return 0;
//}



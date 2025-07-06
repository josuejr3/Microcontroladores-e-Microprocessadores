//#include "main.h"
//#include "Utility.h"
//#include <stdio.h>
//
//
//void setup(){
//
//	Utility_Init();
//	HAL_Init();
//
//	GPIO_Clock_Enable(GPIOA);
//	GPIO_Pin_Mode(GPIOA, PIN_6, OUTPUT);
//	GPIO_Pin_Mode(GPIOA, PIN_7, OUTPUT);
//
//	// Carrega o registrador Reload Value
//	SysTick->LOAD = 6.3e6 - 1;
//	// Liga o Systick, habilita a interrupção e seleciona a fonte de clock
//	SysTick->CTRL = 0b011;
//
//
//}
//
//
//void SysTick_Handler(){
//	GPIO_Toggle_Pin(GPIOA, PIN_7);
//}
//
//int main(){
//
//	setup();
//	while (1){
//
//		GPIO_Toggle_Pin(GPIOA, PIN_6);
//		Delay_ms(1000);
//
//	}
//
//
//	return 0;
//}

#include "main.h"
#include "Utility.h"

void SysTick_Handler(){
	GPIO_Toggle_Pin(GPIOA, PIN_7);
}


int main(){

	Utility_Init();

	GPIO_Clock_Enable(GPIOA);
	GPIO_Pin_Mode(GPIOA, PIN_6, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_7, OUTPUT);

	SysTick->LOAD = 6.3e6 - 1; // Carrega o registrador Reload Value
	SysTick->CTRL = 0b011;     // Liga o SysTick, habilita a interrupção e seleciona



	while(1){

		GPIO_Toggle_Pin(GPIOA, PIN_6);
		Delay_ms(1000);

	}
	return 0;
}

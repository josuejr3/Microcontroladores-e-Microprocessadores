#include "main.h"
#include "Utility.h"


void EXTI3_IRQHandler(){
	GPIO_Write_Pin(GPIOA, PIN_6, LOW);
	for (int i = 30000000; i; --i);
	GPIO_Write_Pin(GPIOA, PIN_6, HIGH);
	EXTI_Clear_Pending(EXTI3);

}

void EXTI4_IRQHandler(){
	GPIO_Write_Pin(GPIOA, PIN_7, LOW);
	for (int j = 30000000; j; --j);
	GPIO_Write_Pin(GPIOA, PIN_7, HIGH);
	EXTI_Clear_Pending(EXTI4);

}

void setup(){
	Utility_Init();                // Inicializa a biblioteca utility
	GPIO_Clock_Enable(GPIOA);      // Ativa o clock do GPIOA
	GPIO_Clock_Enable(GPIOE);      // Ativa o clock do GPIOE

	// Coloca ambos os LEDs em nivel alto
	GPIO_Write_Pin(GPIOA, PIN_6, HIGH);
	GPIO_Write_Pin(GPIOA, PIN_7, HIGH);


	// Configuração de botões e leds
	GPIO_Pin_Mode(GPIOA, PIN_6, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_7, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_3, INPUT);
	GPIO_Pin_Mode(GPIOA, PIN_4, INPUT);

	// Habilitando resistores
	GPIO_Resistor_Enable(GPIOE, PIN_3, PULL_UP);
	GPIO_Resistor_Enable(GPIOE, PIN_4, PULL_UP);

	EXTI_Config(EXTI3, GPIOE, FALLING_EDGE);
	EXTI_Config(EXTI4, GPIOE, FALLING_EDGE);

	NVIC_EnableIRQ(EXTI3_IRQn);
	NVIC_EnableIRQ(EXTI4_IRQn);

	NVIC_SetPriority(EXTI3_IRQn, 1);
	NVIC_SetPriority(EXTI4_IRQn, 0);


}


int main(){

	setup();

	while(1){

		GPIO_Toggle_Pin(GPIOA, PIN_2);
		Delay_ms(1000);

	}
	return 0;
}






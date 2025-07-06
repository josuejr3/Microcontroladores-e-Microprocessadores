#include "main.h"
#include "Utility.h"

int main(void) {

	Utility_Init();
//	GPIO_Clock_Enable(GPIOE);
//	GPIO_Pin_Mode(GPIOE, PIN_3, INPUT);
//	// K1
//	GPIO_Resistor_Enable(GPIOE, PIN_3, PULL_UP);
//	GPIO_Pin_Mode(GPIOE, PIN_4, INPUT);
//	// K0
//	GPIO_Resistor_Enable(GPIOE, PIN_4, PULL_UP);
//
//	GPIO_Clock_Enable(GPIOA);
//	//GPIO_Pin_Mode(GPIOA, PIN_6, OUTPUT);
//	GPIO_Pin_Mode(GPIOA, PIN_6, OUTPUT);



	// AULA 30
	GPIO_Clock_Enable(GPIOA);
	GPIO_Clock_Enable(GPIOE);
	GPIO_Pin_Mode(GPIOA, PIN_7, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_6, OUTPUT);
	GPIO_Resistor_Enable(GPIOE, PIN_3, PULL_UP);
	GPIO_Resistor_Enable(GPIOA, PIN_0, PULL_DOWN);


	while (1) {

//		if (!GPIO_Read_Pin(GPIOE, PIN_4)){
//			if (!GPIO_Read_Pin(GPIOE, PIN_3))
//				GPIO_Write_Pin(GPIOA, PIN_7, LOW);
//			else
//				GPIO_Write_Pin(GPIOA, PIN_7, HIGH);
//		} else if (!GPIO_Read_Pin(GPIOE, PIN_3))
//			if (!GPIO_Read_Pin(GPIOE, PIN_4))
//				GPIO_Write_Pin(GPIOA, PIN_7, HIGH);
//			else
//				GPIO_Write_Pin(GPIOA, PIN_7, HIGH);
//		else
//			GPIO_Write_Pin(GPIOA, PIN_7, HIGH);



//		if(!GPIO_Read_Pin(GPIOE, PIN_3))
//			GPIO_Write_Pin(GPIOA, PIN_6, LOW);
//		else
//			GPIO_Write_Pin(GPIOA, PIN_6, HIGH);

		// Contar de 0 a 3

		// 00
		// 01
		// 10
		// 11


		GPIO_Write_Pin(GPIOA, PIN_7, HIGH);
		GPIO_Write_Pin(GPIOA, PIN_6, HIGH);

		uint8_t t = 0;

		if (GPIO_Read_Pin(GPIOA, PIN_0)){
			if (t > 0){
				t++;
			}
		} else if (!GPIO_Read_Pin(GPIOE, PIN_3)){
			if (t < 3){
				t--;
			}
		}




	}

	return 0;
}

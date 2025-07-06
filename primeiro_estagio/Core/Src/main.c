#include "main.h"
#include "Utility.h"

// GUIA DE SOBREVIVÊNCIA - STM32

// Cada porta possui registradores que permitem controlar
// os seus 16 pinos. Os registradores são:

// MODER - Configura como o pino vai funcionar: entrada, saída, analógica ou função alternativa
// 00 - Entrada digital (estado padrão);
// 01 - Saída digital;
// 10 - Função alternativa;
// 11 - Modo analógico


// Função de configuração
void setup(){

	// Habilitando o Clock da Porta
//	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
//
//	// Configurando modo de funcionamento do pino para ser uma saída
//	GPIOA->MODER &= ~(0b11 << 12);
//	GPIOA->MODER |= 0b01 << 12;
//
//	// Configurando modo de funcionamento do pino para ser uma entrada
//	GPIOA->MODER &= ~(0b11 << 0);
//	GPIOA->MODER |= 0b00 << 0;



	// q17 setup

//	Utility_Init();
//	GPIO_Clock_Enable(GPIOA);
//	GPIO_Pin_Mode(GPIOA, PIN_3, OUTPUT); // PWM
//
//	GPIO_Clock_Enable(GPIOE);
//	GPIO_Pin_Mode(GPIOE, PIN_4, INPUT); // botão 01 - K0
//	GPIO_Resistor_Enable(GPIOE, PIN_4, PULL_UP);
//	GPIO_Pin_Mode(GPIOE, PIN_3, INPUT); // botão 02 - K1
//	GPIO_Resistor_Enable(GPIOE, PIN_3, PULL_UP);




}


// OTYPER - Configura o tipo da saída do pino
// OSPEEDR -
// PUPDR - Configura se os registores pull up e down internos da placa vão estar habilitados ou não.

uint8_t tempo = 2;

void EXTI0_IRQHandler(){
	if (tempo == 2){
		tempo = 5;
	} else{
		tempo = 2;
	}
	EXTI_Clear_Pending(EXTI0);

}

int main(void){

	HAL_Init();
	Utility_Init();

	GPIO_Clock_Enable(GPIOA);
	GPIO_Pin_Mode(GPIOA, PIN_0, INPUT);
	GPIO_Resistor_Enable(GPIOA, PIN_0, PULL_DOWN);
	GPIO_Pin_Mode(GPIOA, PIN_6, OUTPUT);

//	uint32_t pulsoMin = 500;
//	uint32_t pulsoMax = 2500;
//	uint32_t pulso = 500;


	EXTI_Config(EXTI0, GPIOA, RISING_EDGE);
	NVIC_EnableIRQ(EXTI0_IRQn);


	while (1){

//		// Escrever o valor do dado (0 ou 1) no ODR, Output Data Register
//
//		// Enviando sinal alto para o pino 6
//		GPIOA->ODR |= 1 << 6;
//
//		// Essa operação é uma "mescla" de duas, ou seja, o processador executa em dois passos
//		// Uma instrução para deslocar os bits e outra para atribuir.
//
//		// Porém, conseguimos fazer isso com uma única instrução usando
//		// O registrador BSRR - Bit Set Reset Register
//		GPIOA->BSRR |= 1 << 6;
//
//		// Função de delay
//		HAL_Delay(1000); // delay de um segundo
//
//		// Enviando sinal baixo para o pino 6
//		GPIOA->ODR &= ~(1 << 6);
//
//		// Mais um delay de um segundo
//		HAL_Delay(1000);
//
//		// GPIOA->OTYPER - Define se o tipo de saída do pino vai ser push pull ou open drain
//		// GPIOA->PUPDR - Ativa registradores pull up e pull down
//		// 00 - Sem resistores
//		// 01 - Habilita o resistor de pull up
//		// 10 - Habilita o resistor de pull down
//		// 11 - Reservado (sem função)
//
//		// GPIOA->OSPEEDR- Configura o slew rate do pino
//		// 00 - Low speed
//		// 01 - Medium speed
//		// 10 - High speed
//		// 11 - Very high speed
//
//		// Lendo a variável de PA0
//		uint16_t leitura;
//		// Se PA0 tiver alto, leitura é 1 se tiver em nível baixo, leitura é 0
//		leitura = GPIOA->IDR & 1;
//
//		// A diferença para um pino diferente de PA0 é só o deslocamento
//		leitura = GPIOA->IDR & (1 << 5);


		//q17

//		Delay_ms(20);
//				if(!GPIO_Read_Pin(GPIOE, PIN_4)){
//					GPIO_Write_Pin(GPIOA, PIN_3, HIGH);
//					Delay_us(pulso);
//					GPIO_Write_Pin(GPIOA, PIN_3, LOW);
//					if (pulso < pulsoMax)
//						pulso++;
//				}
//				else if(!GPIO_Read_Pin(GPIOE, PIN_3)){
//					GPIO_Write_Pin(GPIOA, PIN_3, HIGH);
//					Delay_us(pulso);
//					GPIO_Write_Pin(GPIOA, PIN_3, LOW);
//					if (pulso > pulsoMin)
//						pulso--;
//				}
//				else {
//					GPIO_Write_Pin(GPIOA, PIN_3, HIGH);
//					Delay_us(pulso);
//					GPIO_Write_Pin(GPIOA, PIN_3, LOW);
//				}
//				Delay_ms(10);
//
//
//	}
		// SEGUNDO ESTAGIO
		GPIO_Toggle_Pin(GPIOA, PIN_6);
		Delay_ms(250);
		if (tempo == 2){
			Delay_ms(250);
		} else{
			Delay_ms(100);
		}
//		GPIO_Write_Pin(GPIOA, PIN_6, HIGH);
//		if (tempo == 2){
//			Delay_ms(250);
//		} else{
//			Delay_ms(100);
//		}

	}
	return 0;
}

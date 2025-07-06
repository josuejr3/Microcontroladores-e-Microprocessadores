#include "main.h"
#include "Utility.h"


void EXTI3_IRQHandler(){
	// Altera o valor da saída (LED)
	GPIO_Toggle_Pin(GPIOA, PIN_6);
	// Limpa a flag de pendência em EXTI0
	// EXTI->PR |= 1 << 3;
	// Vamos substituir pela função da Utility
	EXTI_Clear_Pending(EXTI3);
}

void setup(){
	Utility_Init();                // Inicializa a biblioteca utility
	GPIO_Clock_Enable(GPIOA);      // Ativa o clock do GPIOA
	GPIO_Clock_Enable(GPIOE);      // Ativa o clock do GPIOE

	// Configuração para PE3 como entrada digital e ativação de pull-up
	GPIO_Pin_Mode(GPIOE, PIN_3, INPUT);
	GPIO_Resistor_Enable(GPIOE, PIN_3, PULL_UP);

	// Configuração para PA6 como saída digital e já escreve nível alto para começar desligado
	GPIO_Write_Pin(GPIOA, PIN_6, HIGH);
	GPIO_Pin_Mode(GPIOA, PIN_6, OUTPUT);

	GPIO_Pin_Mode(GPIOA, PIN_7, OUTPUT);

	// Configuração da Interrupção
	//RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN; // Habilita o clock de SYSCFG
	//SYSCFG->EXTICR[0] |= (0b0100 << 12);  // Seleciona PE3 como gatilho da interrupção
	//EXTI->FTSR |= 1 << 3;                 // Seleciona a borda de descida
	//EXTI->IMR |= 1 << 3;                  // Habilita a interrupção EXTI3 no NVIC (envia pro NVIC)

	// Substituindo toda a configuração da interrupção pela função da Utility
	EXTI_Config(EXTI3, GPIOE, FALLING_EDGE);

	// Função CMSIS - Recebe o nome da interrupção que se deseja habilitar
	// Os nomes de todas as interrupções estão no arquivo "stm32f407xx.h" (não achei)
	NVIC_EnableIRQ(EXTI3_IRQn);


}


int main(){

	setup();

	while(1){
		GPIO_Toggle_Pin(GPIOA, PIN_7);
		Delay_ms(500);
	}

	return 0;
}

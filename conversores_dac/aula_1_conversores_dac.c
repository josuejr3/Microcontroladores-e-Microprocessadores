#include "main.h"
#include "Utility.h"

void setup(){
	
	Utility_Init();   				 		// Inicia a biblioteca Utility
	GPIO_Clock_Enable(GPIOA);		 		// Habilita clock do GPIOA
	GPIO_Pin_Mode(GPIOA, PIN_4, ANALOG);	// Configura pino como saída analógica
	
	RCC->APB1ENR |= RCC_APB1ENR_DACEN; 		// Habilita o clock do DAC
	DAC->CR |= DAC_CR_EN1;					// Habilita o canal 1 do DAC

	// Funções da biblioteca utility para DACs
	
	// Liga o clock e configura o pino pa4 no modo analógico
	DAC_Init(DAC_CHANNEL1);
	// Faz a conversão do valor, basta inserir o canal, o valor e a resolução. 
	//DAC_SetValue(DAC_CHANNEL1, valor, DAC_RES_12BITS);
	
	
}

int main(){
	
	while (1){
		
		// Conversão - DAC
		for (uint16_t valor = 0; valor <= 4095; ++valor){
			DAC->DHR12R1 = valor;
			// DAC_SetValue(DAC_CHANNEL1, valor, DAC_RES_12BITS);
			Delay_us(500);
		}
		
	}
	
	return 0;
}
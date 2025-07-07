#include "main.h"
#include "Utility.h"

void setup(){

	// Inicia a Utility
	Utility_Init();

	GPIO_Clock_Enable(GPIOA);
	GPIO_Pin_Mode(GPIOA, PIN_5, ANALOG);

	// Habilita o barramento do DAc
	RCC->APB1ENR |= RCC_APB1ENR_DACEN;

	// Habilita a geração de onda triangular
	DAC->CR |= 0b10 << 22;

	// Escolhe a amplitude da onda de 11 bits no DAC2
	DAC->CR |= 0b1010 << 24;

	// Seleciona gatilhos por software do DAC2
	DAC->CR |= 0b111 << 19;

	// Habilita gatilhos no DAC2
	DAC->CR |= DAC_CR_TEN2;

	// Habilita o canal 2 do DAC
	DAC->CR |= DAC_CR_EN2;

	// Usando a Utilit para geração de ondas triangulares
	// DAC_Init(DAC_CHANNEL2, AUTO_TRIANGLE, AMP_11BITS); (AUTO_NOISE)
	// DAC_SWTrigger(DAC_CHANNEL2); (USAR NO LOOP)
	// Se quisermos somar um valor, usamos DAC_SetValue

}

int main(){




	while (1){
		DAC->SWTRIGR |= 1 << 1;
		Delay_us(1);

		// DAC_SWTrigger(DAC_CHANNEL2);
	}

	return 0;
}

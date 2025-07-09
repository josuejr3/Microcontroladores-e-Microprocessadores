#include "main.h"
#include "Utility.h"
#include <stdio.h>

void ADC_IRQHandler(){
	printf("Saida da Regiao Monitorada\n");
	// Limpando flag
	ADC1->SR &= ~ADC_SR_AWD;
}

int main(){

	Utility_Init();
	USART1_Init();

	ADC_Init(ADC1, SINGLE_CHANNEL, ADC_RES_12BITS);
	ADC_SingleChannel(ADC1, ADC_IN0);

	ADC1->LTR = 1000; // LIMIAR INFERIOR
	ADC1->HTR = 3000; // LIMIAR SUPERIOR
	ADC1->CR1 |= ADC_CR1_AWDSGL; // HABILITA O WATCHDOG EM CANAL SIMPLES
	ADC1->CR1 &= ~ADC_CR1_AWDCH; // SELEÇÃO DO CANAL MONITORADO (IN0)
	ADC1->CR1 |= ADC_CR1_AWDEN; // HABILITA O WATCHDOG


	// Colocando uma interrupção toda vez que o bit sinalizar
	ADC1->CR1 |= ADC_CR1_AWDIE; // Habilita a interrupção o Watchdog
	NVIC_EnableIRQ(ADC_IRQn); // Habilita a interrupção no NIVC.

	while(1){

		ADC1->CR2 |= ADC_CR2_SWSTART;
		while(!(ADC1->SR & ADC_SR_EOC));
		printf("Leitura = %d\n", (int)ADC1->DR);

		if (ADC1->SR & ADC_SR_AWD)
			printf("SAIDA DA REGIAO MONITORADA\n");

		ADC1->SR &= ~ADC_SR_AWD;
		Delay_ms(500);


	}

}

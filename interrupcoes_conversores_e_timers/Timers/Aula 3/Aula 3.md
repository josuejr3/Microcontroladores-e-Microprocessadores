
Nesta última aula vamos ver como que um timer pode gerar ondas PWM de uma forma automática. Além disso, vamos ver também como um timer pode disparar uma ação em outro periférico, usando o recurso de *"saídas de disparo"*.

Alguns timers possuem um recurso chamado de compare, como mostra na figura abaixo.

<div align="center"><img src="Circuito Compare.png"></div>

A parte de contar funciona semelhante ao que vimos antes. Entretanto, nesse caso existe o registrador de comparação **CCR**.

-  Nesse registrador nós vamos escrever um valor que vai ser comparado (*pelo circuito comparador*) com o valor que está sendo contando em **CNT**;
-  Quando os valores batem, ocorre um evento de comparação que é enviado para um circuito de controle de saída e pode: controlar pinos, gerar interrupções ou até sinais periódicos (PWM).
-  A saída pode ter diversos comportamentos que pode ser selecionado pelos bits **OCM** (*Output Compare Mode*), do registrador **CCRMR**.

Cada módulo de comparação (CCR) possui 4 canais de saída (CH1, CH2, CH3 e o CH4). Todos os canais compartilham o mesmo timer.

<div align="center"><img src="Tabela modo de comparação.png"/></div>

<div align="center"><img src="Saída modo alternância.png"/></div>

-  O bit **UIF** (*Update Interrupt Flag*) do registrador de timers **SR** é setado sempre que ocorre um evento de atualização (overflow ou underflow).
-  O bit **CCIF** (*Capture Compare Interrupt Flag*) é setado sempre que ocorre um evento de comparação

<div align="center"><img src="Registrador SR para TIM.png"/></div>

---
###### <span style="color:rgb(4, 255, 0)">Modos PWM 1 e 2</span>

Para contagens crescentes o contadot vai contar de 0 até o valor máximo ARR. Enquanto o valor for menor que o valor presente em CCR a saída ficará em nível alto. Quando os valores ficam iguais o sinal vai para nível  baixo e fica assim até o final da contagem.

<div align="center"><img src="PWM crescente.png"/></div>

O *duty cycle* nesse caso é dado pela fórmula indicada na imagem.

> ~={green}Exemplo de sinal PWM com Timers=~

```C
#include "main.h"
#include "Utility.h"
#include <stdio.h>

int main(){
	
	Utility_Init();
	USART1_Init();
	GPIO_Clock_Enable(GPIOA);
	GPIO_Pin_Mode(GPIOA, PIN_2, ALTERNATE);
	GPIO_Alternate_Function(GPIOA, PIN_2, AF2);
	RCC->APB1ENR |= RCC_APB1ENR_TIM5EN; // Liga o clock do timer 5
	TIM5->PSC = 419;
	TIM5->ARR = 99;
	TIM5->CCMR2 |= 0b110 << 4; // seleciona PWM modo 1 no modo compare
	
	TIM5->CCMR2 |= TIM_CCMR2_OC3PE; // habilita o pre carregamento do registrador CCR3
	// Basicamente esse código faz com que qualquer novo valor em CCR3
	// so seja usado apos a proxima atualizacao de ciclo do timer
	// isso evita transicoes abruptas e glitchs
	
	
	TIM5->CCER |= TIM_CCER_CC3E; // habilita a saída no CANAL 3
	// que vai para o pino PA2
	TIM5->EGR |= TIM_EGR_UG; // update event para escrever o valor do prescaler
	// o EGR_UG aplica imediatamnte o valor do prescaler ao timer
	TIM5->CR1 &= ~TIM_CR1_DIR; // contagem crescente
	// o bit DIR controla se é crescente (0) ou decrecente (1)
	TIM5->CR1 |= TIM_CR1_CEN; // habilita a contagem
	
	// 30% DE DUTY CYCLE
	TIM5->CCR3 = 30;
	
	while(1){
		// Alterando o valor do CCR
		for (int duty = 0; duty < 100; ++duty){
			TIM5->CCR3 = duty; // atualiza o duty cycle
			Delay_ms(20);
		}
			
		// Alterando o valor do CCR
		for (int duty = 99; duty >= 0; --duty){
			TIM5->CCR3 = duty; // atualiza o duty cycle
			Delay_ms(20);
		}
	
	}
	return 0;

}
```

Os timers possuem uma saída de sinal chamada **TRGO** (*Trigger Output*) que pode ser usada para sincronizar a operação com outros periféricos do microcontrolador

-  Para fazer isso o timer deve ser configurado no modo **MESTRE**;

Além disso, devemos seguir o passo a passo abaixo:

1.  Configurar o Timer para a temporização desejada;
2.  Selecionar a fonte do sinal TRGO escrevendo nos bits **MMS\[2:0]** do registrador **CR2**;
3.  Selecione o que gera um evento de atualização do timer no bit **URS** do registrador **CR1**.

>~={green}Exemplo de aplicação do recurso=~

<div align="center"><img src="Exemplo de recurso.png"/></div>

-  Vamos configurar o Timer 3 para gerar pulsos de disparo em TRGO a cada evento de atualização (overflow);
-  O timer vai estourar a cada 200 ms;
-  O pulso vai ser enviado para ADC1 que deverá iniciar uma conversão;
-  Além disso, vamos habilitar a interrupção por fim de conversão EOC;
-  A ISR vai servir para fazer a leitura da conversão e printar o resultado.

```C
#include "main.h"
#include "Utility.h"
#include <stdio.h>

void ADC_IRQHandler(){
	printf("ADC = %u\n", (unsigned int)ADC1->DR);
}

int main(){
	
	Utility_Init();
	USART1_Init();
	ADC_Init(ADC1, SINGLE_CHANNEL, ADC_RES_12BITS);
	ADC_SingleChannel(ADC1, ADC_IN0);
	
	// Configurações do Timer 3
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN; // Liga o clock do timer 3
	TIM3->CR1 &= ~TIM_CR1_DIR; // Contagem crescente
	TIM3->PSC = 419; // prescaler para pulsos a cada 5us
	TIM3->ARR = 39999; // estouros a cada 200ms
	TIM3->CR2 = 0b010 << 4; // master mode (TRGO a cada update)
	TIM3->CR1 |= TIM_CR1_URS; // (ativação do bit) overflow gera um gatilho em TRGO;
	TIM3->EGR = TIM_EGR_UG; // update event para escrever o valor do prescaler
	// imediatamente
	
	// Config do ADC
	ADC1->CR2 |= 0b1000 << 24; // seleciona a saída (TIM3 TRGO) como fonte de gatilho do ADC1
	ADC1->CR2 |= 0b01 << 28; // habilita o disparo em rising edge
	ADC1->CR1 |= ADC_CR1_EOCIE; // habilita a interrupção de EOC
	NVIC_EnableIRQ(ADC_IRQn); // habilita a interrupção no NVIC
	
	TIM3->CR1 |= TIM_CR1_CEN;
	
	while(1){}
	
	return 0;
	
}
```

<div align="center"><img src="TIM CR2.png"/></div>

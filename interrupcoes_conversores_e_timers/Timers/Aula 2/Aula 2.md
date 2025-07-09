
Nesta aula nós vamos estudar os Timers de uso geral TIM2 e TIM5. Eles são timers de uso geral de 32 bits e possuem 4 canais de captura e comparação. Além disso, eles podem contar numa velocidade máxima de 84 MHz. A frequência máxima do acesso aos registradores de controle e configuração desses timers é de 42 MHz.

-  Esses timers são baseados em contadores crescentes/decrescentes;
-  Após ser habilitado, o timer conta até o seu limite (0 ou valor máximo até que seja desabilitado), a depender do modo de contagem;
-  O processo de contagem reinicia sempre que chega no limite;
-  O limite máximo quando é de forma crescente fica armazenado no registrador **ARR** de *Auto Reload Register (32bits)*;
-  Esse registrador ARR possui pré carregamento e escrever ou ler nele, acessa o registrador de carrregamento.

> ~={green}Ok, mas por que isso?=~

Então, isso ocorre para que o valor limite não seja alterado durante o período de contagem. Por exemplo, o timer está contando de 0 até 100, porém o valor foi alterado para menos que 100 ou mais que 100, iria dar problema na contagem. 

Por esse motivo, o valor é precarregado.

-  O timer é acionado por um prescaler programável pelo registrador pelo **PSC** (PSC sempre é o valor + 1);

Outra informação importante é que registradores com pré-carregamento precisam de um evento de atualização (*update event*) para serem gravados. Os eventos podem ser: *overflow*, *underflow*, ou *por software*.

---

Sobre as aplicações dos timers. Bem, eles podem ser usados para várias finalidades, incluindo:

-  Medição da duração de pulsos de entrada (*modo de captura de entrada*);
-  Geração de formas de onda de saída, como PWM (*modo de comparação de saída*).

<div align="center"><img src="TIM2 e TIM5.png"></div>

Para esses timers, a contagem só é iniciada quando o bit de contagem do contador é setado **CEN**.

<div align="center"><img src="TIMX CR1.png"></div>
	*x sendo 2 ou 5*

Sobre a fonte de clock dos timers, basicamente ele vem do sinal de clock dos timers do barramento **APB1**, (84 MHz).

	Porém, se o contador for configurado no modo slave (escravo) e outra fonte de clock for escolhida pelos bits TS do TIMx_SMCR, a frequência muda.

<div align="center"><img src="TIM2 e TIM5 escravo.png"></div>

> ~={green}E quanto aos modos de contagem desses timers?=~

Bem, esses timers possuem três modos distintos de contagem, sendo eles:

<div align="center">
<table>
<tr><th align="center">Crescente</th></tr>
<tr><th align="center">Descrescente</th></tr>
<tr><th align="center">Alinhada ao centro</th></tr>
</table>
<br>
<div align="center"><img src="Modos de Contagem.png"></div>
</div>

-  O período de contagem é controlado pela frequência do sinal de clock do contador e pelo valor armazenado no registrador **ARR**;
-  **CK_CNT** é o clock do contador.

<mark style="background: #FF5582A6;">Obs: os gráficos acima não são ondas, são apenas esquematizações para facilitar o entendimento **APENAS ILUSTRAM O CONTADOR**.</mark>

-  Nesses gráficos conseguimos ver os update events, que são undeflow e overflow.

---

> ~={green}Ok, mas e como usar os timers?=~

A maneira mais simples de usar um timer é fazer ele contar livremente e usar a sua contagem como base para temporização de eventos. **Nesse tipo de configuração nenhum recurso de interrupção é necessário**. 

> Passo a passo para colocar o timers para trabalhar com esse objetivo

-  Selecionar a fonte de clock;
-  Definir o fator de divisão prescaler;
-  Configurar os bits de controle para especificar o modo de operação (crescente/decrescente)

<div align="center"><img src="Contagem livre.png"/></div>

> ~={green}Exemplo de programa com o TIMER5 contando livremente.=~

```C
#include "main.h"
#include "Utility.h"
#include <stdio.h>

int main(){
	
	Utility_Init();
	USART1_Init();
	RCC->APB1ENR |= RCC_APB1ENR_TIM5EN; // Liga o clock do timer 5
	TIM5->PSC = 41999; // prescaler para pulsos a cada 500 us
	TIM5->EGR |= TIM_EGR_UG; // update event para escrever o valor do prescaler
	// o EGR_UG aplica imediatamnte o valor do prescaler ao timer
	TIM5->CR1 &= ~TIM_CR1_DIR; // contagem crescente
	// o bit DIR controla se é crescente (0) ou decrecente (1)
	TIM5->CR1 |= TIM_CR1_CEN; // habilita a contagem
	
	while(1){
		TIM5->CNT = 0;
		Delay_ms(1000);
		printf("TIM5 = %u\n", (unsigned int)TIM5->CNT);
	}
	return 0;
}
```

> ~={green}Outro código, mas dessa vez usando interrupções=~

```C
#include "main.h"
#include "Utility.h"
#include <stdio.h>

void TIM5_IRQHandler(){
	TIM5->SR &= ~TIM_SR_UIF;
	printf("INTERRUPCAO\n");
}

int main(){

	Utility_Init();
	USART1_Init();
	RCC->APB1ENR |= RCC_APB1ENR_TIM5EN; // Liga o clock do timer 5
	TIM5->PSC = 41999; // prescaler para pulsos a cada 500 us
	TIM5->ARR = 1999;
	TIM5->EGR |= TIM_EGR_UG; // update event para escrever o valor do prescaler
	// o EGR_UG aplica imediatamnte o valor do prescaler ao timer
	TIM5->CR1 &= ~TIM_CR1_DIR; // contagem crescente
	// Habilita a interrupção por update
	TIM5->DIER |= TIM_DIER_UIE;
	NVIC_EnableIRQ(TIM5_IRQn); // habilita a interrupção no NVIC
	// o bit DIR controla se é crescente (0) ou decrecente (1)
	TIM5->CR1 |= TIM_CR1_CEN; // habilita a contagem
	
	while(1){}
		
	return 0;
}
```

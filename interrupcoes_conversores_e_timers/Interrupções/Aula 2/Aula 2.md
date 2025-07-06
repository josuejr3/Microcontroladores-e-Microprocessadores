#### <span style="color:rgb(4, 255, 0)">Interrupções Externas (pinos de entrada e saída)</span>

-  Interrupções Externas são úteis pois permitem o monitoramento eficiente de sinais aplicados aos pinos do microcontrolador;
-  Todos os pinos de GPIO podem servir como fonte de requisião de interrupção externa;

Para usarmos um pino como fonte de interrrupção nós devemos:

-  Configurar o pino no modo de entrada digital;
-  Implementar as configurações específicas da interrupção.

<div align="center">
<img width=500 src = "Controlador de Interrupcoes-Eventos externos EXTI.png"/>
</div>
<br></br>

-  Esse controlador tem 23 circuitos detectores de bordas de sinais e essas bordas são usadas para disparar as solicitações de interrupções do controlador NVIC.

---

> Ok, mas como funciona e como devemos manusear?

1.  Devemos definir qual borda vai disparar a requisição de interrupção
	1.  Para isso programamos os dois registrados
		1.  Rising Trigger Selection Register (borda de subida)
		2.  Falling Trigger Selection Register (borda de descida )

		> RTSR (Rising Trigger Selection Register)

<div align="center"><img src="Rising Trigger Register.png"/></div>

>		FTSR (Falling Trigger Selection Register)

<div align="center"><img src="Falling Trigger Register.png"/></div>

Quando escrevemos 1 em cada um desses registradores nós estamos habilitando a borda de subida, descida ou ambas.

2.  Após habilitar as bordas. Nós devemos habilitar a solicitação de interrupção, escrevendo 1 no bit correspondente a linha no registrador de mascára de interrupção (**IMR**).
3.  Quando a borda selecionada ocorre, a solicitação de interrupção é gerada e um bit de pendência correspondente a linha de interrupção é setado (Pending Request Register - **PR**)
4.  A solicitação é enviada para o NVIC
5.  É necessário resetar o bit de pendência dentro da ISR.

Além de requisição de interrupções, esse controlador pode gerar eventos. Os eventos podem disparar coisas que o nosso microcontrolador pode fazer sem a intervenção do processador, como por exemplo, iniciar a contagem de um Timer, iniciar uma amostragem DAC ou ADC e entre outras tarefas.

Em relação a código, as ISR's necessitam de código, já os eventos podem ou não envolver códigos.

> Criação de Eventos

1.  Programando as bordas de disparo (subida, descida ou ambas)
2.  Após habilitar as bordas. Nós devemos habilitar a solicitação de evento, escrevendo 1 no bit correspondente no registrador de mascára de evento (Event Mask Register - **EMR**)
3.  Quando a borda selecionada ocorre, a solicitação de evento é gerada e sincroniza a ação em um outro periférico.

<mark style="background: #FF5582A6;">Obs: uma solicitação de interrupção ou evento pode ser feita via software quando escrevemos 1 no bit correspondente a linha específica no registrador (Software Interrupt Event Register - **SWIER**).</mark>

---

Como vimos no controlador de interrupções EXTI, existem 23 linhas de entrada. Dessas 23 linhas de entrada, os pinos GPIO são multiplexados e conectados à 16 delas. As outras sete linhas restantes são conectadas as outros periféricos como *RTC*, *USB*, *ETHERNET*.

-  As linhas de I/O são nomeadas de EXTI0 até EXTI15.
-  Cada uma dessas interrupções é associada com um pino de I/O específico.
-  Porém, como o microcontrolador possui mais de 16 pinos, para solucionar isso os pinos foram multiplexados nas interrupções, selecionando um dentre nove pinos.

<div align="center"><img src="Mapeamento de Pinos.png"/></div>
<br></br>

A partir disso, podemos verificar que em EXT0 temos interrupções para os pinos PA0, PB0, PC0,... para EXT8 temos PA8, PB8, PB9...

O pino específico que vai servir como fonte de interrupção de cada linha EXTI é selecionado por meio de 4 bits em um dos 4 registradores de controle **EXTICRx** (com x sendo 1, 2, 3 ou 4). Esse registradores ficam no módulo de configuração do sistema. **SYSCFG_EXTICRx**.

>~={green} Exemplo SYSCFG_EXTICR1=~

<div align="center"><img src="Registrador EXTICR1.png"/></div>

-  EXTICR1 - Cobre de EXTI0 até EXTI3
-  EXTICR2 - Cobre de EXTI4 até EXTI7
-  EXTICR3 - Cobre de EXTI8 até EXTI11
-  EXTICR4 - Cobre de EXTI12 até EXTI5

Os 16 bits menos significativos de cada um desses registradores formam 4 campos de bits. Por exemplo, no EXTCR1 temos EXTI0 e dependendo do valor que eu colocar em EXTI0 eu estarei selecionando um dos pinos.

Obs: no CMSIS os 4 registradores eles estão em um array de 4 registradores (pode ser visualizado no arquivo do projeto "stm32f407xx.h")

> ~={green}Exemplo=~

<div align="center"><img src="Codigo com registradores EXTI.png
"/></div>

Ao responder o pedido de uma linha de interrupção externa o microcontrolador executa a ISR associada aquela intrrupção.

	Ou seja, a linha EXTI0 está associada a ISR EXTI0IRQHanlder()

Os nome das tabelas podem ser encontrados na tabela de vetores de interrupção dentro do codigo de inicialização. O nome da ISR deve corresponder ao nome usado nessa tabela para que o linker do compilador possa colocar o endereço corretamente na tabela de vetores de interrupção.

<mark style="background: #FF5582A6;">Obs</mark>

Apesar de no STM32 existirem 16 linhas de interrupção externa associadas aos pinos GPIO, só existem sete ISRs associadas a essas linhas.

As funções são as seguintes:

	EXTI0_IRQHandler() - Para EXTI0
	EXTI1_IRQHandler() - Para EXTI1
	EXTI2_IRQHandler() - Para EXTI2
	EXTI3_IRQHandler() - Para EXTI3
	EXTI4_IRQHandler() - Para EXTI4
	EXTI9_5_IRQHandler() - Para EXTI[5:9]
	EXTI15_10_IRQHandler() - Para EXTI[10:15]

*Essas informações podem ser consultadas no arquivo de startup do projeto da STMCubeIDE na pasta Core.*

<mark style="background: #FF5582A6;">Obs</mark>

Como nas últimas duas funções IRQHandler trabalhamos com várias EXTI, para sabermos qual foi a EXTI que estava sendo tratada, devemos olhar para o bit de pendência no registrador de pendência. A posição que estiver setada é a linha que fez a requisição da interrupção.

> ~={green}Exemplo=~ 

No exemplo abaixo, vamos configurar o pino PE3 como fonte de interrupção, toda vez que ele for pressionado o estado do LED ligado em PA6 será alterado.

<div align="center"><img src="Exemplo prático.png"></div>


-  O arquivo do projeto que termina em it.c é o arquivo em que as interrupções devem ser escritas
-  Funções de tratamento de interrupções devem ser as mais curtas possíveis para que o processador retorne rapidamente ao programa principal (EVITAR USO DE DELAYS).

```C
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
	Utility_Init(); // Inicializa a biblioteca utility
	GPIO_Clock_Enable(GPIOA); // Ativa o clock do GPIOA
	GPIO_Clock_Enable(GPIOE); // Ativa o clock do GPIOE
	// Configuração para PE3 como entrada digital e ativação de pull-up
	GPIO_Pin_Mode(GPIOE, PIN_3, INPUT);
	GPIO_Resistor_Enable(GPIOE, PIN_3, PULL_UP);
	// Configuração para PA6 como saída digital e já escreve nível alto para começar desligado
	GPIO_Write_Pin(GPIOA, PIN_6, HIGH);
	GPIO_Pin_Mode(GPIOA, PIN_6, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_7, OUTPUT);
	// Configuração da Interrupção
	//RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN; // Habilita o clock de SYSCFG
	//SYSCFG->EXTICR[0] |= (0b0100 << 12); // Seleciona PE3 como gatilho da interrupção
	//EXTI->FTSR |= 1 << 3; // Seleciona a borda de descida
	//EXTI->IMR |= 1 << 3; // Habilita a interrupção EXTI3 no NVIC (envia pro NVIC)
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
```

<mark style="background: #FF5582A6;">Obs</mark>

Podemos usar a biblioteca HAL, a função HAL_GPIO_EXTI_Callback que basicamente "coordena" todas as EXTI e a partir dela basta conferir qual o pino que foi usado. 

<div align="center">
<img src="Outra alternativa.png"/>
</div>



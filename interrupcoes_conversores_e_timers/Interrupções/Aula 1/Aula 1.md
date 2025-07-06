
-  São recursos de Hardware;
-  Utilizadas para monitorar e responder imediatamente a eventos específicos;
-  Causam alterações no fluxo normal de execução do programa para atender eventos;
-  Permitem ao microcontrolador executar múltiplas tarefas (multitask).

<div align="center">
  <table>
    <tr>
      <th colspan="2" align="center">Técnicas de Monitoramento</th>
    </tr>
    <tr>
      <th align="center">Pooling</th>
      <th align="center">Interrupções</th>
    </tr>
    <tr>
      <td align="center">A todo momento faz uma verificação no sistema</td>
      <td align="center">Sempre está atento para eventos importantes que acontecerem</td>
    </tr>
    <tr>
      <td align="center">Menos eficiente</td>
      <td align="center">Mais eficiente</td>
    </tr>
  </table>
</div>

-  A diferença de funções normais para interrupções e exceções, basicamente é que funções normais são chamadas explicitamente, enquanto que as interrupções são chamadas de forma ímplicita. O desvio de codigo para outros blocos ocorre em ambos os casos.

-  As interrupções são iniciadas em um ponto imprevisível do programa, por um sinal externo ou interno. O contexto de programa deve ser salvo, *(Modificação de PC)*.

---
##### <span style="color:rgb(4, 255, 0)" align="center">Conceitos Importantes em Interrupções</span> 

> ~={green}Fonte de Interrupção=~

É um elemento de hardware que, após um determinado evento, envia um pedido de interrupção ao processador (Botão, Sensor, Periférico...);

> ~={green}Pedido de Interrupção (IRQ - Interrupt Request)=~

É a sinalização do hardware ao processador que o evento ocorreu;

> ~={green}Rotina de Serviço de Interrupção (ISR - Interrupt Service Routine)=~

É a função a ser executada quando o evento ocorrer;

> ~={green}Vetor de Interrupção (Interrupt Vector)=~

É o endereço de memória da função de tratamento de interrupção (Interrupt Vector Table).

<div align="center">
<table>
<tr>
<th colspan="2" align="center">Tipos de Interrupção</th>
</tr>
<tr>
<th align="center">Preemptiva</th>
<th align="center">Não Preemptiva</div>
</tr>
<tr>
<th align="center">Atendimento Imediato</th>
<th align="center">Atendimento Postergado</th>
</tr>
<tr>
<th align="center">Opera em níveis de prioridade</th>
<th align="center">Não há prioridade</th>
</tr>
<tr>
<th align="center">Maior complexidade para implementar em hardware</th>
<th align="center">Mais simples para implementar em hardware</th>
</tr>
</table>

-  Exemplo 1

<div align="center"><img src="Exemplo Interrupção.png"/></div>

-  Exemplo 2

<div><img src="Exemplo Interrupção com Prioridade.png"/></div>

-  Exemplo 3

<div align="center">
<img src="Exemplo Interrupção com Prioridade 2.png"/>
</div>

O que temos nos últimos dois exemplos são aninhamentos de interrupções

-  Exemplo 4

<div align="center">
<img src="Exemplo Interrupção não Preemptiva.png"/>
</div>

<mark style="background: #FF5582A6;">**Obs: o STM32F407 trabalha com o tipo de Interrupções Preemptivas.**</mark>

---

Levando em consideração a observação acima, o STM32 possui um Hardware controlador de interrupções, chamado de NVIC (**Nested Vectored Interrupt Controller**) que serve para configurar e manipular várias fontes de interrupções e ele permite o atendimento preemptivo das interrupções.

<div align="center">
<img src="Nested Vectored Interrupt Controller.png"/>
</div>
<br></br>
-  O controlador NVIC suporta até 256 fontes de interrupções (apesar de ter bem menos implementadas no hardware do chip).
-  Diferentes microcontroladores pode ter diferentes quantidades de fonte de interrupções implementadas fisicamente no chip.
-  **NMI - Interrupção não mascarada (está sempre habilitada)**
-  **SysTick - Interrupção de um TIMER**
-  **System Exceptions - exceções do sistema**

> Tabela com as exceções e interrupções do **STM32**

<div align="center">
<img src="Lista de exceções e interrupções.png"/>
</div>

-  Cada interrupção na tabela é identificada por um número (-15 até 240)
-  São divididas em duas categorias 
	-  As primeiras 15 (-15 até -1) são as interrupções do sistema, ou também do núcleo do processador. São chamadas de **exceções** do sistema, esses números são predefinidos pela ARM.
	-  O restante das interrupções (241) são reservados para os periféricos. A quantidade e o número identificador de cada interrupção é definido pelo fabricante do chip.
-  As ISR's são chamados de Handler de exceção.
-  O CMSIS define os nomes das ISRs e estão nos arquivos de cabeçalho do dispositivo (fornecidos pelos fabricantes).
-  Os números das interrupções se referem as entradas de interrupção no hardware do NVIC.
-  A prioridade define a ordem em que as interrupções vão ser atendidas (umas tem prioridade fixa e outras programáveis).
-  **O nível de prioridade de cada exceção ou interrupção pode ser modificado por registradores que ficam num bloco de controle do NVIC**
-  No STM32 há 16 níveis de prioridade
-  Quando duas interrupções tem mesmo nível de prioridade, a que tem menor número de exceção é executada primeiro.

> Antes de usar qualquer interrupção nós devemos fazer o seguinte

-  Configure o nível de prioridade da interrupção;
-  Configure e ative o controle de requisição da interrupção no periférico que demanda a interrupção;
-  Habilite a interrupção no controlador NVIC.

Com o objetivo de facilitar o acesso aos registradores a CMSIS disponibiliza de algumas funções para nos auxiliar.

<div align="center">
<img src="Funçoes CMSIS para usar Interrupções.png"/>
</div>

-  Existe uma ISR associada a cada interrupção e quando compilamos o programa ele armazena o endereço de cada uma das ISR's em um array especial chamado **Tabela de vetores de Interrupções** essa tabela se encontra na memória de programa a partir do endereço 0x000000004.

<div align="center">
<img width="300" src="Tabela de vetores de interrupções.png"/>
</div>

-  Cada linha representa um endereço na memória onde a função de atendimento a interrupção se encontra.
-  Cada ISR apontada por cada um dos vetores tem um nome específico já definido, os nome são predefinidos pela ARM e pela fabricante do chip.

---

Quando criamos o projeto no STMCubeIDE temos o seguinte arquivo

```txt
projeto/
|----Core/
|    |-----Inc/
|    |-----Src/
|    |-----Startup/
|    |     |-----startup_stm32f407vetx.s
```

-  O arquivo é do tipo Assembly;
-  A partir da linha 129 temos os nomes de todas as ISR's.
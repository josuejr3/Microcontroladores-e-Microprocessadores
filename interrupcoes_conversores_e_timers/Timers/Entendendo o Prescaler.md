
Como o clock dos timers são muito rápidos, facilmente chegamos ao limite de contagem. Por esse motivo usamos prescalers para diminuir a frequência. 

###### <span style="color:rgb(4, 255, 0)">Exemplo</span> 

```C
TIM2->PSC = 419; // Divide o clock principal
TIM2->ARR = 199; // Contar de 0 até 199 (200)
```

1.  Dividir o valor do clock do timer pelo prescaler para reduzirmos a frequência

```
Clock do TIM2 = 84 MHz
84 MHz = 84.000.000 Hz
```

```
ClockPosPrescaler = 84.000.000 / (PSC + 1) Hz
ClockPosPrescaler = 84.000.000 / (419 + 1) Hz
ClockPosPrescaler = 84.000.000 / 420 Hz
ClockPosPrescaler = 200.000 Hz
```

<mark style="background: #ADCCFFA6;">Por que somar 1 ao prescaler?</mark>

Com isso temos que o contador está contando 200..000 contagens por segundo, (ou 1 contagem a cada **5 µs**).

2.  Analisando a segunda ele, com ARR, significa que o Timer vai contar de 0 até 199 e então reiniciar. 

Com isso, podemos obter o tempo de um ciclo completo de contagem

```
Período (ciclo completo de contagem) = ((ARR + 1)/(ClockPosPrescaler))
Período (ciclo completo de contagem) =  200 / 200.000 = 1 ms 
Período (ciclo completo de contagem) = 1 ms
```

> Fórmulas 

-  Tick

```
Tick = (PSC + 1) / Clock_do_Timer
Obs: clock pós prescaler
```

-  Tempo total da contagem (Período)

```
Tempo_Total = Tick x (ARR + 1)
```


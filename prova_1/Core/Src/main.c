#include "main.h"
#include "Utility.h"
#include "LCD_Blio.h"
#include <stdio.h>

void questao1(){
	GPIO_Write_Pin(GPIOA, PIN_5, HIGH);
	Delay_ms(100);
	GPIO_Write_Pin(GPIOA, PIN_5, LOW);
	Delay_ms(100);
}

void questao2(){
	GPIO_Write_Pin(GPIOA, PIN_5, HIGH);
	Delay_ms(100);
	GPIO_Write_Pin(GPIOA, PIN_5, LOW);
	Delay_ms(1900);
}

void questao3(){}

void questao4(){

	for (int i = 0; i <= 1000; i++){
	GPIO_Write_Pin(GPIOA, PIN_0, LOW);
	GPIO_Write_Pin(GPIOA, PIN_1, HIGH);
	Delay_us(i);
	GPIO_Write_Pin(GPIOA, PIN_0, HIGH);
	GPIO_Write_Pin(GPIOA, PIN_1, LOW);
	Delay_us(1000 - i);
	}

	for (int i = 1000; i > 0; i--){
		GPIO_Write_Pin(GPIOA, PIN_0, LOW);
		GPIO_Write_Pin(GPIOA, PIN_1, HIGH);
		Delay_us(i);
		GPIO_Write_Pin(GPIOA, PIN_0, HIGH);
		GPIO_Write_Pin(GPIOA, PIN_1, LOW);
		Delay_us(1000  - i);
	}
}

void questao5(){}

void questao6(){
	uint8_t lista_pinos[] = {PIN_0, PIN_1, PIN_2, PIN_3, PIN_4, PIN_5, PIN_6, PIN_7};
	for (uint8_t i = 0, j = 0;; i++){

		if (i < 8){
			GPIO_Write_Pin(GPIOA, lista_pinos[i], HIGH);
			HAL_Delay(2000);
			GPIO_Write_Pin(GPIOA, lista_pinos[i], LOW);
			j++;
		} else if (j > 0){
			j--;
			GPIO_Write_Pin(GPIOA, lista_pinos[j], HIGH);
			HAL_Delay(2000);
			GPIO_Write_Pin(GPIOA, lista_pinos[j], LOW);
		//	j--;
		}
	}
}

void questao7(){
		//Verdes A2 e A3
		GPIO_Write_Pin(GPIOA, PIN_2, HIGH); // Acende o vermelho
		GPIO_Write_Pin(GPIOA, PIN_7, HIGH); // Acende o verde
		HAL_Delay(30000);
		GPIO_Write_Pin(GPIOA, PIN_2, LOW); // Apaga o verde
		GPIO_Write_Pin(GPIOA, PIN_4, HIGH); // Acende o amarelo
		HAL_Delay(30000);
		GPIO_Write_Pin(GPIOA, PIN_7, LOW); // Apaga o vermelho
		GPIO_Write_Pin(GPIOA, PIN_4, LOW); // Apaga o amarelo
		GPIO_Write_Pin(GPIOA, PIN_3, HIGH); // Acende um verde
		GPIO_Write_Pin(GPIOA, PIN_6, HIGH); // Acende um vermelho
		HAL_Delay(30000);
 		GPIO_Write_Pin(GPIOA, PIN_3, LOW);
		GPIO_Write_Pin(GPIOA, PIN_5, HIGH);
		HAL_Delay(30000);
		GPIO_Write_Pin(GPIOA, PIN_5, LOW);
		GPIO_Write_Pin(GPIOA, PIN_2, HIGH);
		GPIO_Write_Pin(GPIOA, PIN_6, LOW);
		GPIO_Write_Pin(GPIOA, PIN_7, HIGH);
		HAL_Delay(30000);

		//Amarelos A4 e A5
		//Vermelho A6 e A7
}

void questao8(){
		uint8_t mask[16] = {
		    0b00111111, //00
		    0b00000110, //1
		    0b01011011, //2
		    0b01001111, //3
		    0b01100110, //4
		    0b01101101, //5
		    0b01111101, //6
		    0b00000111, //7
		    0b01111111, //8
		    0b01101111, //9
		    0b01110111, //A
		    0b01111100, //B
		    0b00111001, //C
		    0b01011110, //D
		    0b01111001, //E v
		    0b01110001  //F
		};

		// CRESCENTE
		for (int i = 0; i < 16; i++) {

			GPIO_Write_Port(GPIOA, mask[i]);
			HAL_Delay(5000);
		}
		// DESCRESCENTE
		for (int i = 15; i >= 0; i--) {

			GPIO_Write_Port(GPIOA, mask[i]);
			HAL_Delay(5000   );
		}
}

void questao9(){

	Utility_Init();
	GPIO_Clock_Enable(GPIOA);
	GPIO_Pin_Mode(GPIOA, PIN_0, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_1, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_2, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_3, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_4, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_5, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_6, OUTPUT);
	GPIO_Pin_Mode(GPIOA, PIN_7, OUTPUT);

	GPIO_Clock_Enable(GPIOD);
	GPIO_Pin_Mode(GPIOD, PIN_0, OUTPUT);
	GPIO_Pin_Mode(GPIOD, PIN_1, OUTPUT);

	// Decodificação de display de 7 segmentos com uso de máscaras em matriz
	const uint8_t mask[16]={
		0b00111111, //0
		0b00000110, //1
		0b01011011, //2
		0b01001111, //3
		0b01100110, //4
		0b01101101, //5
		0b01111101, //6
		0b00000111, //7
		0b01111111, //8
		0b01101111, //9
		0b01110111, //A
		0b01111100, //B
		0b00111001, //C
		0b01011110, //D
		0b01111001, //E
		0b01110001}; //F

	while(1){
		for(uint8_t i = 0; i < 16; i++){
			for (uint8_t j = 0; j < 16; j++){
				int32_t cont = 250000;
				while(cont > 0){
					GPIO_Write_Pin(GPIOD, PIN_1, HIGH);
					GPIO_Write_Pin(GPIOD, PIN_0, LOW);
					GPIO_Write_Port(GPIOA, mask[i]);
					Delay_us(1);
					cont--;
					GPIO_Write_Pin(GPIOD, PIN_1, LOW);
					GPIO_Write_Pin(GPIOD, PIN_0, HIGH);
					GPIO_Write_Port(GPIOA, mask[j]);
					Delay_us(1);
					cont--;
				}
			}
		}
		for(int8_t i = 15; i >= 0; i--){
			for (int8_t j = 15; j >= 0; j--){
				int32_t cont = 250000;
				while(cont > 0){
					GPIO_Write_Pin(GPIOD, PIN_1, HIGH);
					GPIO_Write_Pin(GPIOD, PIN_0, LOW);
					GPIO_Write_Port(GPIOA, mask[i]);
					Delay_us(1);
					cont--;
					GPIO_Write_Pin(GPIOD, PIN_1, LOW);
					GPIO_Write_Pin(GPIOD, PIN_0, HIGH);
					GPIO_Write_Port(GPIOA, mask[j]);
					Delay_us(1);
					cont--;
				}
			}
		}
	}

}

void questao10(){

	// Setup

	Utility_Init();
	GPIO_Clock_Enable(GPIOA);
	GPIO_Pin_Mode(GPIOA, PIN_4, OUTPUT);

	GPIO_Clock_Enable(GPIOD);
	GPIO_Pin_Mode(GPIOD, PIN_0, OUTPUT);
	GPIO_Pin_Mode(GPIOD, PIN_1, OUTPUT);
	GPIO_Pin_Mode(GPIOD, PIN_2, OUTPUT);
	GPIO_Pin_Mode(GPIOD, PIN_3, OUTPUT);
	GPIO_Pin_Mode(GPIOD, PIN_4, OUTPUT);
	GPIO_Pin_Mode(GPIOD, PIN_5, OUTPUT);

	LCD_Init(4, 20);

	LCD_Clear();
	LCD_Display_ON();

	char nome1[] = "Papa";
	char nome2[] = "Roach";
	char nome3[] = "lovehatetragedy";

	// Codigo

	while(1){
		for(int i = 10; i >= 0; --i){
			LCD_Clear();
			LCD_Write_String(1, 1, nome1);
			LCD_Write_String(2, 1, nome2);
			LCD_Write_String(3, 1, nome3);
			Delay_ms(500);
			char buffer[3];
			sprintf(buffer, "%d", i);
			LCD_Write_String(4, 1, buffer);
			Delay_ms(1000);
		}
	}


}

void questao11(){

	Utility_Init(); // Inicializa o sistema de clock do STM32. È preciso garantir seu funcionamento correto para garantir a temporização correta do delay.

		//Configura PA4 como saída.
		GPIO_Clock_Enable(GPIOA);
		GPIO_Pin_Mode(GPIOA, PIN_0, OUTPUT); // Sentido horário
		GPIO_Pin_Mode(GPIOA, PIN_1, OUTPUT); // Sentido anti-horário

		GPIO_Pin_Mode(GPIOA, PIN_4, OUTPUT); // PWM

		int tempo_ligado = 0;
		int valor = 200;
		int sentido = 0;

		GPIO_Write_Pin(GPIOA, PIN_0, HIGH);
		GPIO_Write_Pin(GPIOA, PIN_1, LOW);

		while(1){
			GPIO_Write_Pin(GPIOA, PIN_4, HIGH);
			Delay_us(tempo_ligado);
			GPIO_Write_Pin(GPIOA, PIN_4, LOW);
			Delay_us(20000-tempo_ligado);
			tempo_ligado = tempo_ligado + valor;

			if(tempo_ligado >= 20000){
				valor = -200;
				tempo_ligado = 20000;
			}
			if(tempo_ligado <= 0){
				valor = 200;
				tempo_ligado = 0;

				if(sentido == 0){
					GPIO_Write_Pin(GPIOA, PIN_0, LOW);
					GPIO_Write_Pin(GPIOA, PIN_1, HIGH);
					sentido = 1;
				} else {
					GPIO_Write_Pin(GPIOA, PIN_0, HIGH);
					GPIO_Write_Pin(GPIOA, PIN_1, LOW);
					sentido = 0;
				}


			}


		}


}

void questao12(){
	Utility_Init();
	GPIO_Clock_Enable(GPIOA);

	GPIO_Pin_Mode(GPIOA, PIN_0, OUTPUT); //INB1
	GPIO_Pin_Mode(GPIOA, PIN_1, OUTPUT); //INB2
	GPIO_Pin_Mode(GPIOA, PIN_2, OUTPUT); //INA1
	GPIO_Pin_Mode(GPIOA, PIN_3, OUTPUT); //INA2
	GPIO_Pin_Mode(GPIOA, PIN_4, OUTPUT); // PWM1
	GPIO_Pin_Mode(GPIOA, PIN_5, OUTPUT); // PWM2

	while(1){

		for (int i = 0; i < 2; i++){
			for (int i = 0; i < 50; i++){

						// A1 P0
						// A2 P1
						// B1 P2
						// B2 P3
						// PWM1 P4
						// PWM2 P5

						GPIO_Write_Pin(GPIOA, PIN_4, HIGH);
						GPIO_Write_Pin(GPIOA, PIN_5, LOW);
						GPIO_Write_Pin(GPIOA, PIN_2,  LOW);
						GPIO_Write_Pin(GPIOA, PIN_0, HIGH);
						GPIO_Write_Pin(GPIOA, PIN_3,  LOW);
						GPIO_Write_Pin(GPIOA, PIN_1, HIGH);
						Delay_ms(10);

						GPIO_Write_Pin(GPIOA, PIN_4, LOW);
						GPIO_Write_Pin(GPIOA, PIN_5, HIGH);
						GPIO_Write_Pin(GPIOA, PIN_2,  HIGH);
						GPIO_Write_Pin(GPIOA, PIN_0, LOW);
						GPIO_Write_Pin(GPIOA, PIN_3,  LOW);
						GPIO_Write_Pin(GPIOA, PIN_1, HIGH);
						Delay_ms(10);

						GPIO_Write_Pin(GPIOA, PIN_4, HIGH);
						GPIO_Write_Pin(GPIOA, PIN_5, LOW);
						GPIO_Write_Pin(GPIOA, PIN_2,  HIGH);
						GPIO_Write_Pin(GPIOA, PIN_0, LOW);
						GPIO_Write_Pin(GPIOA, PIN_3, HIGH);
						GPIO_Write_Pin(GPIOA, PIN_1, LOW);
						Delay_ms(10);

						GPIO_Write_Pin(GPIOA, PIN_4, LOW);
						GPIO_Write_Pin(GPIOA, PIN_5, HIGH);
						GPIO_Write_Pin(GPIOA, PIN_2,  LOW);
						GPIO_Write_Pin(GPIOA, PIN_0, HIGH);
						GPIO_Write_Pin(GPIOA, PIN_3,  HIGH);
						GPIO_Write_Pin(GPIOA, PIN_1, LOW);
						Delay_ms(10);
					}

		}

		for (int i = 0; i < 50; i++){

			// A1 P0
			// A2 P1
			// B1 P2
			// B2 P3
			// PWM1 P4
			// PWM2 P5

			GPIO_Write_Pin(GPIOA, PIN_4, LOW);
			GPIO_Write_Pin(GPIOA, PIN_5, HIGH);
			GPIO_Write_Pin(GPIOA, PIN_2,  LOW);
			GPIO_Write_Pin(GPIOA, PIN_0, HIGH);
			GPIO_Write_Pin(GPIOA, PIN_3,  HIGH);
			GPIO_Write_Pin(GPIOA, PIN_1, LOW);
			Delay_ms(10);

			GPIO_Write_Pin(GPIOA, PIN_4, HIGH);
			GPIO_Write_Pin(GPIOA, PIN_5, LOW);
			GPIO_Write_Pin(GPIOA, PIN_2,  HIGH);
			GPIO_Write_Pin(GPIOA, PIN_0, LOW);
			GPIO_Write_Pin(GPIOA, PIN_3, HIGH);
			GPIO_Write_Pin(GPIOA, PIN_1, LOW);
			Delay_ms(10);

			GPIO_Write_Pin(GPIOA, PIN_4, LOW);
			GPIO_Write_Pin(GPIOA, PIN_5, HIGH);
			GPIO_Write_Pin(GPIOA, PIN_2,  HIGH);
			GPIO_Write_Pin(GPIOA, PIN_0, LOW);
			GPIO_Write_Pin(GPIOA, PIN_3,  LOW);
			GPIO_Write_Pin(GPIOA, PIN_1, HIGH);
			Delay_ms(10);


			GPIO_Write_Pin(GPIOA, PIN_4, HIGH);
			GPIO_Write_Pin(GPIOA, PIN_5, LOW);
			GPIO_Write_Pin(GPIOA, PIN_2,  LOW);
			GPIO_Write_Pin(GPIOA, PIN_0, HIGH);
			GPIO_Write_Pin(GPIOA, PIN_3,  LOW);
			GPIO_Write_Pin(GPIOA, PIN_1, HIGH);
			Delay_ms(10);

		}

	}

}

void questao13(){

	if (GPIO_Read_Pin(GPIOA, PIN_3) || GPIO_Read_Pin(GPIOA, PIN_4)){
		if (!GPIO_Read_Pin(GPIOA, PIN_3) && GPIO_Read_Pin(GPIOA, PIN_4)){
			GPIO_Write_Pin(GPIOA, PIN_5, HIGH);
		} else if (GPIO_Read_Pin(GPIOA, PIN_3) && !GPIO_Read_Pin(GPIOA, PIN_4)){
			GPIO_Write_Pin(GPIOA, PIN_2, HIGH);
		} else{
			GPIO_Write_Pin(GPIOA, PIN_2, HIGH);
			GPIO_Write_Pin(GPIOA, PIN_5, HIGH);
		}
	} else{
		GPIO_Write_Pin(GPIOA, PIN_2, LOW);
		GPIO_Write_Pin(GPIOA, PIN_5, LOW);
	}
}

void questao14(){
	if (GPIO_Read_Pin(GPIOA, PIN_3)){
		HAL_Delay(1000);
		GPIO_Toggle_Pin(GPIOA, PIN_2);
	}
}

void questao15(){}

void questao16(){}

void questao17(){
	Utility_Init();
	GPIO_Clock_Enable(GPIOA);
	GPIO_Pin_Mode(GPIOA, PIN_3, OUTPUT); // PWM

	GPIO_Clock_Enable(GPIOE);
	GPIO_Pin_Mode(GPIOE, PIN_4, INPUT); // botão 01 - K0
	GPIO_Resistor_Enable(GPIOE, PIN_4, PULL_UP);
	GPIO_Pin_Mode(GPIOE, PIN_3, INPUT); // botão 02 - K1
	GPIO_Resistor_Enable(GPIOE, PIN_3, PULL_UP);

	uint32_t pulsoMin = 500;
	uint32_t pulsoMax = 2500;
	uint32_t pulso = 500;

	while(1){
		Delay_ms(20);
		if(!GPIO_Read_Pin(GPIOE, PIN_4)){
			GPIO_Write_Pin(GPIOA, PIN_3, HIGH);
			Delay_us(pulso);
			GPIO_Write_Pin(GPIOA, PIN_3, LOW);
			if (pulso < pulsoMax)
				pulso++;
		}
		else if(!GPIO_Read_Pin(GPIOE, PIN_3)){
			GPIO_Write_Pin(GPIOA, PIN_3, HIGH);
			Delay_us(pulso);
			GPIO_Write_Pin(GPIOA, PIN_3, LOW);
			if (pulso > pulsoMin)
				pulso--;
		}
		else {
			GPIO_Write_Pin(GPIOA, PIN_3, HIGH);
			Delay_us(pulso);
			GPIO_Write_Pin(GPIOA, PIN_3, LOW);
		}
		Delay_ms(250);
	}
}

void questao18(){

//		Utility_Init();
//		GPIO_Clock_Enable(GPIOA);
//		for (int8_t pinA = 0; pinA < 8; pinA++){
//			GPIO_Pin_Mode(GPIOA, pinA, OUTPUT);
//		}
//
//		GPIO_Clock_Enable(GPIOD);
//		for(int8_t pinD = 0; pinD < 8; pinD++){
//			if (pinD < 4){
//				GPIO_Pin_Mode(GPIOD, pinD, OUTPUT);
//				GPIO_Output_Type(GPIOD, pinD, OPEN_DRAIN);
//				GPIO_Resistor_Enable(GPIOD, pinD, PULL_UP);
//			}
//			else {
//				GPIO_Pin_Mode(GPIOD, pinD, INPUT);
//				GPIO_Resistor_Enable(GPIOD, pinD, PULL_UP);
//			}
//		}
//		// Decodificação de display de 7 segmentos com uso de máscaras em matriz
//		const uint8_t teclado_matricial[4][4]={
//				{
//						0b00000110, //1
//						0b01011011, //2
//						0b01001111, //3
//						0b01110111 //A
//				},
//				{
//						0b01100110, //4
//						0b01101101, //5
//						0b01111101, //6
//						0b01111100 //B
//				},
//				{
//						0b00000111, //7
//						0b01111111, //8
//						0b01101111, //9
//						0b00111001 //C
//				},
//				{
//						0b01110001, // * = F
//						0b00111111, //0
//						0b01111001, // # = E
//						0b01011110 //D
//				}
//		};
//
//		while(1){
//			//Delay_ms(300);
//			for(int8_t linha = 0; linha < 4; linha++){
//				GPIO_Write_Pin(GPIOD, linha, LOW);
//				for(int8_t coluna = 4; coluna < 8; coluna++){
//					while(!GPIO_Read_Pin(GPIOD, coluna)){
//						GPIO_Write_Port(GPIOA, teclado_matricial[linha][coluna - 4]);
//					}
//				}
//				Delay_ms();
//				GPIO_Write_Pin(GPIOD, linha, HIGH);
//				GPIO_Write_Port(GPIOA, LOW);
//			}
//		}


}

void questao19(){
	Utility_Init();
	GPIO_Clock_Enable(GPIOA);
	GPIO_Pin_Mode(GPIOA, PIN_0, OUTPUT); // buzzer
	GPIO_Pin_Mode(GPIOA, PIN_1, OUTPUT); // trig
	GPIO_Pin_Mode(GPIOA, PIN_2, INPUT); // echo

	while(1)
	{
		Delay_ms(10);
		GPIO_Write_Pin(GPIOA, PIN_1, HIGH);
		Delay_us(10);
		GPIO_Write_Pin(GPIOA, PIN_1, LOW);

		uint32_t cont = 30000;

		while(!GPIO_Read_Pin(GPIOA, PIN_2) && cont > 0)
		{
			Delay_us(1);
			cont--;
		}

		uint32_t tempo = 0;
		if (cont > 0){
			while(GPIO_Read_Pin(GPIOA, PIN_2)){
				Delay_us(1);
				tempo++;
			}

			uint32_t distancia = tempo/58;

			if (distancia >= 50){
				GPIO_Write_Pin(GPIOA, PIN_0, LOW);
			}
			else if(distancia < 50 && distancia >= 30){
				GPIO_Write_Pin(GPIOA, PIN_0, HIGH);
				Delay_ms(1000);
				GPIO_Write_Pin(GPIOA, PIN_0, LOW);
				Delay_ms(1000);
			}
			else if (distancia < 30 && distancia >= 10){
				GPIO_Write_Pin(GPIOA, PIN_0, HIGH);
				Delay_ms(300);
				GPIO_Write_Pin(GPIOA, PIN_0, LOW);
				Delay_ms(500);
			}
			else if (distancia < 10){
				GPIO_Write_Pin(GPIOA, PIN_0, HIGH);
			}
		}
	}
}

void questao20(){

	Utility_Init();
		GPIO_Clock_Enable(GPIOA); // Leds
		for(uint8_t pinA = 0; pinA < 4; pinA++){
			GPIO_Pin_Mode(GPIOA, pinA, OUTPUT);
		}
		GPIO_Clock_Enable(GPIOD); // Botões
		for(uint8_t pinD = 0; pinD < 3; pinD++){
			GPIO_Pin_Mode(GPIOD, pinD, INPUT);
		}
		GPIO_Clock_Enable(GPIOE);
		GPIO_Pin_Mode(GPIOE, PIN_3, INPUT);
		GPIO_Resistor_Enable(GPIOE, PIN_3, PULL_UP);

		uint32_t sequencia[32];
		uint16_t faseAtual = 0;

		while(1){
			sequencia[faseAtual] = Random_Number() % 4;
			faseAtual++;
			GPIO_Write_Port(GPIOA, LOW);
			Delay_ms(500);
			for(uint16_t i = 0; i < faseAtual; i++){
				switch(sequencia[i]){
				case 0:
					GPIO_Write_Pin(GPIOA, PIN_0, HIGH);
					break;
				case 1:
					GPIO_Write_Pin(GPIOA, PIN_1, HIGH);
					break;
				case 2:
					GPIO_Write_Pin(GPIOA, PIN_2, HIGH);
					break;
				case 3:
					GPIO_Write_Pin(GPIOA, PIN_3, HIGH);
					break;
				}

				Delay_ms(1000);
				GPIO_Write_Port(GPIOA, LOW); // Manda todos os leds para nivel baixo
				Delay_ms(300);
			}

			GPIO_Write_Port(GPIOA, LOW);

			int8_t roundCompleto = 0;
			uint32_t posicaoSequencia = 0;

			while(roundCompleto == 0){
				GPIO_Write_Port(GPIOA, LOW);
				while(1){
					if (GPIO_Read_Pin(GPIOD, PIN_0)){
						GPIO_Write_Pin(GPIOA, PIN_0, HIGH);
						if (sequencia[posicaoSequencia] == 0){
							posicaoSequencia++;
							if(posicaoSequencia == faseAtual)
								roundCompleto = 1;
							Delay_ms(250);
							break;
						}
						else {
							roundCompleto = -1;
							break;
						}
					}
					else if(GPIO_Read_Pin(GPIOD, PIN_1)){
						GPIO_Write_Pin(GPIOA, PIN_1, HIGH);
						if (sequencia[posicaoSequencia] == 1){
							posicaoSequencia++;
							if(posicaoSequencia == faseAtual)
								roundCompleto = 1;
							Delay_ms(250);
							break;
						}
						else {
							roundCompleto = -1;
							break;
						}

					}
					else if(GPIO_Read_Pin(GPIOD, PIN_2)){
						GPIO_Write_Pin(GPIOA, PIN_2, HIGH);
						if (sequencia[posicaoSequencia] == 2){
							posicaoSequencia++;
							if(posicaoSequencia == faseAtual)
								roundCompleto = 1;
							Delay_ms(250);
							break;
						}
						else {
							roundCompleto = -1;
							break;
						}
					}
					else if(!GPIO_Read_Pin(GPIOE, PIN_3)){
						GPIO_Write_Pin(GPIOA, PIN_3, HIGH);
						if (sequencia[posicaoSequencia] == 3){
							posicaoSequencia++;
							if(posicaoSequencia == faseAtual)
								roundCompleto = 1;
							Delay_ms(250);
							break;
						}
						else {
							roundCompleto = -1;
							break;
						}
					}
				}
			}
			Delay_ms(300);
			GPIO_Write_Port(GPIOA, LOW);
			if (roundCompleto == -1){
				for(int8_t i = 0; i < 4; i++){
					GPIO_Write_Pin(GPIOA, i, HIGH);
					Delay_ms(200);
				}
				faseAtual = 0;
			}
			Delay_ms(1000);
		}
}


void setup(){}


int main(void){



	questao12();

	return 0;

}



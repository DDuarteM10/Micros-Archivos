#include "stm32f4xx.h"                  // Device header
#include "Usart2.h"
#include "stdio.h"
char Datos[40];
int contadorUsart=0;
void IniciarUsart2(void){
	RCC -> APB1ENR |= (1UL<<17); // Enable clock for UART2
	USART2->BRR = 0x683;
	USART2->CR1 = 0x012C;
	USART2->CR1 |= 0x2000;
	GPIOA->MODER |= 0xA0; //PA2 Tx PA3 Rx
	GPIOA->AFR[0] |= 0x7700;
	//NVIC_EnableIRQ(USART2_IRQn);
}
void Enviar4DatosGrafica(float x,float y, float z, float z1){
	int temp=(int)x;
	int pre=(int)y;
	int dis=(int)z;
	int adcaaa=(int)z1;
	sprintf(Datos,"S%d,%d,%d,%d\r\n",temp,pre,dis,adcaaa);
	contadorUsart=0;
	while(Datos[contadorUsart]!=0){
			for(long t=0;t<10000;t++){__NOP();}
			USART2 -> DR=(Datos[contadorUsart]);
			contadorUsart++;
		}
}
void Enviar3DatosGrafica(float x,float y, float z){
	int temp=(int)x;
	int pre=(int)y;
	int dis=(int)z;
	sprintf(Datos,"S%d,%d,%d\r\n",temp,pre,dis);
	contadorUsart=0;
	while(Datos[contadorUsart]!=0){
			for(long t=0;t<10000;t++){__NOP();}
			USART2 -> DR=(Datos[contadorUsart]);
			contadorUsart++;
		}
}
void Enviar2DatosGrafica(float x,float y){
	int temp=(int)x;
	int pre=(int)y;
	sprintf(Datos,"S%d,%d\r\n",temp,pre);
	contadorUsart=0;
	while(Datos[contadorUsart]!=0){
			for(long t=0;t<10000;t++){__NOP();}
			USART2 -> DR=(Datos[contadorUsart]);
			contadorUsart++;
		}
}
void Enviar1DatosGrafica(float x){
	int temp=(int)x;
	sprintf(Datos,"S%d\r\n",temp);
	contadorUsart=0;
	while(Datos[contadorUsart]!=0){
			for(long t=0;t<10000;t++){__NOP();}
			USART2 -> DR=(Datos[contadorUsart]);
			contadorUsart++;
		}
}

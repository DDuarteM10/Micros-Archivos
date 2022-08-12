#include "Usart2.h"
#include "stm32f4xx.h"                  // Device header
#include "stdio.h"
void ConfiguracionUsart2(void){
	RCC -> APB1ENR |= (1UL<<17); // Enable clock for UART2
	USART2->BRR = 0x683; // 9600 baud
	USART2->CR1 = 0x2D; // Usart 2 TX y RX e interrupcion del RX
	GPIOA->AFR[0] |= 0x7700; // Seleccionamos el canal AF8 (UART2) Para pines PA2, PA3
	GPIOA->MODER |= 0xA0;
}

void SendUsart2(char Menu,char valorChart[],int valorInt,float valorFloat){//C para char I para entero F para flotante
	int contadorEnviar=0;
	int contadorEnviar2=0;
	char Enviar[30];
	switch (Menu)
  {
  	case 'C':{
			while(valorChart[contadorEnviar2]!=0){
				Enviar[contadorEnviar2]=valorChart[contadorEnviar2];
				contadorEnviar2++;
			}
			
		}
  		break;{
			}
  	case'I':{sprintf(Enviar,"%d\r\n",valorInt);
		}
  		break;{
			}
		case'F':{sprintf(Enviar,"%0.1f\r\n",valorFloat);
		}
  		break;
  	
  }
	while(Enviar[contadorEnviar]!=0){
			for(long x=0;x<10000;x++){__NOP();}
			USART2 -> DR=(Enviar[contadorEnviar]);
			contadorEnviar++;
		}
}

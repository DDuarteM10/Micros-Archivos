#include "stm32f4xx.h"
#include "math.h"     
#include "stdio.h"
#include "string.h"
int temp, decenas,unidades, contador=0;
long Dela;
int contador2 =0 ;
char variable[30];
int contador3=1; 
char Recibe[30]; int contador_Recorre_RX=0; int z;
 void delay1(void)
	{
		for(Dela=0;Dela<5000;Dela++){__NOP();}
	}
void send_comando(char a){//envia dato
GPIOC->ODR=a|(1UL<<9);
for(int i=0;i<500000;i++){__NOP();}
GPIOC->ODR&=~(1UL<<9);
}
void send_dato(char b){
GPIOC->ODR=b|(3<<8);
for(int i=0;i<500000;i++){__NOP();}
GPIOC->ODR&=~(1UL<<9);
}
void Confi(void){
	RCC -> AHB1ENR |= 0x7; //Activamos los puetros A B c
	RCC -> APB2ENR 	= 0x100; //Habilitamos ADC 1
	GPIOA -> MODER |= 0xA3;//Funcion analoga A0 y alterno A2 Tx y A3 Rx
	GPIOB -> MODER |= 0x5;

	GPIOC -> MODER |= 0x555555;
	//Configuracion ADC
	ADC1 -> CR1 |= 0x0; // 12 bits por defecto
	ADC1 -> CR2 |= 0x1; //Encender ADC
	ADC1 ->CR2 |=ADC_CR2_ADON|ADC_CR2_EXTSEL|ADC_CR2_EXTEN;
	///Configuracion USAR2
	RCC->APB1ENR |= (1UL<<17); // Enable clock for UART2
	USART2->BRR = 0x683; // 9600 baud
	USART2->CR1 = 0x2D; // Enable UART for TX, RX
	GPIOA->AFR[0] |= 0x7700; // select AF8 (UART2) for PA2, PA3 PIN 2 Y 3
	//USART2->CR1    |= 0x0020;      // Enable RX interrupt
	NVIC_EnableIRQ(USART2_IRQn);   // Enable IRQ for UART2 in NVIC
}
void USAR_SEN(long x){//xxxxxxxxxxxxxxx
	USART2 -> DR= x;
	for(int i=0; i<800000; i++);
}
 extern "C"
{
void USART2_IRQHandler(void)    
			{	 
				
				if(USART2->SR & 0x20){
					z=USART2->DR;
					USART2->DR=z;
				}
				
				
			}
		}

		
int main(void){
	Confi();
	
	while(1){
		ADC1->CR2 |= (1UL<<30);//Comenzar la conversion
		temp = (ADC1 -> DR)*8058/100000;
		decenas=temp/10;
		unidades=temp%10;
		sprintf(variable,"%d\r\n",temp);
		
		
		contador2=0;
		/*while(variable[contador2]|=0){
			for(long x=0;x<100000;x++){__NOP();}
			USART2 -> DR=(variable[contador2]);
			contador2++;
		}*/
		}
}
	
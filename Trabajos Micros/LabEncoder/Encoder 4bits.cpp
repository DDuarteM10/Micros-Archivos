# include "stm32f4xx.h"
#include "math.h"
#include "stdio.h"
/*
Pines (8-5)B Mos-LOS
*/

int contador, contador1,x, contador2;
float gradosmin,gradosmax;
int ValorActual;
int ValorAux=0;
char clear=0x01;
char set=0x38;
char disp_on=0x0E;
char mode=0x06;
char ddram1L=0x80;
char ddram2L=0xC0;//de abajo
char a[40];
char Dato_1[7]={'A','n','g','u','l','o',':',};
int CGrados=0;

void send_comando(char f){
GPIOC->ODR=f|(1UL<<9);
for(int i=0;i<50000;i++){__NOP();}
GPIOC->ODR&=~(1UL<<9);//Enable 0
}
void send_dato(char b){
GPIOC->ODR=b|(3<<8);
for(int i=0;i<50000;i++){__NOP();}
GPIOC->ODR&=~(1UL<<9);
}

extern "C"{
void SysTick_Handler (void){
contador++;
	x=(GPIOB-> IDR >> 5);
	switch(x){
		case 0:{
			gradosmin=0.0;
			gradosmax=22.5;
			ValorActual=1;
		break;
		}
		case 1:{
		gradosmin=22.5;
	  gradosmax=45.0;
		ValorActual=2;
			break;
		}
		case 3:{
			gradosmin=45.0;
			gradosmax=67.5;
			ValorActual=3;
			break;
		}
		case 2:{
			gradosmin=67.5;
			gradosmax=90.0;
			ValorActual=4;
			break;
		}
		case 6:{
			gradosmin=90.0;
			gradosmax=112.5;
			ValorActual=5;
			break;
		}
		case 7:{
			gradosmin=112.5;
			gradosmax=135.0;
			ValorActual=6;
			break;
		}
		case 5:{
			gradosmin=135.0;
			gradosmax=157.5;
			ValorActual=7;
			break;
		}
		case 4:{
			gradosmin=157.5;
			gradosmax=180.0;
			ValorActual=8;
			break;
		}
		case 12:{
			gradosmin=180.0;
			gradosmax=202.5;
			ValorActual=9;
			break;
		}
		case 13:{
			gradosmin=202.5;
			gradosmax=225.0;
			ValorActual=10;
			break;
		}
		case 15:{
			gradosmin=225.0;
			gradosmax=247.5;
			ValorActual=11;
			break;
		}
		case 14:{
			gradosmin=247.5;
			gradosmax=270.0;
			ValorActual=12;
			break;
		}
		case 10:{
			gradosmin=270.0;
			gradosmax=292.5;
			ValorActual=13;
			break;
		}
		case 11:{
			gradosmin=292.5;
			gradosmax=315.0;
			ValorActual=14;
			break;
		}
		case 9:{
			gradosmin=315.0;
			gradosmax=337.5;
			ValorActual=15;
			break;
		}
		case 8:{
			gradosmin=337.5;
			gradosmax=360.0;
			ValorActual=16;
			break;
		}
	
	}
if(ValorActual==ValorAux){
	ValorAux=ValorActual;
}
if(ValorActual>ValorAux){
	ValorAux=ValorActual;
	CGrados++;
}
if(ValorActual<ValorAux){
	ValorAux=ValorActual;
	CGrados--;
}
if(CGrados>360){
	
	CGrados=0;
}
if(CGrados<0){
	
	CGrados=360;
}
	if (contador==100){
		
		
		
		//x&=15;
		contador=0;
	}
}



}
int main(void){
RCC->AHB1ENR |=7;
GPIOB->MODER |=0x0;
GPIOB->PUPDR   |=0x0;
GPIOB->PUPDR   |=0x400;
GPIOB->OSPEEDR |=0x7FC;
GPIOC->MODER|=0X55555;

SysTick_Config( SystemCoreClock/1000 );
	SystemCoreClockUpdate();
	
send_comando(clear); 
send_comando(set);
send_comando(disp_on);
send_comando(mode);
send_comando(ddram1L);
for(int conteo=0;conteo<7;conteo++){
send_dato(Dato_1[conteo]);
}

while(1){

 sprintf(a, "=%d      ",CGrados );
 contador2=0;
 send_comando(ddram2L);
 while(a[contador2]!=0){
 send_dato(a[contador2]);
 contador2++;
}
 send_comando(ddram2L);
}
}
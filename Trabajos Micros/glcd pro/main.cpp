#include "stm32f4xx.h"                  // Device header
#include "GLCD.h"
#include "stdio.h"
float val=2.14;
char numero [10];
void IniciarSTm32F4(void){
	RCC->AHB1ENR = 0x7;
}
int main(void){
	IniciarSTm32F4();
	IniciarGLCD();
	sprintf(numero,"%0.3f",val);
	EscribirTexto(1,1,0,numero,1);
	
	
	while(1){
	}
}

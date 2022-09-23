#include "Nokia.h"
#include "stm32f4xx.h"                  // Device header
#include "stdio.h"
int main (void){
	RCC->AHB1ENR |= 0x7;
	Nokia_5110(0xD5);
	for(int time=0;time<150000;time++){__NOP();}
	Escribir_nokia_0(1,0,0,"Habia ",1);
		
		
	while(1){
		
		
	}
}
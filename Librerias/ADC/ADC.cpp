#include "ADC.h"
#include "stm32f4xx.h"                  // Device header
#include"math.h"
int ValADC1=0;
void ConfiguracionADC(void){
	RCC->APB2ENR |=RCC_APB2ENR_ADC1EN; // Activo el reloj del ADC1
	ADC1->CR1 |=0x20; // Activo la interrupcion del ADC		
	ADC1->CR2|= (1UL<<10); // Interrupcion individual
	ADC1->CR2|= 0x01;      // ADON es para inicial el ADC
	ADC1-> SQR3 = 7;
	//Configurar la entrada del ADC
	GPIOA->MODER |=0xC000;
}
/*
		Canal 	|		Pin
			1			|		Pa1		
			2			|		Pa2
			3			|		Pa3
			4			|		Pa4
			5			|		Pa5
			6			|		Pa6
			7			|		Pa7
		 10			|		Pc0
		 11			|		Pc1
		 12			|		Pc2
		 13			|		Pc3
		 14			|		Pc4
		 15			|		Pc5
*/
void LeerADC1(void){
	ADC1-> CR2 |=(1UL<<30);
	while((ADC1->SR & 0x20)==1){__NOP();}
	ValADC1=ADC1 ->DR;
	ValADC1=ValADC1*3300/4095;
	ValADC1=ValADC1*100/3300;
}

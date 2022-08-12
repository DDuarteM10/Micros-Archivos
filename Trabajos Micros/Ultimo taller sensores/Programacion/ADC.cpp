#include "ADC.h"
#include "stm32f4xx.h"                  // Device header

void ConfiguracionADC(void){
	RCC -> APB2ENR 	|= 0x100; //Habilitamos ADC 1
	ADC1 -> CR1 |= 0x0; // 12 bits por defecto
	ADC1 -> CR2 |= 0x1; //Encender ADC
	ADC1 -> CR2 |=ADC_CR2_ADON|ADC_CR2_EXTSEL|ADC_CR2_EXTEN;
	ADC1->CR1 |=0x20; // Activo la interrupcion del ADC	
	NVIC_EnableIRQ(ADC_IRQn); // Activo el vector de interrupciones para el ADC
	ADC1-> SQR3 = 0;
}
//void LeerADC1(void){
//}
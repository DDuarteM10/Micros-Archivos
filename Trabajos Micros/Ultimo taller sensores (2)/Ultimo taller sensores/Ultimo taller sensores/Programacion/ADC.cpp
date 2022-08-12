#include "ADC.h"
#include "stm32f4xx.h"                  // Device header

void ConfiguracionADC(void){
	RCC->APB2ENR |=RCC_APB2ENR_ADC1EN; // Activo el reloj del ADC1
	ADC1->CR1 |=0x20; // Activo la interrupcion del ADC		
	ADC1->CR2|= (1UL<<10); // Interrupcion individual
	ADC1->CR2|= 0x01;      // ADON es para inicial el ADC
	NVIC_EnableIRQ(ADC_IRQn); // Activo el vector de interrupciones para el ADC
	ADC1-> SQR3 = 7;
	GPIOA->MODER |=0xC000;
}
//void LeerADC1(void){
//}
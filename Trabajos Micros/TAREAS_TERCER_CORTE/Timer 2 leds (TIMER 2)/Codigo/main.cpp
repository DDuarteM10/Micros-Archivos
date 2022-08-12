#include "math.h"                   // ARM::CMSIS:DSP
#include "stm32f4xx.h"                  // Device header

/*Variables*/
float contador1=0.0,contador2=00;;
/*Configuracion*/
void configuracion(void){
	RCC->AHB1ENR |=0x7;//Habilita Clock PTA a PTC
	RCC->APB1ENR |=RCC_APB1ENR_TIM2EN;//Habilita clock TIM3
	//RCC->APB2ENR |=0x800;//Habilita clock TIM1
	GPIOA->OSPEEDR =1;
	GPIOA->MODER |=0x5555;//PTA=OUT
	//GPIOA->OTYPER |=0x0;
	
	NVIC_EnableIRQ(TIM2_IRQn);
	//GPIOA->AFR[1] |=0x0200000;//AF2 para PA0 (0010)
	TIM2->ARR=60000;//ARR (0->65536)
	TIM2->DIER |=0x0001;//Habilitar Interrupción
	TIM2->CR1 |=0x0001;//Habilita Conteo
	TIM2->PSC=65;
}
/*Interrupciones*/
extern "C"{
	void TIM2_IRQHandler(void){
		TIM2->SR &= ~TIM_SR_UIF;
		contador1+=0.5;
		contador2+=0.5;
		if(contador1==0.5){
			GPIOA->ODR= (~(GPIOA->IDR) &(1UL));
			contador1=0.0;
		}
		
		if(contador2==2.5){
			GPIOA->ODR= (~(GPIOA->IDR) &(1UL<<1));
			contador2=0.0;
		}
		
		}
	
		
}
int main(void){
	configuracion();
	while(1){
		
			
	}
}
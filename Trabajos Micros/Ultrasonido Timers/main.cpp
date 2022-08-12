#include "stm32f4xx.h"                  // Device header
#include "HCSR04.h"
#include "math.h"
// ********** VARIABLES GLOBALES ****
// Variables Sensor adelante
short tiempo_adelante=0;
float distancia_adelante=0;
int Val=0;
extern "C"{
	void TIM3_IRQHandler(void){
		TIM3->SR &=~0x04; 
		if((GPIOA->IDR & 0x40)==0x40){ 
			tiempo_adelante=TIM3->CCR1; 
		}else{ 
			tiempo_adelante=float(TIM3->CCR1-tiempo_adelante); 
			TIM3->EGR |=0x01; 
			if(tiempo_adelante>0){
				distancia_adelante=float(tiempo_adelante)/58.0; // Calculo la distancia del sensor
			}				
		}
	}
	void TIM4_IRQHandler(void){
		TIM4->SR &= ~TIM_SR_UIF;
		GPIOA->ODR = ~(GPIOA->IDR  & (1UL));
		Val++;
	}
}
int main(void){
	RCC->AHB1ENR |=7; // Activo el Puerto A, B y C
	NVIC_EnableIRQ(TIM3_IRQn);
	NVIC_EnableIRQ(TIM4_IRQn);
	IniciarTimerX();
	while(1){
		__NOP();
	}
}
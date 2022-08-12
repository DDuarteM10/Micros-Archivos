#include "stm32f4xx.h"                  // Device header
#include "Nokia.h"
#include "HCSR04.h"
#include "stdio.h"

void iniciarSTM4(void){
	RCC->AHB1ENR |=7; // Activo el Puerto A, B y C
	NVIC_EnableIRQ(TIM3_IRQn);
	NVIC_EnableIRQ(TIM4_IRQn);
	Nokia_5110(0xD5);
	IniciarTimerX();
	
}
extern "C"{
	void TIM3_IRQHandler(void){
		TIM3->SR &=~0x04; 
		if((GPIOA->IDR & 0x40)==0x40){ 
			tiempo_adelante=TIM3->CCR1;
		}else{ 
			tiempo_adelante=float(TIM3->CCR1-tiempo_adelante); 
			TIM3->EGR |=0x01; 
			if(tiempo_adelante>0){
				Distancia_Sensor=float(tiempo_adelante)/58.0; // Calculo la distancia del sensor
			}				
		}
	}
	void TIM4_IRQHandler(void){
		TIM4->SR &= ~TIM_SR_UIF;
		GPIOA->ODR = ~(GPIOA->IDR  & (1UL));
	}
}
int main(void){
	iniciarSTM4();
	Escribir_nokia_0(1,0,0,"Distancia",1);
	while(1){
		SepararDatos(0,Distancia_Sensor,2,0,2);
	}
}

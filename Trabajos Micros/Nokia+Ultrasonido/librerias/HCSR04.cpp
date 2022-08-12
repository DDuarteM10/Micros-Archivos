#include "stm32f4xx.h"                  // Device header
#include "HCSR04.h"

/*
Entrada PWM tim 3 CH1 PA6 AF02 Eco
Salida PA0 Trimer cada 10 ms
Entrada del Echo PA6
NVIC_EnableIRQ(TIM3_IRQn);
NVIC_EnableIRQ(TIM4_IRQn);
*/

void IniciarTimerX(void){
	//leer sensor  
	GPIOA->MODER |=0x05; // Pines 0 y 1 salida digital
	GPIOA->OSPEEDR |=0x05; // Pines 0 y 1 salida digital
	GPIOA->PUPDR |=0x05; // Pines 0 y 1 salida digital
	///
	// Sensor adelante // cambiar por AAA tim 1 
	GPIOA->MODER |=0x2000; // Pin 6 
	GPIOA->AFR[0] |=0x2000000; // Pin 6 
	
	
	//leer eco
	RCC->APB1ENR |=RCC_APB1ENR_TIM3EN; // Activo el reloj del tim 3
	TIM3->PSC =15; // Frecuencia de conteo cada 1MHz
	TIM3->ARR =20000; // Periodo de conteo de 20ms
	TIM3->CCMR1 =0x01; // Input caal 1
	TIM3->CCER |=0x0B; // La captura del canal 1 y 2 se hara en los flancos de subida y bajada
	TIM3->DIER |=0x02; // Activo la interrupcion por captura canal 1
	TIM3->CR1 |=TIM_CR1_CEN; // Activo el contador
	
	//Enviar tring
	RCC->APB1ENR |=RCC_APB1ENR_TIM4EN; // Activo el reloj del timer
	TIM4->PSC =15; // Conteo a 1MHz
	TIM4->ARR = 20000; // Maximo conteo 1000 
	TIM4->CCER |=0x1111; // Activo el canal 1 y 2 como salida 
	TIM4->CCMR1 |=0x6060; // PWM canal 1 y 2
	TIM4->CR1 |=0x01; // Activo el timer 
	TIM4->DIER |=0x0001;//Habilitar Interrupción
	
	
}

/*Incluir los siguientes copdigos en el external C
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
	}
}
*/




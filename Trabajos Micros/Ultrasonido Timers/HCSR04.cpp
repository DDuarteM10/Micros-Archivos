#include "stm32f4xx.h"                  // Device header
#include "HCSR04.h"
/*
Entrada PWM tim 3 CH1 PA6 AF02 Eco
Salida PA0 Trimer cada 10 ms
Entrada del Echo PA6

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


///* CONEXIONES 
//	PA0->PWM Motor A
//	PA1->PWM Motor B
//	PA2->Servo adelante 
//	PA3->Servo atras
//	
//	PA6-> Echo adelante

//	PB0-> Pin 1 Motor A (Derecha)
//	PB1-> Pin 2 Motor A (Derecha)
//	
//	PB2-> Pin 1 Motor B (Izquierda)
//	PB3-> Pin 2 Motor B (Izquierda)	
//	
//	PB6-> Echo atras
//	
//	PC0 -> Trigger 1
//	PC1 -> Trigger 2
//*/

//// ********** LIBRERIAS *******
//	#include <stdio.h>
//	#include "STM32F4xx.h"
//// ********************

//// ********** VARIABLES GLOBALES ****
//// Variables Sensor adelante
//short tiempo_adelante=0;
//float distancia_adelante=0;

//// Variables Sensor de atras
//short tiempo_atras=0;
//float distancia_atras=0;
//bool direccion=0; 
//short contador_servo=0;
//bool direccion_servo=0;
//// ********************

//// ********** FUNCIONES *******
//void derecha(){
//	GPIOB->ODR =0x07; 
//}
//void izquierda(){
//	GPIOB->ODR =0x0D; 
//}
//void alfrente(){
//	GPIOB->ODR=0x05; 
//}	
//void reversa(){
//	GPIOB->ODR =0x0A;  
//}
//// ********************

//// ********** INTERRUPCIONES ****
//extern "C"{
//	void TIM3_IRQHandler(void){
//		TIM3->SR &=~0x04; 
//		if((GPIOA->IDR & 0x40)==0x40){ 
//			tiempo_adelante=TIM3->CCR1; 
//		}else{ 
//			tiempo_adelante=float(TIM3->CCR1-tiempo_adelante); 
//			TIM3->EGR |=0x01; 
//			if(tiempo_adelante>0){
//				distancia_adelante=float(tiempo_adelante)/58.0; // Calculo la distancia del sensor
//			}				
//		}
//	}
//	void TIM4_IRQHandler(void){
//		TIM4->SR &=~0x04; 
//		if((GPIOB->IDR & 0x40)==0x40){ 
//			tiempo_atras=TIM4->CCR1; 
//		}else{ 
//			tiempo_atras=float(TIM3->CCR1-tiempo_atras); 
//			TIM3->EGR |=0x01; 
//			if(tiempo_atras>0){
//				distancia_atras=float(tiempo_atras)/58.0; // Calculo la distancia del sensor
//			}				
//		}
//	}
//	void SysTick_Handler(void){
//		if(direccion_servo==0){
//			contador_servo+=10;
//			if(contador_servo>180){
//				contador_servo=180;
//				direccion_servo=1;
//			}
//		}else{
//			contador_servo-=10;
//			if(contador_servo<0){
//				contador_servo=0;
//				direccion_servo=0;
//			}
//		}
//		
//		TIM2->CCR3=float(contador_servo*(1500/180)) + 500;  // Servo adelante 
//		TIM2->CCR4=float((180-contador_servo)*(1500/180)) + 500;  // Servo atras
//	}
//}		
//// ********************	

//// ********** MAIN ********
//int main(void){
//	// ********** PUERTOS *******
//			RCC->AHB1ENR |=0x07; // Activo el Puerto A, B y C
//	// ******************

//	// ********** PINES *******
//			// PWM Puente H y servos 
//			GPIOA->MODER |=0xAA; // Pin 0 a 3 alternante 
//			GPIOA->AFR[0]=0x1111; // Pin 0 a 3 AF1
//	
//			// Sensor adelante
//			GPIOA->MODER |=0x2000; // Pin 6 
//			GPIOA->AFR[0] |=0x2000000; // Pin 6 
//	
//			// Direccion Puente H
//			GPIOB->MODER |=0x55; // Pines 0 a 3 salida digital
//			GPIOB->OSPEEDR |=0x55; // Pines 0 a 3 Velocidad media 
//			GPIOB->PUPDR |=0x55; // Pines 0 a 3 Pull-up
//	
//			// Sensor atras
//			GPIOB->MODER |=0x2000; // Pin 6 
//			GPIOB->AFR[0] |=0x2000000; // Pin 6 
//			
//			// Trigger sensores
//			GPIOC->MODER |=0x05; // Pines 0 y 1 salida digital
//			GPIOC->OSPEEDR |=0x05; // Pines 0 y 1 salida digital
//			GPIOC->PUPDR |=0x05; // Pines 0 y 1 salida digital
//	// ******************
//	
//	// ********** TIMERS ********
//			RCC->APB1ENR |=RCC_APB1ENR_TIM2EN; // Activo el reloj del timer
//			TIM2->PSC =15; // Conteo a 1MHz
//			TIM2->ARR = 20000; // Maximo conteo 1000 
//			TIM2->CCER |=0x1111; // Activo el canal 1 y 2 como salida 
//			TIM2->CCMR1 |=0x6060; // PWM canal 1 y 2
//			TIM2->CR1 |=0x01; // Activo el timer 
//	
//			RCC->APB1ENR |=RCC_APB1ENR_TIM3EN; // Activo el reloj del tim 3
//			TIM3->PSC =15; // Frecuencia de conteo cada 1MHz
//			TIM3->ARR =20000; // Periodo de conteo de 20ms 
//			TIM3->CCMR1 =0x01; // Input caal 1
//			TIM3->CCER |=0x0B; // La captura del canal 1 y 2 se hara en los flancos de subida y bajada
//			TIM3->DIER |=0x02; // Activo la interrupcion por captura canal 1
//			TIM3->CR1 |=TIM_CR1_CEN; // Activo el contador
//			NVIC_EnableIRQ(TIM3_IRQn);
//			
//			RCC->APB1ENR |=RCC_APB1ENR_TIM4EN; // Activo el reloj del tim 4
//			TIM4->PSC =15; // Frecuencia de conteo cada 1MHz
//			TIM4->ARR =20000; // Periodo de conteo de 20ms 
//			TIM4->CCMR1 =0x01; // Input caal 1
//			TIM4->CCER |=0x0B; // La captura del canal 1 y 2 se hara en los flancos de subida y bajada
//			TIM4->DIER |=0x02; // Activo la interrupcion por captura canal 1
//			TIM4->CR1 |=TIM_CR1_CEN; // Activo el contador
//			NVIC_EnableIRQ(TIM4_IRQn);
//	// ******************		
//	
//	// ********** BUCLE *******
//			SystemCoreClockUpdate();
//			SysTick_Config(SystemCoreClock/10); 
//	// ******************
//	
//	// ********** BUCLE *******
//			while(true){
//				GPIOC->ODR =0x03; // Pongo en alto el pin 
//				for(short i=0; i<600; i++); // Tiempo de espera del pulso 
//				GPIOC->ODR =0; // Pongo en bajo el pin 
//				for(int i=0; i<100000; i++); // Tiempo de espera entre pulsos
//				
//				if(distancia_adelante>15){ 
//					reversa();
//					if(distancia_atras>20){
//						for(int i=0; i<1000000; i++);
//					}
//					if(direccion==1){
//						derecha();
//					}else{
//						izquierda();
//					}
//					for(int i=0; i<1000000; i++);
//					alfrente(); 
//				}
//			}
//	// ******************	
//}
//// ********************

#include "stm32f4xx.h"                  // Device header
#include "Timer.h"
void IniciarPwmTimer4(void){
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	TIM4->ARR = 20000;
	TIM4->PSC = 15;
	 //reinicia el contador 
	TIM4 -> CCMR1 |= 0X6060;
	TIM4 -> CCMR2 |= 0X6060;
	//TIM4->CCR1 = 0;
//	TIM4->CCR2 = 0;
//	TIM4->CCR3 = 0;
//	TIM4->CCR4 = 0;
	TIM4->CCER |= 0X1111;
	TIM4->CR1 |= 1;
	TIM4 ->CCER |=0x1111;
	TIM4->CCR3 = 50;
	
	//configuracion pines del PB6 al PB9
	GPIOB->MODER |= 0xAA000;
	GPIOB->OSPEEDR |= 0x55000;
	GPIOB->PUPDR |= 0x00055000;//pull up (01) PTB6 a PTB9
	GPIOB->AFR[0]|=0x22000000;//AF2 (0010)
	GPIOB->AFR[1]|= 0x22;
	TIM4->EGR |= 1;
}
void CambiarCicloUtilTimer4(int val){
	TIM4->CCR1 = val;
}
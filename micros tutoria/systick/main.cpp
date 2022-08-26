#include "stm32f4xx.h"                  // Device header
extern "C"{
	void SysTick_Handler (void){
		GPIOA->ODR=(1 & ~(GPIOA->ODR));
	}
}
int main(){
	RCC -> AHB1ENR = 7;
	GPIOA -> MODER |= 0x1;
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/100);
	while(1){
		__NOP();
	}
}
#include "stm32f4xx.h"                  // Device header
// pines carro 
//RX PA11 TX PA12
//Motores 
//IN1 PC0 IN2 PC1 IN3 PC2 IN4 PC3
// pin A11TX  y A12RX
char Entrada;
int Derecho=0x6, Atras=0x9, Izquierda=0x4,Derecha=0x2;
//configuracion
void configuracion(void){
		RCC->AHB1ENR = 0x7;
    //USART6 
    RCC->APB2ENR = (1UL << 5);
    USART6->BRR = 0x683;
    USART6->CR1 = 0x12C;
    USART6->CR1 |= 0x2000;
    NVIC_EnableIRQ(USART6_IRQn);
    GPIOA->MODER |= 0xAA00000;
		GPIOC->MODER |= 0x55555;
    GPIOA->AFR[1] = 0x88000;
}
extern "C"{
	void USART6_IRQHandler(void) {
		if (USART6->SR & 0x20) {
        Entrada = USART6->DR;
		}
    
	}
		}
int main(void){
	configuracion();
	while(1){
		switch (Entrada) {
        case 'F'://Derecho
				GPIOC->ODR =Derecho;
        break;
        case 'B'://Atrás
        GPIOC->ODR =Atras;
        break;
        case 'R'://Derecha
        GPIOC->ODR =Derecha;
        break;
        case 'L'://Izquierda
        GPIOC->ODR =Izquierda;
        break;
        case 'S': 
				GPIOC->ODR =0;
        break;
        case 'G'://diagonal izquierda
        GPIOC->ODR =Derecho;
				for(int time=0;time<300000;time++){__NOP();}
				GPIOC->ODR =Izquierda;
				for(int time=0;time<200000;time++){__NOP();}
        break;
        case 'I':
        GPIOC->ODR =Derecho;
				for(int time=0;time<300000;time++){__NOP();}
				GPIOC->ODR =Derecha ;
				for(int time=0;time<200000;time++){__NOP();}
        break;
        case 'l':
        
        break;
        default:__NOP() ;

    }
	}
	
    
    
}


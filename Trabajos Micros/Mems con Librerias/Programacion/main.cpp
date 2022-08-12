/*
Codigo para Laboratorio de sensores
creado por: Melanie Gabriela Polo
						David Alejandro Duarte Montañez
Configuacion de los pines
	I2C1_SCL Pin PB6
	I2C1_SDA pin PB7  Canales F04
	Grafica LCD 
	E PC11
	RS PC10 
	[D0-PC0->D7 PC7]
	C1 PC8
	C2 PC9
	
*/
#include "stm32f4xx.h"                  // Device header
#include "I2C.h"												//Device by david :D
#include "SensorTHP.h"												//Device by david :D
#include "Delay.h"
void IniciarSTM(void){
	RCC->AHB1ENR |= 7; //Puertos A,B,C
	GPIOB->MODER |= 0xA000; // Funciones especiales P7 y P6
	GPIOB->AFR[0] |= 0x44000000; // canales F4 para P6 y P7
	GPIOB->PUPDR |= 0xA000; //para I2C
	GPIOB->OSPEEDR |= 0;
	GPIOB->OTYPER |= 0xC0;//para I2C
}
int main (void){
	IniciarSTM();
	IniciarI2C();
	IniciarADX();
	
	while(1){
	LeerX();
	CalcularAngulo();
	}
	
}
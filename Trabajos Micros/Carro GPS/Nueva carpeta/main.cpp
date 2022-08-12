/*Codigo para Carro utilizando el sensor HY-271
 Configuacion de los pines
	I2C1_SCL Pin PB6
	I2C1_SDA pin PB7  Canales F04
	SDO GND
	Grafica LCD 
	E PC11
	RS PC10 
	[D0-PC0->D7 PC7]
	C1 PC8
	C2 PC9 */
#include "stm32f4xx.h"                  // Device header
#include "I2C.h"												//Devoce by david :D
#include "Delay.h"
#include "GY-271.h"
void IniciarSTM32F4(void){
	RCC->AHB1ENR |= 7; //Puertos A,B,C
}
int main(void){
	IniciarSTM32F4();
	IniciarI2C();
	IniciarGY271();
	while(1){
		ReadGY271();
		
		if(){
		}
	}
}

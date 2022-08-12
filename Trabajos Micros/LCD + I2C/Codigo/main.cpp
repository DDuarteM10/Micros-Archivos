#include "stm32f4xx.h"                  // Device header
#include "LcdI2c.h"
#include "Delay.h"
#include "I2C.h"
#include "stdio.h"
void IniciarStmF4(void){
	RCC->AHB1ENR |=7;
}
int main(void){
	IniciarStmF4();
	IniciarI2C();
	IniciarLCdConI2C();
	EnviarString("Micros Mecaaaaaa ",1,0);
	while(1){
		
	}
	}
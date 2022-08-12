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
	
	/*pines que si son xd
Motores 
IN1 PC0 IN2 PC1 IN3 PC2 IN4 PC3
	*/
#include "stm32f4xx.h"                  // Device header
#include "I2C.h"												//Devoce by david :D
#include "Delay.h"
#include "GY-271.h"
#include "math.h"
int Iniciox=490,InicioY=-260;
int PasoActualX,PasoActualY;
int Paso2X=510,Paso2Y=-200;
int Paso3X=86,Paso3Y=-305;
int Paso4X=250,Paso4Y=-350;
int Steps=0;
int angulo1=309;
int angulo2=287;
int AnguloActual;
bool condicionInicio=0;
int Derecho=0x6, Atras=0x9, Izquierda=0x4,Derecha=0x2;

void IniciarSTM32F4(void){
	RCC->AHB1ENR |= 7; //Puertos A,B,C
	GPIOC->MODER |= 0x55555;
	
}
int main(void){
	IniciarSTM32F4();
	IniciarI2C();
	IniciarGY271();
	
	while(1){
		ReadGY271();
		PasoActualX=x;
		PasoActualY=y;
		AnguloActual=180.0*atan2(y,x)/3.1416;
		if(AnguloActual<0){AnguloActual=AnguloActual+360;}
		
		if((~GPIOC-> IDR & 0x2000)==0x2000){//iniciar recorrido
			condicionInicio=1;
		}
		if(condicionInicio==1){
			switch (Steps)
			{
				case 0:{
					GPIOC->ODR = Derecho;
//					Dalay(46200000);
//					GPIOC->ODR = 0;
//					Dalay(150);
					
					if(PasoActualX<Paso2X && PasoActualY>=Paso2Y ){// ||
						GPIOC->ODR = 0;
						Steps++;
					}
					
				}
					break;
				case 1:{
					GPIOC->ODR = Derecha;
					Dalay(2200000);
					GPIOC->ODR = 0;
					Steps++;
////					if(AnguloActual){
////						GPIOC->ODR = 0;
////						Steps++;
////					}
					
				}
					break;
				case 2:{
					GPIOC->ODR = Derecho;
//					Dalay(28000000);
//					GPIOC->ODR = 0;
//					Dalay(150);
					if(PasoActualX<Paso3X && PasoActualY>=Paso3Y ){// ||
						GPIOC->ODR = 0;
						Steps++;
					}
					
//					
					
				}
					break;
				case 3:{
					
				}
					break;
				case 4:{
					GPIOC->ODR = Izquierda;
//					Dalay(3500000);
//					GPIOC->ODR = 0;
//					Dalay(150);
					if(PasoActualX>=Paso4X ||PasoActualY<=Paso4Y ){
						GPIOC->ODR = 0;
						Steps++;
					}
					
				}
				
			}
		}
		
		
	}
}

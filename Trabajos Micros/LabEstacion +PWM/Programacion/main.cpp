/*
Ultimo laboratorio de sensores
Estacion meteorologica Elaborado por: David Duarte
																			Melanie Polo
Configuacion de los pines
	I2C1_SCL Pin PB6
	I2C1_SDA pin PB7  Canales F04
	SDO GND
	ADC1 PA7
	Grafica LCD 
	E PC11
	RS PC10 
	[D0-PC0->D7 PC7]
	C1 PC8
	C2 PC9
	
	
*/
#include "stm32f4xx.h"                  // Device header
#include "I2C.h"												//Device by david :D
#include "Delay.h"											//Device by david :D
#include "MBE280.h"
#include "GLCD.h"
#include "math.h" 
#include "ADC.h"
void IniciarStm32F4(void){
	RCC->AHB1ENR |= 7; //clock de puertos A B C
	//configuracion Puerto B para I2C1
	GPIOB->MODER |= 0xA000; // Funciones especiales P7 y P6
	GPIOB->AFR[0] |= 0x44000000; // canales F4 para P6 y P7
	GPIOB->PUPDR |= 0xA000; //para I2C
	GPIOB->OSPEEDR |= 0;
	GPIOB->OTYPER |= 0xC0;//para I2C
	
}
void SepararDAtos(float valor,int menu){//1 Temperatura 2 Presion 3 Velocidad 4 luz 5 rh
	int unidades=0;
	int decenas=0;
	int centenas=0;
	int milares=0;
	switch (menu)
  {
  	case 1:{
			comandoGLCD(2,setY|40);
			comandoGLCD(2, 1 | setX);
			decenas=((valor/10.0));
			unidades=(int)((valor-(decenas*10.0))/1);
			for(int j = 0; j < 8; ++j)
       {  SendGLCD(2,NUM[decenas][j]);}   // para mostrar los numeros de que necesite de 4 bits
			 for(int j = 0; j < 8; ++j)          // a la variable le saca unidades decenas y centenas
       {  SendGLCD(2,NUM[unidades][j]);}
			 for(int f=0;f<4;f++){SendGLCD(2,GradosChar[f]);}
		}
  		break;
  	case 2:{
			comandoGLCD(2,setY|5);
			comandoGLCD(2, 2 | setX);
			milares=(int)(valor/1000.0);
			centenas=(int)((valor-(milares*1000))/100.0);
			decenas=(int)((valor-(milares*1000.0+centenas*100.0))/10.0);
			unidades=(int)((valor-(milares*1000.0+centenas*100.0+decenas*10.0))/1.0);
			for(int j = 0; j < 8; ++j)
       {  SendGLCD(2,NUM[milares][j]);}
			for(int j = 0; j < 8; ++j)
       {  SendGLCD(2,NUM[centenas][j]);}   
			for(int j = 0; j < 8; ++j)
       {  SendGLCD(2,NUM[decenas][j]);}   // para mostrar los numeros de que necesite de 4 bits
			 for(int j = 0; j < 8; ++j)          // a la variable le saca unidades decenas y centenas
       {  SendGLCD(2,NUM[unidades][j]);}
			 for(int j = 0; j < 8; ++j){
			 SendGLCD(2,LH[j] );}
			 for(int j = 0; j < 8; ++j){
			 SendGLCD(2,LP[j] );}
			 for(int j = 0; j < 8; ++j){
			 SendGLCD(2,LA[j] );}
			  
			 
		}
  		break;
		case 3:{
			comandoGLCD(1,setY|19);
			comandoGLCD(1, 5 | setX);
		}
  		break;
  	case 4:{
			comandoGLCD(2,setY|40);
			comandoGLCD(2, 4 | setX);
			decenas=((valor/10.0));
			unidades=(int)((valor-(decenas*10.0))/1);
			for(int j = 0; j < 8; ++j)
       {  SendGLCD(2,NUM[decenas][j]);}   // para mostrar los numeros de que necesite de 4 bits
			 for(int j = 0; j < 8; ++j)          // a la variable le saca unidades decenas y centenas
       {  SendGLCD(2,NUM[unidades][j]);}
			for(int j = 0; j < 8; ++j){
			SendGLCD(2,PorcentajeChar[j] );}
		
		}
  		break;
		case 5:{
			comandoGLCD(2,setY|40);
			comandoGLCD(2, 5 | setX);
			decenas=((valor/10.0));
			unidades=(int)((valor-(decenas*10.0))/1);
			for(int j = 0; j < 8; ++j)
       {  SendGLCD(2,NUM[decenas][j]);}   // para mostrar los numeros de que necesite de 4 bits
			 for(int j = 0; j < 8; ++j)          // a la variable le saca unidades decenas y centenas
       {  SendGLCD(2,NUM[unidades][j]);}
			for(int j = 0; j < 8; ++j){
			SendGLCD(2,PorcentajeChar[j] );}
		}
  		break;
  	
  }
}
 int main (void){
	IniciarStm32F4();
	IniciarI2C();
	IniciarBME280();
	IniciarGLCD();
	ImprimirTemperatura();
	ConfiguracionADC();
	
	while(1){
		ReadBME280();
		MedicionesMBE280();
		LeerADC1();
		SepararDAtos(Temperatura,1);
		Dalay(10000);
		SepararDAtos(PresionB,2);
		Dalay(10000);
		SepararDAtos(RH,5);
		Dalay(10000);
		SepararDAtos(ValADC1,4);
		
		
	}
}

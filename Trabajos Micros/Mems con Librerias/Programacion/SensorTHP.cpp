#include "stm32f4xx.h"                  // Device header
#include "I2C.h"												//Devoce by david :D
#include "SensorTHP.h"												//Devoce by david :D
#include "Delay.h"
#include "math.h"
const static char ADDWrite=0xA6;
const static char ADDRead=0x0;
const static char ADDX1=0x32;
const static char ADDX2=0x33;
const static char ADDy1=0x34;
const static char ADDy2=0x35;
int x,y;
float angulo=0;
char ValoresX [2];
char ValoresY [2];

void LeerX(void){
	ValoresX[0]=I2CRead(ADDWrite,ADDX1);
	Dalay();
	ValoresX[1]=I2CRead(ADDWrite,ADDX2);
	Dalay();
	ValoresY[0]=I2CRead(ADDWrite,ADDy1);
	Dalay();
	ValoresY[1]=I2CRead(ADDWrite,ADDy2);
	Dalay();
}
void IniciarADX(void){
	I2CWrite(0xA6,0x2d,0x00);
	Dalay();
	I2CWrite(0xA6,0x031,0x0);
	Dalay();
	I2CWrite(0xA6,0x2d,0x8);
	Dalay();
}
void CalcularAngulo(void){
	x =(short)((ValoresX[1] << 8) | ValoresX[0]);
	y =(short)((ValoresY[1] << 8) | ValoresY[0]);
	angulo=180.0*(atan2(y/256.5,x/256.5))/3.1416;
	if(angulo < 0.0){angulo+=360.0;}
}




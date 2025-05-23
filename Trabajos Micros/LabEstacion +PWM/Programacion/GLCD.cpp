#include "GLCD.h"
#include "stm32f4xx.h"                  // Device header
const char on =0X3F;
const char off =0X3E;
const char starL =0XC0;
const char setY=0X40;
const const char setX=0XB8;
const char LA[8] = {0x00,0x00,0xFC,0x22,0x22,0x22,0xFC,0x00};
const char LB[8] = {0x00,0x00,0xFE,0x92,0x92,0x92,0x6C,0x00};
const char LC[8] = {0x00,0x00,0x7C,0x82,0x82,0x82,0x44,0x00};
const char LD[8] = {0x00,0x00,0xFE,0x82,0x82,0x44,0x38,0x00};
const char LE[8] = {0x00,0x00,0xFE,0x92,0x92,0x82,0x82,0x00};
const char LF[8] = {0x00,0x00,0xFE,0x12,0x12,0x02,0x02,0x00};
const char LG[8] = {0x00,0x00,0x7C,0x82,0xB2,0x92,0x74,0x00};
const char LH[8] = {0x00,0x00,0xFE,0x10,0x10,0x10,0xFE,0x00};
const char LI[8] = {0x00,0x00,0x82,0xFE,0x82,0x00,0x00,0x00};
const char LJ[8] = {0x00,0x00,0x40,0x82,0x7E,0x02,0x00,0x00};
const char LK[8] = {0x00,0x00,0xFE,0x10,0x10,0x28,0xC6,0x00};
const char LL[8] = {0x00,0xff,0x80,0x80,0x80,0x80,0x00,0x00};
const char LM[8] = {0x00,0x00,0xFE,0x04,0x08,0x04,0xFE,0x00};
const char LN[8] = {0x00,0x00,0xFE,0X10,0x20,0x40,0xFE,0x00};
const char LO[8] = {0x00,0x00,0x7C,0x82,0x82,0x82,0x7C,0x00};
const char LP[8] = {0x00,0x00,0xFE,0x12,0x12,0x12,0x0C,0x00};
const char LQ[8] = {0x00,0x00,0x7C,0x82,0xA2,0x42,0xBC,0x00};
const char LR[8] = {0x00,0x00,0xFE,0x12,0x12,0x12,0xEC,0x00};
const char LS[8] = {0x00,0x00,0x8C,0x92,0x92,0x92,0x62,0x00};
const char LT[8] = {0x00,0x00,0x02,0x02,0xFE,0x02,0x02,0x00};
const char LU[8] = {0x00,0x00,0x7E,0x80,0x80,0x80,0x7E,0x00};
const char LV[8] = {0x00,0x00,0x3E,0x40,0x80,0x40,0x3E,0x00};
const char LW[8] = {0x00,0x00,0xFE,0x40,0x38,0x40,0xFE,0x00};
const char LX[8] = {0x00,0x00,0xC6,0x28,0x10,0x28,0xC6,0x00};
const char LY[8] = {0x00,0x00,0x06,0x08,0xF0,0x08,0x06,0x00};
const char LZ[8] = {0x00,0x00,0xC2,0xA2,0x92,0x8A,0x86,0x00};
const char NO[8] = {0x00,0xff,0x81,0x81,0x81,0x81,0xff,0x00};
const char N1[8] = {0x00,0x00,0x84,0x82,0xff,0x80,0x80,0x00};
const char N2[8] = {0x00,0x00,0x62,0x91,0x89,0x86,0x00,0x00};
const char N3[8] = {0x00,0x00,0x42,0x91,0x99,0x66,0x00,0x00};
const char N4[8] = {0x00,0x0c,0x0a,0x09,0xff,0x08,0x00,0x00};
const char N5[8] = {0x00,0x06,0x89,0x89,0x89,0x89,0x70,0x00};
const char N6[8] = {0x00,0x00,0x30,0x4c,0x8a,0x91,0x60,0x00};
const char N7[8] = {0x00,0x00,0x01,0x11,0x11,0xff,0x00,0x00};
const char N8[8] = {0x00,0x20,0x56,0x89,0x89,0x56,0x20,0x00};
const char N9[8] = {0x00,0x00,0x06,0x89,0x49,0x36,0x00,0x00};
const char NUM[10][8] ={ 0x00,0x00,0x7C,0x92,0x8A,0x86,0x7C,0x00, //0
																0x00,0x00,0x08,0x04,0xFE,0x00,0x00,0x00, //1
																0x00,0x00,0x84,0xC2,0xA2,0x92,0x8C,0x00, //2
																0x00,0x00,0x44,0x82,0x92,0x92,0x6C,0x00, //3
																0x00,0x00,0x30,0x28,0x24,0xFE,0x20,0x00, //4
																0x00,0x00,0x4E,0x8A,0x8A,0x8A,0x72,0x00, //5     //Vectores para los numeros de la variable de 8 bits 
																0x00,0x00,0x7C,0x92,0x92,0x92,0x64,0x00, //6
																0x00,0x00,0x02,0x0E2,0x12,0X0A,0x06,0x00, //7
																0x00,0x00,0x6C,0x92,0x92,0x92,0x6C,0x00, //8
																0x00,0x00,0x4C,0x92,0x92,0x92,0x7C,0X00};//9
const char GradosChar [4]={0x1f,0x11,0x1f,0x00};
const char PorcentajeChar[8]={0x0,0x42,0x4,0x8,0x10,0x20,0x42,0x0};

void comandoGLCD (int cs, char a){
	GPIOC->ODR=0;
	if (cs==1){
		GPIOC->ODR |=1<<8;
	}
	else if (cs==2){
		GPIOC->ODR|=1<<9;
	}
	GPIOC->ODR|=a;
	GPIOC->ODR|=1<<11;
	for (int i=0;i<100000;i++){
		__ASM("NOP");
	}
	GPIOC->ODR&=~(1<<11);
	GPIOC->ODR=0;
}
void SendGLCD  (int cs, char b){
		GPIOC->ODR|=1<<10;
	if (cs==1){
		GPIOC->ODR |=1<<8;
	}
	else if (cs==2){
		GPIOC->ODR|=1<<9;
	}
	GPIOC->ODR|=b;
	GPIOC->ODR|=1<<11;
	for (int i=0;i<10000;i++){
		__ASM("NOP");
	}
	GPIOC->ODR&=~(1<<11);
	GPIOC->ODR=0;
}
void borradoGLCD  (int a){
	for (int i=0;i<8;i++){
		comandoGLCD  (1,setY);	
		comandoGLCD  (2,setY);	
		comandoGLCD  (1,i|setX);	
		comandoGLCD  (2,i|setX);	
		for (int k=0;k<64;k++){
			SendGLCD (1,0XFF*a);
			SendGLCD (2,0XFF*a);
		}
	}
}

void IniciarGLCD(void){
	GPIOC->MODER=0X55555555;
	comandoGLCD(1,on);comandoGLCD(2,on);
	comandoGLCD(1,starL);comandoGLCD(2,starL);
	borradoGLCD(0);
}
void ImprimirTemperatura(void){
	comandoGLCD(1,setY);
  comandoGLCD(1, 1|setX);//x es y xd
	for(int j = 0; j < 8; ++j)
  {  SendGLCD(1,LT[j] );}
	for(int j = 0; j < 8; ++j)
  {  SendGLCD(1,LE[j] );}
	for(int j = 0; j < 8; ++j)
  {  SendGLCD(1,LM[j] );}
		for(int j = 0; j < 8; ++j)
  {  SendGLCD(1,LP[j] );}
	for(int j = 0; j < 8; ++j)
  {  SendGLCD(1,LE[j] );}
	for(int j = 0; j < 8; ++j)
  {  SendGLCD(1,LR[j] );}
	for(int j = 0; j < 8; ++j)
  {  SendGLCD(1,LA[j] );}
	
	for(int j = 0; j < 8; ++j)
  {  SendGLCD(1,LT[j] );}
	comandoGLCD(2,setY);
  comandoGLCD(2, 1|setX);//x es y xd
	for(int j = 0; j < 8; ++j)
  {  SendGLCD(2,LU[j] );}
	for(int j = 0; j < 8; ++j)
  {  SendGLCD(2,LR[j] );}
	for(int j = 0; j < 8; ++j)
  {  SendGLCD(2,LA[j] );}
	//Presion
	comandoGLCD(1,setY);
  comandoGLCD(1, 2|setX);//x es y xd
	for(int j = 0; j < 8; ++j)
  {  SendGLCD(1,LP[j] );}
	for(int j = 0; j < 8; ++j)
  {  SendGLCD(1,LR[j] );}
	for(int j = 0; j < 8; ++j)
  {  SendGLCD(1,LE[j] );}
	for(int j = 0; j < 8; ++j)
  {  SendGLCD(1,LS[j] );}
	for(int j = 0; j < 8; ++j)
  {  SendGLCD(1,LI[j] );}
	for(int j = 0; j < 8; ++j)
  {  SendGLCD(1,LO[j] );}
	for(int j = 0; j < 8; ++j)
  {  SendGLCD(1,LN[j] );}
	//Velocidad
	comandoGLCD(1,setY);
  comandoGLCD(1, 3|setX);//x es y xd
	for(int j = 0; j < 8; ++j)
  {  SendGLCD(1,LV[j] );}
	for(int j = 0; j < 8; ++j)
  {  SendGLCD(1,LE[j] );}
	for(int j = 0; j < 8; ++j)
  {  SendGLCD(1,LL[j] );}
	for(int j = 0; j < 8; ++j)
  {  SendGLCD(1,LO[j] );}
	for(int j = 0; j < 8; ++j)
  {  SendGLCD(1,LC[j] );}
	for(int j = 0; j < 8; ++j)
  {  SendGLCD(1,LI[j] );}
	for(int j = 0; j < 8; ++j)
  {  SendGLCD(1,LD[j] );}
	for(int j = 0; j < 8; ++j)
  {  SendGLCD(1,LA[j] );}
	comandoGLCD(2,setY);
  comandoGLCD(2, 3|setX);//x es y xd
	for(int j = 0; j < 8; ++j)
  {  SendGLCD(2,LD[j] );}
	//luz
	comandoGLCD(1,setY);
  comandoGLCD(1, 4|setX);//x es y xd
		for(int j = 0; j < 8; ++j)
  {  SendGLCD(1,LL[j] );}
		for(int j = 0; j < 8; ++j)
  {  SendGLCD(1,LU[j] );}
		for(int j = 0; j < 8; ++j)
  {  SendGLCD(1,LZ[j] );}
	//RH
	comandoGLCD(1,setY);
  comandoGLCD(1, 5|setX);//x es y xd
	for(int j = 0; j < 8; ++j)
  {  SendGLCD(1,LR[j] );}
	for(int j = 0; j < 8; ++j)
  {  SendGLCD(1,LH[j] );}
	
}
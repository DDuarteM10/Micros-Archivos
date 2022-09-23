# include "stm32f7xx.h"
int tc, a;
int BCD[16]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x67,0x77,0x7C,0X39,0x5E,0x79,0x71};//[0 1 2 3 4 5 6 7 8 9 A B C D E F]
int teclado (void){
int cl=0; int num=0;
for (int f=0; f<4; f++){
	GPIOD -> ODR =(1UL<<f);
	cl=(GPIOD -> IDR & 0XF000)>>12;
	for(int c=0; c<4; c++){
		num++;
		if(cl == (1UL << c)) {return num;}
	}}}
	int main (void){
		RCC -> APB2ENR 	|= (1UL <<14);
		RCC -> AHB1ENR = 0XFFFF;
		GPIOA -> MODER = 0X55555555;
		GPIOD -> MODER = 0X00000555;
		GPIOD -> PUPDR = 0X00000555;
		SYSCFG -> EXTICR[3]=0X3333;
		EXTI -> IMR |=0XF000;
		EXTI -> RTSR |=0XF000;
		NVIC_EnableIRQ(EXTI15_10_IRQn);
		GPIOD -> ODR= 0XF;
		while (1){
		a=tc;
		GPIOA -> ODR |= BCD[a];	
		}
	}
	extern "C"
	{ void EXTI15_10_IRQHandler(void){
		tc=teclado();
		GPIOD -> ODR = 0XF;
		EXTI -> PR = 0XFFFF;
	}}
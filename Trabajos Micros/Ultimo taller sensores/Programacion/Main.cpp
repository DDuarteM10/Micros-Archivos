#include "stm32f4xx.h"                  // Device header
#include "Delay.h"
#include "ADC.h"
#include "Usart2.h"
#include "math.h"
/*
Pines Usart A2 A3 F
			ADC A0 Canal-AF8
*/
int ContadorSystick=0,ValADC=0,contadorint=0;
//variables del filtro
float XK=0.0,Xkp=0.0,Pk=0.0,qf=1000,Rk=0.5,Qk,adc,Gk;
float ConversionADC=0;
void IniciarStm32F4(void){
	RCC -> AHB1ENR = 7;
	GPIOA -> MODER |= 0x3;
	
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/1000);
}

extern "C"{
	
	void ADC_IRQHandler(void){
//			Qk=qf/1000.0;
//			adc=adc*0.86;
//			while((ADC1->SR & 0x20)==1){__NOP();}
//			adc=ADC1 ->DR;
//			Xkp=XK;
//			Pk=Pk+Qk;
//			//if(Pk!=0||Rk!=0){
//				Gk=Pk/(Pk+Rk);
//			//}
//			XK=XK+(Gk*(adc - XK));
//			Pk=(1-Gk)*Pk;
//			Qk=qf;//1000.0;
//			adc=adc*500;
//			while((ADC1->SR & 0x20)==1){__NOP();}
//			adc=ADC1 ->DR;
//			Xkp=XK;
//			Pk=Pk+Qk;
//			//if(Pk!=0||Rk!=0){
//				Gk=Pk/(Pk+Rk);
//			//}
//			XK=XK+(Gk*(adc - XK));
//			Pk=(1-Gk)*Pk;
			Qk=qf;//1000.0;
			//adc=adc*500;
			while((ADC1->SR & 0x20)==1){__NOP();}
			adc=ADC1 ->DR;
			Xkp=adc;
			Pk=Pk+Qk;
			//if(Pk!=0||Rk!=0){
				Gk=Pk/(Pk+Rk);
			//}
			XK=Xkp+(Gk*(1 - XK));
			Pk=(1-Gk)*Pk;
	}
	void SysTick_Handler (void){
		if(ContadorSystick==2){
			ContadorSystick=0;
			ADC1-> CR2 |=(1UL<<30);
			ConversionADC=(adc);
			SendUsart2('F',0,0,ConversionADC);
		}
		ContadorSystick++;
	}
}
		
		
    
int main(void){
	IniciarStm32F4();
	ConfiguracionADC();
	ConfiguracionUsart2();
	
	while(1){
		while((ADC1->SR & 0x20)==1){__NOP();}
		
	}
}
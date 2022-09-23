#include "stm32f4xx.h"                  // Device header
#include "ADC.h"
#include "Delay.h"
#include "Timer.h"
void IniciarStm32(void){
	RCC->AHB1ENR |= 0x7;
}

int main (void){
	IniciarStm32();
	ConfiguracionADC();//Canal 7;
	IniciarPwmTimer4();
	CambiarCicloUtilTimer4(2500); //Max 2500 min 500
	while(1){
		//LeerADC1();
		__NOP();
	}
}
#include "Pines.h"
Pines A0;
int main(void){
	A0.DigitalIn(PA0);
	GPIOA->MODER |= 0x1;
}

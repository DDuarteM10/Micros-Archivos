#include "stm32f4xx.h"                  // Device header
#include "Delay.h" //10000
void Dalay(int delaytimer) {
	for (long int i = 0; i < delaytimer; i++) { __NOP(); }
}

#include "stm32f4xx.h"                  // Device header
#include "Delay.h"
void Dalay(int delay) {
	for (long int i = 0; i < delay; i++) { __NOP(); }
}
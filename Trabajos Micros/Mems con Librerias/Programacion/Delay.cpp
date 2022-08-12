#include "stm32f4xx.h"                  // Device header
#include "Delay.h"
void Dalay(void) {
	for (long int i = 0; i < 10000; i++) { __NOP(); }
}
#include "stm32f4xx.h"                  // Device header

char I2CRead(char address,char registry );
void I2CWrite(char address, uint8_t registry);
void IniciarI2C(void);
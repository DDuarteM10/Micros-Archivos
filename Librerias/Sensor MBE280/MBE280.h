#include "stm32f4xx.h"                  // Device header
//Variables listas
extern float Temperatura;
extern float PresionB;
extern float RH;
void ReadBME280(void);
void IniciarBME280(void);
void MedicionesMBE280(void);
uint32_t CompensarTemperatura(int32_t adc_T);
uint32_t CompensarPresion(int32_t adc_T);
uint32_t CompensarRH(int32_t adc_H);

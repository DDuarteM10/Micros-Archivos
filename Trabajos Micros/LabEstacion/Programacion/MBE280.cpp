/*
Sensor de Temperatura, Humedad y Presion por I2C
SDO GND SDA PB7 DCL PB6
Direccion de sensor 
Write 0xEC
Read 0xED

*/
#include "stm32f4xx.h"                  // Device header
#include "I2C.h"												//Devoce by david :D
#include "MBE280.h"											//Devoce by david :D
#include "Delay.h"											//Devoce by david :D
#include "math.h"												// Device header	
//Direccion de sensor 
const static char AddWrite=0xEC;
const static char AddRead=0xED;
//Direccion de los registros 
const static char AddTemp1=0xFC; //menos significativo
const static char AddTemp2=0xFB; 
const static char AddTemp3=0xFA; //mas significativo
const static char AddPre1=0xF9; //menos significativo
const static char AddPre2=0xF8; 
const static char AddPre3=0xF7; //mas significativo
const static char AddRH1=0xFE; //menos significativo
const static char AddRH2=0xFD; //mas significativo
//Direcciones de los Trimming
const static char TriAddTemp[6]={0x88,0x89,0x8A,0x8B,0x8C,0x8D}; 
const static char TriAddPre[18]={0x8E,0x8F,0x90,0x91,0x92,
																0x93,0x94,0x95,0x96,0x97,0x98,0x99,
																0x9A,0x9B,0x9C,0x9D,0x9E,0x9F};
const static char TriAddRH[9]={0xA1,0xE1,0xE2,0xE3,0xE4,0xE5,
																0xE5,0xE6,0xE7};
//Variables del sensor
char temperatura[3];
char Presion[3];
char Humedad[2];
																
//Trimming
uint16_t dig_T1,
				dig_P1,
				dig_H1,dig_H3;
int16_t dig_T2,dig_T3,
				dig_P2,dig_P3,dig_P4,dig_P5,dig_P6,dig_P7,dig_P8,dig_P9,
			  dig_H2,dig_H4,dig_H5,dig_H6;
uint8_t TrimDataTemp[6];
uint8_t TrimDataPre[18];
uint8_t TrimDataRh[9];
																
																
int32_t tRaw, t_fine , pRaw,hRaw;
extern float Temperatura=0;
extern float PresionB=0;
extern float RH=0;
																
//Leer datos
void ReadBME280(void){
	
	//leer temperatura
	temperatura[0]=I2CRead(AddWrite,AddTemp1);
	Dalay(10000);
	temperatura[1]=I2CRead(AddWrite,AddTemp2);
	Dalay(10000);
	temperatura[2]=I2CRead(AddWrite,AddTemp3);
	Dalay(10000);
	tRaw=(temperatura[2]<<12)|(temperatura[1]<<4)|(temperatura[0]>>4);
	
	//Leer Presion
	
	Presion[0]=I2CRead(AddWrite,AddPre1);
	Dalay(10000);
	Presion[1]=I2CRead(AddWrite,AddPre2);
	Dalay(10000);
	Presion[2]=I2CRead(AddWrite,AddPre3);
	Dalay(10000);
	pRaw=(Presion[2]<<12)|(Presion[1]<<4)|(Presion[0]>>4);
	//Leer RH
	Humedad[0]=I2CRead(AddWrite,AddRH1);
	Dalay(10000);
	Humedad[1]=I2CRead(AddWrite,AddRH2);
	Dalay(10000);
	hRaw = (Humedad[1]<<8)|(Humedad[0]);
}
void IniciarBME280(void){
	//Leer las 32 posiciones del Trimming
	
	// Trimming de temperatura
	TrimDataTemp[0]=I2CRead(AddWrite,TriAddTemp[0]);
	Dalay(10000);
	TrimDataTemp[1]=I2CRead(AddWrite,TriAddTemp[1]);
	Dalay(10000);
	TrimDataTemp[2]=I2CRead(AddWrite,TriAddTemp[2]);
	Dalay(10000);
	TrimDataTemp[3]=I2CRead(AddWrite,TriAddTemp[3]);
	Dalay(10000);
	TrimDataTemp[4]=I2CRead(AddWrite,TriAddTemp[4]);
	Dalay(10000);
	TrimDataTemp[5]=I2CRead(AddWrite,TriAddTemp[5]);
	Dalay(10000);
	//Calcular los Trimming de temperatura
	dig_T1=(TrimDataTemp[1]<<8)|(TrimDataTemp[0]);
	dig_T2=(TrimDataTemp[3]<<8)|(TrimDataTemp[2]);
	dig_T3=(TrimDataTemp[5]<<8)|(TrimDataTemp[4]);
	
	// Trimming de Presion
	TrimDataPre[0]=I2CRead(AddWrite,TriAddPre[0]);
	Dalay(10000);
	TrimDataPre[1]=I2CRead(AddWrite,TriAddPre[1]);
	Dalay(10000);
	TrimDataPre[2]=I2CRead(AddWrite,TriAddPre[2]);
	Dalay(10000);
	TrimDataPre[3]=I2CRead(AddWrite,TriAddPre[3]);
	Dalay(10000);
	TrimDataPre[4]=I2CRead(AddWrite,TriAddPre[4]);
	Dalay(10000);
	TrimDataPre[5]=I2CRead(AddWrite,TriAddPre[5]);
	Dalay(10000);
	TrimDataPre[6]=I2CRead(AddWrite,TriAddPre[6]);
	Dalay(10000);
	TrimDataPre[7]=I2CRead(AddWrite,TriAddPre[7]);
	Dalay(10000);
	TrimDataPre[8]=I2CRead(AddWrite,TriAddPre[8]);
	Dalay(10000);
	TrimDataPre[9]=I2CRead(AddWrite,TriAddPre[9]);
	Dalay(10000);
	TrimDataPre[10]=I2CRead(AddWrite,TriAddPre[10]);
	Dalay(10000);
	TrimDataPre[11]=I2CRead(AddWrite,TriAddPre[11]);
	Dalay(10000);
	TrimDataPre[12]=I2CRead(AddWrite,TriAddPre[12]);
	Dalay(10000);
	TrimDataPre[13]=I2CRead(AddWrite,TriAddPre[13]);
	Dalay(10000);
	TrimDataPre[14]=I2CRead(AddWrite,TriAddPre[14]);
	Dalay(10000);
	TrimDataPre[15]=I2CRead(AddWrite,TriAddPre[15]);
	Dalay(10000);
	TrimDataPre[16]=I2CRead(AddWrite,TriAddPre[16]);
	Dalay(10000);
	TrimDataPre[17]=I2CRead(AddWrite,TriAddPre[17]);
	Dalay(10000);
	
	//Calcular los Trimming de presion
	dig_P1 = (TrimDataPre[1]<<8) | TrimDataPre[0];
	dig_P2 = (TrimDataPre[3]<<8) | TrimDataPre[2];
	dig_P3 = (TrimDataPre[5]<<8) | TrimDataPre[4];
	dig_P4 = (TrimDataPre[7]<<8) | TrimDataPre[6];
	dig_P5 = (TrimDataPre[9]<<8) | TrimDataPre[8];
	dig_P6 = (TrimDataPre[11]<<8) | TrimDataPre[10];
	dig_P7 = (TrimDataPre[13]<<8) | TrimDataPre[12];
	dig_P8 = (TrimDataPre[15]<<8) | TrimDataPre[14];
	dig_P9 = (TrimDataPre[17]<<8) | TrimDataPre[16];
	
	// Trimming de Rh
	TrimDataRh[0]=I2CRead(AddWrite,TriAddRH[0]);
	Dalay(10000);
	TrimDataRh[1]=I2CRead(AddWrite,TriAddRH[1]);
	Dalay(10000);
	TrimDataRh[2]=I2CRead(AddWrite,TriAddRH[2]);
	Dalay(10000);
	TrimDataRh[3]=I2CRead(AddWrite,TriAddRH[3]);
	Dalay(10000);
	TrimDataRh[4]=I2CRead(AddWrite,TriAddRH[4]);
	Dalay(10000);
	TrimDataRh[5]=I2CRead(AddWrite,TriAddRH[5]);
	Dalay(10000);
	TrimDataRh[6]=I2CRead(AddWrite,TriAddRH[6]);
	Dalay(10000);
	TrimDataRh[7]=I2CRead(AddWrite,TriAddRH[7]);
	Dalay(10000);
	TrimDataRh[8]=I2CRead(AddWrite,TriAddRH[8]);
	Dalay(10000);
	
	
	//Calcular los Trimming de RH
	dig_H1 = TrimDataRh[0];
	dig_H2 = (TrimDataRh[2]<<8) | TrimDataRh[1];
	dig_H3 = (TrimDataRh[3]);
	dig_H4 = (TrimDataRh[4]<<4) | (TrimDataRh[5] & 0x0f);
	dig_H5 = (TrimDataRh[7]<<4) | (TrimDataRh[6]>>4);
	dig_H6 = (TrimDataRh[8]);
	
	
	
	I2CWrite(AddWrite,0xE0,0xB6 );//Reinicio del dispositivo
	Dalay(10000);
	I2CWrite(AddWrite,0xF2,0x0);//Escrivir en el registro Ctlr_hum
	Dalay(10000);
	I2CWrite(AddWrite,0xF2,0x05);//Escrivir en el registro Ctlr_hum
	Dalay(10000);
	I2CWrite(AddWrite,0xF5,0xEA);//tiempo 20ms y filtro 10 SPI 0
	Dalay(10000);
	I2CWrite(AddWrite,0xF4,0xA7);//muestreo normal tmeperatura default
}
uint32_t CompensarTemperatura(int32_t adc_T){
	int32_t var1,var2,T;
	var1 = ((((adc_T>>3) - ((int32_t)dig_T1<<1))) * ((int32_t)dig_T2)) >> 11;
	var2 = (((((adc_T>>4) - ((int32_t)dig_T1)) * ((adc_T>>4) - ((int32_t)dig_T1)))>> 12) *((int32_t)dig_T3)) >> 14;
	t_fine = var1 + var2;
	T = (t_fine * 5 + 128) >> 8;
	return T;
}
uint32_t CompensarPresion(int32_t adc_P){
	uint64_t var1, var2, p;
	var1 = ((int64_t)t_fine) - 128000;
	var2 = var1 * var1 * (int64_t)dig_P6;
	var2 = var2 + ((var1*(int64_t)dig_P5)<<17);
	var2 = var2 + (((int64_t)dig_P4)<<35);
	var1 = ((var1 * var1 * (int64_t)dig_P3)>>8) + ((var1 * (int64_t)dig_P2)<<12);
	var1 = (((((int64_t)1)<<47)+var1))*((int64_t)dig_P1)>>33;
	if (var1 == 0)
	{
		return 0; // avoid exception caused by division by zero
	}
	p = 1048576-adc_P;
	p = (((p<<31)-var2)*3125)/var1;
	var1 = (((int64_t)dig_P9) * (p>>13) * (p>>13)) >> 25;
	var2 = (((int64_t)dig_P8) * p) >> 19;
	p = ((p + var1 + var2) >> 8) + (((int64_t)dig_P7)<<4);
	return (int32_t)p;
}
uint32_t CompensarRH(int32_t adc_H)
{
	int32_t v_x1_u32r;
	v_x1_u32r = (t_fine - ((int32_t)76800));
	v_x1_u32r = (((((adc_H << 14) - (((int32_t)dig_H4) << 20) - (((int32_t)dig_H5) *\
			v_x1_u32r)) + ((int32_t)16384)) >> 15) * (((((((v_x1_u32r *\
					((int32_t)dig_H6)) >> 10) * (((v_x1_u32r * ((int32_t)dig_H3)) >> 11) +\
							((int32_t)32768))) >> 10) + ((int32_t)2097152)) * ((int32_t)dig_H2) +\
					8192) >> 14));
	v_x1_u32r = (v_x1_u32r - (((((v_x1_u32r >> 15) * (v_x1_u32r >> 15)) >> 7) *\
			((int32_t)dig_H1)) >> 4));
	v_x1_u32r = (v_x1_u32r < 0 ? 0 : v_x1_u32r);
	v_x1_u32r = (v_x1_u32r > 419430400 ? 419430400 : v_x1_u32r);
	return (uint32_t)(v_x1_u32r>>12);
}

void MedicionesMBE280(void){
	
	if(tRaw==0x800000){Temperatura=0;}else
	{
		Temperatura=(CompensarTemperatura(tRaw))/100.0;
	}
	 if (pRaw == 0x800000) PresionB = 0; // value in case temp measurement was disabled
		  else
		  {
			  PresionB = (CompensarPresion (pRaw)/(256*65  ));  // as per datasheet, the pressure is x256
			}
			 if (hRaw == 0x8000) RH = 0; // value in case temp measurement was disabled
		  else
		  {
			  RH = ((CompensarRH (hRaw))/1024.0);  // as per datasheet, the temp is x1024
		  }
}

			

	
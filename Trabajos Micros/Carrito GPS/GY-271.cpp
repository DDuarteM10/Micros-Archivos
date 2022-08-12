#include "GY-271.h"
#include "I2C.h"
#include "Delay.h"
char ValoresX [2];
char ValoresY [2];
char Valoresz [2];
int x,y,z;
void IniciarGY271(void){
	/*CONFIGURACIÓN DE LA BRÚJULA*/
	//Según DS 0x3C para escribir operaciones
	//(pg.18,I2C COMMUNICATION PROTOCOL)
	
	/*CRA7 to CRA5: bits en 0 para correcta operación
	  CRA4 to CRA2: Establecen la velocidad de salida
	  de datos en los 3 registros de salida de datos
	  se dejan en 1-0 que significa 2Hz
	CRA1 to CRA0: bits en 0*/
	I2CWrite(0x3C, 0x00, 0x08);//Escribe en el registro A
	Dalay(100000);
	
	/*Se deja la configuración por defecto ±1.0Ga (default)*/
	I2CWrite(0x3C, 0x01, 0x20);//Escribe en el registro B
	Dalay(100000);
	
	/*MR7 to MR2: Bits limpios para una correcta operación
	  MR1 to MR0: Seleccionan el modo de operacion del dispositivo
	  (modo de conversión continua)*/
	I2CWrite(0x3C, 0x02, 0x00);//Escribe en el registro de modo
	Dalay(100000);
}
void ReadGY271 (void){
		//Segun el datasheet 0x3D para leer operaciones
		//(pg.18,I2C COMMUNICATION PROTOCOL)
		ValoresX[0]=I2CRead(0x3C,0x03);
		Dalay(30000);
		
		ValoresX[1]=I2CRead(0x3C,0x04);
		Dalay(30000);
		
		ValoresY[0]=I2CRead(0x3C,0x05);
		Dalay(30000);
		
		ValoresY[1]=I2CRead(0x3C,0x06);
		Dalay(30000);
		
		Valoresz[0]=I2CRead(0x3C,0x07);
		Dalay(30000);
		
		Valoresz[1]=I2CRead(0x3C,0x08);
		Dalay(30000);
		
		x=(short)(ValoresX[0]<<8) | ValoresX[1];
		y=(short)(ValoresY[0]<<8) | ValoresY[1];
		z=(short)(Valoresz[0]<<8) | Valoresz[1];
		
		//Dalay(3000000);	
}
#include "Nokia.h"
#include "stm32f4xx.h"                  // Device header
#include "stdio.h"
/*Configuracion de pines LCD NOKIA
Reset PB0
DC PB1
Clock PB3 
Din PB5

Nokia_5110(0xD5);
Escribir_nokia_0(1,0,0,"Habia una vez una iguana",1);

*/
void Puertos_De_Comunicacion_SPI (void){
	//Habilitar puerto A, B y E
	//RCC->AHB1ENR |= 0x13;
	/*Puerto A
	PA0: Salida
	PA1: Salida
	PA5: FA
	PA6: FA
	PA7: FA*/
	//GPIOA->MODER |= 0x0005;
	GPIOB->MODER |= 0xAAA5;
	//No PUPD
	//GPIOA->PUPDR  = 0x000;
	GPIOB->PUPDR  = 0x000;
    //AF5: PB3 clock PB5 DIN
  GPIOB->AFR[0] = 0x555000;	
}

void Configuracion_Modulo_SPI (void){
	RCC->APB2ENR  |= (1UL<<12); //Enciende reloj SPI_1
	//////////////   CR_1    /////////////////////////
	SPI1->CR1 |= (0<<6);
	SPI1->CR1 |= (6<<3);/*
	Bits_5:3 (BR)------->Control de velocidad en baudios
	110:     f_{pclk}(1)/128*/
	SPI1->CR1 |= (1<<0)|(1<<1);/*
	Bit_1:0    (CPHA)----->Fase del reloj
	00:      La primera trancisi�n de reloj es el primer
           borde de captura de datos*/
	SPI1->CR1 &=~(1<<10);/*
	Bit_10   (RXONLY)--->Habilita modo de solo recepcion
	0:       Full-duplex (Transmite y recive)*/
	SPI1->CR1 &=~(1<<7);/*
	Bit_7    (LSBFIRST)->Formato de cuadro
	0:        El dato es transmitido o recibido con el MSB primero*/
	SPI1->CR1 &=~(1<<11);/*
	Bit_11   (CRCL)----->largo del CRC
	0:       8-bit de largo del CRC*/
	SPI1->CR1 |= (1<<2);
	SPI1->CR1 |= (1<<9);
	SPI1->CR1 |= (1<<8);/*
	Bit_2    (MSTR)----->Seleccion maestra
	1:        Modo maestro*/
	SPI1->CR1 |= (1<<6);
}
void TxSPI(unsigned char d){
 //Limpiar bandera overrun
 unsigned char x=SPI1->DR;
 //Transmisi�n del dato
 SPI1->DR=d;
 for(long i=0; i<2; i++){__NOP();}
 //Espera fin de la transmisi�n
 while((SPI1->SR & SPI_SR_BSY));
}
void Nokia_5110 (char contraste){
	Puertos_De_Comunicacion_SPI();
	Configuracion_Modulo_SPI();
	//Encender nokia
  reset(1);//Pulso reset
  for(int i=0;i<100000;i++){__NOP();}
  TxSPI(0x21);//H=1
  TxSPI(contraste);
	////////////
  TxSPI(0x22);//H=0
  TxSPI(0xC);
}
void reset(bool e){
 if(e)GPIOB->BSRR|=(1UL<<1);//Activa en alto
 else GPIOB->BSRR|=(1UL<<17);//Activa en bajo
}
void Escribir_nokia_0(bool e, short Y, short X, char str[], bool clear){
	//La funci�n permite eligir si limpiar o no al escribir algo
	if(clear == 1){
		nokia_pos(0,0);
		for(int j=0; j<504; j++){
			TxSPI(0x0);
		}
	}else if (clear == 0){
		__NOP();
	}
  //Se elije en qu� coordenada se va a empezar a escribir	
	nokia_pos(Y,X);
	
	//Se escribe en la nokia
	int i=0;
	while(str[i]){
		for(int j=0; j<5; j++){
			TxSPI(ASCII[str[i]-32][j]);
		}
		i++;
	}
}
void nokia_pos(short Ypos, short Xpos){
void SepararDatos(){
	
}

	//DC en 0 para poder enviar comandos
	GPIOB->ODR &= 0x2;
	
	//Configuraci�n del DS para coordenadas
	TxSPI(0x20);
	TxSPI(0x40 | Ypos);
	TxSPI(0x80 | Xpos);
	
	//DC en 1 para poder escribir
	GPIOB->ODR |= 1;
}
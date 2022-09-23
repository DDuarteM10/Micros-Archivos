/*
Libreria I2C crada por David Duarte
*/
#include "I2C.h"	


void IniciarI2C(){
	RCC->APB1ENR |= (1Ul << 21); //Clk I2C1 EN
	I2C1->CCR &= ~I2C_CCR_CCR;
	I2C1->CR2 &= ~(I2C_CR2_FREQ);
//	I2C1->CR2 |= 0b000010;
//	I2C1->CCR |= 80;
//	I2C1->TRISE |= 3;
//	I2C1->CR1 |= 0x0001;
//	I2C1->CR2 |= (45<<0);  // PCLK1 FREQUENCY in MHz
//	
	
	//Velovicad normal
//	// Configure the clock control registers
//	I2C1->CCR = 225<<0;  // check calculation in PDF
//	
//	// Configure the rise time register
//	I2C1->TRISE = 46;  // check PDF again 
	//velocidad rapida
	I2C1->CR2|=50;
	I2C1->CCR|=0x2|(1<<15)|(1<<14); 
	I2C1->TRISE=20; //output max rise
	
	// Program the I2C_CR1 register to enable the peripheral
	I2C1->CR1 |= (1<<0);  // Enable I2C
	GPIOB->MODER |= 0xA000; // Funciones especiales P7 y P6
	GPIOB->AFR[0] |= 0x44000000; // canales F4 para P6 y P7
	GPIOB->PUPDR |= 0xA000; //para I2C
	GPIOB->OSPEEDR |= 0;
	GPIOB->OTYPER |= 0xC0;//para I2C
}
unsigned char I2C_Direccion::getAdress(){
	return Adress; 
}
void I2C_Direccion::setAdress(unsigned char direccion){
	Adress=direccion; 
}
void I2C_Direccion::setRegistro_1(unsigned char direccion){
	Registro_1=direccion; 
}
unsigned char I2C_Direccion::getRegistro_1(){
	return Registro_1 ; 
}
void I2C_Direccion::setRegistro_2(unsigned char direccion){
	Registro_2=direccion; 
}
unsigned char I2C_Direccion::getRegistro_2(){
	return Registro_2 ; 
}
void I2C_Direccion::setRegistro_3(unsigned char direccion){
	Registro_3=direccion; 
}
unsigned char I2C_Direccion::getRegistro_3(){
	return  Registro_3; 
}




void I2C_Direccion::I2C_Inicio(){
	I2C1->CR1 |= (1<<10);  // Enable the ACK
	I2C1->CR1 |= (1<<8);  // Generate START
	while (!(I2C1->SR1 & (1<<0)));  // Wait fror SB bit to set
}



//Funcion que genera el envio de la direccion
void I2C_Direccion::I2C_Envio_Direccion(){
//	I2C1->DR = I2C_Direccion::getAdress();					// Write device address (W)
//	while (!(I2C1->SR1 & I2C_SR1_ADDR)){};	// Wait for EV6
//    (void)I2C1->SR2;						// Read SR2
//	while (!(I2C1->SR1 & I2C_SR1_TXE));		// Wait for EV8_1
	I2C1->DR = I2C_Direccion::getAdress();  //  send the address
	while (!(I2C1->SR1 & (1<<1)));  // wait for ADDR bit to set
	uint8_t temp = I2C1->SR1 | I2C1->SR2;  // read SR1 and SR2 to clear the ADDR bit
	
}
//Funcion que genera el envio de la direccion del registro
void I2C_Direccion::I2C_Envio_Registro(unsigned char Registro){
//	I2C1->DR = Registro;					// Write registry address
//	while (!(I2C1->SR1 & I2C_SR1_BTF));	    // Wait for BTF
	while (!(I2C1->SR1 & (1<<7)));  // wait for TXE bit to set
	I2C1->DR = Registro;
	while (!(I2C1->SR1 & (1<<2)));  // wait for BTF bit to set
}
//Funcion que genera el envia del dato
void I2C_Direccion::I2C_Escribir_Dato(unsigned char dato){
	while (!(I2C1->SR1 & (1<<7)));  // wait for TXE bit to set
	I2C1->DR = dato;
	while (!(I2C1->SR1 & (1<<2)));  // wait for BTF bit to set
}
//Funcion que genera el bit de stop
void I2C_Direccion::I2C_Stop(){
		I2C1->CR1 |= I2C_CR1_STOP; //condicion de Stop
}
void I2C_Direccion::I2C_No_ACK(){
	I2C1->CR1 &= ~I2C_CR1_ACK; 
}
void I2C_Direccion::I2C_WriteMulti (char *data, uint8_t size)
{
/**** STEPS FOLLOWED  ************
1. Wait for the TXE (bit 7 in SR1) to set. This indicates that the DR is empty
2. Keep Sending DATA to the DR Register after performing the check if the TXE bit is set
3. Once the DATA transfer is complete, Wait for the BTF (bit 2 in SR1) to set. This indicates the end of LAST DATA transmission
*/	
	while (!(I2C1->SR1 & (1<<7)));  // wait for TXE bit to set 
	while (size)
	{
		while (!(I2C1->SR1 & (1<<7)));  // wait for TXE bit to set 
		I2C1->DR = (uint32_t )*data++;  // send data
		size--;
	}
	
	while (!(I2C1->SR1 & (1<<2)));  // wait for BTF to set
}

void I2C_Direccion::I2C_Enviar_Un_Buffer(unsigned char dato){
	I2C_Inicio();
	I2C_Envio_Direccion();
	I2C_Envio_Registro(dato); //esta funcion manda un dato remplazando el registro
	I2C_No_ACK();
	I2C_Direccion::I2C_Stop();
}
void I2C_Direccion::I2C_Enviar_Multiples_Datos (char *data, uint8_t size) //Funciona :3
{
	I2C_Direccion::I2C_Inicio ();
	I2C_Direccion::I2C_Envio_Direccion ();
	I2C_Direccion::I2C_WriteMulti ( data,  size);
	I2C_Direccion::I2C_Stop();
}
void I2C_Direccion::I2C_Enviar_Multiples_Datos_ConRegistro (unsigned char registro,char *data, uint8_t size) //Funciona :3
{
	I2C_Direccion::I2C_Inicio ();
	I2C_Direccion::I2C_Envio_Direccion ();
	I2C_Direccion::I2C_Envio_Registro(registro);
	I2C_Direccion::I2C_WriteMulti ( data,  size);
	I2C_Direccion::I2C_Stop();
}
void I2C_Direccion::I2C_Enviar_Dato(unsigned char Registro,unsigned char Data){
	I2C_Direccion::I2C_Inicio ();
	I2C_Direccion::I2C_Envio_Direccion ();
	I2C_Direccion::I2C_Envio_Registro(Registro);
	I2C_Direccion::I2C_Escribir_Dato(Data);
	I2C_Direccion::I2C_Stop();
}

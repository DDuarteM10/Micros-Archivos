 #include "stm32f4xx.h" 
void IniciarI2C();//Iniciar protoculo i2c
//Clase que permite usar varios Protoculos
/*Configuacion de los pines
	I2C1_SCL Pin PB6
	I2C1_SDA pin PB7  Canales F04
	SDO GND*/
 class I2C_Direccion{
	private:
	unsigned char Adress;
	unsigned char Registro_1;
	unsigned char Registro_2;
	unsigned char Registro_3;
	public:
	unsigned char getAdress();
	void setAdress(unsigned char direccion);
	void setRegistro_1(unsigned char direccion);
	void setRegistro_2(unsigned char direccion);
	void setRegistro_3(unsigned char direccion);
	unsigned char getRegistro_1();
	unsigned char getRegistro_2();
	unsigned char getRegistro_3();
	void I2C_Inicio();
	void I2C_Envio_Direccion();
	void I2C_Envio_Registro(unsigned char Registro);
	void I2C_Stop();
	void I2C_Escribir_Dato(unsigned char dato);
	void I2C_No_ACK();
	void I2C_Enviar_Un_Buffer(unsigned char dato);
	void I2C_WriteMulti (char *data, uint8_t size);
	void I2C_Enviar_Multiples_Datos ( char  *data, uint8_t   size);
	void I2C_Enviar_Dato(unsigned char Registro,unsigned char Data);
	void I2C_Enviar_Multiples_Datos_ConRegistro (unsigned char registro,char *data, uint8_t size);
};

extern I2C_Direccion LCD16x2;
extern I2C_Direccion SDD1306I2C;
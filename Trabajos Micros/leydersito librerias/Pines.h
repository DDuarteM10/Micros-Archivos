// Librería Pines V1.0 //

#ifndef _PINES_H
#define _PINES_H
 
#if defined (STM32F401xE) // Adición de librerías micro F401
 #include "stm32f401xE.h"
#endif
 
#if defined(STM32F746xx) // Adición de librerías micro F746
 #include "stm32f746xx.h"
#endif
 
//**********************//
// DEFINICIONES DE PINES //
#define PA0   (unsigned char)0x00
#define PA1   (unsigned char)0x01
#define PA2   (unsigned char)0x02
#define PA3   (unsigned char)0x03
#define PA4   (unsigned char)0x04
#define PA5   (unsigned char)0x05
#define PA6   (unsigned char)0x06
#define PA7   (unsigned char)0x07
#define PA8   (unsigned char)0x08
#define PA9   (unsigned char)0x09
#define PA10  (unsigned char)0x0A
#define PA11  (unsigned char)0x0B
#define PA12  (unsigned char)0x0C
#define PA13  (unsigned char)0x0D
#define PA14  (unsigned char)0x0E
#define PA15  (unsigned char)0x0F
 
#define PB0   (unsigned char)0x10
#define PB1   (unsigned char)0x11
#define PB2   (unsigned char)0x12
#define PB3   (unsigned char)0x13
#define PB4   (unsigned char)0x14
#define PB5   (unsigned char)0x15
#define PB6   (unsigned char)0x16
#define PB7   (unsigned char)0x17
#define PB8   (unsigned char)0x18
#define PB9   (unsigned char)0x19
#define PB10  (unsigned char)0x1A
#define PB11  (unsigned char)0x1B
#define PB12  (unsigned char)0x1C
#define PB13  (unsigned char)0x1D
#define PB14  (unsigned char)0x1E
#define PB15  (unsigned char)0x1F
 
#define PC0   (unsigned char)0x20
#define PC1   (unsigned char)0x21
#define PC2   (unsigned char)0x22
#define PC3   (unsigned char)0x23
#define PC4   (unsigned char)0x24
#define PC5   (unsigned char)0x25
#define PC6   (unsigned char)0x26
#define PC7   (unsigned char)0x27
#define PC8   (unsigned char)0x28
#define PC9   (unsigned char)0x29
#define PC10  (unsigned char)0x2A
#define PC11  (unsigned char)0x2B
#define PC12  (unsigned char)0x2C
#define PC13  (unsigned char)0x2D
#define PC14  (unsigned char)0x2E
#define PC15  (unsigned char)0x2F
 
#define PD0   (unsigned char)0x30
#define PD1   (unsigned char)0x31
#define PD2   (unsigned char)0x32
#define PD3   (unsigned char)0x33
#define PD4   (unsigned char)0x34
#define PD5   (unsigned char)0x35
#define PD6   (unsigned char)0x36
#define PD7   (unsigned char)0x37
#define PD8   (unsigned char)0x38
#define PD9   (unsigned char)0x39
#define PD10  (unsigned char)0x3A
#define PD11  (unsigned char)0x3B
#define PD12  (unsigned char)0x3C
#define PD13  (unsigned char)0x3D
#define PD14  (unsigned char)0x3E
#define PD15  (unsigned char)0x3F
 
#define PE0   (unsigned char)0x40
#define PE1   (unsigned char)0x41
#define PE2   (unsigned char)0x42
#define PE3   (unsigned char)0x43
#define PE4   (unsigned char)0x44
#define PE5   (unsigned char)0x45
#define PE6   (unsigned char)0x46
#define PE7   (unsigned char)0x47
#define PE8   (unsigned char)0x48
#define PE9   (unsigned char)0x49
#define PE10  (unsigned char)0x4A
#define PE11  (unsigned char)0x4B
#define PE12  (unsigned char)0x4C
#define PE13  (unsigned char)0x4D
#define PE14  (unsigned char)0x4E
#define PE15  (unsigned char)0x4F
 
#define PF0   (unsigned char)0x50
#define PF1   (unsigned char)0x51
#define PF2   (unsigned char)0x52
#define PF3   (unsigned char)0x53
#define PF4   (unsigned char)0x54
#define PF5   (unsigned char)0x55
#define PF6   (unsigned char)0x56
#define PF7   (unsigned char)0x57
#define PF8   (unsigned char)0x58
#define PF9   (unsigned char)0x59
#define PF10  (unsigned char)0x5A
#define PF11  (unsigned char)0x5B
#define PF12  (unsigned char)0x5C
#define PF13  (unsigned char)0x5D
#define PF14  (unsigned char)0x5E
#define PF15  (unsigned char)0x5F
 
#define PG0   (unsigned char)0x60
#define PG1   (unsigned char)0x61
#define PG2   (unsigned char)0x62
#define PG3   (unsigned char)0x63
#define PG4   (unsigned char)0x64
#define PG5   (unsigned char)0x65
#define PG6   (unsigned char)0x66
#define PG7   (unsigned char)0x67
#define PG8   (unsigned char)0x68
#define PG9   (unsigned char)0x69
#define PG10  (unsigned char)0x6A
#define PG11  (unsigned char)0x6B
#define PG12  (unsigned char)0x6C
#define PG13  (unsigned char)0x6D
#define PG14  (unsigned char)0x6E
#define PG15  (unsigned char)0x6F
// ********************* //
 
// Clase Pines //

class Pines{
	
private: //Declaraciones privadas
 
GPIO_TypeDef * port; //Apuntador a GPIO
 unsigned char pin; //variable para guardar pin asociado
 //Variables para guardar las mascara de activación 1 y 0
 unsigned int mask1, mask0; 

public:
 
	Pines();//Método constructor
	~Pines();//Método destructor 
	void Pin(unsigned char p); // Método para asignar pin a la clase 
	void FuncionAlternativa(unsigned char p,unsigned char f); // Método para usar función alternativa
	void DigitalOut(unsigned char p); // Método para hacer pin de salida
	void DigitalOutOpen(unsigned char p); // Método para hacer pin de salida con open drain
	void DigitalIn(unsigned char p); // Método para hacer pin de entrada
	void DigitalInUp(unsigned char p); // Método para hacer pin de entrada con resistencia Pull-Up
	void DigitalInDown(unsigned char p); // Método para hacer pin de entrada con resistencia Pull-Down
	void Analogo(unsigned char p); // Método para función análogo
	bool GetPin(void); // Método para leer el estado lógico del pin
	void SetPin(bool e); // Método para asignar estado lógico al pin
	bool operator = (bool e); // Operador para igualar el pin a estado lógico
	operator bool(); // Operador para leer el estado lógico del pin
	bool operator = (Pines p); // Operador para igualar el pin a otro pin
	void operator << (unsigned char p); // Operador para definir pin de entrada
	void operator >> (unsigned char p); // Operador para definir pin de salida
	bool operator & (bool e); // Operador lógico AND
	bool operator | (bool e); // Operador lógico OR
	bool operator ^ (bool e); // Operador lógico XOR
	bool operator ! (void); // Operador NOT; 
	void operator &= (bool e); // Operador lógico auto AND 
	void operator |= (bool e); // Operador lógico auto OR
	void operator ^= (bool e); // Operador lógico auto XOR
	
};
//**********************//
#endif 

// Librería Pines V1.0 //


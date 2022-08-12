#include "Pines.h"
 
Pines::Pines()//Constructor de la clase
{
 //Valores iniciales
 port=0;
 pin=0;
}
 
Pines::~Pines()//Destructor de la clase
{
}

//M�todo para asignar pin a la clase 
void Pines::Pin(unsigned char p){

 //Evaluaci�n del nibble superior que codifica el puerto
 //Esta estructura SW asigna al apuntador port el GPIO seg�n el caso    
	switch( p&0xF0 ){
		case 0x00:port=GPIOA;RCC->AHB1ENR|=RCC_AHB1ENR_GPIOAEN;break;
		case 0x10:port=GPIOB;RCC->AHB1ENR|=RCC_AHB1ENR_GPIOBEN;break;
		case 0x20:port=GPIOC;RCC->AHB1ENR|=RCC_AHB1ENR_GPIOCEN;break;
		case 0x30:port=GPIOD;RCC->AHB1ENR|=RCC_AHB1ENR_GPIODEN;break;
		case 0x40:port=GPIOE;RCC->AHB1ENR|=RCC_AHB1ENR_GPIOEEN;break;
	#if defined(STM32F746xx) 
		case 0x50:port=GPIOF;RCC->AHB1ENR|=RCC_AHB1ENR_GPIOFEN;break;
		case 0x60:port=GPIOG;RCC->AHB1ENR|=RCC_AHB1ENR_GPIOGEN;break;
	#endif
 }
	
	//Evaluaci�n del nibble inferior que codifica el pin
	pin=p&0x0F;
	mask1=(1UL<<pin);//Asignaci�n de la m�scara 1
	mask0=(1UL<<(pin+16));// Asignaci�n de la m�scara 0
	//Las siguientes 4 l�neas de c�digo
	//configuran el pin como entrada digital
	port->MODER  &= ~(3UL<<pin*2);
	port->OTYPER &= ~mask1;
	port->OSPEEDR&= ~(3UL<<pin*2);
	port->PUPDR  &= ~(3UL<<pin*2);
}

// Metodo Funcion Alternativa
void Pines::FuncionAlternativa(unsigned char p, unsigned char f){
	Pin(p); // Se asigna PIN
	port -> MODER |= (2UL << pin*2); // Se define Alternativo el pin
	
	if(pin <= 7){ // Se evalua la parte alta y baja de AFR
		port -> AFR[0] &=~ (15UL << pin * 4); // Borrado de la funcion
		port -> AFR[0] |= ((f&15UL)<< pin *4); // Asignado de la funcion	
	}
	else{
		port -> AFR[1] &=~ (15UL << (pin-8)*4); // Se borra la funcion
		port -> AFR[1] |= ((f&15UL)<<(pin-8)*4); // Se asgina la funcion
	}
}

//M�todo para hacer pin de salida
void Pines::DigitalOut(unsigned char p){ 
 
	Pin(p);//M�todo para asignar pin a la clase 
	port->MODER|=(1UL<<pin*2);//Se define de salida el pin
	SetPin(false);//Inicia en 0	
	
}

//M�todo para hacer pin de salida con open drain 
void Pines::DigitalOutOpen(unsigned char p){
 
	DigitalOut(p);//M�todo para hacer pin de salida
	port->OTYPER|=mask1;//Activa Open-Drain 
	
}

//M�todo para hacer pin de entrada 
void Pines::DigitalIn(unsigned char p){
	Pin(p);//M�todo para asignar pin a la clase
}
 
//M�todo para hacer pin de entrada con resistencia Pull-Up
void Pines::DigitalInUp(unsigned char p){
	
	Pin(p);//Metodo para asignar pin a la clase
	port->PUPDR|=(1UL<<pin*2); //Activa Pull-UP
	
}
 
//M�todo para hacer pin de entrada con resistencia Pull-Down
void Pines::DigitalInDown(unsigned char p){
 
	Pin(p);//M�todo para asignar pin a la clase
	port->PUPDR|=(2UL<<pin*2); //Activa Pull-Down
	
}

//M�todo para funci�n an�logo
void Pines::Analogo(unsigned char p){

 Pin(p);//M�todo para asignar pin a la clase 
 port->MODER|=(3UL<<pin*2); //Se define pin an�logo 
	
}

//M�todo para leer el estado l�gico del pin
bool Pines::GetPin(void){
	//Se eval�a estado l�gico del pin y se retorna 1 o 0
	if(port->IDR&mask1)return true;
	return false;
}

//M�todo para asignar estado l�gico al pin
void Pines::SetPin(bool e){
	//Se asigna estado l�gico en el pin 
	if(e)port->BSRR|=mask1;
	else port->BSRR|=mask0;
}

//Operador para igualar el pin a estado l�gico
bool Pines::operator = (bool e){
	
	SetPin(e); //M�todo para asignar estado l�gico al pin
	return e; //retorno del estado l�gico
	
}

//Operador para leer el estado l�gico del pin
Pines::operator bool(){
	//M�todo para leer el estado l�gico del pin
	//y retorno del valor l�gico
	return GetPin();
}

//Operador para igualar el pin a otro pin
bool Pines::operator = (Pines p){
	//M�todo para leer el estado l�gico del pin
	//y m�todo para asignar estado l�gico al pin
	SetPin( p.GetPin() );
	//retorno del valor configurado
	return GetPin();
}
 
//Operador para definir pin de entrada
void Pines::operator << (unsigned char p){
	DigitalIn(p); //M�todo para hacer pin de entrada
}

//Operador para definir pin de salida
void Pines::operator >> (unsigned char p){
	DigitalOut(p);//M�todo para hacer pin de salida
}

//Operador logico AND
bool Pines::operator & (bool e){
	return GetPin()&e;
}

//Operador logico OR
bool Pines::operator | (bool e){
	return GetPin()|e;
}

//Operador logico XOR
bool Pines::operator ^ (bool e){
	return GetPin()^e;
}

//Operador NOT; 
bool Pines::operator ! (void){
	return !GetPin();
}

//Operador l�gico auto AND 
void Pines::operator &= (bool e){
	SetPin(GetPin()&e);
}

//Operador l�gico auto OR
void Pines::operator |= (bool e){
	SetPin(GetPin()|e);
}

//Operador l�gico auto XOR
void Pines::operator ^= (bool e){
	SetPin(GetPin()^e);
}








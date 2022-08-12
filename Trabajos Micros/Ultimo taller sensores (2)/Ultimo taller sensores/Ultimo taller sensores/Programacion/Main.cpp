#include "stm32f4xx.h"                  // Device header
#include "Delay.h"
#include "ADC.h"
#include "Usart2.h"
#include "math.h"
#include "stdio.h"
/*
Pines Usart A2 A3 F
			ADC A0 Canal-AF8
*/
int ContadorSystick=0,ValADC=0,contadorint=0;
//variables del filtro
float XK=0.0,Xkp=0.0,Pk=0.0,qf=1000,Rk=0.5,Qk,adc,Gk;
float ConversionADC=0;
double voltaje =0;
double CAP_ADC[83]={};
int contadorBPM=0;
////////////// GLCD NOKIA ////////////
char LateralGrafica[3]={0x01,0xFF,0x01};
char Horizontal1 [5] = {0x00,0x01,0x01,0x01,0x01};
char Horizontal2 [5] = {0x01,0x01,0x01,0x01,0x01};
char LTemp[26] = {0x01,0x01,0x3F,0x01,0x01,0x00,0x3F,0x25,0x25,0x21,0x00,0x3F,0x02,0x04,0x02,0x3F,0x00,0x3F,0x09,0x09,0x06,0x00,0x00,0x36,0x36,0x00};
char Lt[5]={0x00,0x02,0x0F,0x0A,0x00};
char LT[5]={0x00,0x01,0x0F,0x01,0x00};
int C_Pixel=0;
int setX_Pixel = 0x85;
int setY_Pixel = 0x44;
int Pixel_X=0;
int Pixel_Y=0;
int Unidad_Pixel=0;
int Decena_Pixel=0;
float tiempo =0;
int c=0,d=0,u=0,i=0;
int satatusContador=0;
char N1[5]={0x00,0x22,0x3F,0x20,0x00};
char N2[5]={0x3D,0x25,0x25,0x27,0x00};
char N3[5]={0x25,0x25,0x25,0x3F,0x00};
char N4[5]={0x0F,0x08,0x08,0x3F,0x00};
char N5[5]={0x27,0x25,0x25,0x3D,0x00};
char N6[5]={0x3F,0x25,0x25,0x3D,0x00};
char N7[5]={0x01,0x09,0x09,0x3F,0x00};
char N8[5]={0x3F,0x25,0x25,0x3F,0x00};
char N9[5]={0x0F,0x09,0x09,0x3F,0x00};
char N0[5]={0x3F,0x21,0x21,0x3F,0x00};
char clear=0x01;
char set=0x38;//
char disp_on=0x0E;//
char mode=0x06; //
char ddram1L=0x80;//linea arriba
char ddram2L=0xC0;//de abajo
int contadorBPMAux=0;
int contadorlcd=0;
				char Variablex[30];
void IniciarStm32F4(void){
	RCC -> AHB1ENR = 7;
	RCC->APB2ENR |= (1UL<<14);
	SYSCFG->EXTICR[0] = 0x0;
	NVIC_EnableIRQ(EXTI0_IRQn);
	EXTI->IMR |= 0x1;
	EXTI->EMR |= 0x1;
	EXTI->RTSR |= 0x1;
	EXTI ->PR |= 0x1;
	GPIOC->MODER |=0x55555;
	//GPIOA -> MODER |= 0x300;
	
	GPIOB->MODER |= 0x885;		// PINES EN MODO ALTERNO PARA USO DE SPI  Y 2 EN SALIDA                        
	GPIOB->AFR[0] |= 0x505000;					// PINES PARA SPI
	
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock/2000);
}
void send_comando(char a){//envia dato
GPIOC->ODR=a|(1UL<<9);
for(int i=0;i<50000;i++){__NOP();}
GPIOC->ODR&=~(1UL<<9);
}
void send_dato(char b){
GPIOC->ODR=b|(3<<8);
for(int i=0;i<50000;i++){__NOP();}
GPIOC->ODR&=~(1UL<<9);
}
void TxSPI(char d){
	SPI1 -> DR = d;
	while(SPI1 -> SR&SPI_SR_BSY); //Esperar fin de l transmision
}

void sendComando(char d){
	GPIOB->ODR=2;
	TxSPI(d);
}

void sendDato(char d){
	GPIOB->ODR=3;
	TxSPI(d);
}
 void pixel(int x, int y){ 

	sendComando(x/8+0x80);     			
	sendComando(y/6+	0x40);
	sendDato(pow(2,(y/8)));
}
 void pixel_En_FGrafica(int x, int y){
 
 	sendComando(0x80+x);  
		/*if((0x43-y/10)>=0.8){
			sendComando(0x43+0);
		}else{
						sendComando(0x43-y/10);
		}*/
	sendComando(0x43-y/10);
	 
	Decena_Pixel=y/10;
	Unidad_Pixel=y-(Decena_Pixel*10);
	switch(Unidad_Pixel){
		case 0: if(x==0){C_Pixel=0;}
						else{C_Pixel=0x80;}break;
						case 1: C_Pixel=0x80; break;
						case 2: C_Pixel=0x40; break;
						case 3: C_Pixel=0x20; break;
						case 4: C_Pixel=0x10; break;
						case 5: C_Pixel=0x10; break;
						case 6: C_Pixel=0x8;  break;
						case 7: C_Pixel=0x4;  break;
						case 8: C_Pixel=0x2;  break;
						case 9: C_Pixel=0x1;  break;
	}
	sendDato(C_Pixel);
 }
 void VisualizarNum (int a){
	switch (a){
		case 1:
			for(int i=0; i<5; i++) sendDato(N1[i]);
		break;
		
		case 2:
			for(int i=0; i<5; i++) sendDato(N2[i]);
		break;
		
		case 3:
			for(int i=0; i<5; i++) sendDato(N3[i]);
		break;
		
		case 4:
			for(int i=0; i<5; i++) sendDato(N4[i]);
		break;
		
		case 5:
			for(int i=0; i<5; i++) sendDato(N5[i]);
		break;
		
		case 6:
			for(int i=0; i<5; i++) sendDato(N6[i]);
		break;
		
		case 7:
			for(int i=0; i<5; i++) sendDato(N7[i]);
		break;
		
		case 8:
			for(int i=0; i<5; i++) sendDato(N8[i]);
		break;
		
		case 9:
			for(int i=0; i<5; i++) sendDato(N9[i]);
		break;
		
		default:
			for(int i=0; i<5; i++) sendDato(N0[i]);
		break;
	}
}

extern "C"{
	
	void ADC_IRQHandler(void){
//			Qk=qf/1000.0;
//			adc=adc*0.86;
//			while((ADC1->SR & 0x20)==1){__NOP();}
//			adc=ADC1 ->DR;
//			Xkp=XK;
//			Pk=Pk+Qk;
//			//if(Pk!=0||Rk!=0){
//				Gk=Pk/(Pk+Rk);
//			//}
//			XK=XK+(Gk*(adc - XK));
//			Pk=(1-Gk)*Pk;
//			Qk=qf;//1000.0;
//			adc=adc*500;
//			while((ADC1->SR & 0x20)==1){__NOP();}
//			adc=ADC1 ->DR;
//			Xkp=XK;
//			Pk=Pk+Qk;
//			//if(Pk!=0||Rk!=0){
//				Gk=Pk/(Pk+Rk);
//			//}
//			XK=XK+(Gk*(adc - XK));
//			Pk=(1-Gk)*Pk;
			Qk=qf;//1000.0;
			//adc=adc*500;
			adc=ADC1 ->DR;
		
			Xkp=adc;
			Pk=Pk+Qk;
			//if(Pk!=0||Rk!=0){
				Gk=Pk/(Pk+Rk);
			//}
			XK=Xkp+(Gk*(1 - XK));
			Pk=(1-Gk)*Pk;
			voltaje= (Xkp*3.3)/4095;
			voltaje= voltaje * 100;
			voltaje -= 50;
	 		//SendUsart2('F',0,0,adc);
//			i++;	
//			
//			 CAP_ADC[i] = voltaje;
//			
//			if(i>83){
//				i=0;
//				for(int j=0;j<83;j++){
//				CAP_ADC[j] = 0;
//				}
//			}
			
	}
	void SysTick_Handler (void){			
			
		tiempo=tiempo+0.05;
		if(tiempo>=83.0){
		tiempo=0;
			for (int l=0;l<6;l++){
		 sendComando(0x80);
		 sendComando(0x40+l);	
		for (int co=0;co<84;co++){
				sendDato(0x00);
		}
	}
	
}	
		if(satatusContador==1){
			
			contadorBPMAux=contadorBPM;
			contadorBPMAux=(1/(contadorBPMAux*0.0005))*60;
			sprintf(Variablex, "%d BPM      ",contadorBPMAux );
		
			satatusContador=0;
			contadorBPM=0;
	}
			if(satatusContador==0){
			contadorBPM++;
			
	} 
	

		}
	void EXTI0_IRQHandler(void){
		EXTI ->PR |= 0x1;
		satatusContador=1;
		contadorlcd=0;
		send_comando(ddram2L);
		while(Variablex[contadorlcd]!=0){
			send_dato(Variablex[contadorlcd]);
			contadorlcd++;
		}	
	}
	}
    
int main(void){
	IniciarStm32F4();
	ConfiguracionADC();
	ConfiguracionUsart2();
	send_comando(clear); // limpiar 
	send_comando(set);	//
	send_comando(disp_on);
	send_comando(mode);
	send_comando(ddram1L);//activa linea 1
	//CONFIGURACION SPI
		RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;				// ACTIVACION DE RELOJ SPI
		SPI1->CR1|=0;															
		SPI1->CR1|=(7<<3)|SPI_CR1_MSTR|SPI_CR1_SPE;	// MODO MAESTRO 
		GPIOB->ODR=2;																// MANTIENE ENCENDIDO EL RST
		for(int r=0; r<10000;r++)__ASM("NOP");
		TxSPI(0X20);																
		TxSPI(0X0C);
		GPIOB->ODR |=0x3;
	
		//Configuracion GLCD
	sendComando(0x20);
	sendComando(0x0C);
	sendComando(0x40);
	sendComando(0x80);

	/////// GRAFICA //////////
//	for(int i=0;i<5;i++) sendDato(LT[i]);
//	for(int i=0;i<3;i++) sendDato(LateralGrafica[i]);
//	sendComando(0x41);
//	sendComando(0x80+5);
//	for(int i=0;i<3;i++) sendDato(LateralGrafica[i]);
//	sendComando(0x42);
//	sendComando(0x80+5);
//	for(int i=0;i<3;i++) sendDato(LateralGrafica[i]);
//	sendComando(0x43);
//	sendComando(0x80+5);
//	for(int i=0;i<3;i++) sendDato(LateralGrafica[i]);
//	sendComando(0x44);
//	sendComando(0x80+5);
//	for(int i=0;i<5;i++) sendDato(Horizontal1[i]);
//	for(int j=0;j<11;j++){ for(int i=0;i<5;i++)sendDato(Horizontal2[i]);}
//	for(int i=0;i<5;i++) sendDato(Lt[i]);
//	

	
	while(1){
		ADC1-> CR2 |=(1UL<<30);
		while((ADC1->SR & 0x20)==1);

		pixel_En_FGrafica(tiempo,voltaje);
		
	}
}
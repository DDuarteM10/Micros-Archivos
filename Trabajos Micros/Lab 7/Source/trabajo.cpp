#include "stm32f4xx.h"
#include "stdio.h"
#include "math.h"                  // Device header
#include "Usart2.h"


double volt=0;
double dis=0;
double temp=0;
double foto=0;
int contadorADC1=0;
int cen=0,de=0, un=0, del1=0, del2=0,error1=0,error2=0,error3=0;
int xx=0, adc = 0;
char Label[11] = {'D','i','s','t','a','n','c','i','a',' ','='};
float distancia[10];
float temperatura[10];
float Lumens[10];
float PromedioDistacia,PromedioTemperatura,PromedioFoto,sumdis=0;
int time=0;
/////// LCD /////////
char clear = 0x01;
char Set =0x38;
char Disp_On = 0x0E;
char mode = 6;
char ddram1L = 0x80;
char ddram2L = 0xC0;
int contadorToSendLCD=0;
char DatosDistancia[30];
/////////////////////
////Variables de status/////////
int CondicionDatos=0;//Inicia la convrsion=0 Inicia el promedio =1 }Inicia la comparacion=2
int canalDC;

void send_comando(char d){
	GPIOC -> ODR = d|(1UL<<9);
	for(int i=0;i<50000;i++){__NOP();}
	GPIOC -> ODR &=~ (1UL<<9);
}		
void send_dato(char a){
	GPIOC -> ODR = a|(3<<8);
	for(int i=0;i<50000;i++){__NOP();}
	GPIOC -> ODR &=~ (1UL<<9);
}
float Promedio(float DatosPromediar[] ){
	float pro=0;
	float Suma=0;
	for(int veces=0;veces<10;veces++){
		Suma=DatosPromediar[veces];
	}
	pro=(Suma/10)*10;
	
	return pro;
}

int Luminosidad (float Diff[10],float prom){
 
	int contadorint=0;
	float porcentaje=0;
	for(int i=0;i<10;i++){
	//Diff[i]=round(Diff[i]);
		porcentaje=(Diff[i]-prom)/prom*100;
		if(porcentaje<0){porcentaje=porcentaje*-1;
		}
		if(porcentaje>=10){
			contadorint++;
		}
	}
	
	return contadorint;
}


extern "C"{
	
	void ADC_IRQHandler(void){//Hacer menu para leer los canales 
		
		switch (canalDC)
    {
    	case 0:{
				adc = ADC1 -> DR;
				volt = ( adc * 3.3)/4095;  // lo convierte en el valor de voltaje ACTUAL
				//dis = (((-480.5)*volt) + 1200)/100; 	
				dis= (((-430.4)*volt) + 1400)/100;
				distancia[contadorADC1] =dis;
				
				contadorToSendLCD=0;
				send_comando(ddram2L);
				sprintf(DatosDistancia,"%0.2f  CM",dis);
				while(DatosDistancia[contadorToSendLCD]!=0){
					send_dato(DatosDistancia[contadorToSendLCD]);
					contadorToSendLCD++;
				}
		
				
			}
    		break;
    	case 6:{
				adc = ADC1 -> DR;
				volt = adc;  // lo convierte en el valor de voltaje ACTUAL
				//dis = (((-480.5)*volt) + 1200)/100; 	
				temp= (((8058)*volt))/100000.0;
				temperatura[contadorADC1] =temp;
			}
    		break;
			case 7:{
				adc = ADC1 -> DR;
				volt = adc;  // lo convierte en el valor de voltaje ACTUAL
				//dis = (((-480.5)*volt) + 1200)/100; 	
				foto= volt;
				Lumens[contadorADC1] =foto;
			}
    		break;
    	default:
    		break;
    }
		
		
	}
	void SysTick_Handler (void){

		if(CondicionDatos==1){
			PromedioDistacia=Promedio(distancia);
			//PromedioDistacia=round(PromedioDistacia);
			PromedioTemperatura=Promedio(temperatura);
			//PromedioTemperatura=round(PromedioTemperatura);
			PromedioFoto=Promedio(Lumens);
			//PromedioFoto=round(PromedioFoto);
			error1=Luminosidad(distancia,PromedioDistacia);
			error2=Luminosidad(temperatura,PromedioTemperatura);
			error3=Luminosidad(Lumens,PromedioFoto);
			TIM4->CCR1=(error1*553.6/5);
			TIM4->CCR2=(error2*553.6/5);
			TIM4->CCR3=(error3*553.6/5);
			CondicionDatos=2;
		
		}
		if(CondicionDatos==2){
			for(int veces=0;veces<10;veces++){
			SendUsart2('F',0,0,distancia[veces]);
			}
			for(int veces=0;veces<10;veces++){
			SendUsart2('F',0,0,temperatura[veces]);
			}
			for(int veces=0;veces<10;veces++){
			SendUsart2('F',0,0,Lumens[veces]);
			}
		}
		 
	}
}
 


int main(){ 

	RCC -> AHB1ENR = 7;
	GPIOA -> MODER |= 0xF003;
	GPIOA -> PUPDR |= 0x2;
	GPIOC -> MODER = 0x55555555;
	GPIOB->MODER|=0xAA800;//10 10 10 00 00 00 00 00
	GPIOB->OTYPER|=0x55000;
	GPIOB->OSPEEDR|=0x55000;
	GPIOB->AFR[0] |=0x22200000;
	GPIOB->AFR[1] |=0x22;
	// Timers
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	TIM4 ->PSC=56;
	TIM4 -> ARR=5536;
	TIM4->EGR |=1;
	TIM4->CR1=0x1;
	TIM4->CCMR1 |=0x6060;
	TIM4->CCMR2 |=0x6060;
	TIM4->CCER |=0x1111;
	//TIM4->CCR1 |= 5000; //PB6
	//TIM4->CCR2 |= 5000; //PB7
	//TIM4->CCR3 |= 500; //PB8
	
	// ADC
	RCC->APB2ENR |=RCC_APB2ENR_ADC1EN; // Activo el reloj del ADC1
	ADC1->CR1 |=0x20; // Activo la interrupcion del ADC		
	ADC1->CR2|= (1UL<<10); // Interrupcion individual
	ADC1->CR2|= 0x01;      // ADON es para inicial el ADC
	NVIC_EnableIRQ(ADC_IRQn); // Activo el vector de interrupciones para el ADC
	//Usary
	ConfiguracionUsart2();
	
	send_comando(clear);
	send_comando(Set);
	send_comando(Disp_On);
	send_comando(mode);
	send_comando(ddram1L);
	for(int i=0;i<11;i++){send_dato(Label[i]);}
	
	
	SystemCoreClockUpdate();
	SysTick_Config(SystemCoreClock);
			
	
	
	while(true){
		if(CondicionDatos==0){
			//Canal 0 Distancia PA0
			ADC1-> SQR3 = 0;
			canalDC=0;
			for(int veces=0;veces<10;veces++){
			ADC1-> CR2 |=(1UL<<30);
			while((ADC1->SR & 0x20)==1);
			contadorADC1=veces;
			for(int timer=0;timer<35000;timer++){__NOP();}
			}
			ADC1-> SQR3 = 6;// temperatura PA6
			canalDC=6;
			for(int veces=0;veces<10;veces++){
			ADC1-> CR2 |=(1UL<<30);
			while((ADC1->SR & 0x20)==1);
			contadorADC1=veces;
			for(int timer=0;timer<35000;timer++){__NOP();}
			}
			
			ADC1-> SQR3 = 7;// LED PA7
			canalDC=7;
			for(int veces=0;veces<10;veces++){
			ADC1-> CR2 |=(1UL<<30);
			while((ADC1->SR & 0x20)==1);
			contadorADC1=veces;
			for(int timer=0;timer<35000;timer++){__NOP();}
			}
			CondicionDatos=1;
			//Canal x

		}
		
	}
} 
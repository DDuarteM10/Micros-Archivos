#include "Delay.h" //10000
#include "Delay.h" //10000
#include "oled.h"
#include "horse_anim.h".h"
#include "stdio.h"
char zz[10];
void Uniciar_Clock(void){
	#define PLL_M      4
#define PLL_N      200
#define PLL_P      4
#define PLL_Q      2
	
	
__IO uint32_t StartUpCounter = 0, HSEStatus = 0;
  

  RCC->CR |= ((uint32_t)RCC_CR_HSEON);
 

  do
  {
    HSEStatus = RCC->CR & RCC_CR_HSERDY;
    StartUpCounter++;
  } while((HSEStatus == 0) && (StartUpCounter != 3000));

  if ((RCC->CR & RCC_CR_HSERDY) != RESET)
  {
    HSEStatus = (uint32_t)0x01;
  }
  else
  {
    HSEStatus = (uint32_t)0x00;
  }

  if (HSEStatus == (uint32_t)0x01)
  {
 
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;
    PWR->CR &= (uint32_t)~(PWR_CR_VOS);


    RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
      

    RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;
    

    RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;


    RCC->PLLCFGR = PLL_M | (PLL_N << 6) | (((PLL_P >> 1) -1) << 16) |
                   (RCC_PLLCFGR_PLLSRC_HSE) | (PLL_Q << 24);


    RCC->CR |= RCC_CR_PLLON;

    
    while((RCC->CR & RCC_CR_PLLRDY) == 0)
    {
    }
   
    /* Configure Flash prefetch, Instruction cache, Data cache and wait state */
    FLASH->ACR = FLASH_ACR_ICEN |FLASH_ACR_DCEN |FLASH_ACR_LATENCY_3WS;

    /* Select the main PLL as system clock source */
    RCC->CFGR &= (uint32_t)((uint32_t)~(RCC_CFGR_SW));
    RCC->CFGR |= RCC_CFGR_SW_PLL;

    /* Wait till the main PLL is used as system clock source */
    while ((RCC->CFGR & (uint32_t)RCC_CFGR_SWS ) != RCC_CFGR_SWS_PLL)
    {;}
  }
  else
  { /* If HSE fails to start-up, the application will have wrong clock
         configuration. User can add here some code to deal with this error */
  }
//RCC->AHB1ENR |=7;
}
int main(void){
	
	RCC->AHB1ENR |=7;
	Uniciar_Clock();
	SSD1306_Init();

	SSD1306_GotoXY (10, 10);
	
	SSD1306_Puts ("Mecatronica 2022", &Font_7x10, SSD1306_COLOR_WHITE);
	SSD1306_DrawBitmap(75, 15, corazon, 58, 58,SSD1306_COLOR_BLACK);
	SSD1306_UpdateScreen();

	SSD1306_UpdateScreen(); //display
	for (int i=0; i<500;i++)
	{
	sprintf(zz,"%d",i);
	SSD1306_GotoXY (10, 30);	
	SSD1306_Puts (zz, &Font_7x10, SSD1306_COLOR_WHITE);
	SSD1306_UpdateScreen();
	Dalay(300);
	SSD1306_DrawRectangle(20,50,5,8,SSD1306_COLOR_WHITE);
	SSD1306_DrawTriangle(30,50,35,50,35,60,SSD1306_COLOR_WHITE);
	SSD1306_DrawCircle(60, 40, 15, SSD1306_COLOR_WHITE);}
//		SSD1306_Clear();
//		SSD1306_GotoXY (0, 0);
//		SSD1306_UpdateScreen();
		
		

	
	while(1)
{
	SSD1306_Clear();
	SSD1306_UpdateScreen();
	
SSD1306_Clear();
SSD1306_DrawBitmap(0,0,horse1,128,64,1);
SSD1306_UpdateScreen();

SSD1306_Clear();
SSD1306_DrawBitmap(0,0,horse2,128,64,1);
SSD1306_UpdateScreen();

SSD1306_Clear();
SSD1306_DrawBitmap(0,0,horse3,128,64,1);
SSD1306_UpdateScreen();

SSD1306_Clear();
SSD1306_DrawBitmap(0,0,horse4,128,64,1);
SSD1306_UpdateScreen();

SSD1306_Clear();
SSD1306_DrawBitmap(0,0,horse5,128,64,1);
SSD1306_UpdateScreen();

SSD1306_Clear();
SSD1306_DrawBitmap(0,0,horse6,128,64,1);
SSD1306_UpdateScreen();


SSD1306_Clear();
SSD1306_DrawBitmap(0,0,horse7,128,64,1);
SSD1306_UpdateScreen();

SSD1306_Clear();
SSD1306_DrawBitmap(0,0,horse8,128,64,1);
SSD1306_UpdateScreen();


SSD1306_Clear();
SSD1306_DrawBitmap(0,0,horse9,128,64,1);
SSD1306_UpdateScreen();


SSD1306_Clear();
SSD1306_DrawBitmap(0,0,horse10,128,64,1);
SSD1306_UpdateScreen();	
	
}
	return 0;
}
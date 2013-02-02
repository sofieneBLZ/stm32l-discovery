#include "main.h"
#include "includes.h"
#include "app_cfg.h"
#include <string.h>

#define enableInterrupts()   __enable_irq()
#define disableInterrupts()  __disable_irq()
void RCC_Configuration();
void printk(char *s);


static  OS_TCB   AppTaskStartTCB; 
static  CPU_STK  AppTaskStartStk[APP_TASK_START_STK_SIZE];

static  void  AppTaskStart  (void *p_arg);

OS_ERR  err;

int main()
{
	RCC_ClocksTypeDef RCC_Clocks;
	RCC_GetClocksFreq(&RCC_Clocks);
	RCC_Configuration();
	LCD_GLASS_Configure_GPIO();
	SysTick_Config(RCC_Clocks.HCLK_Frequency/1000);
	disableInterrupts();
	LCD_GLASS_Init();
  	OS_CPU_SysTickInit(RCC_Clocks.HCLK_Frequency/1000);

	CPU_Init();
    OSInit(&err);                                               /* Init uC/OS-III.                                      */
	if(err != OS_ERR_NONE)
	{
	}
    OSTaskCreate((OS_TCB     *)&AppTaskStartTCB,                /* Create the start task                                */
                 (CPU_CHAR   *)"App Task Start",
                 (OS_TASK_PTR )AppTaskStart, 
                 (void       *)0,
                 (OS_PRIO     )APP_TASK_START_PRIO,
                 (CPU_STK    *)&AppTaskStartStk[0],
                 (CPU_STK_SIZE)APP_TASK_START_STK_SIZE / 10,
                 (CPU_STK_SIZE)APP_TASK_START_STK_SIZE,
                 (OS_MSG_QTY  )0,
                 (OS_TICK     )0,
                 (void       *)0,
                 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
                 (OS_ERR     *)&err);
	
	if(err != OS_ERR_NONE)
	{
	}
	
	printk("RDY");
    OSStart(&err);      
	if(err != OS_ERR_NONE)
	{
	}
}


void RCC_Configuration(void)
{  
 	/* SYSCLK has been set in SystemInit() function */
	/* SYSCLK @ 32MHz */
  
  	/* Enable the GPIOs clocks */
 	 RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB | RCC_AHBPeriph_GPIOC| RCC_AHBPeriph_GPIOD| RCC_AHBPeriph_GPIOE| RCC_AHBPeriph_GPIOH, ENABLE);     

  	/* Enable comparator, LCD and PWR mngt clocks */
  	RCC_APB1PeriphClockCmd(RCC_APB1Periph_COMP | RCC_APB1Periph_LCD | RCC_APB1Periph_PWR,ENABLE);
    
  	/* Enable ADC & SYSCFG clocks */
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 | RCC_APB2Periph_SYSCFG , ENABLE);

  	/* Allow access to the RTC */
  	PWR_RTCAccessCmd(ENABLE);

  	/* Reset RTC Backup Domain */
  	RCC_RTCResetCmd(ENABLE);
  	RCC_RTCResetCmd(DISABLE);

 	 /* LSE Enable */
  	RCC_LSEConfig(RCC_LSE_ON);

  	/* Wait until LSE is ready */
  	while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);
  
  	 /* RTC Clock Source Selection */ 
  	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE); 
  
  	/* Enable the RTC */
  	RCC_RTCCLKCmd(ENABLE);   
  
}

/* printk function 
 * print string on LCD
 * the length of string should be less than or equal 6
*/

void printk(char *s)
{
	uint8_t slength;
	uint8_t i;
	if(strlen(s)>6)
		slength = 6;
	else
		slength = strlen(s);
	
	for(i=0;i<slength;i++)
	{
		LCD_GLASS_WriteChar((uint8_t *)s++,FALSE,FALSE,i+1);
	}
}

static  void  AppTaskStart (void *p_arg)
{
	while(1)
	{
		printk("RUN");
	}
}

CPU_TS_TMR  CPU_TS_TmrRd (void)
{
    return ((CPU_TS_TMR)0);
}

void CPU_TS_TmrInit()
{
}
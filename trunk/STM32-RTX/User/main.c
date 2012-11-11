#include "rtl.h"
#include "stm32l1xx.h"
#include "main.h"
#include <math.h>


//task1 is used to create other tasks , and delete it self after creating
OS_TID tsk_1,tsk_2,tsk_3,tsk_4;


__task void task_Init(void);
__task void task_LD(void);
__task void task_LCD(void);
__task void task_VAR(void);

static int stmstudio_var;
static int result;

int main(void)
{
	RCC_Configuration();
	Init_GPIOs();
	enableInterrupts();	
	os_sys_init(task_Init);
  for (;;);

}


__task void task_Init(void)
{
	
	tsk_2 = os_tsk_create(task_LD,0);
	tsk_3 = os_tsk_create(task_LCD,0);
	tsk_4 = os_tsk_create(task_VAR,0);
	os_tsk_delete_self();
}

__task void task_LD(void)
{

  for(;;)
	{
		GPIO_SetBits(LD_GPIO_PORT,LD_GREEN_GPIO_PIN );
		GPIO_ResetBits(LD_GPIO_PORT,LD_BLUE_GPIO_PIN );
		os_dly_wait(100);
		GPIO_ResetBits(LD_GPIO_PORT,LD_GREEN_GPIO_PIN );
		GPIO_SetBits(LD_GPIO_PORT,LD_BLUE_GPIO_PIN );
		os_dly_wait(100);
  }
}

__task void task_LCD(void)
{

	LCD_GLASS_Init();
	
  for(;;)
	{
		LCD_GLASS_ScrollSentence("      RTX KERNEL ON STM32  ",1,SCROLL_SPEED);
		os_dly_wait(500);
  }
}

__task void task_VAR(void)
{

	stmstudio_var = 0;
	os_itv_set(10);
  for(;;)
	{
		os_itv_wait();
		if(stmstudio_var<1000)
		{
			result = sin(stmstudio_var++)*100;
		}
		else
			stmstudio_var = 0;
  }
}








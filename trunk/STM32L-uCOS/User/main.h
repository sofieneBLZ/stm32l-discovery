#ifndef __MAIN_H__
#define __MAIN_H__

#include "os_cpu.h"
#include "stm32l1xx.h"

#define  uC_CFG_OPTIMIZE_ASM_EN                 DEF_ENABLED
#define  LIB_STR_CFG_FP_EN                      DEF_DISABLED


/*
*********************************************************************************************************
*                                            TASK PRIORITIES
*********************************************************************************************************
*/
#define  APP_TASK_TEST_PRIO 															 7
#define  APP_TASK_START_PRIO                               3
#define  APP_TASK_KBD_PRIO                                 4

#define  APP_TASK_USER_IF_PRIO                            12

#define  OS_PROBE_TASK_PRIO              (OS_LOWEST_PRIO - 3)
#define  OS_TASK_TMR_PRIO                (OS_LOWEST_PRIO - 2)

/*
*********************************************************************************************************
*                                            TASK STACK SIZES
*                             Size of the task stacks (# of OS_STK entries)
*********************************************************************************************************
*/
#define  APP_TASK_TEST_STK_SIZE													 128
#define  APP_TASK_START_STK_SIZE                         128
#define  APP_TASK_KBD_STK_SIZE                           128

#define  APP_TASK_USER_IF_STK_SIZE                       256

#define  OS_PROBE_TASK_STK_SIZE                          128

/*
*********************************************************************************************************
*                                                 LCD
*********************************************************************************************************
*/

#define  DISP_BUS_WIDTH                                    4    /* LCD controller is accessed with a 4 bit bus.         */

/*
*********************************************************************************************************
*                                                  LIB
*********************************************************************************************************
*/

#define  uC_CFG_OPTIMIZE_ASM_EN                 DEF_ENABLED
#define  LIB_STR_CFG_FP_EN                      DEF_DISABLED

/*
*********************************************************************************************************
*                                                 PROBE
*********************************************************************************************************
*/

#define  OS_PROBE_TASK                                     1    /* Task will be created for uC/Probe OS Plug-In.        */
#define  OS_PROBE_TMR_32_BITS                              0    /* uC/Probe OS Plugin timer is a 16-bit timer.          */
#define  OS_PROBE_TIMER_SEL                                2    /* Select timer 2.                                      */
#define  OS_PROBE_HOOKS_EN                                 1    /* Hooks to update OS_TCB profiling members included.   */
#define  OS_PROBE_USE_FP                                   1


INT32U  OS_CPU_SysTickClkFreq (void);


#define bool _Bool
#define FALSE 0
#define TRUE !FALSE

/* MACROs for SET, RESET or TOGGLE Output port */

#define GPIO_HIGH(a,b) 		a->BSRRL = b
#define GPIO_LOW(a,b)		a->BSRRH = b
#define GPIO_TOGGLE(a,b) 	a->ODR ^= b 

#define USERBUTTON_GPIO_PORT	GPIOA
#define USERBUTTON_GPIO_PIN     GPIO_Pin_0
#define USERBUTTON_GPIO_CLK     RCC_AHBPeriph_GPIOA

#define LD_GPIO_PORT 		GPIOB
#define LD_GREEN_GPIO_PIN 		GPIO_Pin_7
#define LD_BLUE_GPIO_PIN             GPIO_Pin_6
#define LD_GPIO_PORT_CLK             RCC_AHBPeriph_GPIOB

#define CTN_GPIO_PORT           GPIOC
#define CTN_CNTEN_GPIO_PIN      GPIO_Pin_13
#define CTN_GPIO_CLK            RCC_AHBPeriph_GPIOC

#define WAKEUP_GPIO_PORT        GPIOA

#define IDD_MEASURE_PORT	GPIOA
#define IDD_MEASURE             GPIO_Pin_4

#endif

/***
 * @Description:
 * @Author: Amamiya
 * @Date: 2022-06-19 15:44:42
 * @TechChangeTheWorld
 * @WHUROBOCON_Alright_Reserved
 */
#ifndef _MAIN_H
#define _MAIN_H

#include "delay.h"
#include <includes.h>
#include "led.h"
#include "IRCtrl.h"
#include "Xiao.h"
#include "Beep.h"

#define START_TASK_PRIO 5
#define TASK_RUN_PRIO 10
#define TASK_USART_PRIO 15
#define TASK_Scope_PRIO 20

#define START_TASK_STK_SIZE 128
#define TASK_RUN_STK_SIZE 128
#define TASK_USART_STK_SIZE 128
#define TASK_Scope_STK_SIZE 1024

__align(8) OS_STK start_task_stk[START_TASK_STK_SIZE];
__align(8) OS_STK task_USART_stk[TASK_USART_STK_SIZE];
__align(8) OS_STK task_RUN_stk[TASK_USART_STK_SIZE];
__align(8) OS_STK task_Scope_stk[TASK_Scope_STK_SIZE];

static void TaskStart(void *arg);
static void TaskRUN(void *arg);
static void TaskUSART(void *arg);
static void TaskScope(void *arg);

#endif

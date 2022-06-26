/***
 * @Description:
 * @Author: Amamiya
 * @Date: 2020-03-16 07:55:06
 * @TechChangeTheWorld
 * @WHUROBOCON_Alright_Reserved
 */
#include "main.h"

int main()
{
	SystemInit(); // 系统初始化
	delay_init();
	NVIC_SetPriorityGrouping(NVIC_PriorityGroup_2); // 设置中断分组为第三组

	delay_ms(100); // 启动延时
	GPIOCLKInit();
	Xiao = new XiaoClass();
	IRCtrl = new IRCtrlClass();
	Xiao->Init();
	IRCtrl->Init();
	LED_Init();
	TIM2_Init();
	Beep_Configuration();
	Beep_Start();

	OSInit(); // 启动UCOSII
	OSTaskCreate(TaskStart, (void *)0, &start_task_stk[START_TASK_STK_SIZE - 1], START_TASK_PRIO);
	OSStart();

	return 0;
}

static void TaskStart(void *pdata)
{
	pdata = pdata;
	OS_CPU_SR cpu_sr = 0;
	OSStatInit(); // 开始统计任务

	OS_ENTER_CRITICAL(); // 进入临界区
	OSTaskCreate(TaskUSART, (void *)0, &task_USART_stk[TASK_USART_STK_SIZE - 1], TASK_USART_PRIO);
	OSTaskCreate(TaskRUN, (void *)0, &task_RUN_stk[TASK_RUN_STK_SIZE - 1], TASK_RUN_PRIO);
	OSTaskSuspend(START_TASK_PRIO); // 挂起开始任务
	OS_EXIT_CRITICAL();				// 退出临界区
}

static void TaskRUN(void *pdata)
{
	for (;;)
	{
		switch (Xiao->getControlMode())
		{
		case InfraredRemoteControl:
			IRCtrl->Control(Xiao);
			break;
		}
		Xiao->Run(Master.ControlMsg.leftSpeed, Master.ControlMsg.rightSpeed);
		delay_ms(20);
	}
}

/**
 * @brief 串口消息更新  250hz
 */
char _temp;
static void TaskUSART(void *pdata)
{
	int tic = 0;
	float usart_time_step = 4.0;
	for (;;)
	{
		delay_ms(usart_time_step);
		tic += 1;
		if (tic % (int)(2 * 1000 / usart_time_step) < 1000 / usart_time_step)
			LED2_ON;
		else
			LED2_OFF;
	}
}

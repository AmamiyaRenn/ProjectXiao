/***
 * @Description:
 * @Author: Amamiya
 * @Date: 2020-03-16 07:55:06
 * @TechChangeTheWorld
 * @WHUROBOCON_Alright_Reserved
 */
#include "main.h"

UsartClass Usart;
XiaoClass *Xiao;
GyroCtrlClass *GyroCtrl;

int main()
{
	SystemInit(); // 系统初始化
	delay_init();
	NVIC_SetPriorityGrouping(NVIC_PriorityGroup_2); // 设置中断分组为第三组

	delay_ms(100); // 启动延时
	GPIOCLKInit();
	Chassis.MotorHardwareInit();
	LED_Init();
	TIM2_Init();
	Beep_Configuration();
	Usart.usart3Init(9600);

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
	OSTaskCreate(TaskScope, (void *)0, &task_Scope_stk[TASK_Scope_STK_SIZE - 1], TASK_Scope_PRIO);
	OSTaskSuspend(START_TASK_PRIO); // 挂起开始任务
	OS_EXIT_CRITICAL();				// 退出临界区
}

static void TaskRUN(void *pdata)
{
	GyroCtrl = new GyroCtrlClass(&Master.ControlMsg.roll, &Master.ControlMsg.pitch);
	GyroCtrl->setThreshold(0.05f, 0.1f);
	Xiao = new XiaoClass(&Chassis, GyroCtrl);
	for (;;)
	{
		if (Master.ControlMsg.Begin)
		{
			switch (Master.ControlMsg.ControlMode)
			{
			case BluetoothRemoteControl:
				Xiao->GyroCtrlFunction();
				break;

			case InfraredRemoteControl:
				Xiao->Run(Master.ControlMsg.leftSpeed, Master.ControlMsg.rightSpeed);
				break;
			}
		}
		else
			Xiao->Run(0, 0);
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
		tic += 1;
		if (tic % (int)(2 * 1000 / usart_time_step) < 1000 / usart_time_step)
			LED2_ON;
		else
			LED2_OFF;
		// Master.ReadMsg(_temp); // 上位机消息
		delay_ms(usart_time_step);
	}
}

static void TaskScope(void *pdata)
{
	for (;;)
	{
		Master.SendMsg(); // 发送到手机
		delay_ms(20);
	}
}

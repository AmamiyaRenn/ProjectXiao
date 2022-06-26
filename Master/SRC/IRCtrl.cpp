/***
 * @Description: Infrared Remote Control
 * @Author: Amamiya
 * @Date: 2022-06-19 16:36:11
 * @TechChangeTheWorld
 * @WHUROBOCON_Alright_Reserved
 */
#include "IRCtrl.h"

IRCtrlClass *IRCtrl;

// 外部中断配置 红外遥控配置
void IRCtrlClass::Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure; // 定义一个外部中断相关的结构体
	NVIC_InitTypeDef NVIC_InitStructure; // 定义一个中断的结构体

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	GPIO_InitStructure.GPIO_Pin = IRIN_PIN;			  // 配置使能GPIO管脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;	  // 配置GPIO模式,输入上拉
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; // 配置GPIO端口速度
	GPIO_Init(IRIN_GPIO, &GPIO_InitStructure);

	GPIO_EXTILineConfig(IRIN_PORTSOURCE, IRIN_PINSOURCE);
	EXTI_InitStructure.EXTI_Line = IRIN_EXITLINE;			// 将对应的GPIO口连接到中断线上
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; // 中断事件类型，下降沿
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;		// 选择模式，中断型
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;				// 使能该中断
	EXTI_Init(&EXTI_InitStructure);							// 将配置好的参数写入寄存器

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);			  // 阶级为0，不可嵌套
	NVIC_InitStructure.NVIC_IRQChannel = IRIN_IRQCH;		  // 打开PINA_8的外部中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; // 主优先级0，最高
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;		  // 子优先级，最低
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			  // 使能该模块中断
	NVIC_Init(&NVIC_InitStructure);							  // 中断初始化，将结构体定义的数据执行

	TIM3_Init();
}

// 接受到新消息
void IRCtrlClass::RecNewMsg(void)
{
	unsigned char j, k, N = 0;
	delay_us(2100); // 2.1ms
	if (IRIN == 1)
		return;

	continue_time = 40; // 40*5 = 200ms 无指令停车

	//确认IR信号出现
	while (!IRIN) //等IR变为高电平，跳过9ms的前导低电平信号。
	{
		delay_us(140);
	}

	for (j = 0; j < 4; j++) //收集四组数据
	{
		for (k = 0; k < 8; k++) //每组数据有8位
		{
			while (IRIN) //等 IR 变为低电平，跳过4.5ms的前导高电平信号。
			{
				delay_us(140);
			}
			while (!IRIN) //等 IR 变为高电平
			{
				delay_us(140);
			}
			while (IRIN) //计算IR高电平时长
			{
				delay_us(140);
				N++;
				if (N >= 30)
				{
					return;
				}					  // 0.14ms计数过长自动离开。
			}						  //高电平计数完毕
			IRCOM[j] = IRCOM[j] >> 1; //数据最高位补“0”
			if (N >= 8)
			{
				IRCOM[j] = IRCOM[j] | 0x80;
			} //数据最高位补“1”
			N = 0;
		} // end for k
	}	  // end for j

	k = ~IRCOM[3];
	if (IRCOM[2] != k)
		return;

	//指令转换
	switch (IRCOM[2])
	{
	case 0x46:
		ctrl_comm = COMM_UP;
		break;

	case 0x15:
		ctrl_comm = COMM_DOWN;
		break;

	case 0x44:
		ctrl_comm = COMM_LEFT;
		break;

	case 0x43:
		ctrl_comm = COMM_RIGHT;
		break;

	case 0x40:
		ctrl_comm = COMM_STOP;
		break;

	default:
		return;
	}
	ir_rec_flag = true;
}

/**
 * @brief 红外遥控主函数
 * @param Xiao 被控对象
 */
void IRCtrlClass::Control(XiaoClass *Xiao)
{
	if (ir_rec_flag) // 接收到红外信号
	{
		ir_rec_flag = false;
		switch (ctrl_comm)
		{
		case COMM_UP:
			Xiao->Run(SPEED_DUTY, SPEED_DUTY);
			break;

		case COMM_DOWN:
			Xiao->Run(-SPEED_DUTY, -SPEED_DUTY);
			break;

		case COMM_LEFT:
			Xiao->Run(-20, SPEED_DUTY + 10);
			break;

		case COMM_RIGHT:
			Xiao->Run(SPEED_DUTY + 10, -20);
			break;

		case COMM_STOP:
			Xiao->Run(0, 0);
			break;
		}
	}
}

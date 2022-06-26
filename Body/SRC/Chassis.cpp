/***
 * @Description:
 * @Author: Amamiya
 * @Date: 2022-06-19 11:19:49
 * @TechChangeTheWorld
 * @WHUROBOCON_Alright_Reserved
 */
#include "Chassis.h"

ChassisClass Chassis;

// 电机硬件初始化
void ChassisClass::MotorHardwareInit()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = FRONT_LEFT_F_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(FRONT_LEFT_F_GPIO, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = FRONT_LEFT_B_PIN;
	GPIO_Init(FRONT_LEFT_B_GPIO, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = FRONT_RIGHT_F_PIN;
	GPIO_Init(FRONT_RIGHT_F_GPIO, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = FRONT_RIGHT_B_PIN;
	GPIO_Init(FRONT_RIGHT_B_GPIO, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = BEHIND_LEFT_F_PIN;
	GPIO_Init(BEHIND_LEFT_F_GPIO, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = BEHIND_LEFT_B_PIN;
	GPIO_Init(BEHIND_LEFT_B_GPIO, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = BEHIND_RIGHT_F_PIN;
	GPIO_Init(BEHIND_RIGHT_F_GPIO, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = BEHIND_RIGHT_B_PIN;
	GPIO_Init(BEHIND_RIGHT_B_GPIO, &GPIO_InitStructure);
}

// 更新电机
void ChassisClass::updateAllMotor()
{
	BEHIND_RIGHT_EN;
	// 1. 更新SpeedDutyCount
	SpeedDutyCount++;
	SpeedDutyCount %= 50;
	// 2. 左边速度更新
	if (leftSpeed > 0) // 向前
		if (SpeedDutyCount < leftSpeed)
		{
			FRONT_RIGHT_GO;
		}
		else
		{
			FRONT_RIGHT_STOP;
		}
	else if (leftSpeed < 0) // 向后
		if (SpeedDutyCount < (-1) * leftSpeed)
		{
			FRONT_RIGHT_BACK;
		}
		else
		{
			FRONT_RIGHT_STOP;
		}
	else // 停止
	{
		FRONT_RIGHT_STOP;
	}
	// 3. 右边速度更新
	if (rightSpeed > 0) // 向前
		if (SpeedDutyCount < rightSpeed)
		{
			BEHIND_LEFT_GO;
		}
		else
		{
			BEHIND_LEFT_STOP;
		}
	else if (rightSpeed < 0)
		if (SpeedDutyCount < (-1) * rightSpeed)
		{
			BEHIND_LEFT_BACK;
		}
		else
		{
			BEHIND_LEFT_STOP;
		}
	else // 停止
	{
		BEHIND_LEFT_STOP;
	}
}

/***
 * @Description:
 * @Author: Amamiya
 * @Date: 2022-06-12 15:57:44
 * @TechChangeTheWorld
 * @WHUROBOCON_Alright_Reserved
 */
#include "MasterParam.h"

MasterParam Master;

void MasterParam::ReadMsg(u32 temp)
{
    if (data_process.getHeadMsg(temp))
        if (data_process.headId() == 1) // 上位机->主控板为编号1
        {
            if (data_process.dataDecode<ControlMsgStruct>(temp, &ControlMsg))
                if (ControlMsg.Reset)
                {
                    __set_FAULTMASK(1); // 把FAULTMASK置位，即关闭所有的中断执行复位时不被中断打断
                    NVIC_SystemReset(); // 系统软件复位，配置好的外设寄存器也一起复位
                }
        }
        else
            data_process.clearFlag();
}

void MasterParam::SendMsg()
{
    int length;
    char *data = data_process.dataEncode<RobotMsgStruct>(&RobotMsg, 11, &length); // 主控板->上位机为编号1;
}

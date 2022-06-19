/***
 * @Description:
 * @Author: Amamiya
 * @Date: 2022-06-19 16:37:02
 * @TechChangeTheWorld
 * @WHUROBOCON_Alright_Reserved
 */
#ifndef _IRCTRL_H
#define _IRCTRL_H

#include "timer.h"
#include "Xiao.h"

class IRCtrlClass
{
public:
    void Init();
    void RecNewMsg();
    void Control(XiaoClass *Xiao);

private:
    bool ir_rec_flag; // 接收数据标志位 1 有新数据 0 没有
    u8 continue_time; // 连发信号，表示指令持续(ms)
    u8 IRCOM[4];
    char ctrl_comm;
};

extern IRCtrlClass *IRCtrl;

#endif

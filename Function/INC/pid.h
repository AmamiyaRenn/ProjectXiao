#ifndef __PID_H
#define __PID_H

#include "MyMath.h"

// 位置式PID
struct PIDPosition
{
    float err;
    float errNext;
    float loc_sum; // 累计积分位置
    float pos;     // 位置式输出
    float max_sum;
    float kp, ki, kd;
    float k;         // 结果乘以个系数
    float setNum;    // 设定值
    float actualNum; // 实际值
    float threshold; // 阈值
    float max_out;   // 最大输出值
    void pidInit(float k, float p, float i, float d, float threshold, float max_out)
    {
        k = k;
        kp = p;
        ki = i;
        kd = d;
        threshold = threshold; // 阈值
        max_out = max_out;     // 最大输出
        setNum = 0;            // 设定值
        actualNum = 0;         // 实际值
        err = 0;               // 偏差值
        errNext = 0;
        loc_sum = 0;
        pos = 0;
        max_sum = 10000000;
    };

    // 位置式pid
    float pidPosUpdate(float setNum, float actualNum)
    {
        setNum = setNum;
        actualNum = actualNum;
        err = setNum - actualNum;
        if ((err > threshold) || (err < -threshold))
            loc_sum += err;

        loc_sum = constrainValue(loc_sum, -max_sum, max_sum);

        pos = kp * err + ki * loc_sum + kd * (err - errNext);
        errNext = err;

        pos *= k;
        pos = constrainValue(pos, -max_out, max_out);
        return pos;
    };

    void setPid(float p, float i, float d)
    {
        kp = p;
        ki = i;
        kd = d;
    };
};

// 增量式PID
class PIDIncrement
{
public:
    PIDIncrement(float *actualNum) : actualNum(actualNum){};
    void Init(float KP, float KI, float KD)
    {
        reference = 0;
        errLast = 0;
        errNow = 0;
        errLastLast = 0;
        this->KP = KP;
        this->KI = KI;
        this->KD = KD;
    }
    void Operation()
    {
        errNow = reference - *actualNum;
        // 只有过阈值后才认为需要PID调节
        if ((errNow > threshold) || (errNow < -threshold))
            increment = KP * (errNow - errLast) + KI * errNow + KD * (errNow - 2 * errLast + errLastLast);
        // 输出限幅
        increment = constrainValue(increment, -incrementLimit, incrementLimit);
        // 偏差更新
        errLastLast = errLast;
        errLast = errNow;
    }
    void setParam(float KP, float KI, float KD) { this->KP = KP, this->KI = KI, this->KD = KD; }
    void setReference(float reference) { this->reference = reference; }
    float getIncrement() const { return increment; }
    float getActualNum() const { return *actualNum; }

private:
    float KP;               // 比例系数
    float KI;               // 积分系数
    float KD;               // 微分常数
    float reference;        // 参考值
    float *const actualNum; // 实际值; 考虑到实际值总是与某个值绑定，不能随意修改，故使用指针常量
    float increment;        // 控制量
    float incrementLimit;   // 控制量限幅
    float threshold;        // 启动调节的偏差阈值
    float errLast;          // 偏差值
    float errNow;
    float errLastLast;
};

// 导纳控制
// https://zhuanlan.zhihu.com/p/126338809
class Admittance
{
public:
    Admittance(float _Kd, float _Bd, float _Md, float _max_out)
    {
        Md = _Md, Bd = _Bd, Kd = _Kd;
        xdd_set = xd_set = x_set = 0;
        xdd_now = xd_now = x_now = 0;
        xd_set_pre = x_set_pre = xd_now_pre = x_now_pre = 0;
        // threshold= _threshold;
        max_out = _max_out;
    };
    // 导纳更新  设定值  实际值
    float updateAdmittance(float _x_set, float _x_now)
    {
        x_set = _x_set;
        x_now = _x_now;
        xd_now = (x_now - x_now_pre);
        xdd_now = xd_now - xd_now_pre;
        xd_set = x_set - x_set_pre;
        xdd_set = xd_set - xd_set_pre;
        out_val = Kd * (x_now - x_set) + Bd * (xd_now - xd_set) + Md * (xdd_now - xdd_set);
        if (out_val > max_out)
            out_val = max_out;
        if (out_val < -max_out)
            out_val = -max_out;

        x_set_pre = x_set;
        xd_set_pre = xd_set;
        x_now_pre = x_now;
        xd_now_pre = xd_now;

        return out_val;
    };

private:
    float Kd, Bd, Md;             //刚度特性、阻尼特性和惯性特性
    float x_set, xd_set, xdd_set; //位置  速度 加速度   设定值
    float x_now, xd_now, xdd_now; //实际值
    float xd_set_pre, x_set_pre;
    float xd_now_pre, x_now_pre;
    // float threshold;  //x_now与x_set的阈值 其差值大于阈值再更新
    float max_out; //最大输出值
    float out_val;
};

#endif

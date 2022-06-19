/***
 * @Description: 数学库
 * @Author: Amamiya
 * @Date: 2022-06-09 21:21:03
 * @TechChangeTheWorld
 * @WHUROBOCON_Alright_Reserved
 */
#ifndef __MYMATH_H
#define __MYMATH_H

#include "math.h"
#include "stdio.h"

#define PI 3.1415926535f
#define DegToRad(x) x * 0.0174532925f
#define RadToDeg(x) x * 57.2957795f
#define SIGN(x) x > 0 ? 1 : -1

/**
 * @brief 线性改变值
 * @param val 目标变量
 * @param setval 设定值
 * @param k 单次变化值
 * @param _threshold 阈值
 */
inline void LineToValue(float &val, float setval, float k, float threshold) { val = fabs(val - setval) > threshold ? val - k * SIGN(val - setval) : setval; }

// 将数字约束在一个范围内
inline float constrainValue(float val, float min, float max) { return val < min ? min : (val > max ? max : val); }

enum StateEnum
{
	StatePreparing,	 // 准备中
	StateProcessing, // 进行中
	StateEnd,		 // 结束
};

// 状态流水线类
class PipelineClass
{
public:
	// 查询目前状态
	StateEnum queryStateNow() const { return state; }
	// 查询是否正在运行
	bool isRunning() const { return Running; }
	// 令该状态流水线运行开始运行
	void Start() { Running = true, state = StatePreparing; }
	// 已准备好
	void Prepared() { state = StateProcessing; }
	// 已进行完
	void Processed() { Running = false, state = StateEnd; }

protected:
	bool Running; // 正在运行
	StateEnum state;
};

struct Vector2f
{
	float x, y;
	Vector2f() : x(0), y(0) {}
	Vector2f(float xx) : x(xx), y(xx) {}
	Vector2f(float xx, float yy) : x(xx), y(yy) {}
	Vector2f operator+(const Vector2f &v) const { return Vector2f(x + v.x, y + v.y); }
	Vector2f operator-(const Vector2f &v) const { return Vector2f(x - v.x, y - v.y); }
	Vector2f operator*(const float r) const { return Vector2f(x * r, y * r); }
	// 自加
	void operator+=(const Vector2f &v) { x += v.x, y += v.y; }
	// 自减
	void operator-=(const Vector2f &v) { x -= v.x, y -= v.y; }
	// 自乘
	void operator*=(const Vector2f &v) { x *= v.x, y *= v.y; }
	// 返回自身标准化后的值
	Vector2f normalize() const
	{
		const float mag2 = x * x + y * y;
		if (mag2 > 0)
		{
			const float invMag = 1 / sqrt(mag2);
			return Vector2f(x * invMag, y * invMag);
		}
		return *this;
	}
	// 将自身标准化（化为单位向量）
	void normalized()
	{
		const float mag2 = x * x + y * y;
		if (mag2 > 0)
		{
			const float invMag = 1 / sqrt(mag2);
			x = x * invMag;
			y = y * invMag;
		}
	}
	// 二范数
	float norm() const { return sqrt(x * x + y * y); }
	// 次方和
	float pow(int n) const { return std::pow(x, n) + std::pow(y, n); }
	// 点积
	float dot(const Vector2f &v) const { return x * v.x + y * v.y; }
	// 对另一个向量的投影
	float projection(const Vector2f &v) const { return this->dot(v) / v.dot(v); }
	// 平面角（rad）
	float CalculateAngleRad() const { return y < 0 ? RadToDeg(2 * PI - acos(x)) : RadToDeg(acos(x)); }
};

#endif

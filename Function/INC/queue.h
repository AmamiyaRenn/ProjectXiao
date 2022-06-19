#ifndef __QUEUETEM_H
#define __QUEUETEM_H

#include <string.h>
#include <stdlib.h>
#include <ucos_ii.h>

const int QUEUEMAXSIZE = 128;
// 循环队列模板类
template <class T>
class Queue
{
public:
    Queue(int _size = QUEUEMAXSIZE)
    {
        front = rear = 0;
        size = _size;
        count = 0;
        data = (T *)malloc(sizeof(T) * size); // 申请一片内存
    };
    void clear();
    bool enQueue(T &ch);        // 入队  // 如果队列满了 数据不会入队
    bool enQueue(T *ch, int n); // 入队
    bool deQueue(T *ch);        // 出队
    bool deQueue(T *ch, int n); // 出队
    bool isFull();              // 判断是否满队
    bool isEmpty();

private:
    int front;
    int rear;
    int size;
    int count; // 用于判断队满还是空
    // T data[QUEUEMAXSIZE];
    T *data;
};

template <class T>
bool Queue<T>::isFull()
{
    return count == size;
}

template <class T>
bool Queue<T>::isEmpty()
{
    return count == 0;
}

template <class T>
bool Queue<T>::enQueue(T &ch)
{
    //  if(count!=size)  // 队列内还有空间
    if (count < size)
    {
        data[rear] = ch;
        rear = (rear + 1) % size;
        OS_CPU_SR cpu_sr = 0u; // 加锁
        OS_ENTER_CRITICAL();
        count++;
        OS_EXIT_CRITICAL();
        return true;
    }
    else
    {
        return false;
    }
}
// 入队
template <class T>
bool Queue<T>::enQueue(T *ch, int len)
{
    if (rear < size - len && count < size - len) // 如果剩余内存连续并且剩余长度大于数据长度
    {
        memcpy(&data[rear], ch, len * sizeof(T)); // 拷贝的是字节数   用memcpy快一点
        rear = (rear + len) % size;
        OS_CPU_SR cpu_sr = 0u; // 加锁
        OS_ENTER_CRITICAL();
        count += len;
        OS_EXIT_CRITICAL();
        return true;
    }
    else
    {
        for (int i = 0; i < len; i++)
        {
            if (!enQueue(*(ch + i)))
                return false;
        }
        return true;
    }
}

// 出队  返回是否可以读取
template <class T>
bool Queue<T>::deQueue(T *ch)
{
    // if(count!=0)
    if (count > 0)
    {
        *ch = data[front];
        front = (front + 1) % size;
        OS_CPU_SR cpu_sr = 0u; // 加锁
        OS_ENTER_CRITICAL();
        count--;
        OS_EXIT_CRITICAL();
        return true;
    }
    else
        return false;
}

template <class T>
bool Queue<T>::deQueue(T *ch, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (!deQueue((ch + i)))
            return false;
    }
    return true;
}

template <class T>
void Queue<T>::clear()
{
    front = 0;
    rear = 0;
    count = 0;
}

#endif

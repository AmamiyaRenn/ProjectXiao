<!--
 * @Description:
 * @Author: Amamiya
 * @Date: 2022-06-19 15:52:43
 * TechChangeTheWorld
 * WHUROBOCON_Alright_Reserved
-->

# ProjectXiao

- [ProjectXiao](#projectxiao)
  - [文档说明](#文档说明)
  - [C++面向对象编程经验](#c面向对象编程经验)

## 文档说明

1. 本程序使用 C 和 C++进行混合编程，把整个智能车视为`XiaoClass`对象，这个对象包括一些方法比如`Walk()`、属性比如`mode`还有子对象比如`LegClass`，Xiao 对象在 MyFlag 控制下，运行在`Task_RUN`任务中；所以`Master`文件夹存的是 EVA02 对象和它的运行环境

2. Master
   1. 主控文件夹，放着一些与控制、监视智能车直接相关的文件
      1. main
         1. 主函数，用于实时操作系统任务
      2. Xiao
         1. 智能车对象类，名字来源于《记录的地平线》的晓
      3. MasterParam
         1. 存储主控的一些重要参数
            1. 智能车状态
            2. 智能车控制参数
            3. 调试参数
3. Control
   1. 智能车机体软件层类与工作状态类（各种步态类我不把它理解为“类”（class）而时理解为状态 state）
4. Body
   1. 智能车机体硬件层类
5. Function
   1. 一些算法、数据结构和数据处理函数与一些不要需要管的东西
      1. MyMath
         1. 自定义数学库
      2. queue
         1. 循环队列模板类
      3. pid
         1. pid 控制算法
6. Hardware
   1. 硬件抽象层，抽象了硬件的通讯和使用
      1. can
         1. 现场总线
      2. usart
         1. 串口
      3. timer
         1. 定时器/计数器
      4. dma
         1. 直接内存访问
      5. beep
         1. 蜂鸣器
      6. key
         1. 矩阵键盘
      7. led
         1. 四个小 led
      8. led8
         1. 数码管
7. Ignore
   1. 不存在此文件夹，这个仅仅是把那些不需要关注的文件拖到一个 Groups 从而可以折叠起来而已

## C++面向对象编程经验

1. 所有写在`.c`的会被`.cpp`调用的函数或者写在`.cpp`但是是标准库的函数（比如`void TIM3_IRQHandler(void)`），一定一定要加上`#ifdef __cplusplus......`，不然会引起一些难以发觉的的 bug，下为范例。
   #ifdef **cplusplus
   extern "C"
   {
   #endif
   void TIM2_Configuration(void);
   #ifdef **cplusplus
   }
   #endif
2. 除了最底层的对象比如 Can1 这种需要随处调用的以外，为了方便起见直接在`can.c`里面定义了，其余的对象应当声明为类指针`class*`，而类中嵌套对象也应该声明为类指针，这样的话就能构建指向指针的指针，从而让`new`这个 C++新特性（动态分配内存）能够用上且最重要的是会让对象的捆绑变得很方便。
3. class 构建一定要仔细思考方法、属性、子对象的结构（参考[2 分钟让你明白什么是面向对象编程](https://zhuanlan.zhihu.com/p/75265007)），类构建的好坏会直接影响代码的可读性甚至运行效率。
4. 能在高抽象层类集成的就不要放到低抽象层类中，比如`LegClass`里面应当集成一些腿部运动学解算的方法，就不要在`TrotControl`中写什么运动学逆解、贝塞尔曲线计算之类的了，因为`BoundControl`之类的也会使用运动学逆解。
5. `public`里面放对外的接口，比如各种方法；`private`里面放一些参数：这样可以保证外界调用对象时不会破坏里面的一些重要参数。但如果你要调用和改变这些参数的话，可以写成`getXXX()`与`setXXX()`。

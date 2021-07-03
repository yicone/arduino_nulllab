**[English](READE.md)**
# Nulllab开发板Arduino IDE支持包 

安装包

1、文件->首选项，得到如下界面

2、在附加开发板管理器网址输入如下网址：
https://raw.githubusercontent.com/nulllaborg/arduino_nulllab/master/package_nulllab_boards_index.json
![](./doc/pic/option_zh.png)

3、工具->开发板->开发板管理
搜索nulllab,选择最新版本安装

## 示例程序

- [SysClock](https://github.com/nulllaborg/arduino_nulllab/blob/master/libraries/BasicsExamples/examples/SysClock/SysClock.ino) - 外部晶振和系统时钟配置方法
- [AnalogRead](https://github.com/nulllaborg/arduino_nulllab/blob/master/libraries/BasicsExamples/examples/AnalogRead/AnalogRead.ino) - 12位ADC读取方法

### SysClock 配置

- **sysClock()**
	设置时钟晶振内部32K,32M,外部32K,400K,1M,2M,4M,6M,8M,12M,16M,32MHz
- **sysClockPrescale()**
	设置系统时钟分频系数0,2,4,8,26,42,64,128分频

### AnalogRead 读取

- **analogReference()**
  设置adc参考电压 
	DEFAULT 供电电压AVCC
	EXTERNAL 外部参考电压IOREF
	INTERNAL1V024 内部高精度1.024V
	INTERNAL2V048 内部高精度2.048V
	INTERNAL4V096 内部高精度4.096V
- **analogReadResolution()**
	设置adc精度有两种ADC10BIT和ADC12BIT默认精度是10bit
- **sysClockOutput()**
	1:使能D8引脚输出CPU系统主频 0:关闭D8输出
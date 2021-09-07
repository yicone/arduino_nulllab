**[English](https://github.com/nulllaborg/arduino_nulllab/blob/master/README.md)**

# Nulllab开发板Arduino IDE支持包 

安装包

1、文件->首选项，得到如下界面

2、在附加开发板管理器网址输入如下网址：
https://gitee.com/nulllab/nulllab_arduino/raw/master/package_nulllab_boards_index.json
![](./doc/pic/option_zh.png)

3、工具->开发板->开发板管理
搜索nulllab,选择最新版本安装

## 开发板

基于LGT8F328P系列主控做了5款款开发板分别针对于不同创客的应用场景

| 名字 | Nano V3.1                                                    | Nano Pro                                                     | Maker-Nano                                                   | Mango Uno                                                    | Orion                                                        |
| ---- | ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------------ |
| 图片 | ![](./doc/pic/nano3.1.png)                                   | ![](./doc/pic/nano_pro.png)                                  | ![](./doc/pic/maker-nano.png)                                | ![](./doc/pic/mango_uno.png)                                 | ![](./doc/pic/orion.png)                                     |
| 参数 | CH340下载芯片<br />内部晶振<br />16M主频<br />PCB尺寸：50.8x25.4MM | CH340下载芯片<br />内部晶振<br />16M主频<br />PCB尺寸：50.8x25.4mm | 兼容官方驱动下载芯片<br />内部晶振<br />16M主频<br />PCB尺寸：56x32mm | 兼容官方驱动下载芯片<br />外部晶振<br />16M主频<br />PCB尺寸：68.6x53.4mm | 兼容官方驱动下载芯片<br />外部晶振<br />32M主频<br />PCB尺寸： |
| 特点 | 尺寸完全兼容官方arduino nano 3.0                             | Micro-Usb接口<br />功能尺寸兼容Nano V3.0 单面贴片            | 2路电机驱动(最大1.5A输出)<br />兼容乐高孔                    | 尺寸完全兼容官方arduino uno r3                               | 补强Uno IO口不够用情况，功能介于Uno和Mega2560简单            |
| 状态 | 已量产<br />[淘宝](https://item.taobao.com/item.htm?spm=a1z10.5-c-s.w4002-21257395099.47.1e64226e0PHZp6&id=650808111227) | 已量产<br />[淘宝](https://item.taobao.com/item.htm?spm=a1z10.5-c-s.w4002-21257395099.47.1e64226e0PHZp6&id=650808111227) | 准备量产                                                     | 准备量产                                                     | 开发中                                                       |

和Arduino Uno官方主板有差异的地方，请参考如下

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

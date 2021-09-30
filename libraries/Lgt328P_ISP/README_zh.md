**[English](https://github.com/nulllaborg/arduino_nulllab/libraries/Lgt328P_ISP/README.md)**
# 前言
这是 LGT8Fx8P ISP 下载协议的实现。 您可以制作 arduino 板或 nulllab 板（基于 lgt328p）作为 ISP 来编程 LGT8Fx8P，或者直接使用ISP工具烧录。

## 一、官方Arduino Uno给LGT-Nano烧录bootloard

### 使用说明
 1.制作一个ISP：
    1.将 Lgt328P_ISP.ino 烧录到 arduino 板中。
    2.将arduino板的`RESET`引脚和`VCC`引脚短接以避免引导加载程序执行。
    3.arduino板现在变成了 LGTISP！ 连接`SWD`和`SWC`。 `RST` 可以连接也可以不连接。
       | Arduino Uno|| LGT |
       |:-:|:-:|:-:|
       | D13 | -> | SWC |
       | D12 | -> | SWD |
       | D10 | -> | RST |
 ![](./Arduino_ISP.png)

2.将bootloader烧录到 LGT8Fx8P：
    1. 安装 [Arduino IDE for lgt328p](https://github.com/nulllaborg/arduino_nulllab).
    2.选择开发板：工具->开发板->开发板管理->Nulllab AVR Compatible Boards->Nulllab Nano
    3.选择烧录器：工具->编程器->Arduino/Nulllab as ISP(LGT328P)
    4.点击烧录引导程序

## 二、LGT-Nano给LGT-Nano烧录bootloard

### 使用说明
 1.制作一个ISP：
    1.将 Lgt328P_ISP.ino 烧录到 Lgt-nano 板中。
    2.将 Lgt-nano 板的`RESET`引脚和`VCC`引脚短接以避免引导加载程序执行。
    3.Lgt-nano 板现在变成了 LGTISP！ 连接`SWD`和`SWC`。 `RST` 可以连接也可以不连接。
       | Nano/ Nulllab boards|| LGT |
       |:-:|:-:|:-:|
       | D13 | -> | SWC |
       | D12 | -> | SWD |
       | D10 | -> | RST |
 ![](./Lgt-Nano_ISP.png)

 2.将bootloader烧录到 LGT8Fx8P：
    1. 安装 [Arduino IDE for lgt328p](https://github.com/nulllaborg/arduino_nulllab).
    2.选择开发板：工具->开发板->开发板管理->Nulllab AVR Compatible Boards->Nulllab Nano
    3.选择烧录器：工具->编程器->Arduino/Nulllab as ISP(LGT328P)
    4.点击烧录引导程序
## 三、LGT-ISP 专用bootloard工具烧录

### 使用说明
 上电后，将烧录工具的1脚对应LGT-Nano烧录接口1脚插入，可以看见红绿灯交替闪烁，直至绿灯常亮即可。
![](./ISP_Tool.png)

烧录工具如有需要，链接如下：
https://item.taobao.com/item.htm?ft=t&id=650808111227




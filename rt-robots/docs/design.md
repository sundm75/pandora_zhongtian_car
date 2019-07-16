# [ 一起 DIY 智能战车 ]
## 1. 软硬件环境准备

1. 硬件底盘+驱动+电池
蓝牙APP控制全向轮智能小车PS2遥控麦克纳姆轮底盘万向轮避障小车 颜色分类：全套底盘(含手柄电控电池套件)
该套件物件齐全，仅需要替换主控，就能实现功能。
且麦克纳姆轮底盘操控灵活，方便室内运行。

![麦克纳姆轮底盘万向轮小车](./pictures/1mecanum.jpg)

2. 主控： 潘多拉IoT Board物联网开发板 

![多拉IoT Board物联网开发板](./pictures/2pandora.jpg)

3. 软件：RT-Thread 3.1.3

## 2. 移植工程
到官网下下载 RT-Thread 3.1.3，env。
安装好 IAR 和 MDK。

指定了编译工具使用 iar，并设置了 iar 安装路径， 按照自己电脑的实际路径
设置，iar 安装路径是 D:\Program Files (x86)\IAR Systems\Embedded Workbench 8.1
将路径设置为： r'D:\Program Files (x86)\IAR Systems\Embedded Workbench 8.1' 或者： 'D:/Program Files (x86)/IAR Systems/Embedded Workbench 8.1'，
即使用‘/’时不用在路径前加‘r’ ,使用‘\’时需要在路径前加‘r’。
设置好 iar 路径后，右键打开 evn 的 cmd 命令行窗口，将工作目录切换到  \rt-thread\bsp\stm32\stm32l475-atk-pandora 目录，输
入 scons –j4 命令，即可开始构建编译工程。
构建工程用命令： scons --target=iar 

## 3. 等待硬件到来开始写程序




# 基于 STM32 的智能手表项目 (My First Embedded Project)

[![Platform](https://img.shields.io/badge/Platform-STM32F103X8-blue.svg)](https://www.st.com)
[![Tools](https://img.shields.io/badge/Tools-CubeMX%20%7C%20VSCode%20%7C%20EIDE-orange.svg)](https://marketplace.visualstudio.com/items?itemName=clovergit.eide)
[![Language](https://img.shields.io/badge/Language-C-green.svg)](https://en.wikipedia.org/wiki/C_(programming_language))

本项目是我的第一个嵌入式开发实践项目，基于 **STM32CubeMX + VSCode + EIDE** 环境开发，历时一周独立完成。项目完整实现了智能手表的经典多级菜单架构、非阻塞动效切换、时间日期校准、秒表以及基于 6 轴传感器的姿态解算等核心功能。

---

## 🛠️ 硬件与开发环境

- **核心板**: STM32F103C8T6 / X8T6
- **显示屏**: 128x64 I2C OLED 屏幕
- **传感器**: MPU6050（六轴陀螺仪与加速度计）
- **输入控制**: 4 个独立按键（非阻塞消抖扫描）
- **开发工具**: STM32CubeMX + VSCode + EIDE (Embedded IDE) + OpenOCD / ST-Link

---

## 🚀 核心功能与技术亮点

### 1. 经典多级菜单与动态过渡效果
- 基于状态机（`ui_state`）构建清晰的页面跳转逻辑，支持主页、菜单选择、设置等多个层级。
- **平滑动画**: 菜单切换采用非阻塞时间戳步进算法（`HAL_GetTick()`），图标以每 10ms 偏移 4 像素的速率丝滑滚动，避免了传统阻断式 `delay` 导致的系统卡顿。

### 2. 实时时钟 (RTC) 与同步设置
- 充分利用 STM32 硬件 RTC 保证本地时间的精准走时。
- 具备完整的**时间日期设置控件**，支持年、月、日、时、分、秒的选择与单独微调，修改后无缝同步更新至底层硬件 RTC 寄存器。

### 3. 高精度秒表 (Stopwatch)
- 利用滴答定时器时间戳差值计算技术，完美支持秒表的“开始-停止-清除”逻辑。
- 采用**非阻塞时间戳补偿算法**，确保秒表在暂停和恢复期间计时绝对精确，不丢失任何 Tick。

### 4. 基于一阶互补滤波的姿态解算 (MPU6050)
- **姿态解算**: 实时读取 MPU6050 的三轴加速度与三轴角速度。
- **数据滤波**: 采用**一阶互补滤波算法**（结合 `atan2` 加速度计静态解算与陀螺仪动态积分），有效滤除高频震动噪声并抑制低频漂移，实现稳定丝滑的**水平仪小球动画**及姿态数据输出。

### 5. 辅助功能
- **手电筒**: 硬件级 GPIO 控制，支持强光照明模式。
- **电池状态监测**: 预留电量渲染接口。

---

## 📂 工程目录结构

```text
├── .mxproject          # CubeMX 配置文件
├── watch.ioc           # STM32CubeMX 芯片配置引脚文件
├── README.md           # 项目说明文档
├── code/               # 核心业务逻辑及驱动层代码
│   ├── all.c           # 主业务状态机、按键触发、秒表及姿态解算
│   ├── all.h           # 函数声明
│   ├── allhead.h       # 全局头文件包含
│   ├── OLED.c / .h     # OLED 屏幕底层驱动及图形绘制 API
│   ├── OLED_Data.c/.h  # 菜单图标、字模、图片点阵数据
│   ├── MyI2C.c / .h    # 软件模拟 I2C 驱动
│   └── MPU6050.c / .h  # MPU6050 寄存器配置及原始数据读取
└── Core/               # 自动生成的初始化代码 (main.c/gpio.c/rtc.c 等)

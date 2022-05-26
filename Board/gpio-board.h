//
// Created by paopaozhi on 2022/5/22.
//

#ifndef GPIO_BOARD_H
#define GPIO_BOARD_H

#include "stm32l4xx_hal.h"

/*!
 * STM32 Pin Names
 */
#define MCU_PINS \
    PA_0 = 0, PA_1, PA_2, PA_3, PA_4, PA_5, PA_6, PA_7, PA_8, PA_9, PA_10, PA_11, PA_12, PA_13, PA_14, PA_15, \
    PB_0, PB_1, PB_2, PB_3, PB_4, PB_5, PB_6, PB_7, PB_8, PB_9, PB_10, PB_11, PB_12, PB_13, PB_14, PB_15,     \
    PC_0, PC_1, PC_2, PC_3, PC_4, PC_5, PC_6, PC_7, PC_8, PC_9, PC_10, PC_11, PC_12, PC_13, PC_14, PC_15

/**
 * GPIO 引脚名
 */
typedef enum {
    MCU_PINS,
    // Not connected
    NC = (int) 0xFFFFFFFF
} PinNames;

/**
 * GPIO 运行模式
 */
typedef enum {
    PIN_INPUT = 0,      //输入模式
    PIN_OUTPUT,         //输出模式
    PIN_ALTERNATE_FCT,  //复用模式
    PIN_ANALOGIC        //模拟输入
} PinModes;

/*!
 * GPIO 推挽输出 或 开漏输出
 */
typedef enum {
    PIN_PUSH_PULL = 0,  //推挽输出
    PIN_OPEN_DRAIN      //开漏输出
} PinConfigs;

/**
 * GPIO 上拉 下拉 不上拉不下拉
 */
typedef enum {
    PIN_NO_PULL = 0,
    PIN_PULL_UP,
    PIN_PULL_DOWM
} PinTypes;

/*!
 * GPIO 句柄
 */
typedef struct {
    PinNames pin;
    uint16_t pinIndex;
    void *port;
    uint16_t portIndex;
    PinTypes pull;
} Gpio_t;


#endif //GPIO_BOARD_H

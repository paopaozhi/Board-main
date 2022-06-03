//
// Created by paopaozhi on 2022/5/22.
//

#include "gpio-board.h"

/**
 * @brief gpio口初始化
 * @param obj gpio指针对象
 * @param pin gpio引脚 (示例:PA_1 ...)
 * @param mode gpio模式  输入模式/输出模式/复用模式/模拟输入
 * @param config gpio模式 开漏模式/推挽输出
 * @param value gpio初始值
 * @return HAL status
 */
HAL_StatusTypeDef
GPIO_Init(Gpio_t *obj, PinNames pin, PinModes mode, PinConfigs config, PinTypes types, uint8_t value) {
    GPIO_InitTypeDef GPIOInitStructure;

    obj->pin = pin;
    if (pin == NC) {
        return HAL_ERROR;
    }
    switch (pin & 0xF0) {
        case 0x00:
            obj->port = GPIOA;
            __HAL_RCC_GPIOA_CLK_ENABLE();
            break;
        case 0x10:
            obj->port = GPIOB;
            __HAL_RCC_GPIOB_CLK_ENABLE();
            break;
        case 0x20:
            obj->port = GPIOC;
            __HAL_RCC_GPIOC_CLK_ENABLE();
            break;
        default:
            return HAL_ERROR;
    }

    switch (mode) {
        case PIN_INPUT:
            GPIOInitStructure.Mode = GPIO_MODE_INPUT;
            break;
        case PIN_OUTPUT:
            if (types == PIN_PUSH_PULL) {
                GPIOInitStructure.Mode = GPIO_MODE_OUTPUT_PP;
            } else if (types == PIN_OPEN_DRAIN) {
                GPIOInitStructure.Mode = GPIO_MODE_OUTPUT_OD;
            } else {
                return HAL_ERROR;
            }
            break;
        case PIN_ALTERNATE_FCT:
            break;
        case PIN_ANALOGIC:
            break;
        default:
            return HAL_ERROR;
    }

    switch (types) {
        case PIN_NO_PULL :
            GPIOInitStructure.Pull = GPIO_NOPULL;
            break;
        case PIN_PULL_UP:
            GPIOInitStructure.Pull = GPIO_PULLUP;
            break;
        case PIN_PULL_DOWM:
            GPIOInitStructure.Pull = GPIO_PULLDOWN;
            break;
        default:
            return HAL_ERROR;
    }

    GPIOInitStructure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(obj->port, &GPIOInitStructure);
    return HAL_OK;
}

uint8_t GPIO_EXTI_SetInputInit(Gpio_t *obj, PinNames name, PinTypes types) {


    return HAL_OK;
}

uint8_t GPIO_Write(Gpio_t *obj, uint8_t value) {

}

uint8_t GPIO_Read(Gpio_t *obj, uint8_t value) {

}

uint8_t GPIO_Toggle(Gpio_t *obj) {

}

void EXTI1_IRQHandler(void) {

}

void EXTI2_IRQHandler(void) {

}

void EXTI3_IRQHandler(void) {

}

void EXTI4_IRQHandler(void) {

}

void EXTI9_5_IRQHandler(void) {

}

void EXTI15_10_IRQHandler(void) {

};

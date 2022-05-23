//
// Created by paopaozhi on 2022/5/22.
//

#include "gpio-board.h"

uint8_t GPIO_OutputInit(Gpio_t *obj, PinNames pin, PinConfigs config, uint8_t value) {
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
        case 0x01:
            obj->port = GPIOB;
            __HAL_RCC_GPIOB_CLK_ENABLE();
            break;
        case 0x02:
            obj->port = GPIOC;
            __HAL_RCC_GPIOC_CLK_ENABLE();
            break;
        default:
            return HAL_ERROR;
    }

    HAL_GPIO_Init(obj->port, &GPIOInitStructure);
    return HAL_OK;
}


uint8_t GPIO_InputInit(Gpio_t *obj, PinNames name, PinTypes types) {


    return HAL_OK;
}

uint8_t GPIO_EXTI_InputInit(Gpio_t *obj, PinNames name, PinTypes types) {


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

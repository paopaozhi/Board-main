//
// Created by paopaozhi on 2022/5/11.
//

#include <string.h>
#include <stdio.h>
#include "esp.h"
#include "main.h"
#include "usart.h"

#define ATE1 "ATE0\r\n"

uint8_t esp_Rxbuf[128];
uint8_t ATE1_OK[] = {0x41, 0x54, 0x45, 0x30, 0x0D, 0x0D, 0x0A, 0x0D, 0x0A, 0x4F, 0x4B, 0x0D, 0x0A};
uint8_t AT_OK[6] = {0x0D, 0x0A, 0x4F, 0x4B, 0x0D, 0x0A};

static void ESP_ATE(void) {
    if (HAL_UART_Transmit(&hlpuart1, (uint8_t *) ATE1, sizeof(ATE1), 0xff) != HAL_OK) {
        Error_Handler();
    }
    if (HAL_UART_Receive(&hlpuart1, esp_Rxbuf, 13, 0xff) == HAL_OK) {
        for (int ii = 0; ii <= 11; ii++) {
            if (*(ATE1_OK + ii) != esp_Rxbuf[ii]) {

            }
            if (ii == 11) {
                HAL_UART_Transmit(&huart1, "OK\n", 3, 0xff);
            }
        }
    }
    memset(esp_Rxbuf, 0, sizeof(esp_Rxbuf));
}

static HAL_StatusTypeDef isAT_OK(void) {
    if (HAL_UART_Receive(&hlpuart1, esp_Rxbuf, 6, 0xff) == HAL_OK) {
        for (int i = 0; i <= 6; ++i) {
            if (*(AT_OK + i) != esp_Rxbuf[i]) {

            }
            if (i == 6) {
                return HAL_OK;
            }
        }
    } else {
        return HAL_ERROR;
    }
}

static HAL_StatusTypeDef ESP_Set_CWMODE_DEF(void) {
    uint8_t ESP_Txbuf[] = "AT+CWMODE_DEF=1\r\n";
    if (HAL_UART_Transmit(&hlpuart1, ESP_Txbuf, sizeof(ESP_Txbuf), 0xff) != HAL_OK) {
        Error_Handler();
    }
    return isAT_OK();
}

static HAL_StatusTypeDef ESP_Set_CWJAP(uint8_t *ssid, uint8_t *passwd) {
    char ESP_Txbuf[128];
    sprintf(ESP_Txbuf, "AT+CWJAP_DEF=\"%s\",\"%s\"", ssid, passwd);
    if (HAL_UART_Transmit(&hlpuart1, (uint8_t *) ESP_Txbuf, strlen(ESP_Txbuf), 0xff) != HAL_OK) {
        Error_Handler();
    }
    return isAT_OK();
}

static HAL_StatusTypeDef ESP_Set_CIPSTART(uint8_t *remote_IP, uint8_t remote_port) {
    char ESP_Txbuf[128];
    sprintf(ESP_Txbuf, "AT+CWJAP_DEF=\"TCP\",\"%s\",\"%d\"", remote_IP, remote_port);
    if (HAL_UART_Transmit(&hlpuart1, (uint8_t *) ESP_Txbuf, strlen(ESP_Txbuf), 0xff) != HAL_OK) {
        Error_Handler();
    }
    return isAT_OK();
}

static HAL_StatusTypeDef ESP_Set_CIPMODE(void) {
    char ESP_Txbuf[] = "AT+CIPMODE=1";
    if (HAL_UART_Transmit(&hlpuart1, (uint8_t *) ESP_Txbuf, sizeof(ESP_Txbuf), 0xff) != HAL_OK) {
        Error_Handler();
    }
    return isAT_OK();
}

static HAL_StatusTypeDef ESP_Set_CIPSEND() {
    char ESP_Txbuf[] = "AT+CIPSEND";
    if (HAL_UART_Transmit(&hlpuart1, (uint8_t *) ESP_Txbuf, strlen(ESP_Txbuf), 0xff) != HAL_OK) {
        Error_Handler();
    }
    return isAT_OK();
}

/**
 * @brief 初始化ESP 使其关闭回显 联网 建立TCP连接 开启TCP透传
 */
void ESP_Init(uint8_t *ssid, uint8_t *passwd, uint8_t *remote_IP, uint16_t remote_port) {
    ESP_ATE();
    if (ESP_Set_CWMODE_DEF() != HAL_OK) {

    }
    if (ESP_Set_CWJAP(ssid, passwd) != HAL_OK) {

    }
    if (ESP_Set_CIPSTART(remote_IP, remote_port) != HAL_OK) {

    }
    if (ESP_Set_CIPMODE() != HAL_OK) {

    }
    if (ESP_Set_CIPSEND() != HAL_OK) {

    }
}

/**
 * @brief 通过TCP透传发送数据
 */
void ESP_SendData(uint8_t *RxData) {
    HAL_UART_Transmit(&hlpuart1, RxData, strlen(RxData), 0xff);
}


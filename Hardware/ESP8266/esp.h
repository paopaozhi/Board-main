//
// Created by paopaozhi on 2022/5/11.
//

#ifndef TCPT_EMP_ESP_H
#define TCPT_EMP_ESP_H

void ESP_Init(uint8_t *ssid, uint8_t *passwd, uint8_t *remote_IP, uint16_t remote_port);

void ESP_SendData(uint8_t *RxData);

#endif //TCPT_EMP_ESP_H

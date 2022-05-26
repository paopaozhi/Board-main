#include "main.h"
#include <string.h>
#include <stdio.h>
#include "gpio.h"
#include "usart.h"
#include "tim.h"
#include "i2c.h"
#include <stdio.h>

#include "lcd.h"
#include "esp.h"
#include "sht30.h"
#include "bh1750.h"

uint8_t Uart1_Rxbuf[128];
char Uart1_Txbuf[128];
float temperature = 0.0;
float humidity = 0.0;
uint16_t light = 0;
//uint8_t dat[2] = {0};

void SystemClock_Config(void);

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void) {
    //MCU初始化
    HAL_Init();
    SystemClock_Config();
    //外设初始化
    MX_GPIO_Init();
    MX_USART1_UART_Init();
    MX_LPUART1_UART_Init();
    MX_TIM6_Init();
    MX_I2C1_Init();

    //等待ESP发送完初始化日志
    HAL_Delay(500);

    LCD_Init();
    LCD_Clear(WHITE);

    SHT30_reset();
    if (SHT30_Init() == HAL_OK) {
        printf("sht30ok\r\n");
    }

    while (1) {
        printf("%d\r\n", BH1750_GetLux());
        SHT30_Get_Temp_Hum(&temperature, &humidity);
        printf("%.2f\n%.2f\n", temperature, humidity);
        HAL_Delay(8000);
    }
}

/**
 * @brief 重定向printf串口输出
 * @param fd
 * @param pBuffer
 * @param size
 * @return
 */
int _write(int fd, char *pBuffer, int size) {
    for (int i = 0; i < size; i++) {
        while ((USART1->ISR & 0X40) == 0);//等待上一次串口数据发送完成
        USART1->TDR = (uint8_t) pBuffer[i];       //写DR,串口1将发送数据
    }
    return size;
}


/**
  * @brief 系统时钟配置
  * @retval None
  */
void SystemClock_Config(void) {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Configure the main internal regulator output voltage
    */
    if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK) {
        Error_Handler();
    }

    /** Configure LSE Drive Capability
    */
    HAL_PWR_EnableBkUpAccess();
    __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_LOW);

    /** Initializes the RCC Oscillators according to the specified parameters
    * in the RCC_OscInitTypeDef structure.
    */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE | RCC_OSCILLATORTYPE_MSI;
    RCC_OscInitStruct.LSEState = RCC_LSE_ON;
    RCC_OscInitStruct.MSIState = RCC_MSI_ON;
    RCC_OscInitStruct.MSICalibrationValue = 0;
    RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
    RCC_OscInitStruct.PLL.PLLM = 1;
    RCC_OscInitStruct.PLL.PLLN = 40;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
    RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
    RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB buses clocks
    */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                  | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK) {
        Error_Handler();
    }

    /** Enable MSI Auto calibration
    */
    HAL_RCCEx_EnableMSIPLLMode();
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void) {
    /* USER CODE BEGIN Error_Handler_Debug */
    /* User can add his own implementation to report the HAL error return state */
    __disable_irq();
    while (1) {
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
    }
    /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

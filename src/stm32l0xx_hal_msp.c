/**********************************************************************************************************************
 * \file stm32l0xx_hal_msp.c
 *
 * \author  MarcoAAG
 *
 * \date Oct-03-2024
 *
 * \version 1.0 \n \n
 *
 *********************************************************************************************************************/

#include "stm32l0xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

// Definition for I2Cx clock resources
#define I2Cx_CLK_ENABLE()          __HAL_RCC_I2C1_CLK_ENABLE()
#define I2Cx_SDA_GPIO_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE()
#define I2Cx_SCL_GPIO_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE()
#define I2Cx_FORCE_RESET()         __HAL_RCC_I2C1_FORCE_RESET()
#define I2Cx_RELEASE_RESET()       __HAL_RCC_I2C1_RELEASE_RESET()
// Definition for I2Cx Pins
#define I2Cx_SCL_PIN       GPIO_PIN_6
#define I2Cx_SCL_GPIO_PORT GPIOB
#define I2Cx_SDA_PIN       GPIO_PIN_7
#define I2Cx_SDA_GPIO_PORT GPIOB
#define I2Cx_SCL_SDA_AF    GPIO_AF1_I2C1

// Definition for USARTx clock resources
#define USARTx                      USART2
#define USARTx_CLK_ENABLE()         __HAL_RCC_USART2_CLK_ENABLE();
#define USARTx_RX_GPIO_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE()
#define USARTx_TX_GPIO_CLK_ENABLE() __HAL_RCC_GPIOA_CLK_ENABLE()
#define USARTx_FORCE_RESET()        __HAL_RCC_USART2_FORCE_RESET()
#define USARTx_RELEASE_RESET()      __HAL_RCC_USART2_RELEASE_RESET()
// Definition for USARTx Pins
#define USARTx_TX_PIN       GPIO_PIN_2
#define USARTx_TX_GPIO_PORT GPIOA
#define USARTx_TX_AF        GPIO_AF4_USART2
#define USARTx_RX_PIN       GPIO_PIN_3
#define USARTx_RX_GPIO_PORT GPIOA
#define USARTx_RX_AF        GPIO_AF4_USART2

/** \defgroup HAL_MSP_Private_Functions
 * @{
 */

/**
 * \brief I2C MSP Initialization
 *        This function configures the hardware resources:
 *           - Peripheral's clock enable
 *           - Peripheral's GPIO Configuration
 * \param[in] hi2c: I2C handle pointer
 * \return None
 */
void HAL_I2C_MspInit(I2C_HandleTypeDef* hi2c)
{
  GPIO_InitTypeDef         GPIO_InitStruct;
  RCC_PeriphCLKInitTypeDef RCC_PeriphCLKInitStruct;

  // Configure the I2C clock source. The clock is derived from the SYSCLK
  RCC_PeriphCLKInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2C1;
  RCC_PeriphCLKInitStruct.I2c1ClockSelection   = RCC_I2C1CLKSOURCE_SYSCLK;
  HAL_RCCEx_PeriphCLKConfig(&RCC_PeriphCLKInitStruct);

  // Enable peripherals and GPIO Clocks
  // Enable GPIO TX/RX clock
  I2Cx_SCL_GPIO_CLK_ENABLE();
  I2Cx_SDA_GPIO_CLK_ENABLE();
  // Enable I2Cx clock
  I2Cx_CLK_ENABLE();

  // Configure peripheral GPIO
  // I2C TX GPIO pin configuration
  GPIO_InitStruct.Pin       = I2Cx_SCL_PIN;
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_OD;
  GPIO_InitStruct.Pull      = GPIO_PULLUP;
  GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_LOW;
  GPIO_InitStruct.Alternate = I2Cx_SCL_SDA_AF;
  HAL_GPIO_Init(I2Cx_SCL_GPIO_PORT, &GPIO_InitStruct);

  // I2C RX GPIO pin configuration
  GPIO_InitStruct.Pin       = I2Cx_SDA_PIN;
  GPIO_InitStruct.Alternate = I2Cx_SCL_SDA_AF;
  HAL_GPIO_Init(I2Cx_SDA_GPIO_PORT, &GPIO_InitStruct);
}

/**
 * \brief I2C MSP De-Initialization
 *        This function frees the hardware resources:
 *          - Disable the Peripheral's clock
 *          - Revert GPIO configuration to their default state
 * \param[in] hi2c: I2C handle pointer
 * \return None
 */
void HAL_I2C_MspDeInit(I2C_HandleTypeDef* hi2c)
{
  // 1- Reset peripherals
  I2Cx_FORCE_RESET();
  I2Cx_RELEASE_RESET();

  // 2- Disable peripherals and GPIO Clocks
  // Configure I2C Tx as alternate function
  HAL_GPIO_DeInit(I2Cx_SCL_GPIO_PORT, I2Cx_SCL_PIN);
  // Configure I2C Rx as alternate function
  HAL_GPIO_DeInit(I2Cx_SDA_GPIO_PORT, I2Cx_SDA_PIN);
}

/**
 * \brief UART MSP Initialization
 *        This function configures the hardware resources:
 *           - Peripheral's clock enable
 *           - Peripheral's GPIO Configuration
 * \param[in] huart: UART handle pointer
 * \return None
 */
void HAL_UART_MspInit(UART_HandleTypeDef* huart)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  // 1- Enable peripherals and GPIO Clocks
  // Enable GPIO TX/RX clock
  USARTx_TX_GPIO_CLK_ENABLE();
  USARTx_RX_GPIO_CLK_ENABLE();

  // Enable USARTx clock
  USARTx_CLK_ENABLE();

  // 2- Configure peripheral GPIO
  // UART TX GPIO pin configuration
  GPIO_InitStruct.Pin       = USARTx_TX_PIN;
  GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull      = GPIO_PULLUP;
  GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = USARTx_TX_AF;

  HAL_GPIO_Init(USARTx_TX_GPIO_PORT, &GPIO_InitStruct);

  // UART RX GPIO pin configuration
  GPIO_InitStruct.Pin       = USARTx_RX_PIN;
  GPIO_InitStruct.Alternate = USARTx_RX_AF;

  HAL_GPIO_Init(USARTx_RX_GPIO_PORT, &GPIO_InitStruct);
}

/**
 * \brief UART MSP De-Initialization
 *        This function frees the hardware resources:
 *          - Disable the Peripheral's clock
 *          - Revert GPIO and NVIC configuration to their default state
 * \param[in] huart: UART handle pointer
 * \return None
 */
void HAL_UART_MspDeInit(UART_HandleTypeDef* huart)
{
  // 1- Reset peripherals
  USARTx_FORCE_RESET();
  USARTx_RELEASE_RESET();

  // 2- Disable peripherals and GPIO Clocks
  // Configure UART Tx as alternate function
  HAL_GPIO_DeInit(USARTx_TX_GPIO_PORT, USARTx_TX_PIN);
  // Configure UART Rx as alternate function
  HAL_GPIO_DeInit(USARTx_RX_GPIO_PORT, USARTx_RX_PIN);
}

/** @} */ // end of HAL_MSP_Private_Functions

#ifdef __cplusplus
}
#endif

/**********************************************************************************************************************
 * \file sr04m_if.c
 *
 * \author  MarcoAAG
 *
 * \date Sep-03-2025
 *
 * \version 1.0 \n \n
 *
 *********************************************************************************************************************/

#include <sr04m_if.h>
#include <stm32l0xx_hal.h>

#ifdef __cplusplus
extern "C" {
#endif

static uint32_t SR04M_WriteCommand(uint8_t* pData, uint8_t Length);
static uint32_t SR04M_ReadData(uint8_t* pData, uint8_t Length);

SR04M_IO t_SR04T_IO = {
  .writeReg = SR04M_WriteCommand,
  .readReg  = SR04M_ReadData,
};

UART_HandleTypeDef UartHandle;

LEVEL_ERROR SR04M_InitInterface(SR04M_Object* tp_obj)
{
  LEVEL_ERROR e_retVal = LEVEL_OK;

  /*Configure the UART peripheral */
  /* Put the USART peripheral in the Asynchronous mode (UART Mode) */
  /* UART configured as follows:
      - Word Length = 8 Bits (7 data bit + 1 parity bit) :
      - Stop Bit    = One Stop bit
      - Parity      = ODD parity
      - BaudRate    = 9600 baud
      - Hardware flow control disabled (RTS and CTS signals) */
  UartHandle.Instance = USART2;

  UartHandle.Init.BaudRate   = 9600;
  UartHandle.Init.WordLength = UART_WORDLENGTH_8B;
  UartHandle.Init.StopBits   = UART_STOPBITS_1;
  UartHandle.Init.Parity     = UART_PARITY_NONE;
  UartHandle.Init.HwFlowCtl  = UART_HWCONTROL_NONE;
  UartHandle.Init.Mode       = UART_MODE_TX_RX;
  if(HAL_UART_Init(&UartHandle) != HAL_OK)
  {
    e_retVal = LEVEL_ERR_UART;
  }
  else
  {
    if(SR04M_u_Init(tp_obj, &t_SR04T_IO, MODE5) == SR04M_ERROR)
    {
      e_retVal = LEVEL_ERR_INIT;
    }
  }

  return e_retVal;
}

static uint32_t SR04M_WriteCommand(uint8_t* pData, uint8_t Length)
{
  HAL_UART_Transmit(&UartHandle, pData, Length, 5000);
  return 0;
}

static uint32_t SR04M_ReadData(uint8_t* pData, uint8_t Length)
{
  HAL_UART_Receive(&UartHandle, pData, Length, 5000);
  return 0;
}

#ifdef __cplusplus
}
#endif

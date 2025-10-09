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

#include <sr04m.h>
#include <sr04m_if.h>
#include <stm32l0xx_hal.h>

#ifdef __cplusplus
extern "C" {
#endif

static uint8_t  SR04MIF_Init(void);
static uint32_t SR04M_WriteCommand(uint8_t* pData, uint8_t Length);
static uint32_t SR04M_ReadData(uint8_t* pData, uint8_t Length);

SR04M_IO t_SR04T_IO = {
  .init     = SR04MIF_Init,
  .writeReg = SR04M_WriteCommand,
  .readReg  = SR04M_ReadData,
};

UART_HandleTypeDef UartHandle;
SR04M_Object       SR04M_Obj;

LEVEL_Status SR04M_InitInterface(void)
{
  LEVEL_Status e_retVal = LEVEL_OK;

  if(SR04M_e_RegisterBusIO(&SR04M_Obj, &t_SR04T_IO) == SR04M_OK)
  {
    if(SR04M_Driver.Init(&SR04M_Obj) == SR04M_ERROR)
    {
      e_retVal = LEVEL_ERR_INIT;
    }
    else
    {
      SR04M_Driver.SetMode(&SR04M_Obj, MODE4);
    }
  }
  else
  {
    e_retVal = LEVEL_ERR_INIT;
  }

  return e_retVal;
}

LEVEL_Status SR04MIF_e_GetDistance(uint16_t* u_distance)
{
  return SR04M_Driver.GetDistance(&SR04M_Obj, u_distance);
}

static uint8_t SR04MIF_Init(void)
{
  LEVEL_Status e_retVal = LEVEL_OK;

  UartHandle.Instance        = USART2;
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

  return e_retVal;
}

static uint32_t SR04M_WriteCommand(uint8_t* pData, uint8_t Length)
{
  HAL_UART_Transmit(&UartHandle, pData, Length, 10);
  return 0;
}

static uint32_t SR04M_ReadData(uint8_t* pData, uint8_t Length)
{
  HAL_UART_Receive(&UartHandle, pData, Length, 100);
  return 0;
}

#ifdef __cplusplus
}
#endif

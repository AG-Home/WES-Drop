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

LEVEL_Status SR04M_InitInterface(SR04M_Object* tp_obj, LEVEL_UART_PARAMS* tp_uartObj)
{
  LEVEL_Status e_retVal = LEVEL_OK;

  // Configure the UART peripheral
  UartHandle.Instance        = tp_uartObj->pt_instance;
  UartHandle.Init.BaudRate   = tp_uartObj->t_parameters.BaudRate;
  UartHandle.Init.WordLength = tp_uartObj->t_parameters.WordLength;
  UartHandle.Init.StopBits   = tp_uartObj->t_parameters.StopBits;
  UartHandle.Init.Parity     = tp_uartObj->t_parameters.Parity;
  UartHandle.Init.HwFlowCtl  = tp_uartObj->t_parameters.HwFlowCtl;
  UartHandle.Init.Mode       = tp_uartObj->t_parameters.Mode;
  if(HAL_UART_Init(&UartHandle) != HAL_OK)
  {
    e_retVal = LEVEL_ERR_UART;
  }
  else
  {
    if(SR04M_u_Init(tp_obj, &t_SR04T_IO) == SR04M_ERROR)
    {
      e_retVal = LEVEL_ERR_INIT;
    }
  }

  return e_retVal;
}

static uint32_t SR04M_WriteCommand(uint8_t* pData, uint8_t Length)
{
  HAL_UART_Transmit(&UartHandle, pData, Length, 100);
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

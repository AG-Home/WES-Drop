/**********************************************************************************************************************
 * \file wes.c
 *
 * \author MarcoAAG
 *
 * \date Sep-04-2025
 *
 * \version 1.0 \n \n
 *
 *********************************************************************************************************************/

#include <display.h>
#include <level.h>
#include <wes.h>

#ifdef __cplusplus
extern "C" {
#endif

Display_Object t_displayObj;
Level_Object   t_levelObj;

void WES_v_Init(void)
{
  t_levelObj.t_uartParams.pt_instance             = USART2;
  t_levelObj.t_uartParams.t_parameters.BaudRate   = 9600;
  t_levelObj.t_uartParams.t_parameters.WordLength = UART_WORDLENGTH_8B;
  t_levelObj.t_uartParams.t_parameters.StopBits   = UART_STOPBITS_1;
  t_levelObj.t_uartParams.t_parameters.Parity     = UART_PARITY_NONE;
  t_levelObj.t_uartParams.t_parameters.HwFlowCtl  = UART_HWCONTROL_NONE;
  t_levelObj.t_uartParams.t_parameters.Mode       = UART_MODE_TX_RX;
  ;

  LEVEL_e_Init(&t_levelObj);
  DISPLAY_e_Init(&t_displayObj);
}

void WES_v_RunApp(void)
{
  DISPLAY_e_ShowLevel(&t_displayObj, 15);
}

#ifdef __cplusplus
}
#endif

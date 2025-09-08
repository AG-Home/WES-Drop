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

Display_Object     t_displayObj;
Level_Object       t_levelObj;

static void WES_v_ErrHandling(void);

void WES_v_Init(void)
{
  t_levelObj.t_uartParams.pt_instance             = USART2;
  t_levelObj.t_uartParams.t_parameters.BaudRate   = 9600;
  t_levelObj.t_uartParams.t_parameters.WordLength = UART_WORDLENGTH_8B;
  t_levelObj.t_uartParams.t_parameters.StopBits   = UART_STOPBITS_1;
  t_levelObj.t_uartParams.t_parameters.Parity     = UART_PARITY_NONE;
  t_levelObj.t_uartParams.t_parameters.HwFlowCtl  = UART_HWCONTROL_NONE;
  t_levelObj.t_uartParams.t_parameters.Mode       = UART_MODE_TX_RX;
  t_levelObj.e_mode                               = MODE4;

  LEVEL_e_Init(&t_levelObj);
  DISPLAY_e_Init(&t_displayObj);
}

void WES_v_RunApp(void)
{
  uint8_t        level;
  static uint8_t u_errCntr;
  if(LEVEL_e_GetLevel(&t_levelObj, &level) != LEVEL_OK)
  {
    u_errCntr++;
  }
  if(DISPLAY_e_ShowLevel(&t_displayObj, level) != DISPLAY_OK)
  {
    u_errCntr++;
  }
  if(u_errCntr > 20)
  {
    WES_v_ErrHandling();
  }
}

static void WES_v_ErrHandling(void)
{
  while(1);
}

#ifdef __cplusplus
}
#endif

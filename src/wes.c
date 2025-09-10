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
#include <error_handler.h>
#include <level.h>
#include <wes.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BAUDRATE                 9600u
#define MAX_LEVEL_INIT_ATTEMPS   5u
#define MAX_DISPLAY_INIT_ATTEMPS 5u
#define DELAY_ATTEMPS            20u

Display_Object    t_displayObj;
Level_Object      t_levelObj;
WES_ErrorHandler* t_errorInstance;

void WES_v_Init(void)
{
  LEVEL_Status   e_levelStatus;
  DISPLAY_Status e_displayStatus;
  uint8_t        u_attemps = 0u;

  ERRH_v_Init(t_errorInstance);

  t_levelObj.t_uartParams.pt_instance             = USART2;
  t_levelObj.t_uartParams.t_parameters.BaudRate   = BAUDRATE;
  t_levelObj.t_uartParams.t_parameters.WordLength = UART_WORDLENGTH_8B;
  t_levelObj.t_uartParams.t_parameters.StopBits   = UART_STOPBITS_1;
  t_levelObj.t_uartParams.t_parameters.Parity     = UART_PARITY_NONE;
  t_levelObj.t_uartParams.t_parameters.HwFlowCtl  = UART_HWCONTROL_NONE;
  t_levelObj.t_uartParams.t_parameters.Mode       = UART_MODE_TX_RX;
  t_levelObj.e_mode                               = MODE4;

  e_levelStatus = LEVEL_e_Init(&t_levelObj);
  if(e_levelStatus != LEVEL_OK)
  {
    while(e_levelStatus != LEVEL_OK && u_attemps < MAX_LEVEL_INIT_ATTEMPS)
    {
      t_errorInstance->setError(ERR_LEVEL);
      e_levelStatus = LEVEL_e_Init(&t_levelObj);
      u_attemps++;
      if(u_attemps >= MAX_LEVEL_INIT_ATTEMPS)
      {
        t_errorInstance->setError(ERR_FATAL);
      }
      HAL_Delay(DELAY_ATTEMPS);
    }
  }
  else
  {
    e_displayStatus = DISPLAY_e_Init(&t_displayObj);
    u_attemps       = 0u;
    while(e_displayStatus != DISPLAY_OK && u_attemps < MAX_DISPLAY_INIT_ATTEMPS)
    {
      t_errorInstance->setError(ERR_DISPLAY);
      e_displayStatus = DISPLAY_e_Init(&t_displayObj);
      u_attemps++;
      if(u_attemps >= MAX_DISPLAY_INIT_ATTEMPS)
      {
        t_errorInstance->setError(ERR_FATAL);
      }
      HAL_Delay(DELAY_ATTEMPS);
    }
  }
}

void WES_v_RunApp(void)
{
  LEVEL_Status   e_levelStatus;
  DISPLAY_Status e_displayStatus;
  static uint8_t u_prevLevel;
  static uint8_t u_level;

  e_levelStatus = LEVEL_e_GetLevel(&t_levelObj, &u_level);

  if(e_levelStatus == LEVEL_OK)
  {
    u_prevLevel = u_level;
    t_errorInstance->setError(ERR_LEVEL_CLEAR);
    e_displayStatus = DISPLAY_e_ShowLevel(&t_displayObj, u_level);
    if(e_displayStatus == DISPLAY_OK)
    {
      t_errorInstance->setError(ERR_DISPLAY_CLEAR);
    }
    else
    {
      t_errorInstance->setError(ERR_DISPLAY);
    }
  }
  else
  {
    t_errorInstance->setError(ERR_LEVEL);
    e_displayStatus = DISPLAY_e_ShowLevel(&t_displayObj, u_prevLevel); // Remains the previous value
    if(e_displayStatus == DISPLAY_OK)
    {
      t_errorInstance->setError(ERR_DISPLAY_CLEAR);
    }
    else
    {
      t_errorInstance->setError(ERR_DISPLAY);
    }
  }
}

#ifdef __cplusplus
}
#endif

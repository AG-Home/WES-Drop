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
#include <stm32l0xx_hal.h>
#include <wes.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_LEVEL_INIT_ATTEMPS   5u
#define MAX_DISPLAY_INIT_ATTEMPS 5u
#define DELAY_ATTEMPS            20u

Display_Object    t_displayObj;
WES_ErrorHandler* t_errorInstance;

void WES_v_Init(void)
{
  LEVEL_Status   e_levelStatus;
  DISPLAY_Status e_displayStatus;
  uint8_t        u_attemps = 0u;

  t_errorInstance = ERRH_t_Init();

  e_levelStatus = LEVEL_e_Init();
  if(e_levelStatus != LEVEL_OK)
  {
    while(e_levelStatus != LEVEL_OK && u_attemps < MAX_LEVEL_INIT_ATTEMPS)
    {
      t_errorInstance->setError(ERR_LEVEL);
      e_levelStatus = LEVEL_e_Init();
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

  e_levelStatus = LEVEL_e_GetLevel(&u_level);

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

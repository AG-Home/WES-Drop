/**********************************************************************************************************************
 * \file main.c
 *
 * \author MarcoAAG
 *
 * \date April-18-2025
 *
 * \version 1.0 \n \n
 *
 *********************************************************************************************************************/

#include <stm32l0xx_hal.h>
#include <system_clock.h>
#include <wes.h>

#ifdef __cplusplus
extern "C" {
#endif

int main()
{
  HAL_Init();
  WES_v_Init();

  // Configure the system clock to 2 MHz
  SYSTEMCLOCK_v_Config();

  // Infinite loop
  while(1)
  {
    WES_v_RunApp();
    HAL_Delay(100);
  }
}

#ifdef __cplusplus
}
#endif

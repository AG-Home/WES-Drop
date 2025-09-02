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
#include <display.h>

#ifdef __cplusplus
extern "C" {
#endif

int main()
{
  HAL_Init();

  // Configure the system clock to 2 MHz
  SYSTEMCLOCK_v_Config();

  DISPLAY_Init();

  DISPLAY_ShowLevel(12);

  // Infinite loop
  while(1)
  {
  }
}

#ifdef __cplusplus
}
#endif

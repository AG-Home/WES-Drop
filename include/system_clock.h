/**********************************************************************************************************************
 * \file system_clock.h
 *
 * \author MarcoAAG
 *
 * \date Apr-18-2025
 *
 * \version 1.0 \n \n
 *
 *********************************************************************************************************************/

#ifndef SYSTEM_CLOCK_H
#define SYSTEM_CLOCK_H

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *
 * \brief System Clock Configuration \n
 *        The system Clock is configured as follow : \n
 *            System Clock source            = MSI      \n
 *            SYSCLK(Hz)                     = 2000000  \n
 *            HCLK(Hz)                       = 2000000  \n
 *            AHB Prescaler                  = 1        \n
 *            APB1 Prescaler                 = 1        \n
 *            APB2 Prescaler                 = 1        \n
 *            Flash Latency(WS)              = 0        \n
 *
 ******************************************************************************/
void SYSTEMCLOCK_v_Config(void);

#ifdef __cplusplus
}
#endif

#endif // SYSTEM_CLOCK_H
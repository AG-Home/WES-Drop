/**********************************************************************************************************************
 * \file sr04m_if.h
 *
 * \author  MarcoAAG
 *
 * \date Sep-03-2025
 *
 * \version 1.0 \n \n
 *
 *********************************************************************************************************************/

#ifndef SR04M_IF_H
#define SR04M_IF_H

#include <level_errors.h>
#include <sr04m.h>
#include <stm32l0xx_hal.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
  USART_TypeDef*   pt_instance;
  UART_InitTypeDef t_parameters;
} LEVEL_UART_PARAMS;

LEVEL_Status SR04M_InitInterface(SR04M_Object* tp_obj, LEVEL_UART_PARAMS* tp_uartObj);

#ifdef __cplusplus
}
#endif

#endif // SR04M_IF_H
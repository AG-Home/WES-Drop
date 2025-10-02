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
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

LEVEL_Status SR04M_InitInterface(void);

LEVEL_Status SR04MIF_e_GetDistance(uint16_t* u_distance);

#ifdef __cplusplus
}
#endif

#endif // SR04M_IF_H
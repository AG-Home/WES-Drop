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

#ifdef __cplusplus
extern "C" {
#endif

LEVEL_ERROR SR04M_InitInterface(SR04M_Object* tp_obj);

#ifdef __cplusplus
}
#endif

#endif // SR04M_IF_H
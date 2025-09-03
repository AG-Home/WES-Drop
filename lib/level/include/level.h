/**********************************************************************************************************************
 * \file level.h
 *
 * \author  MarcoAAG
 *
 * \date Sep-03-2025
 *
 * \version 1.0 \n \n
 *
 *********************************************************************************************************************/

#ifndef LEVEL_H
#define LEVEL_H

#include <sr04m_if.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
  SR04M_Object t_driver;
  SR04M_Modes  e_mode;
} Level_Object;

/* ============================================================================================== */
/*                                         Public Functions                                       */
/* ============================================================================================== */

LEVEL_ERROR LEVEL_e_Init(Level_Object* p_obj);

LEVEL_ERROR LEVEL_e_GetLevel(Level_Object* p_obj, uint8_t* pu_level);

#ifdef __cplusplus
}
#endif

#endif // LEVEL_H
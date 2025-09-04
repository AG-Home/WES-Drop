/**********************************************************************************************************************
 * \file level.c
 *
 * \author  MarcoAAG
 *
 * \date Sep-03-2025
 *
 * \version 1.0 \n \n
 *
 *********************************************************************************************************************/

#include <level.h>

#ifdef __cplusplus
extern "C" {
#endif

LEVEL_Status LEVEL_e_Init(Level_Object* p_obj)
{
  LEVEL_Status e_retVal;

  e_retVal = SR04M_InitInterface(&p_obj->t_driver, &p_obj->t_uartParams);

  return e_retVal;
}

LEVEL_Status LEVEL_e_GetLevel(Level_Object* p_obj, uint8_t* pu_level)
{
  LEVEL_Status e_retVal;
  uint16_t     u_distance;

  e_retVal = SR04M_u_GetDistance(&p_obj->t_driver, &u_distance, p_obj->e_mode);

  return e_retVal;
}

#ifdef __cplusplus
}
#endif

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

LEVEL_ERROR LEVEL_e_Init(Level_Object* p_obj)
{
  LEVEL_ERROR e_retVal;

  e_retVal = SR04M_InitInterface(&p_obj->t_driver);

  return e_retVal;
}

LEVEL_ERROR LEVEL_e_GetLevel(Level_Object* p_obj, uint8_t* pu_level)
{
  return LEVEL_OK;
}

#ifdef __cplusplus
}
#endif

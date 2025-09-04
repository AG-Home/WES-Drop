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

#define CM_TO_MM(x)     (x * 10)
#define MIN_MEAS        CM_TO_MM(25)  // 30cm
#define MAX_MEAS        CM_TO_MM(148) // 148cm
#define CAPACITY        MAX_MEAS - MIN_MEAS
#define PACE_PERCENTAGE CAPACITY

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
  uint32_t     u_distanceRes;
  uint32_t     u_tmp;

  if(SR04M_u_GetDistance(&p_obj->t_driver, &u_distance, p_obj->e_mode) != SR04M_OK)
  {
    e_retVal = LEVEL_ERR_DISTANCE;
  }

  if(e_retVal == LEVEL_OK)
  {
    if(u_distance < MIN_MEAS)
    {
      u_distance = MIN_MEAS;
    }
    if(u_distance > MAX_MEAS)
    {
      u_distance = MAX_MEAS;
    }

    u_distanceRes = u_distance * 100;
    u_tmp         = (MAX_MEAS * 100) - u_distanceRes;
    *pu_level     = u_tmp / PACE_PERCENTAGE;
  }

  return e_retVal;
}

#ifdef __cplusplus
}
#endif

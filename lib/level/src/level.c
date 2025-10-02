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

#define MIN_MEAS 25
#define MAX_MEAS 145

static const uint32_t u_MIN_MEAS        = MIN_MEAS * 10U;
static const uint32_t u_MAX_MEAS        = MAX_MEAS * 10U;
static const uint32_t u_CAPACITY        = u_MAX_MEAS - u_MIN_MEAS;
static const uint32_t u_PACE_PERCENTAGE = u_CAPACITY;

LEVEL_Status LEVEL_e_Init(Level_Object* p_obj)
{
  LEVEL_Status e_retVal;

  e_retVal = SR04M_InitInterface(&p_obj->t_driver, &p_obj->t_uartParams);

  return e_retVal;
}

LEVEL_Status LEVEL_e_GetLevel(Level_Object* p_obj, uint8_t* pu_level)
{
  LEVEL_Status e_retVal = LEVEL_OK;
  uint16_t     u_distance;
  uint32_t     u_distanceRes;
  uint32_t     u_tmp;

  if(SR04M_Driver.GetDistance(&p_obj->t_driver, &u_distance) != SR04M_OK)
  {
    e_retVal = LEVEL_ERR_DISTANCE;
  }

  if(e_retVal == LEVEL_OK)
  {
    if(u_distance < u_MIN_MEAS)
    {
      u_distance = u_MIN_MEAS;
    }
    else if(u_distance > u_MAX_MEAS)
    {
      u_distance = u_MAX_MEAS;
    }

    u_distanceRes = (uint32_t)u_distance * 100u;
    u_tmp         = (u_MAX_MEAS * 100U) - u_distanceRes;
    *pu_level     = u_tmp / u_PACE_PERCENTAGE;
  }

  return e_retVal;
}

#ifdef __cplusplus
}
#endif

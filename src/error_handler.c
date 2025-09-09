/**********************************************************************************************************************
 * \file error_handler.C
 *
 * \author MarcoAAG
 *
 * \date Sep-09-2025
 *
 * \version 1.0 \n \n
 *
 *********************************************************************************************************************/

#include <error_handler.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MAX_LEVEL_ERROR_CNTR   50u
#define MAX_DISPLAY_ERROR_CNTR 20u

static void          ERRH_v_SetError(WES_ErrorCode t_err);
static WES_ErrorCode ERRH_t_GetError(void);
static void          ERRH_v_Handle(void);

static WES_ErrorHandler t_obj;

void ERRH_v_Init(WES_ErrorHandler* pt_handler)
{
  t_obj              = *pt_handler;
  t_obj.currentError = ERR_NONE;
  t_obj.setError     = ERRH_v_SetError;
  t_obj.getError     = ERRH_t_GetError;
}

static void ERRH_v_SetError(WES_ErrorCode t_err)
{
  t_obj.currentError = t_err;
  ERRH_v_Handle();
}

static WES_ErrorCode ERRH_t_GetError(void)
{
  return t_obj.currentError;
}

static void ERRH_v_Handle(void)
{
  static uint8_t u_cntrLevelErr;
  static uint8_t u_cntrDisplayErr;

  switch(t_obj.currentError)
  {
    case ERR_NONE:
      break;
    case ERR_DISPLAY:
      u_cntrDisplayErr++;
      if(u_cntrDisplayErr > MAX_DISPLAY_ERROR_CNTR)
      {
        ERRH_v_SetError(ERR_FATAL);
      }
      break;
    case ERR_LEVEL:
      u_cntrLevelErr++;
      if(u_cntrDisplayErr > MAX_LEVEL_ERROR_CNTR)
      {
        ERRH_v_SetError(ERR_FATAL);
      }
      break;
    case ERR_FATAL:
      while(1);
      break;
    default:
      break;
  }
}

#ifdef __cplusplus
}
#endif

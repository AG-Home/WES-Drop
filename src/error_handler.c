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

#define MAX_LEVEL_ERROR_CNTR   10u
#define MAX_DISPLAY_ERROR_CNTR 8u

static void          ERRH_v_SetError(WES_ErrorCode t_err);
static WES_ErrorCode ERRH_t_GetError(void);
static void          ERRH_v_Handle(void);
static void          ERRH_v_DisplayErrHandler(void);
static void          ERRH_v_LevelErrHandler(void);
static void          ERRH_v_FatalErrHandler(void);

static uint8_t          u_cntrDisplayErr;
static uint8_t          u_cntrLevelErr;
static WES_ErrorCode    e_currentError;
static WES_ErrorHandler t_obj;

void ERRH_v_Init(WES_ErrorHandler* pt_handler)
{
  t_obj          = *pt_handler;
  t_obj.setError = ERRH_v_SetError;
  t_obj.getError = ERRH_t_GetError;
}

static void ERRH_v_SetError(WES_ErrorCode t_err)
{
  e_currentError = t_err;
  ERRH_v_Handle();
}

static WES_ErrorCode ERRH_t_GetError(void)
{
  return e_currentError;
}

static void ERRH_v_Handle(void)
{
  switch(e_currentError)
  {
    case ERR_NONE:
      break;
    case ERR_DISPLAY:
      ERRH_v_DisplayErrHandler();
      break;
    case ERR_LEVEL:
      ERRH_v_LevelErrHandler();
      break;
    case ERR_FATAL:
      ERRH_v_FatalErrHandler();
      break;
    case ERR_DISPLAY_CLEAR:
      u_cntrDisplayErr = 0u;
      break;
    case ERR_LEVEL_CLEAR:
      u_cntrLevelErr = 0u;
      break;
    default:
      break;
  }
}

static void ERRH_v_DisplayErrHandler(void)
{
  u_cntrDisplayErr++;

  if(u_cntrDisplayErr > MAX_DISPLAY_ERROR_CNTR)
  {
    ERRH_v_FatalErrHandler();
  }
  else
  {
    e_currentError = ERR_NONE; // clear error
  }
}

static void ERRH_v_LevelErrHandler(void)
{
  u_cntrLevelErr++;

  if(u_cntrLevelErr > MAX_LEVEL_ERROR_CNTR)
  {
    ERRH_v_FatalErrHandler();
  }
  else
  {
    e_currentError = ERR_NONE; // clear error
  }
}

static void ERRH_v_FatalErrHandler(void)
{
  while(1);
}

#ifdef __cplusplus
}
#endif

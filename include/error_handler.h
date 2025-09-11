/**********************************************************************************************************************
 * \file error_handler.h
 *
 * \author MarcoAAG
 *
 * \date Sep-09-2025
 *
 * \version 1.0 \n \n
 *
 *********************************************************************************************************************/

#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
  ERR_DISPLAY_CLEAR = 2,
  ERR_LEVEL_CLEAR   = 1,
  ERR_NONE          = 0,
  ERR_LEVEL         = -1,
  ERR_DISPLAY       = -2,
  ERR_FATAL         = -3
} WES_ErrorCode;

typedef struct WES_ErrorHandler WES_ErrorHandler;

typedef void (*SetErrorFunc)(WES_ErrorCode);
typedef WES_ErrorCode (*GetErrorFunc)(void);

struct WES_ErrorHandler {
  SetErrorFunc setError;
  GetErrorFunc getError;
};

WES_ErrorHandler* ERRH_t_Init(void);

#ifdef __cplusplus
}
#endif

#endif // ERROR_HANDLER_H
/**********************************************************************************************************************
 * \file level_errors.h
 *
 * \author  MarcoAAG
 *
 * \date Sep-03-2025
 *
 * \version 1.0 \n \n
 *
 *********************************************************************************************************************/

#ifndef LEVEL_ERRORS_H
#define LEVEL_ERRORS_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
  LEVEL_OK       = 0,
  LEVEL_ERR_UART = -1,
  LEVEL_ERR_INIT = -2
} LEVEL_ERROR;

#ifdef __cplusplus
}
#endif

#endif // LEVEL_ERRORS_H
/**********************************************************************************************************************
 * \file display_errors.h
 *
 * \author  MarcoAAG
 *
 * \date Sep-01-2025
 *
 * \version 1.0 \n \n
 *
 *********************************************************************************************************************/

#ifndef DISPLAY_ERRORS_H
#define DISPLAY_ERRORS_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
  DISPLAY_OK          = 0,
  DISPLAY_ERR_IIC     = -1,
  DISPLAY_ERR_SSD1309 = -2
} DISPLAY_ERROR;

#ifdef __cplusplus
}
#endif

#endif // DISPLAY_ERRORS_H
/**********************************************************************************************************************
 * \file display.h
 *
 * \author  MarcoAAG
 *
 * \date Ago-23-2025
 *
 * \version 1.0 \n \n
 *
 *********************************************************************************************************************/

#ifndef DISPLAY_H
#define DISPLAY_H

/* ============================================================================================== */
/*                                         Include Files                                          */
/* ============================================================================================== */
#include <display_errors.h>
#include <font.h>
#include <ssd1315.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
  SSD1315_Object_t t_driver;
  Font_t           t_font;
} Display_Object;

/* ============================================================================================== */
/*                                         Public Functions                                       */
/* ============================================================================================== */

DISPLAY_ERROR DISPLAY_e_Init(Display_Object* p_obj);

DISPLAY_ERROR DISPLAY_e_ShowLevel(Display_Object* p_obj, uint8_t u_percentage);

#ifdef __cplusplus
}
#endif

#endif // DISPLAY_H
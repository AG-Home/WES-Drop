/**********************************************************************************************************************
 * \file display.c
 *
 * \author  Marco Aguilar
 *
 * \date Ago-23-2025
 *
 * \version 1.0 \n \n
 *
 *********************************************************************************************************************/

#include <display.h>
#include <ssd1309_if.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

static void DISPLAY_v_U8ToStr(uint8_t u_num, char* p_str);
static void DISPLAY_v_GetCenteredCoords(const char* p_str, const Font_t* t_font, uint8_t* pu_x, uint8_t* pu_y);
static void DISPLAY_v_DrawChar(SSD1315_Object_t* t_pObj, uint8_t u_posX, uint8_t u_posY, char c_char, const Font_t* t_font);
static void DISPLAY_v_DrawString(SSD1315_Object_t* p_obj, uint8_t u_posX, uint8_t u_posY, const char* p_str, const Font_t* t_font);

DISPLAY_ERROR DISPLAY_e_Init(Display_Object* p_obj)
{
  DISPLAY_ERROR e_retVal;

  p_obj->t_font.p_data       = FONT32x56;
  p_obj->t_font.u_charHeight = 56;
  p_obj->t_font.u_charWidth  = 32;

  e_retVal = SSD1309_InitInterface(&p_obj->t_driver);

  return e_retVal;
}

DISPLAY_ERROR DISPLAY_e_ShowLevel(Display_Object* p_obj, uint8_t u_percentage)
{
  DISPLAY_ERROR e_retVal = DISPLAY_OK;
  char          str_percentage[5];
  uint8_t       u_digits, u_posX, u_posY;

  if(u_percentage > 100)
  {
    e_retVal = DISPLAY_ERR_EXCEEDED;
  }
  else
  {
    DISPLAY_v_U8ToStr(u_percentage, str_percentage);

    u_digits                     = strlen(str_percentage);
    str_percentage[u_digits]     = '%';
    str_percentage[u_digits + 1] = '\0';

    DISPLAY_v_GetCenteredCoords(str_percentage, &p_obj->t_font, &u_posX, &u_posY);
    ssd1315_Clear(SSD1315_COLOR_BLACK);
    DISPLAY_v_DrawString(&p_obj->t_driver, u_posX, u_posY, str_percentage, &p_obj->t_font);
  }

  return e_retVal;
}

static void DISPLAY_v_DrawChar(SSD1315_Object_t* t_pObj, uint8_t u_posX, uint8_t u_posY, char c_char, const Font_t* t_font)
{
  const char s_VALIDCHARS[] = "%0123456789";

  // Verify if is valid char
  const char* s_CHARPOS = strchr(s_VALIDCHARS, c_char);

  // Get index based on char position
  uint32_t char_index = (s_CHARPOS - s_VALIDCHARS) * t_font->u_charHeight;

  // Get char's bitmap
  const uint32_t* p_bitmap = (const uint32_t*)t_font->p_data + char_index;

  for(uint8_t u_row = 0; u_row < t_font->u_charHeight; u_row++)
  {
    uint32_t u_rowData = p_bitmap[u_row];

    for(uint8_t u_col = 0; u_col < t_font->u_charWidth; u_col++)
    {
      if(u_rowData & (1 << (31 - u_col))) // MSB first
      {
        SSD1315_SetPixel(t_pObj, u_posX + u_col, u_posY + u_row, SSD1315_COLOR_WHITE);
      }
      else
      {
        SSD1315_SetPixel(t_pObj, u_posX + u_col, u_posY + u_row, SSD1315_COLOR_BLACK);
      }
    }
  }
}

static void DISPLAY_v_DrawString(SSD1315_Object_t* p_obj, uint8_t u_posX, uint8_t u_posY, const char* p_str, const Font_t* t_font)
{
  uint8_t u_offsetX  = 0;
  uint8_t u_tracking = 0; // pixels of space between chars

  while(*p_str)
  {
    DISPLAY_v_DrawChar(p_obj, u_posX + u_offsetX, u_posY, *p_str, t_font);
    u_offsetX += t_font->u_charWidth + u_tracking; // Go to next char
    p_str++;
  }
  SSD1315_Refresh(p_obj);
}

static void DISPLAY_v_U8ToStr(uint8_t u_num, char* p_str)
{
  if(u_num > 99)
  {
    // 3 Digits
    p_str[0] = (u_num / 100) + '0';
    p_str[1] = ((u_num / 10) % 10) + '0';
    p_str[2] = (u_num % 10) + '0';
    p_str[3] = '\0';
  }
  else if(u_num >= 10)
  {
    // 2 Digits
    p_str[0] = (u_num / 10) + '0';
    p_str[1] = (u_num % 10) + '0';
    p_str[2] = '\0';
  }
  else
  {
    // 1 Digit
    p_str[0] = u_num + '0';
    p_str[1] = '\0';
  }
}

static void DISPLAY_v_GetCenteredCoords(const char* p_str, const Font_t* t_font, uint8_t* pu_x, uint8_t* pu_y)
{
  uint8_t u_len       = strlen(p_str);
  uint8_t u_textWidth = u_len * t_font->u_charWidth;

  *pu_x = (SSD1315_LCD_PIXEL_WIDTH - u_textWidth) / 2;
  *pu_y = (SSD1315_LCD_PIXEL_HEIGHT - t_font->u_charHeight) / 2;
}

#ifdef __cplusplus
}
#endif
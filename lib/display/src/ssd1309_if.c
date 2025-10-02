/**********************************************************************************************************************
 * \file ssd1309_if.c
 *
 * \author  Marco Aguilar
 *
 * \date Ago-23-2025
 *
 * \version 1.0 \n \n
 *
 *********************************************************************************************************************/

#include <ssd1309_if.h>
#include <stdint.h>
#include <stm32l0xx_hal.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================================== */
/*                                        Defines & Macros                                        */
/* ============================================================================================== */
#define I2C_TIMING      268501508U // 100 kHz with analog Filter ON, Rise Time 1000ns, Fall Time 1000ns
#define I2C_ADDRESS     0x3C
#define I2Cx            I2C1
#define SSD1309_MAX_LEN (128 * 8) // 128*8 -> PhysFrameBuffer

/* ============================================================================================== */
/*                                    Private Function Prototypes                                 */
/* ============================================================================================== */
static int32_t SSD1309_Initialize(void);
static int32_t SSD1309_DeInitialize(void);
static int32_t SSD1309_WriteCommand(uint16_t Addr, uint8_t* pData, uint16_t Length);
static int32_t SSD1309_ReadData(uint16_t Addr, uint8_t* pData, uint16_t Length);
static int32_t SSD1309_GetTick(void);

/* ============================================================================================== */
/*                                         Private Types                                          */
/* ============================================================================================== */

SSD1315_IO_t SSD1315_IO = {
  .Init     = SSD1309_Initialize,
  .DeInit   = SSD1309_DeInitialize,
  .WriteReg = SSD1309_WriteCommand,
  .ReadReg  = SSD1309_ReadData,
  .GetTick  = SSD1309_GetTick,
};

I2C_HandleTypeDef t_iicHandle;

/* ============================================================================================== */
/*                                         Public Functions                                       */
/* ============================================================================================== */

DISPLAY_Status SSD1309_InitInterface(SSD1315_Object_t* tp_obj)
{
  DISPLAY_Status e_retVal           = DISPLAY_OK;
  t_iicHandle.Instance              = I2Cx;
  t_iicHandle.Init.Timing           = I2C_TIMING;
  t_iicHandle.Init.OwnAddress1      = I2C_ADDRESS;
  t_iicHandle.Init.AddressingMode   = I2C_ADDRESSINGMODE_7BIT;
  t_iicHandle.Init.DualAddressMode  = I2C_DUALADDRESS_DISABLE;
  t_iicHandle.Init.OwnAddress2      = 0xFF;
  t_iicHandle.Init.OwnAddress2Masks = I2C_OA2_NOMASK;
  t_iicHandle.Init.GeneralCallMode  = I2C_GENERALCALL_DISABLE;
  t_iicHandle.Init.NoStretchMode    = I2C_NOSTRETCH_DISABLE;

  // Enable the Analog I2C
  if(HAL_I2C_Init(&t_iicHandle) != HAL_OK)
  {
    e_retVal = DISPLAY_ERR_IIC;
  }

  // Enable the Analog I2C Filter
  if(HAL_I2CEx_ConfigAnalogFilter(&t_iicHandle, I2C_ANALOGFILTER_ENABLE) != HAL_OK)
  {
    e_retVal = DISPLAY_ERR_IIC;
  }
  if(SSD1315_RegisterBusIO(tp_obj, &SSD1315_IO) != SSD1315_OK)
  {
    e_retVal = DISPLAY_ERR_SSD1309;
  }

  e_retVal = SSD1315_Driver.Init(tp_obj, SSD1315_FORMAT_DEFAULT, SSD1315_ORIENTATION_LANDSCAPE);
  if(e_retVal == SSD1315_OK)
  {
    e_retVal = SSD1315_Driver.DisplayOn(tp_obj);
  }

  return e_retVal;
}

/* ============================================================================================== */
/*                                         Private Functions                                      */
/* ============================================================================================== */
static int32_t SSD1309_Initialize(void)
{
  uint8_t u_iicStat = 0;

  return u_iicStat;
}

static int32_t SSD1309_DeInitialize(void)
{
  return 0;
}

static int32_t SSD1309_WriteCommand(uint16_t Addr, uint8_t* pData, uint16_t Length)
{
  uint8_t        u_stat       = 0;
  const uint32_t u_timeoutIIC = 10000;
  uint8_t        u_buffer[SSD1309_MAX_LEN + 1];

  if(Length > SSD1309_MAX_LEN)
  {
    u_stat = DISPLAY_ERR_IIC;
  }
  else
  {
    u_buffer[0] = (uint8_t)Addr;
    memcpy(&u_buffer[1], pData, Length);
    u_stat = HAL_I2C_Master_Transmit(&t_iicHandle, (uint16_t)I2C_ADDRESS << 1, u_buffer, Length + 1, u_timeoutIIC);
  }

  return u_stat;
}

static int32_t SSD1309_ReadData(uint16_t Addr, uint8_t* pData, uint16_t Length)
{
  // NOT SUPPORTED
  return DISPLAY_ERR_NOTSUPP;
}

static int32_t SSD1309_GetTick(void)
{
  return HAL_GetTick();
}

#ifdef __cplusplus
}
#endif
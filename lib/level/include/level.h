/**********************************************************************************************************************
 * \file level.h
 *
 * \author  MarcoAAG
 *
 * \date Sep-03-2025
 *
 * \version 1.0 \n \n
 *
 *********************************************************************************************************************/

#ifndef LEVEL_H
#define LEVEL_H

#include <level_errors.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ============================================================================================== */
/*                                         Public Functions                                       */
/* ============================================================================================== */

LEVEL_Status LEVEL_e_Init(void);

LEVEL_Status LEVEL_e_GetLevel(uint8_t* pu_level);

#ifdef __cplusplus
}
#endif

#endif // LEVEL_H
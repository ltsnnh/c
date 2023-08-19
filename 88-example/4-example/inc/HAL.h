#ifndef _HAL_H_
#define _HAL_H_

/******************************************************************************
 * Definitions
******************************************************************************/
/* @define Boot sector size (Byte) */
#define HAL_BS_SZ   512u

/******************************************************************************
 * API
******************************************************************************/
void* HAL_mountDisk(const char* const diskName);
uint16_t HAL_readSector(const uint32_t index, uint8_t* const secBuff);
uint32_t HAL_readMultiSector(const uint32_t index, const uint8_t number, uint8_t* const bigBuff);
int32_t HAL_unMountDisk(void);
void HAL_updateSectorSize(const uint16_t newSecSz);

#endif  /* _HAL_H_ */

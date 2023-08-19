/**
 * HAL (Hardware Abstraction Layer)
 *
 * The third layer is concerned with the physical operation of the storage
 * device (e.g. disk), processes reading or writing directly to hardware
*/
#include <stdio.h>
#include <stdint.h>
#include "HAL.h"

/******************************************************************************
 * Definitions
******************************************************************************/
/* @define Return value of fseek() if success */
#define HAL_FSEEK_SUCCESS 0u

/******************************************************************************
 * Variables
******************************************************************************/
static FILE* gs_pDisk = NULL;                       /* Disk pointer */
static uint16_t gs_secSz = HAL_BS_SZ;               /* Sector size (Byte) */
static const int32_t gs_szUChar = sizeof(uint8_t);  /* Sizeof(UChar) is 1 */

/******************************************************************************
 * Code
******************************************************************************/
/**
 * @brief   Mounting Disk
 *
 * @param   Disk name
 * @return  gs_pDisk if success | NULL if an error occurred
*/
void* HAL_mountDisk(const char* const diskName)
{
    return(gs_pDisk = fopen(diskName, "rb"));
}

/**
 * @brief   Read sector at index position, save to memory area pointed by
 * secBuff
 *
 * @param   index (Sector), &buff
 * @return  Number of bytes has read
*/
uint16_t HAL_readSector(const uint32_t index, uint8_t* const secBuff)
{
    uint16_t retVal = 0;

    if (fseek(gs_pDisk, index * gs_secSz, SEEK_SET) == HAL_FSEEK_SUCCESS)
    {
        retVal = fread(secBuff, gs_szUChar, gs_secSz, gs_pDisk);
    }

    return(retVal);
}

/**
 * @brief   Read number of contiguously sectors started at position index,
 * save into memory area pointed by bigBuff
 *
 * @param   index (Sector), number (Sector), &buff
 * @return  Number of bytes has read
*/
uint32_t HAL_readMultiSector(const uint32_t index, const uint8_t number, uint8_t* const bigBuff)
{
    uint32_t retVal = 0;

    if (fseek(gs_pDisk, index * gs_secSz, SEEK_SET) == HAL_FSEEK_SUCCESS)
    {
        retVal = fread(bigBuff, gs_szUChar, number * gs_secSz, gs_pDisk);
    }

    return(retVal);
}

/**
 * @brief   Unmounting Disk
 *
 * @param   void
 * @return  0 if success | EOF if an error occurred
*/
int32_t HAL_unMountDisk(void)
{
    return(fclose(gs_pDisk));
}

/**
 * @brief   Update sector size
 *
 * @param   Sector size after calculated
*/
void HAL_updateSectorSize(const uint16_t newSecSz)
{
    gs_secSz = newSecSz;
}

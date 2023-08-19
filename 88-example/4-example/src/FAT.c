/**
 * FAT (File Allocate Table) file system
 *
 * Virtual file system
 * The second layer allows support for multiple concurrent instances of
 * physical file systems
 * There are three variants of the FAT: FAT12, FAT16, FAT32
*/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "FAT.h"
#include "HAL.h"

/******************************************************************************
 * Definitions
******************************************************************************/
/* @define __attribute__((packed)) :the compiler don't align struct elements */
#ifdef __GNUC__
#define FAT_PACK __attribute__((packed))
#else
#define FAT_PACK
#endif

/**
 * @groupdef Read a number written in little-endian form
*/
#define FAT_READ_UINT16(ADDR)  (*((uint16_t*)(ADDR)))
#define FAT_READ_UINT32(ADDR)  (*((uint32_t*)(ADDR)))

/**
 * @groupdef Calculator time-date in directory entry
*/
#define FAT_READ_SEC(time)      ((uint8_t)((time) & 0x001Fu) * 2u)
#define FAT_READ_MINUTE(time)   ((uint8_t)(((time) >> 5u) & 0x003Fu))
#define FAT_READ_HOUR(time)     ((uint8_t)((time)  >> 11u))
#define FAT_READ_DAY(date)      ((uint8_t)((date) & 0x001Fu))
#define FAT_READ_MONTH(date)    ((uint8_t)(((date) >> 5u) & 0x000Fu))
#define FAT_READ_YEAR(date)     (((date) >> 9u) + 1980u)

/* @define Boot sector offset (Sector) */
#define FAT_BS_OFFSET   0u

/* @define Default first cluster number, should be 2 */
#define FAT_DEFAUT_FIRST_CLUSTER_NUMBER     2u

/* @define Directory entry size (Byte) */
#define FAT_DIR_ENTRY_SZ   32u

/**
 * @defgroup Total clusters limits for FAT types (Cluster)
*/
#define FAT_MIN_CLUSTERS_LIMIT          2u
#define FAT_TOTAL_CLUSTERS_LIMIT_FAT12  4085u
#define FAT_TOTAL_CLUSTERS_LIMIT_FAT16  65525u
#define FAT_TOTAL_CLUSTERS_LIMIT_FAT32  268435444u

/**
 * @defgroup DIR_Name[0] special values
*/
#define FAT_AVAILABLE_ENTRY     0x00u   /* Important */
#define FAT_DOT_DOTDOT_ENTRY    0x2Eu   /* Important */
#define FAT_PRE_ERASED_ENTRY    0xE5u

/**
 * @defgroup File/Directory attributes mask
*/
#define FAT_READ_ONLY           0x01u
#define FAT_HIDDEN              0x02u
#define FAT_SYSTEM              0x04u
#define FAT_VOLUME_ID           0x08u
#define FAT_DIRECTORY           0x10u   /* Important */
#define FAT_ARCHIVE             0x20u

/* @define An attribute combination stand for VFAT LFN */
#define VFAT_LFN_ATTRIBUTE      0x0Fu   /* Important */

/**
 * @defgroup 8.3 file name element length
*/
#define FAT_NAME_LENGTH     8u
#define FAT_EXT_LENGTH      3u

/**
 * @defgroup FAT entry value corresponding type of FAT
*/

#define FAT_freeValueCm         0u          /*  end-of-chain marker */
#define FAT_reservedValueCm     1u          /*  end-of-chain marker */
#define FAT12                   0xFF8u              /* EOC */
#define FAT16                   0xFFF8u             /* EOC */
#define FAT32                   0x0FFFFFF8u         /* EOC */


/**
 * @define  Type of directory entry
*/
typedef enum
{
    FAT_normalEntry = 0u,
    FAT_freeEntry   = 1u,
    FAT_eocEntry    = 2u,
    FAT_lfnEntry    = 3u
} FAT_dirEntryType_t;

/**
 * @define BIOS Parameter Block is located in the first sector of the volume
 * in the Reserved Region
 *
 * This sector is sometimes called the “boot sector” or the “0th sector”
*/
typedef struct
{
    /* BPB structure common - 36 bytes */
    uint8_t beNotParsed0[11];
    uint16_t BPB_BytsPerSec;    /* Bytes per sector */
    uint8_t BPB_SecPerClus;     /* Sectors per cluster */
    uint16_t BPB_RsvdSecCnt;    /* Number of reserved sectors */
    uint8_t BPB_NumFATs;        /* The count of FATs */
    uint16_t BPB_RootEntCnt;    /* FAT12-FAT16: Count of 32-byte entries in the root directory. FAT32: 0 */
    uint16_t BPB_TotSec16;      /* FAT12-FAT16: Count of sectors on
    the volume, if be 0 refer to BPB_TotSec32. FAT32: 0 */
    uint8_t beNotParsed1;
    uint16_t BPB_FATSz16;       /* FAT12-FAT16: Count of sectors occupied by one FAT. FAT32: 0, refer to BPB_FATSz32 */
    uint8_t beNotParsed2[8];
    uint32_t BPB_TotSec32;      /* Count of sectors on the volume. FAT12-FAT16: contains the sector count if BPB_TotSec16 is 0*/
    /* Extended BPB structure for FAT12 and FAT16 volumes */
    /* Nothing important */
    /* Extended BPB structure for FAT32 volumes - 476 bytes */
    uint32_t BPB_FATSz32;       /* FAT32: Count of sectors occupied by one FAT. BPB_FATSz16 must be 0*/
    uint8_t beNotParsed3[4];
    uint32_t BPB_RootClus;      /* The cluster number of the first cluster (should be 2) */
    uint8_t beNotParsed4[464];
} FAT_PACK FAT_BPB_struct_t;    /* sizeof = 512 bytes */

/**
 * @define Directory entry structure
 *
 * Directory entry represents a contained file or sub-directory
*/
typedef struct
{
    char DIR_name[FAT_NAME_LENGTH];
    char DIR_ext[FAT_EXT_LENGTH];
    uint8_t DIR_attr;
    uint8_t beNotParsed0[2];
    uint16_t DIR_crtTime;
    uint16_t DIR_crtDate;
    uint16_t DIR_lstAccDate;
    uint16_t DIR_fstClusHI;
    uint16_t DIR_wrtTime;
    uint16_t DIR_wrtDate;
    uint16_t DIR_fstClusLO;
    uint32_t DIR_fileSize;
} FAT_PACK FAT_DIR_entry_struct_t;

/******************************************************************************
 * Prototypes
******************************************************************************/
static FAT_errorCode_t FAT_initRootDirectory(void);
static FAT_errorCode_t FAT_readDirectoryData(const uint32_t index, const uint16_t size);
static FAT_dirEntryType_t FAT_parseDirEntry(const FAT_DIR_entry_struct_t* const dirEntry);
static uint32_t FAT_getClusterNum(const uint32_t N);
static FAT_errorCode_t FAT_initDirectory(uint32_t firstCluster);
static FAT_errorCode_t FAT_printFile(uint32_t firstCluster, uint32_t fileSz);
/* Linked-list */
static void FAT_addNode(FAT_dir_struct_t* const node);
static void FAT_freeLinkedList(void);

/******************************************************************************
 * Variables
******************************************************************************/
/**
 * @group FAT info
*/
static uint16_t gs_bytsPerSec;  /* Bytes per Sector (Byte) */
static uint8_t gs_secPerClus;   /* Sectors per Cluster (Sector) */
/**
 * @group FAT info after calculated
*/
static uint32_t gs_fatType;     /* FAT12 - FAT16 - FAT32 */
static uint32_t gs_fatOffset;   /* Sector number at the start of FAT region */
static uint32_t gs_rootOffset;  /* Sector number at the start of ROOT region */
static uint16_t gs_rootSz;      /* Size of ROOT region (Sector) */
static uint32_t gs_dataOffset;  /* Sector number at the start of DATA region */
/* The first cluster number, should be 2 */
static uint32_t gs_rootClus = FAT_DEFAUT_FIRST_CLUSTER_NUMBER;

/* Linked-list */
FAT_dir_struct_t* gs_pHead = NULL;

/******************************************************************************
 * Code
******************************************************************************/
/**
 * @brief   Mounting Disk, calculate fat's parameters and init ROOT directory
 *
 * @param   &diskName
 * @return  FAT_errorCode_t
*/
FAT_errorCode_t FAT_mountDisk(const char* const diskName, FAT_dir_struct_t** const pFolder)
{
    FAT_errorCode_t retVal = FAT_success;
    FAT_BPB_struct_t bootSector;
    /* FAT info */
    uint16_t rsvdSecCnt = 0;
    uint8_t numFATs = 0;
    uint16_t rootEntCnt = 0;
    uint32_t totSec = 0;
    uint32_t fatSz = 0;
    /* FAT info after calculated */
    uint32_t totClus;

    if (HAL_mountDisk(diskName) != NULL)
    {
        /* Read first 512 bytes in BOOT sector */
        if (HAL_readSector(FAT_BS_OFFSET, (uint8_t*)&bootSector) == HAL_BS_SZ)
        {
            gs_bytsPerSec = bootSector.BPB_BytsPerSec;
            gs_secPerClus = bootSector.BPB_SecPerClus;
            rsvdSecCnt = bootSector.BPB_RsvdSecCnt;
            numFATs = bootSector.BPB_NumFATs;
            rootEntCnt = bootSector.BPB_RootEntCnt;
            totSec = bootSector.BPB_TotSec16;
            if (totSec == 0)
            {
                totSec = bootSector.BPB_TotSec32;
            }
            fatSz = bootSector.BPB_FATSz16;
            if (fatSz == 0)
            {
                fatSz = bootSector.BPB_FATSz32;
            }
            /* FAT info calculation */
            gs_fatOffset = rsvdSecCnt;
            gs_rootOffset = gs_fatOffset + (numFATs * fatSz);
            gs_rootSz = (rootEntCnt * FAT_DIR_ENTRY_SZ) / gs_bytsPerSec;
            totClus = (totSec - gs_rootOffset - gs_rootSz) / gs_secPerClus;
            if (totClus < FAT_TOTAL_CLUSTERS_LIMIT_FAT12)
            {
                gs_fatType = FAT12;
            }
            else if (totClus < FAT_TOTAL_CLUSTERS_LIMIT_FAT16)
            {
                gs_fatType = FAT16;
            }
            else
            {
                gs_fatType = FAT32;
                gs_rootClus = bootSector.BPB_RootClus;
            }
            gs_dataOffset = gs_rootOffset + gs_rootSz;
            HAL_updateSectorSize(gs_bytsPerSec);
            /* After parsing BOOT sector, list folders and files in ROOT */
            retVal = FAT_initRootDirectory();
            if (retVal == FAT_success)
            {
                *pFolder = gs_pHead;
            }
        }
        else
        {
            retVal = FAT_hal_readBootFailed;
        }
    }
    else
    {
        retVal = FAT_hal_mountDiskFailed;
    }

    return(retVal);
}

/**
 * @brief   Init ROOT directory
 *
 * @param   void
 * @return  FAT_errorCode_t
*/
static FAT_errorCode_t FAT_initRootDirectory(void)
{
    FAT_errorCode_t retVal = FAT_success;

    FAT_freeLinkedList();
    if ((gs_fatType == FAT12) || (gs_fatType == FAT16))
    {
        /* On volumes formatted FAT12, FAT16, ROOT directory is fixed size */
        retVal = FAT_readDirectoryData(gs_rootOffset, gs_rootSz);
    }
    else
    {
        /* On volumes formatted FAT32, ROOT dir can be of variable size */
        retVal = FAT_initDirectory(gs_rootClus);
    }

    return(retVal);
}

/**
 * @brief   Read directory data sector by sector and parsing dir entry
 *
 * @param   index (Sector), size (Sector)
 * @return  FAT_errorCode_t
*/
static FAT_errorCode_t FAT_readDirectoryData(const uint32_t index,const uint16_t size)
{
    FAT_errorCode_t retVal = FAT_success;
    FAT_dirEntryType_t entryType = FAT_normalEntry;
    uint8_t secBuff[gs_bytsPerSec];     /* Buffer to store sector data */
    uint16_t sec = 0;                   /* Offset to begin of area (sector) */
    uint16_t ent = 0;                   /* Offset to begin of sector (byte) */
    FAT_DIR_entry_struct_t dirEntry;

    /* Read sector by sector in directory data */
    for (sec = 0; (sec < size) && (retVal == FAT_success); sec++)
    {
        if (HAL_readSector(index + sec, secBuff) == gs_bytsPerSec)
        {
            /* Read entry by entry in sector */
            for (ent = 0; ent < gs_bytsPerSec; ent += FAT_DIR_ENTRY_SZ)
            {
                memcpy(&dirEntry, &secBuff[ent], FAT_DIR_ENTRY_SZ);
                entryType = FAT_parseDirEntry(&dirEntry);   /*  */
                if (entryType == FAT_eocEntry)
                {
                    /* Entry is available and no subsequent entry is in use */
                    /* Just out of 2 for looping */
                    ent = gs_bytsPerSec;
                    sec = size;
                }
            }
        }
        else
        {
            retVal = FAT_hal_readDiskFailed;    /* Rarely happens */
        }
    }

    return(retVal);
}

/**
 * @brief   Parsing a directory entry
 *
 * @param   &entry
 * @return  FAT_dirEntryType_t
*/
static FAT_dirEntryType_t FAT_parseDirEntry(const FAT_DIR_entry_struct_t* const dirEntry)
{
    FAT_dirEntryType_t retVal = FAT_normalEntry;
    char fstCharName = dirEntry->DIR_name[0];
    FAT_dir_struct_t* pNode = NULL;
    uint16_t i = 0;
    uint16_t mark = 0;
    /* Support LFN */
    static char fileName[256];
    static uint16_t lfnLen = 0;
    uint8_t* buff = (uint8_t*)dirEntry;

    if (dirEntry->DIR_attr == VFAT_LFN_ATTRIBUTE)
    {
        retVal = FAT_lfnEntry;
        if ((buff[0] & 0x40u) != 0)     /* last LFN entry: 010? ???? */
        {
            lfnLen = 0;
        }
        for (i = 0; i < 10; i += 2, lfnLen++)
        {
            fileName[lfnLen] = buff[0x01 + i];
        }
        for (i = 0; i < 12; i += 2, lfnLen++)
        {
            fileName[lfnLen] = buff[0x0E + i];
        }
        for (i = 0; i < 4; i += 2, lfnLen++)
        {
            fileName[lfnLen] = buff[0x1C + i];
        }
        /* remove padding spaces */
        while (fileName[lfnLen - 1] == ' ')
        {
            lfnLen--;
        }
        fileName[lfnLen] = '\0';   /* remove last space, add 'End of string' */
    }
    else if (fstCharName == FAT_AVAILABLE_ENTRY)
    {
        retVal = FAT_eocEntry;
    }
    else if (fstCharName == FAT_PRE_ERASED_ENTRY)
    {
        retVal = FAT_freeEntry;
    }
    else
    {
        pNode = (FAT_dir_struct_t*)malloc(sizeof(FAT_dir_struct_t));
        if (pNode == NULL)
        {
            /* If not allocated, it is considered to have ignored the entry */
            retVal = FAT_freeEntry;
            lfnLen = 0;
        }
        else
        {
            if(lfnLen > 0)
            {
                strcpy(pNode->name, fileName);
                lfnLen = 0;
            }
            else
            {
                /* 8.3 file name */
                memcpy(pNode->name, dirEntry->DIR_name, FAT_NAME_LENGTH);
                while ((i < FAT_NAME_LENGTH) && (pNode->name[i] != ' '))
                {
                    i++;
                }
                if (dirEntry->DIR_ext[0] == ' ')
                {
                    pNode->name[i] = '\0';
                }
                else
                {
                    pNode->name[i] = '.';
                    i++;
                    mark = i;
                    memcpy(&pNode->name[i], dirEntry->DIR_ext, FAT_EXT_LENGTH);
                    while ((i < (mark + FAT_EXT_LENGTH)) && (pNode->name[i] != ' '))
                    {
                        i++;
                    }
                    pNode->name[i] = '\0';
                }
            }
            /* Attributes */
            pNode->readOnly = dirEntry->DIR_attr & FAT_READ_ONLY;
            pNode->hidden = dirEntry->DIR_attr & FAT_HIDDEN;
            pNode->system = dirEntry->DIR_attr & FAT_SYSTEM;
            pNode->volumeID = dirEntry->DIR_attr & FAT_VOLUME_ID;
            pNode->directory = dirEntry->DIR_attr & FAT_DIRECTORY;
            pNode->archive = dirEntry->DIR_attr & FAT_ARCHIVE;
            /* Create date and time */
            pNode->createTime.sec = FAT_READ_SEC(dirEntry->DIR_crtTime);
            pNode->createTime.minute = FAT_READ_MINUTE(dirEntry->DIR_crtTime);
            pNode->createTime.hour = FAT_READ_HOUR(dirEntry->DIR_crtTime);
            pNode->createTime.day = FAT_READ_DAY(dirEntry->DIR_crtDate);
            pNode->createTime.month = FAT_READ_MONTH(dirEntry->DIR_crtDate);
            pNode->createTime.year = FAT_READ_YEAR(dirEntry->DIR_crtDate);
            /* Last modify date and time */
            pNode->modifyTime.sec = FAT_READ_SEC(dirEntry->DIR_wrtTime);
            pNode->modifyTime.minute = FAT_READ_MINUTE(dirEntry->DIR_wrtTime);
            pNode->modifyTime.hour = FAT_READ_HOUR(dirEntry->DIR_wrtTime);
            pNode->modifyTime.day = FAT_READ_DAY(dirEntry->DIR_wrtDate);
            pNode->modifyTime.month = FAT_READ_MONTH(dirEntry->DIR_wrtDate);
            pNode->modifyTime.year = FAT_READ_YEAR(dirEntry->DIR_wrtDate);
            /* Last access date and time */
            pNode->accessDate.sec = 0;
            pNode->accessDate.minute = 0;
            pNode->accessDate.hour = 0;
            pNode->accessDate.day = FAT_READ_DAY(dirEntry->DIR_lstAccDate);
            pNode->accessDate.month = FAT_READ_MONTH(dirEntry->DIR_lstAccDate);
            pNode->accessDate.year = FAT_READ_YEAR(dirEntry->DIR_lstAccDate);
            /* First cluster */
            pNode->firstCluster = ((uint32_t)(dirEntry->DIR_fstClusHI) << 16) | dirEntry->DIR_fstClusLO;
            /* File size */
            pNode->fileSize = dirEntry->DIR_fileSize;
            /* End of parsing directory entry */
            FAT_addNode(pNode);
        }
    }

    return(retVal);
}

/**
 * @brief   Given any valid cluster number N, the algorithm used to determine
 *          the entry in the first FAT and return cluster number corresponding
 *          All calculating refer to first FAT table
 *
 * @param   current cluster
 * @return  next cluster | 0 if an error occurred
*/
uint32_t FAT_getClusterNum(const uint32_t N)
{
    uint32_t retVal = 0;        /* next cluster */
    uint32_t offset = 0;        /* Offset to begin of FAT */
    uint32_t secNum = 0;        /* Sector num contains entry for cluster N */
    uint32_t entOffset = 0;     /* Entry offset to begin of sector */
    uint8_t secBuff[gs_bytsPerSec * 2];

    if (gs_fatType == FAT16)
    {
        offset = N * 2;
    }
    else if (gs_fatType == FAT32)
    {
        offset = N * 4;
    }
    else if (gs_fatType == FAT12)
    {
        offset = N + (N / 2);
    }
    secNum = gs_fatOffset + (offset / gs_bytsPerSec);
    entOffset = offset % gs_bytsPerSec;

    /* FAT16/FAT32 FAT entries cannot span a sector boundary */
    /* FAT12 FAT entries may span over sector boundary */
    /* The easiest way is to load FAT12 FAT sectors into memory in pairs */
    if (((gs_bytsPerSec - 1) == entOffset) && (gs_fatType == FAT12))
    {
        if (HAL_readMultiSector(secNum, 2, secBuff) != (gs_bytsPerSec * 2))
        {
            retVal = 0;
        }
        else
        {
            retVal = FAT_READ_UINT16(&secBuff[entOffset]);
            if (N & 0x0001u)    /* Cluster number is ODD */
            {
                retVal = retVal >> 4;
            }
            else                /* Cluster number is EVEN */
            {
                retVal = retVal & 0x0FFFu;
            }
        }
    }
    else
    {
        if (HAL_readSector(secNum, secBuff) != gs_bytsPerSec)
        {
            retVal = 0;
        }
        else
        {
            if (gs_fatType == FAT16)
            {
                retVal = FAT_READ_UINT16(&secBuff[entOffset]);
            }
            else if (gs_fatType == FAT32)
            {
                retVal = FAT_READ_UINT32(&secBuff[entOffset]) & 0x0FFFFFFFu;
            }
            else if (gs_fatType == FAT12)
            {
                retVal = FAT_READ_UINT16(&secBuff[entOffset]);
                if (N & 0x0001u)
                {
                    retVal = retVal >> 4;   /* Cluster number is ODD */
                }
                else
                {
                    retVal = retVal & 0x0FFFu;  /* Cluster number is EVEN */
                }
            }
        }
    }

    return(retVal);
}

/**
 * @brief   Print error code
 *
 * @param   FAT_errorCode_t
*/
void FAT_printErrCode(const FAT_errorCode_t errCode)
{
    switch (errCode)
    {
        case FAT_hal_mountDiskFailed:
        printf("Mounting disk failed\n");
        break;
        case FAT_hal_readBootFailed:
        printf("Read boot sector failed\n");
        break;
        case FAT_hal_readDiskFailed:
        printf("Read disk failed\n");
        break;
        case FAT_nameDoesNotExist:
        printf("Name does not existed\n");
        break;
        case FAT_dirTreeNotInitYet:
        printf("Directory tree is not initialized yet, pls init it before\n");
        break;
        case FAT_nameIsNotFolder:
        printf("Name is a file, not a folder, can not change directory\n");
        break;
        case FAT_nameIsNotFile:
        printf("Name is a folder, not a file, can not read file\n");
        break;
        case FAT_addressFileError:
        printf("Can not read file due to address'file error\n");
        break;
        case FAT_hal_unMountDiskFailed:
        printf("Unmounting disk failed\n");
        break;
        default:
        printf("Unknown error code\n");
        break;
    }
}

/**
 * @brief   Given an valid directory name to access it
 *
 * @param   &(directory name), &pFolder
 * @return  FAT_errorCode_t
*/
FAT_errorCode_t FAT_changeDirectory(const char* const name, FAT_dir_struct_t** const pFolder)
{
    FAT_errorCode_t retVal = FAT_success;
    FAT_dir_struct_t* pCurrent = gs_pHead;

    if (pCurrent == NULL)
    {
        retVal = FAT_dirTreeNotInitYet;
    }
    else if (!strcmp(name, "~"))
    {
        retVal = FAT_initRootDirectory();
    }
    else
    {
        /* strcmp(): 0 if Same | 1 if Different */
        /* NOTE: reversing the position of 2 parameters will cause Segmentation fault (core dumped) */
        /* Because of how logic operators '&&'' work. May be different on gcc varials, or due to optimization, may be not i'm not clearly */
        while ((pCurrent != NULL) && strcmp(pCurrent->name, name))
        {
            pCurrent = pCurrent->pNext;
        }
        if (pCurrent == NULL)
        {
            retVal = FAT_nameDoesNotExist;
        }
        else if (pCurrent->directory == false)
        {
            retVal = FAT_nameIsNotFolder;
        }
        else
        {
            retVal = FAT_initDirectory(pCurrent->firstCluster);
        }
    }
    if (retVal == FAT_success)
    {
        *pFolder = gs_pHead;
    }

    return(retVal);
}

/**
 * @brief   Init a directory (either sub-dir or ROOT dir of FAT32)
 *
 * @param   first cluster
 * @return  FAT_errorCode_t
*/
static FAT_errorCode_t FAT_initDirectory(uint32_t firstCluster)
{
    FAT_errorCode_t retVal = FAT_success;

    FAT_freeLinkedList();

    if ((firstCluster == 0u) && ((gs_fatType == FAT12) || (gs_fatType == FAT16)))
    {
        retVal = FAT_initRootDirectory();
    }
    else
    {
        do
        {
            retVal = FAT_readDirectoryData(gs_dataOffset + (firstCluster - gs_rootClus) * gs_secPerClus, gs_secPerClus);
            firstCluster = FAT_getClusterNum(firstCluster);
        }
        while ((firstCluster > FAT_reservedValueCm) && (firstCluster < gs_fatType) && (retVal == FAT_success));
    }

    return(retVal);
}

/**
 * @brief   Read a file
 *
 * @param   file name
 * @return  FAT_errorCode_t
*/
FAT_errorCode_t FAT_readFile(const char* const name)
{
    FAT_errorCode_t retVal = FAT_success;
    FAT_dir_struct_t* pCurrent = gs_pHead;

    if (pCurrent == NULL)
    {
        retVal = FAT_dirTreeNotInitYet;
    }
    else
    {
        /* refer to NOTE of function FAT_changeDirectory() */
        while ((pCurrent != NULL) && strcmp(pCurrent->name, name))
        {
            pCurrent = pCurrent->pNext;
        }

        if (pCurrent == NULL)
        {
            retVal = FAT_nameDoesNotExist;
        }
        else if (pCurrent->directory == true)
        {
            retVal = FAT_nameIsNotFile;
        }
        else
        {
            retVal = FAT_printFile(pCurrent->firstCluster, pCurrent->fileSize);
        }
    }

    return(retVal);
}

/**
 * @brief   Print data of file to screen
 *
 * @param   first cluster, file size
 * @return  FAT_errorCode_t
*/
static FAT_errorCode_t FAT_printFile(uint32_t firstCluster, uint32_t fileSz)
{
    FAT_errorCode_t retVal = FAT_success;
    uint32_t bytsPerClus = gs_bytsPerSec * gs_secPerClus;
    uint8_t bigBuff[bytsPerClus + 1];   /* +1: add '\0' to printf("%s") */

    if ((firstCluster < gs_rootClus) || (firstCluster >= gs_fatType))
    {
        retVal = FAT_addressFileError;  /* Rarely happens, maybe never */
    }
    else
    {
        do
        {
            HAL_readMultiSector(gs_dataOffset + (firstCluster - gs_rootClus) *
                gs_secPerClus, gs_secPerClus, bigBuff);
            if (fileSz > bytsPerClus)
            {
                bigBuff[bytsPerClus] = '\0';
                fileSz = fileSz - bytsPerClus;
            }
            else
            {
                bigBuff[fileSz] = '\0';
            }
            printf("%s\n", bigBuff);
            firstCluster = FAT_getClusterNum(firstCluster);
        }
        while ((firstCluster > FAT_reservedValueCm) && (firstCluster < gs_fatType));
    }

    return(retVal);
}

/**
 * @brief   Unmount disk
 *
 * @param   void
 * @return  FAT_errorCode_t
*/
FAT_errorCode_t FAT_unMountDisk(void)
{
    FAT_errorCode_t retVal = FAT_success;

    if (HAL_unMountDisk() != 0)
    {
        retVal = FAT_hal_unMountDiskFailed;
    }

    FAT_freeLinkedList();

    return(retVal);
}


/******************************************************************************
 * Linked-list handle code
******************************************************************************/
/**
 * @brief   Add node to tail of linked-list (create if not available)
 *
 * @param   &node
*/
static void FAT_addNode(FAT_dir_struct_t* const node)
{
    FAT_dir_struct_t* pCurrent = gs_pHead;

    if (pCurrent == NULL)
    {
        node->pNext = NULL;
        gs_pHead = node;
    }
    else
    {
        while (pCurrent->pNext != NULL)
        {
            pCurrent = pCurrent->pNext;
        }
        node->pNext = NULL;
        pCurrent->pNext = node;
    }
}

/**
 * @brief   Free linked-list
 *
 * @param   void
*/
static void FAT_freeLinkedList(void)
{
    FAT_dir_struct_t* pCurrent = NULL;

    while (gs_pHead != NULL)
    {
        pCurrent = gs_pHead;
        gs_pHead = gs_pHead->pNext;
        free(pCurrent);
    }
}

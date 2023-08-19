#ifndef _FAT_H_
#define _FAT_H_

/******************************************************************************
 * Definitions
******************************************************************************/
/**
 * @define  Error code of functions in FAT library
*/
typedef enum
{
    FAT_success = 0u,
    FAT_hal_mountDiskFailed = -1,
    FAT_hal_readBootFailed = -2,
    FAT_hal_readDiskFailed = -3,
    FAT_nameDoesNotExist = -4,
    FAT_dirTreeNotInitYet = -5,
    FAT_nameIsNotFolder = -6,
    FAT_nameIsNotFile = -7,
    FAT_addressFileError = -8,
    FAT_hal_unMountDiskFailed = -9
} FAT_errorCode_t;

/**
 * @define Group define struct date and time
*/
typedef struct
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t sec;
} FAT_time_struct_t;

/**
 * @define Group define struct info of file or directory
*/
typedef struct entry
{
    char name[255];
    bool readOnly;
    bool hidden;
    bool system;
    bool volumeID;
    bool directory;
    bool archive;
    FAT_time_struct_t createTime;       /* Create time */
    FAT_time_struct_t accessDate;       /* Last access date */
    FAT_time_struct_t modifyTime;       /* Last modified time */
    uint32_t firstCluster;              /* First cluster number */
    uint32_t fileSize;                  /* File size in bytes (folder = 0) */
    struct entry* pNext;                /* Self-pointing structure */
} FAT_dir_struct_t;

/******************************************************************************
 * API
******************************************************************************/
FAT_errorCode_t FAT_mountDisk(const char* const diskName, FAT_dir_struct_t** const pFolder);
FAT_errorCode_t FAT_changeDirectory(const char* const name, FAT_dir_struct_t** const pFolder);
FAT_errorCode_t FAT_readFile(const char* const name);
FAT_errorCode_t FAT_unMountDisk(void);
void FAT_printErrCode(const FAT_errorCode_t errCode);

#endif  /* _FAT_H_ */

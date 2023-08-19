/**
 * The logical file system
 * The first layer is responsible for interaction with the user application
 * It provides the application program interface (API) for file operations
 * OPEN, CLOSE, READ, etc., and passes the requested operation to the layer
 * below it for processing.
*/
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "utils.h"
#include "FAT.h"

/******************************************************************************
 * Definitions
******************************************************************************/
/**
 * @define Linked-list contains PATH of working directory
*/
typedef struct ll
{
    char name[256];
    struct ll* pNext;
} utils_path_struct_t;

/******************************************************************************
 * Prototypes
******************************************************************************/
static void UTILS_printPath(void);
static void UTILS_list(void);
static void UTILS_getNameFromCommand(const char* const command, char* const name, uint8_t pos);
static void UTILS_editPath(const char* const name);
static void UTILS_freePath(void);

/******************************************************************************
 * Variables
******************************************************************************/
static FAT_dir_struct_t* pFolder = NULL;
static utils_path_struct_t* pPath = NULL;

/******************************************************************************
 * Code
******************************************************************************/
/**
 * @brief   Run FAT view program
 *
 * @param   &diskName
*/
void UTILS_fatView(const char* const diskName)
{
    FAT_errorCode_t errCode = FAT_success;
    char command[256] = {};
    char name[256] = {};
    bool running = true;

    errCode = FAT_mountDisk(diskName, &pFolder);
    if (errCode != FAT_success)
    {
        FAT_printErrCode(errCode);
    }
    else
    {
        while (running)
        {
            /* Print directory path */
            putchar('~');
            if (pPath != NULL)
            {
                UTILS_printPath();
            }
            printf("$ ");
            /* Get command and parsing */
            if (fgets(command, 256, stdin) != NULL)
            {
                /* exit */
                if ((command[0] == 'e') && \
                    (command[1] == 'x') && \
                    (command[2] == 'i') && \
                    (command[3] == 't') && \
                    (command[4] == '\n'))
                {
                    UTILS_freePath();
                    errCode = FAT_unMountDisk();
                    if (errCode == FAT_success)
                    {
                        running = false;
                    }
                    else
                    {
                        FAT_printErrCode(errCode);
                    }
                }
                /* pwd */
                else if ((command[0] == 'p') && \
                    (command[1] == 'w') && \
                    (command[2] == 'd') && \
                    (command[3] == '\n'))
                {
                    UTILS_printPath();
                    putchar('\n');
                }
                /* ls */
                else if ((command[0] == 'l') && \
                    (command[1] == 's') && \
                    (command[2] == '\n'))
                {
                    UTILS_list();
                }
                /* cd */
                else if ((command[0] == 'c') && \
                        (command[1] == 'd') && \
                        (command[2] == ' ' ))
                {
                    UTILS_getNameFromCommand(command, name, 3);
                    errCode = FAT_changeDirectory(name, &pFolder);
                    if (errCode == FAT_success)
                    {
                        UTILS_editPath(name);
                    }
                    else
                    {
                        FAT_printErrCode(errCode);
                    }
                }
                /* cat */
                else if ((command[0] == 'c') && \
                        (command[1] == 'a') && \
                        (command[2] == 't' ) && \
                        (command[3] == ' ' ))
                {
                    UTILS_getNameFromCommand(command, name, 4);
                    errCode = FAT_readFile(name);
                    if (errCode != FAT_success)
                    {
                        FAT_printErrCode(errCode);
                    }
                }
                else
                {
                    printf("Incorrect command\n");
                }
            }
            else
            {
                /* Rarely happens */
                printf("Can not get commmad (system error)\n");
            }
        }
    }
}

/**
 * @brief   Print all elements of current directory
 *
 * @param   void
*/
static void UTILS_list(void)
{
    FAT_dir_struct_t* temp = pFolder;

    printf("%-24s%-12s%-16s%s\n", "Name", "Size(byte)", "Date modified", "Time modified");
    while((temp != NULL) && (temp->hidden == false))
    {
        printf("%-24s", temp->name);
        if(temp->directory)
        {
            printf("%-12s", "");
        }
        else
        {
            printf("%-12u", temp->fileSize);
        }
        printf("%hhu/%hhu/%hu", temp->modifyTime.day, temp->modifyTime.month, temp->modifyTime.year);
        printf("%9hhu/%hhu/%hu\n", temp->modifyTime.day, temp->modifyTime.month, temp->modifyTime.year);
        temp = temp->pNext;
    }
}

/**
 * @brief   Print directory path (pwd)
 *
 * @param   void
*/
static void UTILS_printPath(void)
{
    utils_path_struct_t* temp = pPath;

    while (temp != NULL)
    {
        printf("/%s", temp->name);
        temp = temp->pNext;
    }
}

/**
 * @brief   Get file/folder name from command
 *
 * @param   &command, &name, start position
*/
static void UTILS_getNameFromCommand(const char* const command, char* const name, uint8_t pos)
{
    uint8_t offset = pos;
    while (command[pos] != '\n')
    {
        name[pos - offset] = command[pos];
        pos++;
    }
    name[pos - offset] = '\0';
}

/**
 * @brief   Edit PATH
 *
 * @param   folder of file name
*/
static void UTILS_editPath(const char* const name)
{
    utils_path_struct_t* pCurrent = pPath;
    utils_path_struct_t* pPrevious = NULL;

    if (!strcmp(name, "."))
    {
        ;   /* null statement */
    }
    else if (!strcmp(name, ".."))
    {
        /* free() tail */
        while (pCurrent->pNext != NULL)
        {
            pPrevious = pCurrent;
            pCurrent = pCurrent->pNext;
        }
        if (pPrevious == NULL)
        {
            pPath = NULL;
        }
        else
        {
            pPrevious->pNext = NULL;
        }
        free(pCurrent);
    }
    else if (!strcmp(name, "~"))
    {
        UTILS_freePath();
    }
    else
    {
        /* add to tail */
        pPrevious = (utils_path_struct_t*)malloc(sizeof(utils_path_struct_t));
        if (pPrevious != NULL)
        {
            strcpy(pPrevious->name, name);
            if (pCurrent == NULL)
            {
                pPath = pPrevious;
                pPrevious->pNext = NULL;
            }
            else
            {
                while (pCurrent->pNext != NULL)
                {
                    pCurrent = pCurrent->pNext;
                }
                pCurrent->pNext= pPrevious;
                pPrevious->pNext = NULL;
            }
        }
    }
}

/**
 * @brief   Free Path linked-list
 *
 * @param   void
*/
static void UTILS_freePath(void)
{
    utils_path_struct_t* pCurrent = NULL;

    while (pPath != NULL)
    {
        pCurrent = pPath;
        pPath = pPath->pNext;
        free(pCurrent);
    }
}

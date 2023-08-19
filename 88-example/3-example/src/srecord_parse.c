#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "srecord_parse.h"
#include "SREC.h"

/******************************************************************************
 * Prototypes
******************************************************************************/
static void srecordParse_print(const SREC_t* const srec);

/******************************************************************************
 * Variables
******************************************************************************/
static FILE *fp_in = NULL;
static FILE *fp_out = NULL;

/******************************************************************************
 * Code
******************************************************************************/
/**
 * @brief   Program to parse file SREC
 *
 * @param   void
 * @return  void
 */
void srecordParse(void)
{
    char file_name[27] = {};
    /* Save current read line information */
    SREC_t srec = {};
    SREC_error_code_t error_code = SREC_SUCCESS;

    /* Get srec file name */
    printf("Enter SREC file name: ");
    if (fgets(file_name, 27, stdin) == NULL)
    {
        printf("Fail to read the input stream...");
        exit(1);
    }
    else
    {
        file_name[strcspn(file_name, "\n")] = '\0';
    }

    /* Open source file in read text mode */
    fp_in = fopen(file_name, "rt");
    if (fp_in == NULL)
    {
        printf("File %s is not existed...\n", file_name);
        exit(1);
    }

    /* Open output file in write text mode */
    fp_out = fopen("output.txt", "wt");
    if (fp_out == NULL)
    {
        printf("File %s can not be created...\n", "output.txt");
        exit(1);
    }

    do
    {
        error_code = SRECparse(&srec, fp_in);
        if (error_code == SREC_SUCCESS)
        {
            srecordParse_print(&srec);
        }
        else if (error_code == SREC_EOF)
        {
            printf("Parsing SREC file '%s' have done.\n", file_name);
        }
        else
        {
            SRECprintError(srec.current_line, error_code);
            remove("output.txt");
        }
    } while (error_code == SREC_SUCCESS);

    fclose(fp_in);
    fclose(fp_out);
}

/**
 * @brief   Program to print data field to file
 *
 * @param   SREC_t*
 * @return  void
 */
static void srecordParse_print(const SREC_t* const srec)
{
    uint8_t i = 0;  /* Variable i for counting purposes */

    if ((srec->type == (uint8_t)SREC_TYPE_S1)
        || (srec->type == (uint8_t)SREC_TYPE_S2)
        || (srec->type == (uint8_t)SREC_TYPE_S3))
    {
        for (i = srec->type + 1; i < srec->byte_count - 1; i++)
        {
            fprintf(fp_out, "%02hhX", srec->address_data[i]);
        }
        fputc('\n', fp_out);
    }
}

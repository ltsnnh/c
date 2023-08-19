#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "SREC.h"

/******************************************************************************
 * Prototypes
******************************************************************************/
static bool SREC_length(SREC_t* const srec);
static bool SREC_start(void);
static bool SREC_type(SREC_t* const srec);
static bool SREC_syntax(SREC_t* const srec);
static bool SREC_byte_count_fixed(SREC_t* const srec);
static bool SREC_length_fixed(SREC_t* const srec);
static bool SREC_byte_count(SREC_t* const srec);
static bool SREC_check_sum(SREC_t* const srec);
static bool SREC_type_s5_s6(SREC_t* const srec);
static bool SREC_line_count(SREC_t* const srec);
static bool SREC_convert2CharToDec(const uint8_t i, uint8_t* const dec);

/******************************************************************************
 * Variables
******************************************************************************/
static char buffer[SREC_BUFF_SIZE] = {};
static uint8_t s_buffer_len = 0u;     /* Number ascii char in buffer */
static uint32_t s_count_line = 0u;    /* Indicate number of current line */

/******************************************************************************
 * Code
******************************************************************************/
/**
 * @brief   Function check error S-Record line by line
 *
 * @param   SREC_t*, FILE*
 * @return  SREC_error_code_t
 */
SREC_error_code_t SRECparse(SREC_t* const srec, FILE* const fp)
{
    SREC_error_code_t retVal = SREC_SUCCESS;

    if (fgets(buffer, SREC_BUFF_SIZE, fp) == NULL)
    {
        retVal = SREC_EOF;
    }
    else if (SREC_length(srec))
    {
        retVal = SREC_LENGTH_ERROR;
    }
    else if (SREC_start())
    {
        retVal = SREC_START_ERROR;
    }
    else if (SREC_type(srec))
    {
        retVal = SREC_TYPE_ERROR;
    }
    else if (SREC_syntax(srec))
    {
        retVal = SREC_SYNTAX_ERROR;
    }
    else if (SREC_byte_count_fixed(srec))
    {
        retVal = SREC_BYTE_COUNT_FIXED_ERROR;
    }
    else if (SREC_length_fixed(srec))
    {
        retVal = SREC_LENGTH_FIXED_ERROR;
    }
    else if (SREC_byte_count(srec))
    {
        retVal = SREC_BYTE_COUNT_ERROR;
    }
    else if (SREC_type_s5_s6(srec))
    {
        retVal = SREC_TYPE_S5_S6_ERROR;
    }
    else if (SREC_line_count(srec))
    {
        retVal = SREC_LINE_COUNT_ERROR;
    }
    else if (SREC_check_sum(srec))
    {
        retVal = SREC_CHECK_SUM_ERROR;
    }

    return(retVal);
}

/**
 * @brief   Number ascii char in buffer is constanly even (never is odd)
 *          and >= SREC_MIN_LEN and <= SREC_MAX_LEN
 *
 * @param   SREC_t*
 * @return  true if error | false if not
 */
static bool SREC_length(SREC_t* const srec)
{
    bool retVal = false;

    s_buffer_len = strcspn(buffer, "\r\n");
    buffer[s_buffer_len] = '\0';       /* Replace '\r''\n' by '\0' */
    s_count_line++;                    /* Count line increases */
    srec->current_line = s_count_line;
    if ((s_buffer_len < (uint8_t)SREC_MIN_LEN) || s_buffer_len % 2 || (s_buffer_len > (uint8_t)SREC_MAX_LEN))
    {
        retVal = true;
    }

    return(retVal);
}

/**
 * @brief   Function check start character ('S')
 *
 * @param   void
 * @return  true if error | false if not
 */
static bool SREC_start(void)
{
    bool retVal = false;

    if(buffer[SREC_START_OFFSET] != SREC_START)
    {
        retVal = true;
    }

    return(retVal);
}

/**
 * @brief   Function check type of srec (S1-S9)
 *
 * @param   SREC_t*
 * @return  true if error | false if not
 */
static bool SREC_type(SREC_t* const srec)
{
    bool retVal = false;
    uint8_t type = buffer[SREC_TYPE_OFFSET] - SREC_offset_0_9;

    if (type < SREC_TYPE_S0 || type > SREC_TYPE_S9 || type == SREC_TYPE_S4)
    {
        retVal = true;
    }
    else
    {
        srec->type = type;
    }

    return(retVal);
}

/**
 * @brief   Function check syntax (inside hex character)
 *
 * @param   SREC_t*
 * @return  true if error | false if not
 */
static bool SREC_syntax(SREC_t* const srec)
{
    bool retVal = false;
    uint8_t dec = 0;
    uint8_t i = 0;

    for (i = SREC_COUNT_OFFSET; (i < s_buffer_len) && (retVal != true); i += SREC_ASCII_TO_BYTE)
    {
        if (i == SREC_COUNT_OFFSET)
        {
            retVal = SREC_convert2CharToDec(i, &dec);
            srec->byte_count = dec;
        }
        else if (i == (s_buffer_len - SREC_CHECKSUM_LEN))
        {
            retVal = SREC_convert2CharToDec(i, &dec);
            srec->checksum = dec;
        }
        else
        {
            retVal = SREC_convert2CharToDec(i, &dec);
            srec->address_data[(i - SREC_ADDRESS_OFFSET)/SREC_ASCII_TO_BYTE] = dec;
        }
    }

    return(retVal);
}

/**
 * @brief   Function check byte count of S-Record fixed length (S5-9)
 *
 * @param   SREC_t*
 * @return  true if error | false if not
 */
static bool SREC_byte_count_fixed(SREC_t* const srec)
{
    bool retVal = false;

    retVal = retVal || ((srec->type == SREC_TYPE_S5) && (srec->byte_count != SREC_BYTE_COUNT_S5));
    retVal = retVal || ((srec->type == SREC_TYPE_S6) && (srec->byte_count != SREC_BYTE_COUNT_S6));
    retVal = retVal || ((srec->type == SREC_TYPE_S7) && (srec->byte_count != SREC_BYTE_COUNT_S7));
    retVal = retVal || ((srec->type == SREC_TYPE_S8) && (srec->byte_count != SREC_BYTE_COUNT_S8));
    retVal = retVal || ((srec->type == SREC_TYPE_S9) && (srec->byte_count != SREC_BYTE_COUNT_S9));

    return(retVal);
}

/**
 * @brief   Function check length of S-Record fixed length (S5-9)
 *
 * @param   SREC_t*
 * @return  true if error | false if not
 */
static bool SREC_length_fixed(SREC_t* const srec)
{
    bool retVal = false;
    uint8_t type = srec->type;

    if ((type == SREC_TYPE_S5) || (type == SREC_TYPE_S6) || (type == SREC_TYPE_S7) || (type == SREC_TYPE_S8) || (type == SREC_TYPE_S9))
    {
        if ((s_buffer_len - SREC_ADDRESS_OFFSET)/SREC_ASCII_TO_BYTE != srec->byte_count)
        {
            retVal = true;
        }
    }

    return(retVal);
}

/**
 * @brief   Function check byte count
 *
 * @param   SREC_t*
 * @return  true if error | false if not
 */
static bool SREC_byte_count(SREC_t* const srec)
{
    bool retVal = false;

    if ((s_buffer_len - SREC_ADDRESS_OFFSET)/SREC_ASCII_TO_BYTE != srec->byte_count)
    {
        retVal = true;
    }

    return(retVal);
}

/**
 * @brief   Function check type S5 or S6
 *
 * @param   SREC_t*
 * @return  true if error | false if not
 */
static bool SREC_type_s5_s6(SREC_t* const srec)
{
    bool retVal = false;

    /* 2 = 1 line(S0) + 1 line(current line) */
    if (((s_count_line -2 > 0xFFFF)&&(srec->type == (uint8_t)SREC_TYPE_S5))
        || ((s_count_line -2 < 0xFFFF)&&(srec->type == (uint8_t)SREC_TYPE_S6)))
    {
        retVal = true;
    }

    return(retVal);
}

/**
 * @brief   Function check line count S1 S2 S3
 *
 * @param   SREC_t*
 * @return  true if error | false if not
 */
static bool SREC_line_count(SREC_t* const srec)
{
    bool retVal = false;

    /* 2 = 1 line(S0) + 1 line(current line) */
    if (srec->type == (uint8_t)SREC_TYPE_S5)
    {
        if ((s_count_line - 2) != ((srec->address_data[0] << 8) | srec->address_data[1]))
        /* S5: address_data[0],[1] belong line count field (16 bits) */
        {
            retVal = true;
        }
    }
    else if (srec->type == (uint8_t)SREC_TYPE_S6)
    {
        if (s_count_line - 2 != ((srec->address_data[0] << 16) | ((srec->address_data[1] << 8) | srec->address_data[2])))
        /* S6: address_data[0],[1],[2] belong line count field (24 bits) */
        {
            retVal = true;
        }
    }

    return(retVal);
}

/**
 * @brief   Function check sum
 *
 * @param   SREC_t*
 * @return  true if error | false if not
 */
static bool SREC_check_sum(SREC_t* const srec)
{
    bool retVal = false;
    uint16_t sum = (uint16_t)srec->byte_count;
    uint8_t i = 0;

    for (i = 0; i < srec->byte_count - (SREC_CHECKSUM_LEN/SREC_ASCII_TO_BYTE); i++)
    {
        sum += (uint16_t)srec->address_data[i];
    }

    if ((uint8_t)(~sum) != srec->checksum)
    {
        retVal = true;
    }

    return(retVal);
}

/**
 * @brief   Function convert 2 char to 1 dec (1 byte hex format )
 *
 * @param   i (position), &integer
 * @return  true if error | false if not
 */
static bool SREC_convert2CharToDec(const uint8_t i, uint8_t* const dec)
{
    bool retVal = false;
    uint8_t a = buffer[i];
    uint8_t b = buffer[i + 1];

    if ('0' <= a && a <= '9')
    {
        a = a - SREC_offset_0_9;
    }
    else if ('A' <= a && a <= 'F')
    {
        a = a - SREC_offset_A_F;
    }
    else
    {
        retVal = true;
    }

    if ('0' <= b && b <= '9')
    {
        b = b - SREC_offset_0_9;
    }
    else if ('A' <= b && b <= 'F')
    {
        b = b - SREC_offset_A_F;
    }
    else
    {
        retVal = true;
    }

    *dec = (a << 4) | b;    /* convert 2 dec (0-F) to 1 dec (0-FF) */

    return(retVal);
}

/**
 * @brief   Function to print error
 *
 * @param   line, error
 * @return  void
 */
void SRECprintError(const uint32_t line, const SREC_error_code_t error_code)
{
    printf("Line %u : ", line);
    switch(error_code)
    {
        case SREC_LENGTH_ERROR:
            printf("Length S-Record is not suitable\n");
            break;
        case SREC_START_ERROR:
            printf("S-Record does not start with S\n");
            break;
        case SREC_TYPE_ERROR:
            printf("S-Record has incorrect type\n");
            break;
        case SREC_SYNTAX_ERROR:
            printf("S-Record includes character without hex characters\n");
            break;
        case SREC_BYTE_COUNT_FIXED_ERROR:
            printf("S-Record byte count is incorrect (Its value is fixed)\n");
            break;
        case SREC_LENGTH_FIXED_ERROR:
            printf("S-Record length is incorrect (Its value is fixed)\n");
            break;
        case SREC_BYTE_COUNT_ERROR:
            printf("S-Record byte count is incorrect\n");
            break;
        case SREC_CHECK_SUM_ERROR:
            printf("S-Record check sum is incorrect\n");
            break;
        case SREC_TYPE_S5_S6_ERROR:
            printf("S-Record is wrong type between S5 and S6\n");
            break;
        case SREC_LINE_COUNT_ERROR:
            printf("S-Record line count is incorrect\n");
            break;
        default:
            printf("Error code is undefined\n");
            break;
    }
}

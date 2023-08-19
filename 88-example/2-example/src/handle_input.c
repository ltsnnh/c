#include <stdio.h>
#include <stdint.h>
#include "handle_input.h"

/******************************************************************************
 * Code
******************************************************************************/
/**
 * @brief   Get 1 character from stdin
 *
 * @param   &character
 * @return  HANDLEINPUT_SUCCESS or HANDLEINPUT_GET_CHAR_FAIL
 */
handleInput_error_code_t handleInput_get_char(int8_t* const character)
{
    /* Return value */
    handleInput_error_code_t retVal = HANDLEINPUT_GET_CHAR_FAIL;
    /* Temp variable get remaining characters*/
    int8_t clear_stdin = 0;

    *character = getchar();

    /* Accepted format: 'character''\n' */
    if (((*character >= 'A') && (*character <= 'Z')) || \
        ((*character >= 'a') && (*character <= 'z')) || \
        ((*character >= '0') && (*character <= '9')))
    {
        clear_stdin = getchar();
        if (clear_stdin == '\n')
        {
            retVal = HANDLEINPUT_SUCCESS;
        }
        else
        {
            do
            {
                clear_stdin = getchar();
            } while (clear_stdin != '\n');      /* Clear stdin */
        }
    }
    else if (*character == '\n')
    {
        ;   /* NULL statement */
    }
    else
    {
        do
        {
            clear_stdin = getchar();
        } while (clear_stdin != '\n');          /* Clear stdin */
    }

    return(retVal);
}

/**
 * @brief   Get 1 integer from stdin
 *
 * @param   &integer
 * @return  HANDLEINPUT_SUCCESS or HANDLEINPUT_GET_INT_FAIL
 */
handleInput_error_code_t handleInput_get_int(int32_t* const integer)
{
    /* Return value */
    handleInput_error_code_t retVal = HANDLEINPUT_GET_INT_FAIL;
    /* Result of fucntion scanf */
    uint8_t retVal_scanf = 0;
    /* Temp variable get remaining characters*/
    int8_t clear_stdin = 0;

    retVal_scanf = scanf("%d", integer);
    clear_stdin = getchar();

    /* Accepted format: 'integer''\n' */
    if ((retVal_scanf == 1) && (clear_stdin == '\n'))
    {
        retVal = HANDLEINPUT_SUCCESS;
    }
    else
    {
        do
        {
            clear_stdin = getchar();
        } while (clear_stdin != '\n');          /* Clear stdin */
    }

    return(retVal);
}

/**
 * @brief   Get 1 float from stdin
 *
 * @param   &float
 * @return  HANDLEINPUT_SUCCESS or HANDLEINPUT_GET_FLOAT_FAIL
 */
handleInput_error_code_t handleInput_get_float(float* const slack)
{
    /* Return value */
    handleInput_error_code_t retVal = HANDLEINPUT_GET_FLOAT_FAIL;
    /* Result of fucntion scanf */
    uint8_t retVal_scanf = 0;
    /* Temp variable get remaining characters*/
    int8_t clear_stdin = 0;

    retVal_scanf = scanf("%f", slack);
    clear_stdin = getchar();

    /* Accepted format: 'float''\n' */
    if ((retVal_scanf == 1) && (clear_stdin == '\n'))
    {
        retVal = HANDLEINPUT_SUCCESS;
    }
    else
    {
        do
        {
            clear_stdin = getchar();
        } while (clear_stdin != '\n');          /* Clear stdin */
    }

    return(retVal);
}

/**
 * @brief   Print input handling error
 *
 * @param   handleInput_error_code_t
 * @return  void
 */
void handleInput_print_error(const handleInput_error_code_t error_code)
{
    switch (error_code)
    {
        case HANDLEINPUT_GET_CHAR_FAIL:
            printf("Value entered is not a character...\n");
            break;
        case HANDLEINPUT_GET_INT_FAIL:
            printf("Value entered is not an integer...\n");
            break;
        case HANDLEINPUT_GET_FLOAT_FAIL:
            printf("Value entered is not an float...\n");
            break;
        default:
            printf("Unknown handle input error code...\n");
            break;
    }
}

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
 * @return  handle_input_success OR handle_input_get_char_fail
 */
handle_input_error_code_t handle_input_get_char(int8_t *character)
{
    /* Return value */
    handle_input_error_code_t retVal = handle_input_get_char_fail;
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
            retVal = handle_input_success;
        }
        else
        {
            do
            {
                clear_stdin = getchar();
            } while (clear_stdin != '\n');      /* Clear stdin */
        }
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
 * @brief   Get 1 integer (uint8_t) from stdin
 *
 * @param   &integer
 * @return  handle_input_success OR handle_input_get_int_fail
 */
handle_input_error_code_t handle_input_get_int(uint8_t *integer)
{
    /* Return value */
    handle_input_error_code_t retVal = handle_input_success;
    /* Result of fucntion scanf */
    uint8_t retVal_scanf = 0;
    /* Temp variable get remaining characters*/
    int8_t clear_stdin = 0;
    /* temp to avoid the scanf function overwriting in some cases */
    int32_t temp = 0;

    retVal_scanf = scanf("%d", &temp);
    clear_stdin = getchar();

    /* Accepted format: 'integer''\n' */
    if ((retVal_scanf == 1) && (clear_stdin == '\n'))
    {
        *integer = (uint8_t)temp;
        retVal = handle_input_success;
    }
    else
    {
        retVal = handle_input_get_int_fail;
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
 * @param   handle_input_error_code_t
 * @return  void
 */
void handle_input_print_error(handle_input_error_code_t handle_input_error_code)
{
    switch (handle_input_error_code)
    {
        case handle_input_get_char_fail:
            printf("Value entered is not a character...\n");
            break;
        case handle_input_get_int_fail:
            printf("Value entered is not an integer...\n");
            break;
        default:
            break;
    }

    return;
}

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "handle_array.h"
#include "handle_input.h"

/******************************************************************************
 * Definitions
******************************************************************************/
#define MAX_LENGTH 99u

/******************************************************************************
 * Prototypes
******************************************************************************/
static void handle_array_get_int(int32_t *integer);
static void handle_array_fill_array(void);

/******************************************************************************
 * Variables
******************************************************************************/
static int32_t *sp_handle_array = NULL;
static int32_t s_handle_array_length = 0;

/******************************************************************************
 * Code
******************************************************************************/
/**
 * @brief   Creat array
 *
 * @param   void
 * @return  handle_array_success OR handle_array_creat_array_fail
 */
handle_array_error_code_t handle_array_creat_array(void)
{
    /* Return value */
    handle_array_error_code_t result = handle_array_success;

    if (sp_handle_array != NULL)
    {
        printf("Clear old array...\n");
        free(sp_handle_array);
    }

    printf("Creating new array, enter length of array: ");
    handle_array_get_int(&s_handle_array_length);

    if ((s_handle_array_length < 1) || (s_handle_array_length > MAX_LENGTH))
    {
        printf("Over max length.\n");
        result = handle_array_creat_array_fail;
    }
    else
    {
        sp_handle_array = (int32_t*)calloc(s_handle_array_length, sizeof(int32_t));
        if (sp_handle_array == NULL)
        {
            result = handle_array_creat_array_fail;
        }
        else
        {
            handle_array_fill_array();
        }
    }

    return(result);
}

/**
 * @brief   Print array
 *
 * @param   void
 * @return  void
 */
void handle_array_print_array(void)
{
    /* Count variable */
    uint8_t i = 0;

    if (sp_handle_array == NULL)
    {
        printf("Empty array. ");
    }
    else
    {
        printf("Array:\t");
        for (i = 0; i < s_handle_array_length; i++)
        {
            printf("%d\t", *(sp_handle_array + i));
        }
        putchar('\n');
    }

    return;
}

/**
 * @brief   Add element to the last of array
 *
 * @param   void
 * @return  handle_array_success OR handle_array_add_element_fail
 */
handle_array_error_code_t handle_array_add_element(void)
{
    /* Return value */
    handle_array_error_code_t result = handle_array_success;

    if (sp_handle_array == NULL)
    {
        result = handle_array_add_element_fail;
    }
    else if (s_handle_array_length == MAX_LENGTH)
    {
        result = handle_array_add_element_fail;
    }
    else
    {
        sp_handle_array = realloc(sp_handle_array, (s_handle_array_length + 1) * sizeof(int));
        if (sp_handle_array == NULL)
        {
            result = handle_array_add_element_fail;
        }
        else
        {
            s_handle_array_length += 1;
            printf("array[%d] = ", s_handle_array_length - 1);
            handle_array_get_int(sp_handle_array + s_handle_array_length - 1);
        }
    }

    return(result);
}

/**
 * @brief   Erase element of array
 *
 * @param   void
 * @return  handle_array_success OR handle_array_erase_element_fail
 */
handle_array_error_code_t handle_array_erase_element(void)
{
    /* Return value */
    handle_array_error_code_t result = handle_array_success;
    /* Position of erasing element */
    int32_t position = 0;
    /* Count variable */
    uint8_t i = 0;

    printf("Position want to be erase: ");
    handle_array_get_int(&position);

    if (sp_handle_array == NULL)
    {
        result = handle_array_erase_element_fail;
    }
    else if (position > s_handle_array_length)
    {
        result = handle_array_erase_element_fail;
    }
    else if (position == s_handle_array_length)
    {
        sp_handle_array = realloc(sp_handle_array, (s_handle_array_length - 1) * sizeof(int));
        if (sp_handle_array == NULL)
        {
            result = handle_array_erase_element_fail;
        }
        else
        {
            s_handle_array_length -= 1;
            if(s_handle_array_length == 0)
            {
                handle_array_free_memory();
                printf("Array is cleared.\n");
            }
        }
    }
    else if (position < s_handle_array_length)
    {
        for (i = position - 1; i < s_handle_array_length - 1; i++)
        {
            *(sp_handle_array + i) = *(sp_handle_array + i + 1);
        }
        sp_handle_array = realloc(sp_handle_array, (s_handle_array_length - 1) * sizeof(int));
        if (sp_handle_array == NULL)
        {
            result = handle_array_erase_element_fail;
        }
        else
        {
            s_handle_array_length -= 1;
            if(s_handle_array_length == 0)
            {
                handle_array_free_memory();
                printf("Array is cleared.\n");
            }
        }
    }

    return(result);
}

/**
 * @brief   Sort array to ascending order
 *
 * @param   void
 * @return  handle_array_success OR handle_array_sort_ascending_fail
 */
handle_array_error_code_t handle_array_sort_ascending(void)
{
    /* Return value */
    handle_array_error_code_t result = handle_array_success;
    /* Count variable */
    uint8_t i = 0;
    uint8_t j = 0;
    /* Temp variable to switch 2 variables */
    uint32_t temp = 0;

    if (sp_handle_array == NULL)
    {
        result = handle_array_sort_ascending_fail;
    }
    else if (s_handle_array_length == 1)
    {
        ;   /* Array have 1 element, do nothing */
    }
    else if (s_handle_array_length > 1)
    {
        for (i = 0; i < s_handle_array_length - 1; i++)
        {
            for (j = i + 1; j < s_handle_array_length; j++)
            {
                if (*(sp_handle_array + i) > *(sp_handle_array + j))
                {
                    temp = *(sp_handle_array + i);
                    *(sp_handle_array + i) = *(sp_handle_array + j);
                    *(sp_handle_array + j) = temp;
                }
            }
        }
    }

    return(result);
}

/**
 * @brief   Sort array to descending order
 *
 * @param   void
 * @return  handle_array_success OR handle_array_sort_descending_fail
 */
handle_array_error_code_t handle_array_sort_descending(void)
{
    /* Return value */
    handle_array_error_code_t result = handle_array_success;
    /* Count variable */
    uint8_t i = 0;
    uint8_t j = 0;
    /* Temp variable to switch 2 variables */
    uint32_t temp = 0;

    if (sp_handle_array == NULL)
    {
        result = handle_array_sort_descending_fail;
    }
    else if (s_handle_array_length == 1)
    {
        ;   /* Array have 1 element, do nothing */
    }
    else if (s_handle_array_length > 1)
    {
        for (i = 0; i < s_handle_array_length - 1; i++)
        {
            for (j = i + 1; j < s_handle_array_length; j++)
            {
                if (*(sp_handle_array + i) < *(sp_handle_array + j))
                {
                    temp = *(sp_handle_array + i);
                    *(sp_handle_array + i) = *(sp_handle_array + j);
                    *(sp_handle_array + j) = temp;
                }
            }
        }
    }

    return(result);
}

/**
 * @brief   Find a element of array
 *
 * @param   void
 * @return  handle_array_success OR handle_array_find_number_fail
 */
handle_array_error_code_t handle_array_find_number(void)
{
    /* Return value */
    handle_array_error_code_t result = handle_array_success;
    /* Number be found */
    int32_t number = 0;
    /* Number element's value = number */
    uint8_t count = 0;
    /* Count value */
    uint8_t i = 0;
    /* Array to get position of element's value = number */
    /* This is max size fixing, can be dinamic allocated */
    uint8_t arrayPosition[MAX_LENGTH] = {};

    if (sp_handle_array == NULL)
    {
        result = handle_array_find_number_fail;
    }
    else
    {
        printf("Enter number to find: ");
        handle_array_get_int(&number);
        for (i = 0; i < s_handle_array_length; i++)
        {
            if (*(sp_handle_array + i) == number)
            {
                count += 1;
                *(arrayPosition + count - 1) = i + 1;
                /* 'i + 1' is position of element that value = number */
            }
        }
        if (count == 0)
        {
            printf("There is no number equal to the number entered (%d)\n", number);
        }
        else
        {
            printf("There is %hhu number equal to the number entered (%d) at ", count, number);
            for (i = 0; i < count; i++)
            {
                printf("%hhu ", *(arrayPosition + i));
            }
            putchar('\n');
        }
    }

    return(result);
}

/**
 * @brief   Print array handling error
 *
 * @param   handle_array_error_code_t
 * @return  void
 */
void handle_array_print_error(handle_array_error_code_t handle_array_error_code)
{
    switch (handle_array_error_code)
    {
        case handle_array_creat_array_fail:
            printf("Creating an array fail.\n");
            break;
        case handle_array_add_element_fail:
            printf("Adding an element fail.\n");
            break;
        case handle_array_erase_element_fail:
            printf("Erasing an element fail.\n");
            break;
        case handle_array_sort_ascending_fail:
            printf("Sorting elements ascending fail.\n");
            break;
        case handle_array_sort_descending_fail:
            printf("Sorting elements descending fail.\n");
            break;
        case handle_array_find_number_fail:
            printf("Finding number fail.\n");
            break;
        default:
            break;
    }

    return;
}

/**
 * @brief   Get until receive an integer
 *
 * @param   &integer
 * @return  void
 */
static void handle_array_get_int(int32_t *integer)
{
    handle_input_error_code_t handle_input_error_code = handle_input_success;

    handle_input_error_code = handle_input_get_int(integer);
    while (handle_input_error_code == handle_input_get_int_fail)
    {
        handle_input_print_error(handle_input_error_code);
        printf("Re-enter an integer: ");
        handle_input_error_code = handle_input_get_int(integer);
    }

    return;
}

/**
 * @brief   Fill all elements array
 *
 * @param   void
 * @return  void
 */
static void handle_array_fill_array(void)
{
    /* Count variable */
    uint8_t i = 0;

    printf("Fill elements to array:\n");
    for (i = 0; i < s_handle_array_length; i++)
    {
        printf("array[%d] = ", i);
        handle_array_get_int(sp_handle_array + i);
    }

    return;
}

/**
 * @brief   Free memory allocated with poiter
 *
 * @param   void
 * @return  void
 */
void handle_array_free_memory(void)
{
    free(sp_handle_array);

    return;
}

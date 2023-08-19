#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "number_management.h"
#include "handle_array.h"
#include "handle_input.h"

/******************************************************************************
 * Definitions
******************************************************************************/
enum
{
    creat_array = 'c',
    print_array = 'p',
    add_element = 'i',
    erase_element = 'd',
    sort_array_ascending = 's',
    sort_array_descending = 'x',
    find_number = 't',
    exit_program = 'e'
};

/******************************************************************************
 * Prototypes
******************************************************************************/
static void number_management_print_feature(void);
static bool number_management_switch_feature(int8_t command);
static void number_management_get_character(int8_t *command);

/******************************************************************************
 * Code
******************************************************************************/
/**
 * @brief   Manage numbers using array
 *
 * @param   void
 * @return  void
 */
void number_management(void)
{
    bool running = true;    /* Program is stopped when running is false */
    /* Command be got from user */
    int8_t command = 0;
    /* Count while looping to remind feature table */
    int8_t count_while = 0;
    printf("\t\t\t\tProgram to manage numbers using array.\n");
    /* Print feature table */
    number_management_print_feature();
    while (running == true)
    {
        /* Remind feature table after each 12 cycles while looping */
        count_while++;
        if ((count_while % 12) == 0)
        {
            count_while = 0;
            /* Print feature table */
            number_management_print_feature();
        }

        printf("Enter a command: ");
        number_management_get_character(&command);
        running = number_management_switch_feature(command);
    }

    /* Free memory before exiting */
    handle_array_free_memory();

    return;
}

/**
 * @brief   Print features of program
 *
 * @param   void
 * @return  void
 */
static void number_management_print_feature(void)
{
    printf("\t\t\tEnter 'c' to creat a array of integers.\n");
    printf("\t\t\tEnter 'p' to print array.\n");
    printf("\t\t\tEnter 'i' to add a element to the last.\n");
    printf("\t\t\tEnter 'd' to erase a element.\n");
    printf("\t\t\tEnter 's' to sort array in ascending.\n");
    printf("\t\t\tEnter 'x' to sort array in descending.\n");
    printf("\t\t\tEnter 't' to find a number in array.\n");
    printf("\t\t\tEnter 'e' exit program.\n");

    return;
}

/**
 * @brief   Switch-case process command
 *
 * @param   command
 * @return  true - keep going program
 *          false - exit program
 */
static bool number_management_switch_feature(int8_t command)
{
    bool result = true;
    handle_array_error_code_t handle_array_error_code = handle_array_success;

    switch (command)
    {
        case exit_program:
            printf("Exiting program...\n");
            result = false;
            break;
        case creat_array:
            handle_array_error_code = handle_array_creat_array();
            if (handle_array_error_code == handle_array_success)
            {
                printf("Array is created.\n");
            }
            else
            {
                handle_array_print_error(handle_array_error_code);
            }
            break;
        case print_array:
            handle_array_print_array();
            break;
        case add_element:
            handle_array_error_code = handle_array_add_element();
            if (handle_array_error_code == handle_array_success)
            {
                printf("Add an element success.\n");
            }
            else
            {
                handle_array_print_error(handle_array_error_code);
            }
            break;
        case erase_element:
            handle_array_error_code = handle_array_erase_element();
            if (handle_array_error_code == handle_array_success)
            {
                printf("Erase an element success.\n");
            }
            else
            {
                handle_array_print_error(handle_array_error_code);
            }
            break;
        case sort_array_ascending:
            handle_array_error_code = handle_array_sort_ascending();
            if (handle_array_error_code == handle_array_success)
            {
                printf("Sort elements ascending success.\n");
            }
            else
            {
                handle_array_print_error(handle_array_error_code);
            }
            break;
        case sort_array_descending:
            handle_array_error_code = handle_array_sort_descending();
            if (handle_array_error_code == handle_array_success)
            {
                printf("Sort elements descending success.\n");
            }
            else
            {
                handle_array_print_error(handle_array_error_code);
            }
            break;
        case find_number:
            handle_array_error_code = handle_array_find_number();
            if (handle_array_error_code == handle_array_success)
            {
                printf("Finding element success.\n");
            }
            else
            {
                handle_array_print_error(handle_array_error_code);
            }
            break;
        default:
            printf("Incorrect command.\n");
            break;
    }

    return(result);
}

static void number_management_get_character(int8_t *command)
{
    handle_input_error_code_t handle_input_error_code = handle_input_success;

    handle_input_error_code = handle_input_get_char(command);
    while (handle_input_error_code == handle_input_get_char_fail)
    {
        handle_input_print_error(handle_input_error_code);
        printf("Re-enter an character: ");
        handle_input_error_code = handle_input_get_char(command);
    }

    return;
}

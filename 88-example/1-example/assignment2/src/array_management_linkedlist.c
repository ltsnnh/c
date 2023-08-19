#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "array_management_linkedlist.h"
#include "handle_linkedlist.h"
#include "handle_input.h"

/******************************************************************************
 * Definitions
******************************************************************************/
#define LOOP_REMIND 12u

/* Define command */
enum
{
    ADD_ELEMENT = '1',
    ERASE_ELEMENT = '2',
    PRINT_ELEMENTS = '3',
    EXIT_PROGRAM = '4'
};

/* Define print command */
enum
{
    PRINT_RAW_ORDER = '1',
    PRINT_SORTED_ORDER = '2'
};

/******************************************************************************
 * Prototypes
******************************************************************************/
static void array_management_linkedlist_menu(void);
static bool array_management_linkedlist_switch_feature(int8_t command);
static void array_management_linkedlist_get_command(int8_t *command);

/******************************************************************************
 * Code
******************************************************************************/
/**
 * @brief   Manage array using linked-list
 *
 * @param   void
 * @return  void
 */
void array_management_linkedlist(void)
{
    /* Program is stopped when running is false */
    bool running = true;
    /* Command be got from user */
    int8_t command = 0;
    /* Count while looping to remind feature table */
    int8_t count_while = 0;
    /* Init array */
    handle_linkedlist_init_array();
    printf("\t\t\t\tProgram to manage array using linked list.\n");
    /* Print feature table */
    array_management_linkedlist_menu();
    while (running == true)
    {
        /* Remind feature table after each 12 cycles while looping */
        count_while++;
        if ((count_while % LOOP_REMIND) == 0)
        {
            count_while = 0;
            /* Print feature table */
            array_management_linkedlist_menu();
        }

        /* Enter a command and switch features */
        printf(" - Enter a command (1-2-3-4): ");
        array_management_linkedlist_get_command(&command);
        running = array_management_linkedlist_switch_feature(command);
    }

    return;
}

/**
 * @brief   Print features of program
 *
 * @param   void
 * @return  void
 */
static void array_management_linkedlist_menu(void)
{
    printf("\t\t\tEnter '1' to add a value to an element of array.\n");
    printf("\t\t\tEnter '2' to erase a value (if it's in array).\n");
    printf("\t\t\tEnter '3' to print all elements of array.\n");
    printf("\t\t\tEnter '4' to exit program.\n");

    return;
}

/**
 * @brief   Switch-case process command
 *
 * @param   command
 * @return  true - keep going program
 *          false - exit program
 */
static bool array_management_linkedlist_switch_feature(int8_t command)
{
    bool retVal = true;
    handle_linkedlist_error_code_t handle_linkedlist_error_code = handle_linkedlist_success;

    switch (command)
    {
        case EXIT_PROGRAM:
            printf("Exiting program...\n");
            retVal = false;
            break;
        case ADD_ELEMENT:
            handle_linkedlist_error_code = handle_linkedlist_add_element();
            if (handle_linkedlist_error_code == handle_linkedlist_success)
            {
                printf("Add element success.\n");
            }
            else
            {
                handle_linkedlist_print_error(handle_linkedlist_error_code);
            }
            break;
        case ERASE_ELEMENT:
            handle_linkedlist_error_code = handle_linkedlist_erase_element();
            if (handle_linkedlist_error_code == handle_linkedlist_success)
            {
                printf("Erase element success.\n");
            }
            else
            {
                handle_linkedlist_print_error(handle_linkedlist_error_code);
            }
            break;
        case PRINT_ELEMENTS:
            /* Enter a print command and switch features */
            printf("\t\t\tEnter '1' to print all elements.\n");
            printf("\t\t\tEnter '2' to print all elements sorted.\n");
            printf(" - Enter a print command (1-2): ");
            array_management_linkedlist_get_command(&command);
            if ((command != PRINT_RAW_ORDER) && (command != PRINT_SORTED_ORDER))
            {
                printf("Incorrect print command.\n");
            }
            else if (command == PRINT_RAW_ORDER)
            {
                handle_linkedlist_error_code = handle_linkedlist_print_array();
                handle_linkedlist_print_error(handle_linkedlist_error_code);
            }
            else if (command == PRINT_SORTED_ORDER)
            {
                handle_linkedlist_error_code = handle_linkedlist_print_linkedlist();
                handle_linkedlist_print_error(handle_linkedlist_error_code);
            }
            break;
        default:
            printf("Incorrect command.\n");
            break;
    }

    return(retVal);
}

/**
 * @brief   Get until receive an character
 *
 * @param   &character
 * @return  void
 */
static void array_management_linkedlist_get_command(int8_t *command)
{
    handle_input_error_code_t handle_input_error_code = handle_input_success;

    handle_input_error_code = handle_input_get_char(command);
    while (handle_input_error_code == handle_input_get_char_fail)
    {
        handle_input_print_error(handle_input_error_code);
        printf(" - Re-enter a command: ");
        handle_input_error_code = handle_input_get_char(command);
    }

    return;
}

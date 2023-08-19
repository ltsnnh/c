#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "class_management.h"
#include "handle_linkedlist.h"
#include "handle_input.h"

/******************************************************************************
 * Definitions
******************************************************************************/
/* Remind menu after a number loop 'while' */
#define LOOP_REMIND 12u

/* Define character commits which math with functions */
enum
{
    PRINT_LIST = 'p',
    INSERT_STUDENT = 'i',
    REMOVE_STUDENT = 'r',
    FIND_STUDENT = 'f',
    SORT_SCORE = 's',
    SORT_NAME = 'n',
    EXIT_PROGRAM = 'e'
};

/******************************************************************************
 * Prototypes
******************************************************************************/
static void classManagement_menu(void);
static bool classManagement_switch_feature(const int8_t command);
static void classManagement_get_command(int8_t* const command);

/******************************************************************************
 * Variables
******************************************************************************/
/* Initial information of class */
const student_t starting_students[] =
{
    {1, "Pham Huy Hoang", "HoangPH19", 8.2},
    {2, "Hoang Trong Hieu", "HieuHT53", 8.7},
    {3, "Nguyen The Dao", "DaoNT40", 8.3},
    {4, "Dam Duc Hoa", "HoaDD5", 8.1},
    {5, "Nguyen Ba Phi Hung", "HungNBP", 8.6},
    {6, "Tran Quang Canh", "CanhTQ1", 8.4},
    {7, "Vu Huu Luc", "LucVH2", 8.9},
    {8, "Phan Thi Hoai", "HoaiPT22", 8.5},
    {9, "Tran Van Binh", "BinhTV19", 8.9},
    {10, "Le Tuan Anh", "AnhLT88", 8.8},
};
/* Initial number member of class */
const uint32_t num_starting_students = sizeof(starting_students)/sizeof(student_t);

/******************************************************************************
 * Code
******************************************************************************/
/**
 * @brief   Manage students of class using linked-list
 *
 * @param   void
 * @return  void
 */
void classManagement(void)
{
    /* Program is stopped when running is false */
    bool running = true;
    /* Command be got from user */
    int8_t command = 0;
    /* Count while looping to remind feature table */
    int8_t count_while = 0;
    /* Check init linked-list error */
    handleLinkedlist_error_code_t error_code = handleLinkedlist_init(starting_students, num_starting_students);

    if (error_code == HANDLELINKEDLIST_SUCCESS)
    {
        printf("\t\t\t\tProgram to manage fresher class.\n");
        /* Print feature table */
        classManagement_menu();
        while (running == true)
        {
            /* Remind feature table after each 12 cycles while looping */
            count_while++;
            if ((count_while % LOOP_REMIND) == 0)
            {
                count_while = 0;
                /* Print feature table */
                classManagement_menu();
            }
            /* Enter a command and switch features */
            printf(" - Enter a command (p-i-r-f-s-n-e): ");
            classManagement_get_command(&command);
            running = classManagement_switch_feature(command);
        }
    }
    else
    {
        handleLinkedlist_print_error(error_code);
    }
}

/**
 * @brief   Print features of program
 *
 * @param   void
 * @return  void
 */
static void classManagement_menu(void)
{
    printf("\t\t\tEnter 'p' print all students of class.\n");
    printf("\t\t\tEnter 'i' to add a student.\n");
    printf("\t\t\tEnter 'r' to erase a student.\n");
    printf("\t\t\tEnter 'f' to find a student.\n");
    printf("\t\t\tEnter 's' to sort all students by score.\n");
    printf("\t\t\tEnter 'n' to sort all students by name.\n");
    printf("\t\t\tEnter 'e' to exit program.\n");
}

/**
 * @brief   Switch-case process command
 *
 * @param   command
 * @return  true: keep going program
 *          false: exit program
 */
static bool classManagement_switch_feature(const int8_t command)
{
    bool retVal = true;
    handleLinkedlist_error_code_t error_code = HANDLELINKEDLIST_SUCCESS;

    switch (command)
    {
        case EXIT_PROGRAM:
            printf("Exiting program...\n");
            retVal = false;
            break;
        case PRINT_LIST:
            error_code = handleLinkedlist_print();
            if (error_code != HANDLELINKEDLIST_SUCCESS)
            {
                handleLinkedlist_print_error(error_code);
            }
            break;
        case INSERT_STUDENT:
            error_code = handleLinkedlist_add_student();
            if (error_code == HANDLELINKEDLIST_SUCCESS)
            {
                printf("Insert a student success.\n");
            }
            else
            {
                handleLinkedlist_print_error(error_code);
            }
            break;
        case REMOVE_STUDENT:
            error_code = handleLinkedlist_erase_student();
            if (error_code == HANDLELINKEDLIST_SUCCESS)
            {
                printf("Erase a student success.\n");
            }
            else
            {
                handleLinkedlist_print_error(error_code);
            }
            break;
        case FIND_STUDENT:
            error_code = handleLinkedlist_find_student();
            if (error_code != HANDLELINKEDLIST_SUCCESS)
            {
                handleLinkedlist_print_error(error_code);
            }
            break;
        case SORT_SCORE:
            error_code = handleLinkedlist_sort_score();
            if (error_code == HANDLELINKEDLIST_SUCCESS)
            {
                printf("Sort students by score success.\n");
            }
            else
            {
                handleLinkedlist_print_error(error_code);
            }
            break;
        case SORT_NAME:
            error_code = handleLinkedlist_sort_name();
            if (error_code == HANDLELINKEDLIST_SUCCESS)
            {
                printf("Sort students by name success.\n");
            }
            else
            {
                handleLinkedlist_print_error(error_code);
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
static void classManagement_get_command(int8_t* const command)
{
    handleInput_error_code_t error_code = HANDLEINPUT_SUCCESS;

    error_code = handleInput_get_char(command);
    while (error_code == HANDLEINPUT_GET_CHAR_FAIL)
    {
        handleInput_print_error(error_code);
        printf(" - Re-enter a command: ");
        error_code = handleInput_get_char(command);
    }
}

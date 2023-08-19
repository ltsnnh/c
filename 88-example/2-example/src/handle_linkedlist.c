#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "handle_linkedlist.h"
#include "handle_input.h"

/******************************************************************************
 * Definitions
******************************************************************************/
/* Structure node_t define type of node - the element of linked list */
typedef struct linkedlist
{
    student_t student;
    struct linkedlist *next;
} node_t;

/******************************************************************************
 * Prototypes
******************************************************************************/
static void handleLinkedlist_deinit(void);
static handleLinkedlist_error_code_t handleLinkedlist_add_node(const student_t student, const uint32_t position);
static handleLinkedlist_error_code_t handleLinkedlist_check_code_account(const uint32_t code, const char* account);
static bool handleLinkedlist_compare_name(const node_t* p_previous, const node_t* p_current);

static void handleLinkedlist_get_int(int32_t* const integer);
static void handleLinkedlist_get_float(float* const slack);

/******************************************************************************
 * Variables
******************************************************************************/
static node_t *sp_head = NULL;      /* Head of linked-list */
static uint32_t s_num_student = 0;  /* Number node of linked-list */

/******************************************************************************
 * Code
******************************************************************************/
/**
 * @brief   Init linked-list with starting data
 *
 * @param   p_student[], a number students
 * @return  handleLinkedlist_error_code_t
 */
handleLinkedlist_error_code_t handleLinkedlist_init(const student_t* p_student, const uint32_t num_student)
{
    handleLinkedlist_error_code_t retVal = HANDLELINKEDLIST_SUCCESS;
    uint32_t i = 0;
    uint32_t j = 0;

    /* Check duplicate student code and account from starting data */
    for (i = 0; i < (num_student - 1); i++)
    {
        for (j = i + 1; j < num_student; j++)
        {
            if (p_student[i].code == p_student[j].code)
            {
                retVal = HANDLELINKEDLIST_DUPLICATE_CODE;
            }
            else if (!strcmp(p_student[i].account, p_student[j].account))
            {
                retVal = HANDLELINKEDLIST_DUPLICATE_ACCOUNT;
            }
        }
    }

    /* If data is not duplicate */
    /* Add student information one by one and starting from position 1 */
    i = 1;
    while ((i <= num_student) && (retVal == HANDLELINKEDLIST_SUCCESS))
    {
        retVal = handleLinkedlist_add_node(p_student[i - 1], i);
        i++;
    }

    /* Check allocate status all starting data node */
    if ((i == (num_student + 1)) && (retVal == HANDLELINKEDLIST_SUCCESS))
    {
        s_num_student = num_student;
    }
    else
    {
        retVal = HANDLELINKEDLIST_ALLOCATE_ERROR;
        /* Free all nodes allocated */
        handleLinkedlist_deinit();
    }

    return(retVal);
}

/**
 * @brief   Function to print linked-list
 *
 * @param   void
 * @return  handleLinkedlist_error_code_t
 */
handleLinkedlist_error_code_t handleLinkedlist_print(void)
{
    handleLinkedlist_error_code_t retVal = HANDLELINKEDLIST_SUCCESS;
    node_t *p_current = sp_head;

    if (p_current == NULL)
    {
        retVal = HANDLELINKEDLIST_EMPTY;
    }
    else
    {
        printf("%-8s%-27s%-12s\t%s\n", "CODE", "NAME", "ACCOUNT", "SCORE");
        while (p_current != NULL)
        {
            printf("%-8hhd%-27s%-12s\t%.2f\n", p_current->student.code, p_current->student.name, p_current->student.account, p_current->student.score);
            p_current = p_current->next;
        }
    }

    return(retVal);
}

/**
 * @brief   Function to add student to a position
 *
 * @param   void
 * @return  handleLinkedlist_error_code_t
 */
handleLinkedlist_error_code_t handleLinkedlist_add_student(void)
{
    handleLinkedlist_error_code_t retVal = HANDLELINKEDLIST_SUCCESS;
    student_t student = {};
    int32_t position = 0;
    int32_t i = 0;

    printf("Enter position of new student: ");
    handleLinkedlist_get_int(&position);
    printf("Enter code of new student: ");
    handleLinkedlist_get_int(&student.code);
    printf("Enter name of new student: ");
    fgets(student.name, MAX_LENGTH_NAME, stdin);
    printf("Enter account of new student: ");
    fgets(student.account, MAX_LENGTH_ACCOUNT, stdin);
    printf("Enter score of new student: ");
    handleLinkedlist_get_float(&student.score);

    /* fgets() get '\n' from stdin, must ignore it */
    for (i = 0; i < MAX_LENGTH_NAME; i++)
    {
        if (student.name[i] == '\n')
        {
            student.name[i] = '\0';
        }
    }
    for (i = 0; i < MAX_LENGTH_ACCOUNT; i++)
    {
        if (student.account[i] == '\n')
        {
            student.account[i] = '\0';
        }
    }

    retVal = handleLinkedlist_check_code_account(student.code, student.account);

    if (retVal != HANDLELINKEDLIST_SUCCESS)
    {
        ;   /* NULL statement */
    }
    else if ((position <= 0) || (position > (s_num_student + 1)))
    {
        retVal = HANDLELINKEDLIST_OUT_OF_POSITION;
    }
    else
    {
        retVal = handleLinkedlist_add_node(student, position);
        if (retVal == HANDLELINKEDLIST_SUCCESS)
        {
            s_num_student++;
        }
    }

    return(retVal);
}

/**
 * @brief   Function to erase student
 *
 * @param   void
 * @return  handleLinkedlist_error_code_t
 */
handleLinkedlist_error_code_t handleLinkedlist_erase_student(void)
{
    handleLinkedlist_error_code_t retVal = HANDLELINKEDLIST_SUCCESS;
    int32_t position = 0;
    node_t *p_current = sp_head;
    node_t *p_previous = NULL;
    int32_t i = 0;

    printf("Enter position to erase student: ");
    handleLinkedlist_get_int(&position);

    if (sp_head == NULL)
    {
        retVal = HANDLELINKEDLIST_EMPTY;
    }
    else if ((position < 1) || (position > s_num_student))
    {
        retVal = HANDLELINKEDLIST_OUT_OF_POSITION;
    }
    else if (position == 1)
    {
        sp_head = p_current->next;
        free(p_current);
        s_num_student--;
    }
    else if (position > 1)
    {
        for (i = 1; i < position; i++)
        {
            p_previous = p_current;
            p_current = p_current->next;
        }
        p_previous->next = p_current->next;
        free(p_current);
        s_num_student--;
    }

    return(retVal);
}

/**
 * @brief   Function to find student with name
 *
 * @param   void
 * @return  handleLinkedlist_error_code_t
 */
handleLinkedlist_error_code_t handleLinkedlist_find_student(void)
{
    handleLinkedlist_error_code_t retVal = HANDLELINKEDLIST_NOT_FOUND;
    char name[MAX_LENGTH_NAME] = {};
    node_t *p_current = sp_head;
    int32_t i = 0;

    printf("Enter name to find student: ");
    fgets(name, MAX_LENGTH_NAME, stdin);
    /* fgets() get '\n' from stdin, must ignore it */
    for (i = 0; i < MAX_LENGTH_NAME; i++)
    {
        if (name[i] == '\n')
        {
            name[i] = '\0';
        }
    }

    if (p_current == NULL)
    {
        retVal = HANDLELINKEDLIST_EMPTY;
    }
    else
    {
        while (p_current != NULL)
        {
            if (!strcmp(p_current->student.name, name))
            {
                printf("%-8hhd%-27s%-12s\t%.2f\n", p_current->student.code, p_current->student.name, p_current->student.account, p_current->student.score);
                retVal = HANDLELINKEDLIST_SUCCESS;
            }
            p_current = p_current->next;
        }
    }

    return(retVal);
}

/**
 * @brief   Function to sort student by score
 *
 * @param   void
 * @return  handleLinkedlist_error_code_t
 */
handleLinkedlist_error_code_t handleLinkedlist_sort_score(void)
{
    handleLinkedlist_error_code_t retVal = HANDLELINKEDLIST_SUCCESS;
    node_t *p_current = sp_head;
    node_t *p_previous = NULL;
    student_t student = {};

    if (p_current == NULL)
    {
        retVal = HANDLELINKEDLIST_EMPTY;
    }
    else if (p_current->next == NULL)
    {
        ;   /* NULL statement */
    }
    else
    {
        p_previous = p_current;
        while (p_previous != NULL)
        {
            p_current = p_previous->next;
            while (p_current != NULL)       /* p_current = NULL is last node */
            {
                if (p_previous->student.score < p_current->student.score)
                {
                    student = p_previous->student;
                    p_previous->student = p_current->student;
                    p_current->student = student;
                }
                p_current = p_current->next;
            }
            p_previous = p_previous->next;
        }
    }

    return(retVal);
}

/**
 * @brief   Function to sort student by first name
 *
 * @param   void
 * @return  handleLinkedlist_error_code_t
 */
handleLinkedlist_error_code_t handleLinkedlist_sort_name(void)
{
    handleLinkedlist_error_code_t retVal = HANDLELINKEDLIST_SUCCESS;
    node_t *p_current = sp_head;
    node_t *p_previous = NULL;
    student_t student = {};

    if (p_current == NULL)
    {
        retVal = HANDLELINKEDLIST_EMPTY;
    }
    else if (p_current->next == NULL)
    {
        ;   /* NULL statement */
    }
    else
    {
        p_previous = p_current;
        while (p_previous != NULL)
        {
            p_current = p_previous->next;
            while (p_current != NULL)   /* p_current = NULL is last node */
            {
                if (handleLinkedlist_compare_name(p_previous, p_current))
                {
                    student = p_previous->student;
                    p_previous->student = p_current->student;
                    p_current->student = student;
                }
                p_current = p_current->next;
            }
            p_previous = p_previous->next;
        }
    }

    return(retVal);
}

/**
 * @brief   Print linked-list handling error
 *
 * @param   handleLinkedlist_error_code_t
 * @return  void
 */
void handleLinkedlist_print_error(const handleLinkedlist_error_code_t error_code)
{
    switch (error_code)
    {
        case HANDLELINKEDLIST_DUPLICATE_CODE:
            printf("Duplicate code in students info.\n");
            break;
        case HANDLELINKEDLIST_DUPLICATE_ACCOUNT:
            printf("Duplicate account in students info.\n");
            break;
        case HANDLELINKEDLIST_ALLOCATE_ERROR:
            printf("Allocate new node to store student info fail.\n");
            break;
        case HANDLELINKEDLIST_EMPTY:
            printf("Empty class!\n");
            break;
        case HANDLELINKEDLIST_OUT_OF_POSITION:
            printf("Position is not existed.\n");
            break;
        case HANDLELINKEDLIST_NOT_FOUND:
            printf("Name entered is not existed.\n");
            break;
        default:
            printf("Unknown handle input error code.\n");
            break;
    }
}

/**
 * @brief   Deinit linked-list
 *
 * @param   void
 * @return  void
 */
static void handleLinkedlist_deinit(void)
{
    node_t *current_node = sp_head;

    while (sp_head != NULL)
    {
        sp_head = current_node->next;
        free(current_node);
        current_node = sp_head;
    }
    s_num_student = 0;
}

/**
 * @brief   Allocate and insert new node to linked-list
 *
 * @param   student data, position insert
 * @return  handleLinkedlist_error_code_t
 */
static handleLinkedlist_error_code_t handleLinkedlist_add_node(const student_t student, const uint32_t position)
{
    handleLinkedlist_error_code_t retVal = HANDLELINKEDLIST_SUCCESS;
    node_t *current_node = sp_head;
    node_t* const new_node = (node_t*)malloc(sizeof(node_t));
    uint32_t i = 0;

    if (new_node == NULL)
    {
        retVal = HANDLELINKEDLIST_ALLOCATE_ERROR;
    }
    else if (position == 1)
    {
        /* Link new node */
        new_node->next = sp_head;
        sp_head = new_node;
        /* Add data new node */
        new_node->student = student;
    }
    else
    {
        for (i = 0; i < (position - 2); i++)
        {
            current_node = current_node->next;
        }
        /* Link new node */
        new_node->next = current_node->next;
        current_node->next = new_node;
        /* Add data new node */
        new_node->student = student;
    }

    return(retVal);
}

/**
 * @brief   Get until receive an integer
 *
 * @param   &integer
 * @return  void
 */
static void handleLinkedlist_get_int(int32_t* const integer)
{
    handleInput_error_code_t error_code = HANDLEINPUT_SUCCESS;

    error_code = handleInput_get_int(integer);
    while (error_code == HANDLEINPUT_GET_INT_FAIL)
    {
        handleInput_print_error(error_code);
        printf("Re-enter an integer: ");
        error_code = handleInput_get_int(integer);
    }
}

/**
 * @brief   Get until receive an float
 *
 * @param   &float
 * @return  void
 */
static void handleLinkedlist_get_float(float* const slack)
{
    handleInput_error_code_t error_code = HANDLEINPUT_SUCCESS;

    error_code = handleInput_get_float(slack);
    while (error_code == HANDLEINPUT_GET_FLOAT_FAIL)
    {
        handleInput_print_error(error_code);
        printf("Re-enter an float: ");
        error_code = handleInput_get_float(slack);
    }
}

/**
 * @brief   Check duplacate code and account
 *
 * @param   code
 * @return  handleLinkedlist_error_code_t
 */
static handleLinkedlist_error_code_t handleLinkedlist_check_code_account(const uint32_t code, const char* account)
{
    handleLinkedlist_error_code_t retVal = HANDLELINKEDLIST_SUCCESS;
    node_t *p_current = sp_head;

    while ((p_current != NULL) && (retVal == HANDLELINKEDLIST_SUCCESS))
    {
        if (p_current->student.code == code)
        {
            retVal = HANDLELINKEDLIST_DUPLICATE_CODE;
        }
        else if (!strcmp(p_current->student.account, account))
        {
            retVal = HANDLELINKEDLIST_DUPLICATE_ACCOUNT;
        }
        else
        {
            p_current = p_current->next;
        }
    }

    return(retVal);
}

/**
 * @brief   Function to compare first character of student first name
 *
 * @param   p_previous, p_current
 * @return  true: p_previous > p_current
 *          false: p_previous < p_current
 */
static bool handleLinkedlist_compare_name(const node_t* p_previous, const node_t* p_current)
{
    bool retVal = false;
    char previous = 0;
    char current = 0;
    uint8_t i = 0;

    for (i = 0; i < MAX_LENGTH_NAME; i++)
    {
        if ((p_previous->student.name[i] == ' ') && (p_previous->student.name[i + 1] != ' '))
        {
            previous = p_previous->student.name[i + 1];
        }
        if ((p_current->student.name[i] == ' ') && (p_current->student.name[i + 1] != ' '))
        {
            current = p_current->student.name[i + 1];
        }
    }

    if(previous > current)
    {
        retVal = true;
    }

    return(retVal);
}

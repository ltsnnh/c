#include <stdio.h>
#include <stdint.h>
#include "handle_linkedlist.h"
#include "handle_input.h"

/******************************************************************************
 * Definitions
******************************************************************************/
#define MAX_NUM_ELEMENTS    20u
#define MIN_NUM_ELEMENTS    0u
#define MAX_POSITION        (MAX_NUM_ELEMENTS - 1u)
#define MIN_POSITION        0u
#define MAX_VALUE           100u
#define MIN_VALUE           0u
#define RESET_VALUE         0xFFu

/* Typedef node */
typedef struct handle_linkedlist
{
    uint8_t data;
    struct handle_linkedlist *pNext;
} handle_linkedlist_node_t;

/******************************************************************************
 * Prototypes
******************************************************************************/
static void handle_linkedlist_get_int(uint8_t *integer);
static uint8_t handle_linkedlist_check_value_existed(uint8_t value);
static void handle_linkedlist_add_element_ascending(uint8_t position, uint8_t value);

/******************************************************************************
 * Variables
******************************************************************************/
static uint8_t s_assignment3[MAX_NUM_ELEMENTS] = {};            /* Array */
static handle_linkedlist_node_t s_node[MAX_NUM_ELEMENTS] = {};  /* Nodes */

static handle_linkedlist_node_t *sp_head = NULL;    /* Head of linked-list */
static uint8_t s_number_of_elements = 0;            /* Number elements */

/******************************************************************************
 * Code
******************************************************************************/
/**
 * @brief   Add an element to array and manage it with linked-list
 *
 * @param   void
 * @return  handle_linkedlist_error_code_t
 */
handle_linkedlist_error_code_t handle_linkedlist_add_element(void)
{
    handle_linkedlist_error_code_t retVal = handle_linkedlist_success;
    uint8_t position = MAX_NUM_ELEMENTS;
    uint8_t value = RESET_VALUE;

    printf("Enter element position to add (0 - 19):");
    handle_linkedlist_get_int(&position);
    printf("Enter element value to add (0 - 100):");
    handle_linkedlist_get_int(&value);

    if (s_number_of_elements >= MAX_NUM_ELEMENTS)
    {
        retVal = handle_linkedlist_max_num_elements;
    }
    else if ((position < MIN_POSITION) || (position > MAX_POSITION))
    {
        retVal = handle_linkedlist_position_out_of_size_array;
    }
    else if (s_assignment3[position] != RESET_VALUE)
    {
        retVal = handle_linkedlist_position_has_been_entered;
    }
    else if ((value < MIN_VALUE) || (value > MAX_VALUE))
    {
        retVal = handle_linkedlist_value_out_of_value_range;
    }
    else if (handle_linkedlist_check_value_existed(value) != MAX_NUM_ELEMENTS)
    {
        retVal = handle_linkedlist_value_existed;
    }
    else
    {
        /* Array handling */
        s_assignment3[position] = value;
        /* Add data to node */
        s_node[position].data = value;
        /* Insert node to linked-list */
        handle_linkedlist_add_element_ascending(position, value);
        /* Increase number elements */
        s_number_of_elements++;
    }

    return(retVal);
}

/**
 * @brief   Erase an element to array and manage it with linked-list
 *
 * @param   void
 * @return  handle_linkedlist_error_code_t
 */
handle_linkedlist_error_code_t handle_linkedlist_erase_element(void)
{
    handle_linkedlist_error_code_t retVal = handle_linkedlist_success;
    uint8_t value = RESET_VALUE;
    uint8_t position = MAX_NUM_ELEMENTS;
    handle_linkedlist_node_t *pCurrent_node = sp_head;
    handle_linkedlist_node_t *pPrevious_node = NULL;

    printf("Enter element value to erase (0 - 100):");
    handle_linkedlist_get_int(&value);

    position = handle_linkedlist_check_value_existed(value);

    if ((s_number_of_elements <= MIN_NUM_ELEMENTS) && (sp_head == NULL))
    {
        retVal = handle_linkedlist_no_element;
    }
    else if ((value < MIN_VALUE) || (value > MAX_VALUE))
    {
        retVal = handle_linkedlist_value_out_of_value_range;
    }
    else if (position == MAX_NUM_ELEMENTS)
    {
        retVal = handle_linkedlist_value_not_existed;
    }
    else
    {
        /* Array handling */
        s_assignment3[position] = RESET_VALUE;
        /* Linked-list handling */
        /* If the first node is node to erase */
        if (pCurrent_node->data == value)
        {
            /* Change head */
            sp_head = pCurrent_node->pNext;
            /* Reduce number elements */
            s_number_of_elements--;
        }
        else
        {
            /* Search node to be deleted, keep track of the previous node */
            do
            {
                pPrevious_node = pCurrent_node;
                pCurrent_node = pCurrent_node->pNext;
            }
            while ((pCurrent_node != NULL) && (pCurrent_node->data != value));
            /* Unlink the node from linked list */
            pPrevious_node->pNext = pCurrent_node->pNext;
            /* Reduce number elements */
            s_number_of_elements--;
        }
    }

    return(retVal);
}

/**
 * @brief   Print elements of array
 *
 * @param   void
 * @return  handle_linkedlist_error_code_t
 */
handle_linkedlist_error_code_t handle_linkedlist_print_array(void)
{
    handle_linkedlist_error_code_t retVal = handle_linkedlist_success;
    uint8_t i = 0;

    if ((s_number_of_elements <= MIN_NUM_ELEMENTS) && (sp_head == NULL))
    {
        retVal = handle_linkedlist_no_element;
    }
    else
    {
        for (i = MIN_POSITION; i <= MAX_POSITION; i++)
        {
            if (s_assignment3[i] != RESET_VALUE)
            {
                printf("%hhu\t", s_assignment3[i]);
            }
        }
        putchar('\n');
    }

    return(retVal);
}

/**
 * @brief   Print elements sorted of linked-list
 *
 * @param   void
 * @return  handle_linkedlist_error_code_t
 */
handle_linkedlist_error_code_t handle_linkedlist_print_linkedlist(void)
{
    handle_linkedlist_error_code_t retVal = handle_linkedlist_success;
    handle_linkedlist_node_t *pCurrent_node = sp_head;

    if ((s_number_of_elements <= MIN_NUM_ELEMENTS) && (sp_head == NULL))
    {
        retVal = handle_linkedlist_no_element;
    }
    else
    {
        pCurrent_node = sp_head;
        while (pCurrent_node != NULL)
        {
            printf("%hhu\t", pCurrent_node->data);
            pCurrent_node = pCurrent_node->pNext;
        }
        putchar('\n');
    }

    return(retVal);
}

/**
 * @brief   Print linked-list handling error
 *
 * @param   handle_array_error_code_t
 * @return  void
 */
void handle_linkedlist_print_error(handle_linkedlist_error_code_t handle_linkedlist_error_code)
 {
    switch (handle_linkedlist_error_code)
    {
        case handle_linkedlist_max_num_elements:
            printf("Array has maximum number elements.\n");
            break;
        case handle_linkedlist_position_out_of_size_array:
            printf("Position entered is out of array size.\n");
            break;
        case handle_linkedlist_position_has_been_entered:
            printf("Position entered has been entered.\n");
            break;
        case handle_linkedlist_value_out_of_value_range:
            printf("Value entered is out of value range.\n");
            break;
        case handle_linkedlist_value_existed:
            printf("Value entered is existed.\n");
            break;
        case handle_linkedlist_no_element:
            printf("Array is empty.\n");
            break;
        case handle_linkedlist_value_not_existed:
            printf("Value entered is not existed.\n");
        default:
            break;
    }

    return;
 }

/**
 * @brief   Init a array
 *
 * @param   void
 * @return  void
 */
void handle_linkedlist_init_array(void)
{
    uint8_t i = 0;

    for (i = 0; i <= MAX_POSITION; i++)
    {
        s_assignment3[i] = RESET_VALUE;
    }

    s_number_of_elements = MIN_NUM_ELEMENTS;
    sp_head = NULL;

    return;
}

/**
 * @brief   Get until receive an integer (uint8_t)
 *
 * @param   &integer
 * @return  void
 */
static void handle_linkedlist_get_int(uint8_t *integer)
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
 * @brief   Check value has been entered or not
 *
 * @param   &value
 * @return  if found: position of element in array
 *          if not found: MAX_NUM_ELEMENTS
 */
static uint8_t handle_linkedlist_check_value_existed(uint8_t value)
{
    uint8_t retVal = MAX_NUM_ELEMENTS;
    uint8_t i = 0;

    for (i = MIN_POSITION; i <= MAX_POSITION; i++)
    {
        if (s_assignment3[i] == value)
        {
            retVal = i;
        }
    }

    return(retVal);
}

/**
 * @brief   Add node to linked-list in ascending order
 *
 * @param   position, value
 * @return  void
 */
static void handle_linkedlist_add_element_ascending(uint8_t position, uint8_t value)
{
    handle_linkedlist_node_t *pCurrent_node = sp_head;
    handle_linkedlist_node_t *pPrevious_node = NULL;

    /* Inserts a new node in ascending order */
    if (pCurrent_node == NULL)
    {
        sp_head = &s_node[position];
        s_node[position].pNext = NULL;
    }
    else
    {
        while ((pCurrent_node->data < value) && (pCurrent_node->pNext != NULL))
        {
            pCurrent_node = pCurrent_node->pNext;
            if (pPrevious_node != NULL)
            {
                pPrevious_node = pPrevious_node->pNext;
            }
            else
            {
                pPrevious_node = sp_head;
            }
        }
        if (pCurrent_node->data > value)
        {
            if (pPrevious_node != NULL)
            {
                pPrevious_node->pNext = &s_node[position];
                s_node[position].pNext = pCurrent_node;
            }
            else
            {
                sp_head = &s_node[position];
                s_node[position].pNext = pCurrent_node;
            }
        }
        else
        {
            pCurrent_node->pNext = &s_node[position];
            s_node[position].pNext = NULL;
        }
    }

    return;
}

#ifndef _HANDLE_LINKEDLIST_H_
#define _HANDLE_LINKEDLIST_H_

/******************************************************************************
 * Definitions
******************************************************************************/
typedef enum
{
    handle_linkedlist_success = 0,
    handle_linkedlist_max_num_elements = -1,
    handle_linkedlist_position_out_of_size_array = -2,
    handle_linkedlist_position_has_been_entered = -3,
    handle_linkedlist_value_out_of_value_range = -4,
    handle_linkedlist_value_existed = -5,
    handle_linkedlist_no_element = -6,
    handle_linkedlist_value_not_existed = -7
} handle_linkedlist_error_code_t;

/******************************************************************************
 * API
******************************************************************************/
void handle_linkedlist_init_array(void);
handle_linkedlist_error_code_t handle_linkedlist_add_element(void);
handle_linkedlist_error_code_t handle_linkedlist_erase_element(void);
handle_linkedlist_error_code_t handle_linkedlist_print_array(void);
handle_linkedlist_error_code_t handle_linkedlist_print_linkedlist(void);

void handle_linkedlist_print_error(handle_linkedlist_error_code_t handle_linkedlist_error_code);

#endif  /* _HANDLE_LINKEDLIST_H_ */

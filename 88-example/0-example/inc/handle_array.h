#ifndef _HANDLE_ARRAY_H_
#define _HANDLE_ARRAY_H_

/******************************************************************************
 * Definitions
******************************************************************************/
typedef enum
{
    handle_array_success = 0,
    handle_array_creat_array_fail = -1,
    handle_array_add_element_fail = -2,
    handle_array_erase_element_fail = -3,
    handle_array_sort_ascending_fail = -4,
    handle_array_sort_descending_fail = -5,
    handle_array_find_number_fail = -6
} handle_array_error_code_t;

/******************************************************************************
 * API
******************************************************************************/
handle_array_error_code_t handle_array_creat_array(void);
void handle_array_print_array(void);
handle_array_error_code_t handle_array_add_element(void);
handle_array_error_code_t handle_array_erase_element(void);
handle_array_error_code_t handle_array_sort_ascending(void);
handle_array_error_code_t handle_array_sort_descending(void);
handle_array_error_code_t handle_array_find_number(void);
void handle_array_free_memory(void);

void handle_array_print_error(handle_array_error_code_t handle_array_error_code);

#endif  /* _HANDLE_ARRAY_H_ */

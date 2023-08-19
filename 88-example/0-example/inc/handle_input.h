#ifndef _HANDLE_INPUT_H_
#define _HANDLE_INPUT_H_

/******************************************************************************
 * Definitions
******************************************************************************/
typedef enum
{
    handle_input_success = 0,
    handle_input_get_char_fail = -1,
    handle_input_get_int_fail = -2
} handle_input_error_code_t;

/******************************************************************************
 * API
******************************************************************************/
handle_input_error_code_t handle_input_get_char(int8_t *character);
handle_input_error_code_t handle_input_get_int(int32_t *integer);

void handle_input_print_error(handle_input_error_code_t handle_input_error_code);

#endif  /* _HANDLE_INPUT_H_ */

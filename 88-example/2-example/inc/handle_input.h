#ifndef _HANDLE_INPUT_H_
#define _HANDLE_INPUT_H_

/******************************************************************************
 * Definitions
******************************************************************************/
typedef enum
{
    HANDLEINPUT_SUCCESS = 0,
    HANDLEINPUT_GET_CHAR_FAIL = -1,
    HANDLEINPUT_GET_INT_FAIL = -2,
    HANDLEINPUT_GET_FLOAT_FAIL = -3
} handleInput_error_code_t;

/******************************************************************************
 * API
******************************************************************************/
handleInput_error_code_t handleInput_get_char(int8_t* const character);
handleInput_error_code_t handleInput_get_int(int32_t* const integer);
handleInput_error_code_t handleInput_get_float(float* const slack);

void handleInput_print_error(const handleInput_error_code_t error_code);

#endif  /* _HANDLE_INPUT_H_ */

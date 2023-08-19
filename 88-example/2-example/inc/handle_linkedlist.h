#ifndef _HANDLE_LINKEDLIST_H_
#define _HANDLE_LINKEDLIST_H_

/******************************************************************************
 * Definitions
******************************************************************************/
#define MAX_LENGTH_NAME 27u
#define MAX_LENGTH_ACCOUNT 12u

typedef enum
{
    HANDLELINKEDLIST_SUCCESS = 0,
    HANDLELINKEDLIST_DUPLICATE_CODE = -1,
    HANDLELINKEDLIST_DUPLICATE_ACCOUNT = -2,
    HANDLELINKEDLIST_ALLOCATE_ERROR = -3,
    HANDLELINKEDLIST_EMPTY = -4,
    HANDLELINKEDLIST_OUT_OF_POSITION = -5,
    HANDLELINKEDLIST_NOT_FOUND = -6
} handleLinkedlist_error_code_t;

/* Structure student_t contain student information */
typedef struct
{
    int32_t code;
    char name[MAX_LENGTH_NAME];
    char account[MAX_LENGTH_ACCOUNT];
    float score;
} student_t;

/******************************************************************************
 * API
******************************************************************************/
handleLinkedlist_error_code_t handleLinkedlist_init(const student_t* p_student, const uint32_t num_student);

handleLinkedlist_error_code_t handleLinkedlist_print(void);
handleLinkedlist_error_code_t handleLinkedlist_add_student(void);
handleLinkedlist_error_code_t handleLinkedlist_erase_student(void);
handleLinkedlist_error_code_t handleLinkedlist_find_student(void);
handleLinkedlist_error_code_t handleLinkedlist_sort_score(void);
handleLinkedlist_error_code_t handleLinkedlist_sort_name(void);

void handleLinkedlist_print_error(const handleLinkedlist_error_code_t error_code);

#endif  /* _HANDLE_LINKEDLIST_H_ */

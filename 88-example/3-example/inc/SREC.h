#ifndef _SREC_H_
#define _SREC_H_

/******************************************************************************
 * Definitions
******************************************************************************/
/* General definition of the S-Record specification */
enum SRECstructure
{
    /* Ascii hex length to convert  */
    SREC_ASCII_TO_BYTE = 2u,
    /* 81 bytes are enough to read an S-Record record */
    /* 1(S) + 1(TYPE) + 1*2(BYTE COUNT) + 4*2(MAX ADDRESS) + 32*2(MAX DATA) */
    /* + 1*2(CHECK SUM) + 1(CR) + 1(LF) + '\0' */
    SREC_BUFF_SIZE = 81u,
    /* Offsets and lengths of fields in an S-Record record */
    /* S */
    SREC_START_OFFSET = 0u,
    SREC_START = 'S',
    /* TYPE */
    SREC_TYPE_OFFSET = 1u,
    SREC_TYPE_LEN = 1u,
    /* Byte count */
    SREC_COUNT_OFFSET = 2u,
    SREC_COUNT_LEN = 2u,
    /* Address */
    SREC_ADDRESS_OFFSET = 4u,
    SREC_MAX_ADDRESS_LEN = 8u,
    /* Check sum */
    SREC_CHECKSUM_LEN = 2u,
    /* Data */
    SREC_MAX_DATA_LEN = 64u,
    /* Fixed length fields */
    /* Address length of S5 = 16 bits */
    SREC_ADDRESS_S5_LEN = 4u,
    /* Address length of S6 = 24 bits */
    SREC_ADDRESS_S6_LEN = 6u,
    /* Address length of S7 = 32 bits */
    SREC_ADDRESS_S7_LEN = 8u,
    /* Address length of S8 = 24 bits */
    SREC_ADDRESS_S8_LEN = 6u,
    /* Address length of S9 = 16 bits */
    SREC_ADDRESS_S9_LEN = 4u,
    /* Fixed byte count S-Record */
    /* Byte count of S5 */
    SREC_BYTE_COUNT_S5 = SREC_ADDRESS_S5_LEN/SREC_ASCII_TO_BYTE + SREC_CHECKSUM_LEN/SREC_ASCII_TO_BYTE,
    /* Byte count of S6 */
    SREC_BYTE_COUNT_S6 = SREC_ADDRESS_S6_LEN/SREC_ASCII_TO_BYTE + SREC_CHECKSUM_LEN/SREC_ASCII_TO_BYTE,
    /* Byte count of S7 */
    SREC_BYTE_COUNT_S7 = SREC_ADDRESS_S7_LEN/SREC_ASCII_TO_BYTE + SREC_CHECKSUM_LEN/SREC_ASCII_TO_BYTE,
    /* Byte count of S8 */
    SREC_BYTE_COUNT_S8 = SREC_ADDRESS_S8_LEN/SREC_ASCII_TO_BYTE + SREC_CHECKSUM_LEN/SREC_ASCII_TO_BYTE,
    /* Byte count of S9 */
    SREC_BYTE_COUNT_S9 = SREC_ADDRESS_S9_LEN/SREC_ASCII_TO_BYTE + SREC_CHECKSUM_LEN/SREC_ASCII_TO_BYTE,
    /* Max - Min Length S-Record */
    /* 2(Record type) + 2(Byte count) + 4(Address) + 2(Check sum) */
    SREC_MIN_LEN = 10u,
    /* 2(Record type) + 2(Byte count) + 8(Address) + 64(Data) + 2(Check sum) */
    SREC_MAX_LEN = 78u
};

/* Motorola S-Record Types S0-S9 */
enum SRECtype
{
    SREC_TYPE_S0 = 0u,  /* Header record. 16-bit address = 0x0000 and header information is stored in the data field. */
    SREC_TYPE_S1,       /* Data record with 16-bit address */
    SREC_TYPE_S2,       /* Data record with 24-bit address */
    SREC_TYPE_S3,       /* Data record with 32-bit address */
    SREC_TYPE_S4,       /* Extension by LSI Logic, Inc. Reserved. */
    SREC_TYPE_S5,       /* 16-bit address field that contains the number of S1, S2, and S3 records transmitted. No data field. */
    SREC_TYPE_S6,       /* 24-bit address field that contains the number of S1, S2, and S3 records transmitted. No data field. */
    SREC_TYPE_S7,       /* Termination record for S3 records. 32-bit address field contains address of the entry point after the S-Record file has been processed. No data field. */
    SREC_TYPE_S8,       /* Termination record for S2 records. 24-bit address field contains address of the entry point after the S-Record file has been processed. No data field. */
    SREC_TYPE_S9,       /* Termination record for S1 records. 16-bit address field contains address of the entry point after the S-Record file has been processed. No data field. */
};

/* Offset to convert char >> int */
enum SRECconvert
{
    SREC_offset_0_9 = 48u,
    SREC_offset_A_F = 55u
};

/* Error code */
typedef enum
{
    SREC_SUCCESS = 0u,
    SREC_EOF = -1,
    SREC_LENGTH_ERROR = -2,
    SREC_START_ERROR = -3,
    SREC_TYPE_ERROR = -4,
    SREC_SYNTAX_ERROR = -5,
    SREC_BYTE_COUNT_FIXED_ERROR = -6,
    SREC_LENGTH_FIXED_ERROR = -7,
    SREC_BYTE_COUNT_ERROR = -8,
    SREC_TYPE_S5_S6_ERROR = -9,
    SREC_LINE_COUNT_ERROR = -10,
    SREC_CHECK_SUM_ERROR = -11
} SREC_error_code_t;

/* Structure to hold the fields of a Motorola S-Record record. */
typedef struct
{
    uint8_t type;
    uint8_t byte_count;
    uint8_t address_data[(SREC_MAX_ADDRESS_LEN + SREC_MAX_DATA_LEN)/SREC_ASCII_TO_BYTE];
    uint8_t checksum;
    uint32_t current_line;
} SREC_t;

/******************************************************************************
 * API
******************************************************************************/
SREC_error_code_t SRECparse(SREC_t* const srec, FILE* const fp);
void SRECprintError(const uint32_t line, const SREC_error_code_t error_code);

#endif  /* _SREC_H_ */

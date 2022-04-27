#ifndef PARSE_COMMAND_H
#define PARSE_COMMAND_H
#include "IO.h"
#include "table.h"


typedef enum
{
    STATEMENT_INSERT,
    STATEMENT_SELECT,
    STATEMENT_EXIT,
    STATEMENT_PRINT_TREE
} StatementType;

typedef struct
{
    StatementType type;
    Row row_to_insert;
} Statement;

ParseResult parse_command(InputBuffer *input_buffer, Statement *statement);

ParseResult parse_insert(InputBuffer *input_buffer, Statement *statement);

ParseResult parse_meta_command(InputBuffer *input_buffer, Statement *statement);

#endif
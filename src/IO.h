
#ifndef IO_H
#define IO_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>

typedef enum
{
    EXECUTE_SUCCESS,
    EXECUTE_TABLE_FULL,
    EXECUTE_DUPLICATE_KEY,
    EXECUTE_ACCESS_INVALID_KEY,
} ExecuteResult;

typedef enum
{
    PARSE_SUCCESS,
    PARSE_SYNTAX_ERROR,
    PARSE_UNRECOGNIZED_STATEMENT,
    PARSE_NEGATIVE_ID,
    PARSE_STRING_TOO_LONG,
} ParseResult;

typedef enum{
    PAGER_OUT_OF_BOUNDS,
    PAGER_FILE_READ_ERROR,
} PagerResult;

typedef struct
{
    char *buffer;
    size_t buffer_length;
    ssize_t text_length;
} InputBuffer;

InputBuffer *new_input_buffer();

void prompt_read();

void print_parse_error(ParseResult result);

void print_execute_error(ExecuteResult result);

void print_pager_error(PagerResult result);

void read_input(InputBuffer *input_buffer);

void close_buffer(InputBuffer *input_buffer);

void indent(int indent_level);
#endif

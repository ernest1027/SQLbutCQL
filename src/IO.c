#include "IO.h"

void prompt_read() { printf("SQLbutCQL > "); }

void print_parse_error(ParseResult result)
{
    switch (result)
    {
    case (PARSE_NEGATIVE_ID):
        printf("ID must be positive.\n");
        break;
    case (PARSE_STRING_TOO_LONG):
        printf("String is too long.\n");
        break;
    case (PARSE_SYNTAX_ERROR):
        printf("Syntax error. Could not parse statement.\n");
        break;

    case (PARSE_UNRECOGNIZED_STATEMENT):
        printf("Unrecognized statement\n");
        break;
    }
}

void print_execute_error(ExecuteResult result)
{
    switch (result)
    {
    case (EXECUTE_TABLE_FULL):
        printf("Table too full.\n");
        break;
    case (EXECUTE_DUPLICATE_KEY):
        printf("Duplicate key entered.\n");
        break;
    case (EXECUTE_ACCESS_INVALID_KEY):
        printf("Invalid key entered.\n");
        break;
    }
}

void print_pager_error(PagerResult result)
{
    switch (result)
    {
    case (PAGER_OUT_OF_BOUNDS):
        printf("Tried to fetch a page out of bounds\n");
        break;
    case (PAGER_FILE_READ_ERROR):
        printf("Can't read file\n");
        break;
    }
}


InputBuffer *new_input_buffer()
{
    InputBuffer *input_buffer = malloc(sizeof(InputBuffer));
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->text_length = 0;

    return input_buffer;
}

void close_buffer(InputBuffer *input_buffer)
{
    free(input_buffer->buffer);
    free(input_buffer);
}

void read_input(InputBuffer *input_buffer)
{
    ssize_t text_length = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin) - 1;

    if (text_length < 0)
    {
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }

    input_buffer->text_length = text_length;
    input_buffer->buffer[text_length] = 0;
}

void indent(int indent_level){
    for(int i =0 ; i<indent_level; i++)
    {
        printf("    ");
    }
}
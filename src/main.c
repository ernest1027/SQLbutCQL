#include "table.h"
#include "parseCommand.h"
#include "executeCommand.h"

int main(int argc, char *argv[])
{

    if (argc < 2)
    {
        printf("Must supply a database filename.\n");
        exit(EXIT_FAILURE);
    }
    char *filename = argv[1];
    Table *table = open_db(filename);

    InputBuffer *input_buffer = new_input_buffer();

    while (true)
    {
        Statement statement;
        prompt_read();
        read_input(input_buffer);

        ParseResult parseResult = parse_command(input_buffer, &statement);
        if (parseResult != PARSE_SUCCESS)
        {
            print_parse_error(parseResult);
            continue;
        }

        ExecuteResult executeResult = execute_statement(input_buffer, &statement, table);
        if (executeResult != EXECUTE_SUCCESS)
        {
            print_execute_error(executeResult);
            continue;
        }
    }
}

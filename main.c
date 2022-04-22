#include "table.h"
#include "parseCommand.h"
#include "executeCommand.h"


int main()
{
    InputBuffer *input_buffer = new_input_buffer();
    Table *table = new_table();

    while (true)
    {
        Statement statement;
        prompt_read();
        read_input(input_buffer);

        ParseResult parseResult = parse_command(input_buffer, &statement);
        if(parseResult != PARSE_SUCCESS){
            print_parse_error(parseResult);
            continue;
        }

        ExecuteResult executeResult = execute_statement(input_buffer, &statement, table);
        if(executeResult != EXECUTE_SUCCESS){
            print_execute_error(executeResult);
            continue;
        }        
    }
}

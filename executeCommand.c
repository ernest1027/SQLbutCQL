#include "executeCommand.h"


ExecuteResult execute_statement(InputBuffer *input_buffer, Statement *statement, Table *table)
{
    switch (statement->type)
    {
    case (STATEMENT_INSERT):
        return execute_insert(input_buffer, statement, table);
    case (STATEMENT_SELECT):
        return execute_select(input_buffer, statement, table);
    case (STATEMENT_EXIT):
        return execute_exit(input_buffer, statement, table);
    }
}

ExecuteResult execute_insert(InputBuffer *input_buffer, Statement *statement, Table *table)
{
    if (table->num_rows >= TABLE_MAX_ROWS)
    {
        return EXECUTE_TABLE_FULL;
    }

    Row *row_to_insert = &(statement->row_to_insert);

    serialize_row(row_to_insert, row_slot(table, table->num_rows));
    table->num_rows += 1;

    return EXECUTE_SUCCESS;
}

ExecuteResult execute_select(InputBuffer *input_buffer, Statement *statement, Table *table)
{
    Row row;
    for (uint32_t i = 0; i < table->num_rows; i++)
    {
        deserialize_row(row_slot(table, i), &row);
        print_row(&row);
    }
    return EXECUTE_SUCCESS;
}

ExecuteResult execute_exit(InputBuffer *input_buffer, Statement *statement, Table *table)
{
    close_buffer(input_buffer);
    free_table(table);
    exit(EXIT_SUCCESS);
}
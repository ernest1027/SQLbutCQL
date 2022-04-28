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
    case (STATEMENT_PRINT_TREE):
        return execute_print_tree(table);
    }
}

ExecuteResult execute_insert(InputBuffer *input_buffer, Statement *statement, Table *table)
{
    
    void *node = get_page(table->pager, table->root_page_num);
    uint32_t num_cells = (*leaf_node_num_cells(node));
    Row *row_to_insert = &(statement->row_to_insert);
    uint32_t key_to_insert = row_to_insert->id;
    Cursor* cursor = table_find(table, key_to_insert);
    if (cursor->cell_num < num_cells) {
        if (*leaf_node_key(node, cursor->cell_num) == key_to_insert) {
         return EXECUTE_DUPLICATE_KEY;
        }
    }

    leaf_node_insert(cursor, row_to_insert->id, row_to_insert);
    free(cursor);
    return EXECUTE_SUCCESS;
}

ExecuteResult execute_select(InputBuffer *input_buffer, Statement *statement, Table *table)
{
    Row row;
    Cursor *cursor = table_start(table);
    while (!(cursor)->end_of_table)
    {
        deserialize_row(cursor_value(cursor), &row);
        print_row(&row);
        cursor_advance(cursor);
    }
    return EXECUTE_SUCCESS;
    free(cursor);
}

ExecuteResult execute_exit(InputBuffer *input_buffer, Statement *statement, Table *table)
{
    close_buffer(input_buffer);
    close_db(table);
    exit(EXIT_SUCCESS);
}

ExecuteResult execute_print_tree(Table *table)
{
    printf("Tree:\n");
    print_tree(table->pager,0,0);
    return EXECUTE_SUCCESS;
}
#ifndef EXECUTE_COMMAND_H
#define EXECUTE_COMMAND_H
#include "parseCommand.h"
#include "cursor.h"
#include "tree.h"

ExecuteResult execute_statement(InputBuffer *input_buffer, Statement *statement, Table *table);

ExecuteResult execute_insert(InputBuffer *input_buffer, Statement *statement, Table *table);

ExecuteResult execute_select(InputBuffer *input_buffer, Statement *statement, Table *table);

ExecuteResult execute_exit(InputBuffer *input_buffer, Statement *statement, Table *table);

ExecuteResult execute_print_tree(Table *table);

#endif


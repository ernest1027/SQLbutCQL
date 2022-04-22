#ifndef EXECUTE_COMMAND_H
#define EXECUTE_COMMAND_H
#include "parseCommand.h"



extern uint32_t ID_SIZE;
extern uint32_t USERNAME_SIZE;
extern uint32_t EMAIL_SIZE;
extern uint32_t ID_OFFSET;
extern uint32_t USERNAME_OFFSET;
extern uint32_t EMAIL_OFFSET;
extern uint32_t ROW_SIZE;
extern uint32_t PAGE_SIZE;
extern uint32_t ROWS_PER_PAGE;
extern uint32_t TABLE_MAX_ROWS;

ExecuteResult execute_statement(InputBuffer *input_buffer, Statement *statement, Table *table);

ExecuteResult execute_insert(InputBuffer *input_buffer, Statement *statement, Table *table);

ExecuteResult execute_select(InputBuffer *input_buffer, Statement *statement, Table *table);

ExecuteResult execute_exit(InputBuffer *input_buffer, Statement *statement, Table *table);

#endif


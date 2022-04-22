#ifndef CURSOR_H
#define CURSOR_H
#include "table.h"

extern uint32_t ID_SIZE;
extern uint32_t USERNAME_SIZE;
extern uint32_t EMAIL_SIZE;
extern uint32_t ID_OFFSET;
extern uint32_t USERNAME_OFFSET;
extern uint32_t EMAIL_OFFSET;
extern uint32_t ROW_SIZE;
extern uint32_t ROWS_PER_PAGE;
extern uint32_t TABLE_MAX_ROWS;

typedef struct{
    Table *table;
    uint32_t row_num;
    bool end_of_table;
} Cursor;

Cursor *table_start(Table *table);
Cursor *table_end(Table *table);
void cursor_advance(Cursor *cursor);
void* cursor_value(Cursor *cursor);

#endif
#ifndef CURSOR_H
#define CURSOR_H
#include "table.h"

typedef struct{
    Table *table;
    uint32_t page_num;
    uint32_t cell_num;
    bool end_of_table;
} Cursor;

Cursor *table_start(Table *table);
Cursor *table_end(Table *table);
void cursor_advance(Cursor *cursor);
void* cursor_value(Cursor *cursor);
Cursor *table_find(Table *table, uint32_t key);
Cursor *leaf_node_find(Table *table, uint32_t page_num, uint32_t key);
Cursor *internal_node_find(Table *table, uint32_t page_num, uint32_t key);

#endif
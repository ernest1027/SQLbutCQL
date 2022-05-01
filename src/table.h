#ifndef TABLE_H
#define TABLE_H
#include "IO.h"
#include "pager.h"


typedef struct
{
    uint32_t root_page_num;
    Pager *pager;
} Table;


void serialize_row(Row *source, void *destination);

void deserialize_row(void *source, Row *destination);

Table *open_db(char *filename);

void close_db(Table *table);

void print_row(Row* row);

#endif
#ifndef TABLE_H
#define TABLE_H
#include "IO.h"
#include "pager.h"


typedef struct
{
    uint32_t num_rows;
    Pager *pager;
} Table;

typedef struct
{
    uint32_t id;
    char username[COLUMN_USERNAME_SIZE+1];
    char email[COLUMN_EMAIL_SIZE+1];
} Row;

void serialize_row(Row *source, void *destination);

void deserialize_row(void *source, Row *destination);

Table *open_db(char *filename);

void close_db(Table *table);

void print_row(Row* row);

#endif
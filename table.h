#ifndef TABLE_H
#define TABLE_H
#include "IO.h"

#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255
#define size_of_attribute(Struct, Attribute) sizeof(((Struct *)0)->Attribute)
#define TABLE_MAX_PAGES 100

typedef struct
{
    uint32_t num_rows;
    void *pages[TABLE_MAX_PAGES];
} Table;

typedef struct
{
    uint32_t id;
    char username[COLUMN_USERNAME_SIZE+1];
    char email[COLUMN_EMAIL_SIZE+1];
} Row;

void serialize_row(Row *source, void *destination);

void deserialize_row(void *source, Row *destination);

void *row_slot(Table *table, uint32_t row_num);

Table *new_table();

void free_table(Table *table);

void print_row(Row* row);

#endif
#ifndef PAGER_H
#define PAGER_H
#include "IO.h"

#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255
#define size_of_attribute(Struct, Attribute) sizeof(((Struct *)0)->Attribute)
#define TABLE_MAX_PAGES 100
#define PAGE_SIZE 4096

typedef struct {
    int file_descriptor;
    uint32_t file_length;
    void* pages[TABLE_MAX_PAGES];
} Pager;

void *get_page(Pager *pager, uint32_t page_number);
Pager *pager_open(char * filename);
void page_flush(Pager *pager, uint32_t page_number, uint32_t size);

#endif
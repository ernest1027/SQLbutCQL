#include "table.h"
const uint32_t ID_SIZE = size_of_attribute(Row, id);
const uint32_t USERNAME_SIZE = size_of_attribute(Row, username);
const uint32_t EMAIL_SIZE = size_of_attribute(Row, email);
const uint32_t ID_OFFSET = 0;
const uint32_t USERNAME_OFFSET = ID_OFFSET + ID_SIZE;
const uint32_t EMAIL_OFFSET = USERNAME_OFFSET + USERNAME_SIZE;
const uint32_t ROW_SIZE = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE;
const uint32_t ROWS_PER_PAGE = PAGE_SIZE / ROW_SIZE;
const uint32_t TABLE_MAX_ROWS = ROWS_PER_PAGE * TABLE_MAX_PAGES;


void serialize_row(Row *source, void *destination)
{
  memcpy(destination + ID_OFFSET, &(source->id), ID_SIZE);
  memcpy(destination + USERNAME_OFFSET, &(source->username), USERNAME_SIZE);
  memcpy(destination + EMAIL_OFFSET, &(source->email), EMAIL_SIZE);
}

void deserialize_row(void *source, Row *destination)
{
  memcpy(&(destination->id), source + ID_OFFSET, ID_SIZE);
  memcpy(&(destination->username), source + USERNAME_OFFSET, USERNAME_SIZE);
  memcpy(&(destination->email), source + EMAIL_OFFSET, EMAIL_SIZE);
}

Table *open_db(char *filename)
{
  Pager *pager = pager_open(filename);
  Table *table = (Table *)malloc(sizeof(Table));
  table->num_rows = pager->file_length/ROW_SIZE;
  table->pager = pager;
  return table;
}

void close_db(Table *table)
{
  Pager *pager = table->pager;
  uint32_t num_pages = table->num_rows/ROWS_PER_PAGE;
  for(int i =0 ; i<num_pages; i++){
    if(pager->pages[i] == NULL)continue;
    page_flush(pager, i, PAGE_SIZE);
  }
  uint32_t num_additional_rows = table->num_rows % ROWS_PER_PAGE;
  if (num_additional_rows > 0) {
     if (pager->pages[num_pages] != NULL) {
         page_flush(pager, num_pages, num_additional_rows * ROW_SIZE);
     }
  }

  close(pager->file_descriptor);
  for(int i =0 ; i<TABLE_MAX_PAGES;i++){
    free(pager->pages[i]);
  }
  free(pager);
  free(table);
}

void print_row(Row *row)
{
  printf("(%d, %s, %s)\n", row->id, row->username, row->email);
}
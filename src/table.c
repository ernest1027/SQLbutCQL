#include "table.h"




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
  table->root_page_num =0;
  table->pager = pager;

  if(pager->num_pages == 0){
    void* root_node = get_page(pager,0);
    initialize_leaf_node(root_node);
    set_node_root(root_node, true);
  }
  return table;
}

void close_db(Table *table)
{
  Pager *pager = table->pager;
 
  for(int i =0 ; i<pager->num_pages; i++){
    if(pager->pages[i] == NULL)continue;
    page_flush(pager, i);
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
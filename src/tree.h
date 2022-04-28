#ifndef TREE_H
#define TREE_H
#include "cursor.h"
void leaf_node_insert(Cursor *cursor, uint32_t key, Row *value);
void print_tree(Pager *pager, uint32_t page_num, uint32_t indent_level);
void leaf_node_split_insert(Cursor *cursor, uint32_t key, Row *value);
void create_new_root(Table *table, uint32_t right_child_page_num);
#endif
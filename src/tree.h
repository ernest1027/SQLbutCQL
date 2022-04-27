#ifndef TREE_H
#define TREE_H
#include "cursor.h"
void leaf_node_insert(Cursor *cursor, uint32_t key, Row *value);
void print_leaf_node(void *node);
#endif
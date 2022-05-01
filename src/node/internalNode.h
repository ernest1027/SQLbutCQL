#ifndef INTERNAL_NODE_H
#define INTERNAL_NODE_H
#include "node.h"
#define INTERNAL_NODE_NUM_KEYS_SIZE sizeof(uint32_t)
#define INTERNAL_NODE_NUM_KEYS_OFFSET COMMON_NODE_HEADER_SIZE
#define INTERNAL_NODE_RIGHT_CHILD_SIZE sizeof(uint32_t)
#define INTERNAL_NODE_RIGHT_CHILD_OFFSET  (INTERNAL_NODE_NUM_KEYS_OFFSET + INTERNAL_NODE_NUM_KEYS_SIZE)
#define INTERNAL_NODE_HEADER_SIZE (COMMON_NODE_HEADER_SIZE + INTERNAL_NODE_NUM_KEYS_SIZE + INTERNAL_NODE_RIGHT_CHILD_SIZE)

#define INTERNAL_NODE_KEY_SIZE sizeof(uint32_t)
#define INTERNAL_NODE_CHILD_SIZE sizeof(uint32_t)
#define INTERNAL_NODE_CELL_SIZE  (INTERNAL_NODE_CHILD_SIZE + INTERNAL_NODE_KEY_SIZE)
#define INTERNAL_NODE_SPACE_FOR_CELLS  (PAGE_SIZE - INTERNAL_NODE_CELL_SIZE)
#define INTERNAL_NODE_MAX_CELLS (INTERNAL_NODE_SPACE_FOR_CELLS/INTERNAL_NODE_CELL_SIZE)
#define INTERNAL_NODE_MAX_KEYS INTERNAL_NODE_MAX_CELLS

#define INTERNAL_NODE_RIGHT_SPLIT_COUNT ((INTERNAL_NODE_MAX_KEYS + 1) / 2)
#define INTERNAL_NODE_LEFT_SPLIT_COUNT ((INTERNAL_NODE_MAX_KEYS + 1) - INTERNAL_NODE_RIGHT_SPLIT_COUNT)

uint32_t *internal_node_num_keys(void *node);
uint32_t *internal_node_right_child(void *node);
uint32_t *internal_node_cell(void *node, uint32_t cell_num);
uint32_t *internal_node_child(void *node, uint32_t child_num);
uint32_t *internal_node_key(void *node, uint32_t key_num);
void initialize_internal_node(void *node);
void update_internal_node_key(void *node, uint32_t old_key, uint32_t new_key);
uint32_t internal_node_find_child(void *node, uint32_t key);
#endif
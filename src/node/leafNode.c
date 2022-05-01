#include "leafNode.h"
uint32_t *leaf_node_num_cells(void *node)
{
    return node + LEAF_NODE_NUM_CELLS_OFFSET;
}
void *leaf_node_cell(void *node, uint32_t cell_num)
{
    return (node + LEAF_NODE_HEADER_SIZE + cell_num * LEAF_NODE_CELL_SIZE);
}
uint32_t *leaf_node_key(void *node, uint32_t cell_num)
{
    return leaf_node_cell(node, cell_num);
}
void *leaf_node_value(void *node, uint32_t cell_num)
{
    return leaf_node_cell(node, cell_num) + LEAF_NODE_KEY_SIZE;
}
void initialize_leaf_node(void *node)
{
    set_node_type(node, NODE_LEAF);
    set_node_root(node, false);
    *leaf_node_num_cells(node) = 0;
    *leaf_next_leaf(node) = 0;
}
uint32_t *leaf_next_leaf(void *node)
{
    return node + LEAF_NODE_NEXT_LEAF_OFFSET;
}
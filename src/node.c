#include "node.h"
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

NodeType get_node_type(void *node)
{
    uint8_t value = *((uint8_t *)(node + NODE_TYPE_OFFSET));
    return (NodeType)value;
}
void set_node_type(void *node, NodeType type)
{
    *((uint8_t *)(node + NODE_TYPE_OFFSET)) = type;
}

uint32_t *internal_node_num_keys(void *node)
{
    return node + INTERNAL_NODE_NUM_KEYS_OFFSET;
}
uint32_t *internal_node_right_child(void *node)
{
    return node + INTERNAL_NODE_RIGHT_CHILD_OFFSET;
}
uint32_t *internal_node_cell(void *node, uint32_t cell_num)
{
    return node + INTERNAL_NODE_HEADER_SIZE + cell_num * INTERNAL_NODE_CELL_SIZE;
}
uint32_t *internal_node_child(void *node, uint32_t child_num)
{
    uint32_t num_keys = *internal_node_num_keys(node);

    if (child_num > num_keys)
    {
        print_execute_error(EXECUTE_ACCESS_INVALID_KEY);
        exit(EXIT_FAILURE);
    }
    if (child_num == num_keys)
        return internal_node_right_child(node);
    return internal_node_cell(node, child_num);
}
uint32_t *internal_node_key(void *node, uint32_t key_num)
{
    return (void *)internal_node_cell(node, key_num) + INTERNAL_NODE_CHILD_SIZE;
}
void initialize_internal_node(void *node)
{
    set_node_type(node, NODE_INTERNAL);
    set_node_root(node, false);
    *internal_node_num_keys(node) = 0;
}
void update_internal_node_key(void *node, uint32_t old_key, uint32_t new_key)
{
    uint32_t old_child_index = internal_node_find_child(node, old_key);
    *internal_node_key(node, old_child_index) = new_key;
}
uint32_t internal_node_find_child(void *node, uint32_t key)
{
    uint32_t num_keys = *internal_node_num_keys(node);
    
    uint32_t low = 0;
    uint32_t high = num_keys;
    while (low != high)
    {
        uint32_t index = (low + high) / 2;
        uint32_t key_to_right = *internal_node_key(node, index);
        if (key_to_right >= key)
        {
            high = index;
        }
        else
        {
            low = index + 1;
        }
    }
    return low;
}
bool is_node_root(void *node)
{
    uint8_t value = *((uint8_t *)(node + IS_ROOT_OFFSET));
    return (bool)value;
}
void set_node_root(void *node, bool is_root)
{
    *((uint8_t *)(node + IS_ROOT_OFFSET)) = (uint8_t)is_root;
}

uint32_t get_node_max_key(void *node)
{

    switch (get_node_type(node))
    {
    case NODE_INTERNAL:
        return *internal_node_key(node, *internal_node_num_keys(node) - 1);
    case NODE_LEAF:
        return *leaf_node_key(node, *leaf_node_num_cells(node) - 1);
    }
}

uint32_t *node_parent(void *node)
{
    return node + PARENT_POINTER_OFFSET;
}
#include "internalNode.h"
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
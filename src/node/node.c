#include "node.h"


NodeType get_node_type(void *node)
{
    uint8_t value = *((uint8_t *)(node + NODE_TYPE_OFFSET));
    return (NodeType)value;
}
void set_node_type(void *node, NodeType type)
{
    *((uint8_t *)(node + NODE_TYPE_OFFSET)) = type;
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



uint32_t *node_parent(void *node)
{
    return node + PARENT_POINTER_OFFSET;
}
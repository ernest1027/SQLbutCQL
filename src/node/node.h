#ifndef NODE_H
#define NODE_H
#include "../IO.h"

typedef enum {NODE_INTERNAL, NODE_LEAF} NodeType;

#define size_of_attribute(Struct, Attribute) sizeof(((Struct *)0)->Attribute)

#define COLUMN_USERNAME_SIZE 32
#define COLUMN_EMAIL_SIZE 255
#define TABLE_MAX_PAGES 1000
#define PAGE_SIZE 4096

typedef struct
{
    uint32_t id;
    char username[COLUMN_USERNAME_SIZE+1];
    char email[COLUMN_EMAIL_SIZE+1];
} Row;

#define ID_SIZE  size_of_attribute(Row, id)
#define USERNAME_SIZE  size_of_attribute(Row, username)
#define EMAIL_SIZE  size_of_attribute(Row, email)
#define ID_OFFSET  0
#define USERNAME_OFFSET  (ID_OFFSET + ID_SIZE)
#define EMAIL_OFFSET  (USERNAME_OFFSET + USERNAME_SIZE)
#define ROW_SIZE  (ID_SIZE + USERNAME_SIZE + EMAIL_SIZE)

#define NODE_TYPE_SIZE sizeof(uint8_t)
#define NODE_TYPE_OFFSET  0
#define IS_ROOT_SIZE  sizeof(uint8_t)
#define IS_ROOT_OFFSET  NODE_TYPE_SIZE
#define PARENT_POINTER_SIZE  sizeof(uint32_t)
#define PARENT_POINTER_OFFSET  (IS_ROOT_OFFSET + IS_ROOT_SIZE)
#define COMMON_NODE_HEADER_SIZE (NODE_TYPE_SIZE + IS_ROOT_SIZE + PARENT_POINTER_SIZE)

bool is_node_root(void *node);
void set_node_root(void *node, bool is_root);

NodeType get_node_type(void *node);
void set_node_type(void *node, NodeType type);
uint32_t *node_parent(void *node);

#endif
#include "tree.h"
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
void leaf_node_insert(Cursor *cursor, uint32_t key, Row *value)
{

    void *node = get_page(cursor->table->pager, cursor->page_num);

    uint32_t num_cells = *leaf_node_num_cells(node);
    if (num_cells >= LEAF_NODE_MAX_CELLS)
    {
        leaf_node_split_insert(cursor, key, value);
        return;
    }

    if (cursor->cell_num < num_cells)
    {
        for (uint32_t i = num_cells; i > cursor->cell_num; i--)
        {
            memcpy(leaf_node_cell(node, i), leaf_node_cell(node, i - 1),
                   LEAF_NODE_CELL_SIZE);
        }
    }

    *(leaf_node_num_cells(node)) += 1;
    *(leaf_node_key(node, cursor->cell_num)) = key;
    serialize_row(value, leaf_node_value(node, cursor->cell_num));
}

void leaf_node_split_insert(Cursor *cursor, uint32_t key, Row *value)
{

    void *prev_node = get_page(cursor->table->pager, cursor->page_num);
    uint32_t prev_max = get_node_max_key(prev_node);
    uint32_t new_page_num = get_free_page_num(cursor->table->pager);

    void *new_node = get_page(cursor->table->pager, new_page_num);

    initialize_leaf_node(new_node);
    *leaf_next_leaf(new_node) = *leaf_next_leaf(prev_node);
    *leaf_next_leaf(prev_node) = new_page_num;
    *node_parent(new_node) = *node_parent(prev_node);
    for (int i = LEAF_NODE_MAX_CELLS; i >= 0; i--)
    {
        void *dest_node;
        if (i >= LEAF_NODE_LEFT_SPLIT_COUNT)
        {
            dest_node = new_node;
        }
        else
        {
            dest_node = prev_node;
        }

        uint32_t index = i % LEAF_NODE_LEFT_SPLIT_COUNT;
        void *dest_cell = leaf_node_cell(dest_node, index);

        if (i == cursor->cell_num)
        {
            serialize_row(value, leaf_node_value(dest_node, index));
            *leaf_node_key(dest_node, index) = key;
            continue;
        }
        if (i > cursor->cell_num)
        {
            memcpy(dest_cell, leaf_node_cell(prev_node, i - 1), LEAF_NODE_CELL_SIZE);
            continue;
        }
        memcpy(dest_cell, leaf_node_cell(prev_node, i), LEAF_NODE_CELL_SIZE);
    }
    *(leaf_node_num_cells(prev_node)) = LEAF_NODE_LEFT_SPLIT_COUNT;
    *(leaf_node_num_cells(new_node)) = LEAF_NODE_RIGHT_SPLIT_COUNT;
    if (is_node_root(prev_node))
    {
        return create_new_root(cursor->table, new_page_num);
    }
    else
    {
        uint32_t parent_page_num = *node_parent(prev_node);
        uint32_t new_max = get_node_max_key(prev_node);
        void *parent = get_page(cursor->table->pager, parent_page_num);
        update_internal_node_key(parent, prev_max, new_max);
        internal_node_insert(cursor->table, parent_page_num, new_page_num);
    }
}

void create_new_root(Table *table, uint32_t right_child_page_num)
{
    void *root = get_page(table->pager, table->root_page_num);
    void *right_child = get_page(table->pager, right_child_page_num);
    uint32_t left_child_page_num = get_free_page_num(table->pager);
    void *left_child = get_page(table->pager, left_child_page_num);

    memcpy(left_child, root, PAGE_SIZE);
    set_node_root(left_child, false);

    initialize_internal_node(root);
    set_node_root(root, true);
    *internal_node_num_keys(root) = 1;
    *internal_node_child(root, 0) = left_child_page_num;
    *internal_node_right_child(root) = right_child_page_num;
    *internal_node_key(root, 0) = get_node_max_key(left_child);

    *node_parent(left_child) = table->root_page_num;
    *node_parent(right_child) = table->root_page_num;
}

void print_tree(Pager *pager, uint32_t page_num, uint32_t indent_level)
{
    void *node = get_page(pager, page_num);
    uint32_t num_keys, child;
    switch (get_node_type(node))
    {
    case (NODE_LEAF):
        num_keys = *leaf_node_num_cells(node);
        indent(indent_level);
        printf("- leaf (size %d)\n", num_keys);
        for (int i = 0; i < num_keys; i++)
        {
            indent(indent_level + 1);
            printf("- %d\n", *leaf_node_key(node, i));
        }
        break;
    case (NODE_INTERNAL):
        num_keys = *internal_node_num_keys(node);
        indent(indent_level);
        printf("- internal node (num keys %d)\n", num_keys);
        for (int i = 0; i < num_keys; i++)
        {
            child = *internal_node_child(node, i);
            print_tree(pager, child, indent_level + 1);
            indent(indent_level + 1);
            printf("- key %d\n", (*internal_node_key(node, i)));
        }
        child = *internal_node_right_child(node);
        print_tree(pager, child, indent_level + 1);
        break;
    }
}

void internal_node_insert(Table *table, uint32_t parent_page_num, uint32_t child_page_num)
{
    void *parent = get_page(table->pager, parent_page_num);
    void *child = get_page(table->pager, child_page_num);

    uint32_t child_max_key = get_node_max_key(child);
    uint32_t index = internal_node_find_child(parent, child_max_key);

    uint32_t num_keys = (*internal_node_num_keys(parent));
    if (num_keys >= INTERNAL_NODE_MAX_KEYS)
    {
        internal_node_split_and_insert(table, parent_page_num,child_page_num);
        return;
    }
    (*internal_node_num_keys(parent)) = num_keys + 1;
    uint32_t right_child_page_num = *internal_node_right_child(parent);
    void *right_child = get_page(table->pager, right_child_page_num);
    if (child_max_key > get_node_max_key(right_child))
    {
        *internal_node_child(parent, num_keys) = right_child_page_num;
        *internal_node_key(parent, num_keys) = get_node_max_key(right_child);
        *internal_node_right_child(parent) = child_page_num;
    }
    else
    {
        for (int i = num_keys; i > index; i--)
        {
            void *dest = internal_node_cell(parent, i);
            void *source = internal_node_cell(parent, i - 1);
            memcpy(dest, source, INTERNAL_NODE_CELL_SIZE);
        }
        *internal_node_child(parent, index) = child_page_num;
        *internal_node_key(parent, index) = child_max_key;
    }
}

void internal_node_split_and_insert(Table *table, uint32_t parent_page_num, uint32_t child_page_num)
{
    void *prev_node = get_page(table->pager, parent_page_num);
    uint32_t prev_max = get_node_max_key(prev_node);
    uint32_t right_page_num = get_free_page_num(table->pager);
    void *right_node = get_page(table->pager, right_page_num);

    initialize_internal_node(right_node);
    *node_parent(right_node) = *node_parent(prev_node);
    for (int i = INTERNAL_NODE_MAX_KEYS; i >= INTERNAL_NODE_LEFT_SPLIT_COUNT; i--)
    {

        uint32_t index = i % INTERNAL_NODE_LEFT_SPLIT_COUNT;
        uint32_t key, child;
        if (i == INTERNAL_NODE_MAX_KEYS)
        {
            *internal_node_right_child(right_node) = *internal_node_right_child(prev_node);
            continue;
        }       
        else
        {
            child = *internal_node_child(prev_node, i);
            key = *internal_node_key(prev_node, i);
            *internal_node_cell(right_node, index) = child;
            *internal_node_key(right_node, index) = key;
        }        
    }
    *internal_node_right_child(prev_node) = *internal_node_child(prev_node, INTERNAL_NODE_LEFT_SPLIT_COUNT-1);
    *(internal_node_num_keys(prev_node)) = INTERNAL_NODE_LEFT_SPLIT_COUNT-1;
    *(internal_node_num_keys(right_node)) = INTERNAL_NODE_RIGHT_SPLIT_COUNT-1;
    uint32_t new_max = get_node_max_key(prev_node);
    void *child = get_page(table->pager,child_page_num);
    uint32_t child_max = get_node_max_key(child);
    if(child_max > new_max)
    {
        internal_node_insert(table,right_page_num,child_page_num);
    }
    else{
        internal_node_insert(table,parent_page_num,child_page_num);
    }

    if (is_node_root(prev_node))
    {
        return create_new_root(table, right_page_num);
    }
    else
    {
        uint32_t parent_page_num = *node_parent(prev_node);
        
        void *parent = get_page(table->pager, parent_page_num);
        update_internal_node_key(parent, prev_max, new_max);
        internal_node_insert(table, parent_page_num, right_page_num);
    }

}
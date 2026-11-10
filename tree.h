#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define DUMP_FILE_NAME "dump.dot"

struct tree_node_s{
    long int data;
    tree_node_s *left;
    tree_node_s *right;
    tree_node_s *parent;
};

typedef struct tree_node_s tree_node_s;

typedef enum {
    TREE_SUCCESS,
    TREE_MEMORY_ALLOCATION,
    TREE_POINTERS_TRUBBLE,
    TREE_LINKING_TROUBLE,
} tree_errors_e;

tree_node_s * tree_node_init(int data, tree_node_s *parent);
tree_errors_e tree_node_delete(tree_node_s *node);
tree_errors_e link_right_node(int data, tree_node_s *parent);
tree_errors_e link_left_node(int data, tree_node_s *parent);
tree_errors_e create_new_node(int data_for_new_node, tree_node_s *root);
// tree_errors_e add_node(int data, tree_node_s *root);
tree_errors_e node_dump(tree_node_s current_node);

tree_node_s error_node_CONST = {
            .data = 2989,
            .left = NULL,
            .right = NULL
            .parent = NULL,
        };
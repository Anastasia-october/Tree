#include "tree.h"

int main() {
    tree_node_s root = {
        .data = 50,
        .left = NULL,
        .right = NULL,
        .parent = NULL,
    };
    tree_node_s current = root;

    int data_for_new_node = 30;

    tree_errors_e res_making_new_node = create_new_node(data_for_new_node, &root);

    if (res_making_new_node != 0) {
        fprintf(stderr, "ERROR truble with making new node\n\tin main\n");
    }

}

tree_node_s *  tree_node_init(int data, tree_node_s *parent) {
    assert(parent && "wrong parent pointer");

    tree_node_s *node = (tree_node_s *) calloc(1, sizeof(tree_node_s));
    if (node == NULL) {
        fprintf(stderr, "ERROR wrong memory allocation\n\tin tree_node_init\n");
        return &error_node_CONST;
    }

    node->data = data;
    node->parent = parent;

    return node;
}

tree_errors_e   tree_node_delete(tree_node_s *node) {
    assert(node);

    node->data = 2989; //NOTE: 0xBAD
    if (node->left != NULL || node->right != NULL) {
        fprintf(stderr, "Warning: you want delete node, which has not NULL pointers to left or right node\n");
    }
    node->right = NULL;
    node->left = NULL;

    if (node->parent->left == node) {
        node->parent->left = NULL;
    }
    else {
        node->parent->right = NULL;
    }

    free(node);
    return TREE_SUCCESS;
}

tree_errors_e   link_right_node(int data, tree_node_s *current_node) {
    assert(current_node->parent && "wrong parent pointer");

    tree_node_s *created_node = tree_node_init(data, current_node);
    if (created_node->data == 2989) {
        fprintf(stderr, "ERROR null data in created_node\n\tin link_right_node\n");
        return TREE_POINTERS_TRUBBLE;
    }

    current_node->right = created_node;

    return TREE_SUCCESS;
}

tree_errors_e   link_left_node(int data, tree_node_s *current_node) {
    assert(current_node->parent && "wrong parent pointer");

    tree_node_s *created_node = tree_node_init(data, current_node);
    if (created_node->data == 2989) {
        fprintf(stderr, "ERROR null data in created_node\n\tin link_right_node\n");
        return TREE_POINTERS_TRUBBLE;
    }

    current_node->left = created_node;

    return TREE_SUCCESS;
}

tree_errors_e   create_new_node(int data_for_new_node, tree_node_s *current) {
    int f = 0;
    tree_errors_e res_link = TREE_SUCCESS;

    while (f == 0) {
        if (data_for_new_node > current->data) {
            if (current->left != NULL) {
                current = current->left;
            }
            else {
                res_link = link_left_node(data_for_new_node, current);
                f = 1;
            }
        }

        else {
            if (current->right != NULL) {
                current = current->right;
            }
            else {
                res_link = link_right_node(data_for_new_node, current);
                f = 1;
            }
        }

    }
    if (res_link != 0) {
        fprintf(stderr, "ERROR truble with linking\n\tin main\n");
        return TREE_LINKING_TROUBLE;
    }

    return TREE_SUCCESS;
}
//NOTE: not ready, do not look on while 
tree_errors_e node_dump(tree_node_s *current_node) {
    FILE *dump_file_pointer = fopen(DUMP_FILE_NAME, "a");
    if (dump_file_pointer == NULL) {
        fprintf(stderr, "ERROR truble with openning dump file\n\tin node_dump\n");
        return TREE_POINTERS_TRUBBLE;
    }

    while (current_node->left != NULL) {
        fprintf(dump_file_pointer, "digraph Tree {\nrankdir=TB;\nnode [shape=Mrecord];\n");

        fprintf(dump_file_pointer, "knot_%d [ style=filled, fillcolor=\"#FFC0C0\",  label=\"{ <data> data\n50 | { <left> left\n30 | <right> right\n60 }} \"];\n");

        fprintf(dump_file_pointer, "knot_1:<left> -> knot_2;\nknot_1:<right> -> knot_3;\n}");
    }

    return TREE_SUCCESS;
}


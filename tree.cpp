#include "tree.h"

int main() {
    tree_node_s *root = (tree_node_s *) calloc(1, sizeof(tree_node_s)); 
    root->data = 50;
    root->left = NULL;
    root->parent = NULL;
    root->right = NULL;
    
    // tree_node_s *current = root;

    long int data_for_new_node = 47;

    tree_errors_e res_making_new_node = create_new_node(data_for_new_node, root);

    data_for_new_node = 60;
    res_making_new_node = create_new_node(data_for_new_node, root);

    data_for_new_node = 20;
    res_making_new_node = create_new_node(data_for_new_node, root);

    data_for_new_node = 33;
    res_making_new_node = create_new_node(data_for_new_node, root);

    data_for_new_node = 69;
    res_making_new_node = create_new_node(data_for_new_node, root);

    data_for_new_node = 59;
    res_making_new_node = create_new_node(data_for_new_node, root);

    data_for_new_node =36;
    res_making_new_node = create_new_node(data_for_new_node, root);

    data_for_new_node = 16;
    res_making_new_node = create_new_node(data_for_new_node, root);

    data_for_new_node = 3;
    res_making_new_node = create_new_node(data_for_new_node, root);

    data_for_new_node = 91;
    res_making_new_node = create_new_node(data_for_new_node, root);

    data_for_new_node = 89;
    res_making_new_node = create_new_node(data_for_new_node, root);

    data_for_new_node = 50;
    res_making_new_node = create_new_node(data_for_new_node, root);
    
    printf("A\n");
    
    tree_errors_e res_tree_dump = wrap_tree_dump(root);
    if (res_tree_dump != TREE_SUCCESS) {
        fprintf(stderr, "ERROR trouble with tree dump");
    }

    int res_system = system("dot -Tsvg dump.dot -o dump_comp.svg");
    printf("res system %d\n", res_system);

    tree_errors_e result = delete_tree(root);
    if (result != TREE_SUCCESS) {
        fprintf(stderr, "ERROR troublle with deleting tree\n\tin main\n");
    }

    return 0;
}

tree_node_s *  tree_node_init(long int data, tree_node_s *parent) {
    assert(parent && "wrong parent pointer");

    tree_node_s *node = (tree_node_s *) calloc(1, sizeof(tree_node_s));
    if (node == NULL) {
        fprintf(stderr, "ERROR wrong memory allocation\n\tin tree_node_init\n");
        return &error_node_CONST;
    }

    node->data = data;
    node->parent = parent;
    // fprintf(stderr, "Done\n");

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

    if (node->parent != NULL) {
        if (node->parent->left == node) {
            node->parent->left = NULL;
        }
        else {
            node->parent->right = NULL;
        }
    }

    free(node);
    return TREE_SUCCESS;
}

tree_errors_e   link_right_node(long int data, tree_node_s *current_node) {
    //assert(current_node->parent && "wrong parent pointer");

    tree_node_s *created_node = tree_node_init(data, current_node);
    if (created_node->data == 2989) {
        fprintf(stderr, "ERROR null data in created_node\n\tin link_right_node\n");
        return TREE_POINTERS_TRUBBLE;
    }

    current_node->right = created_node;
    // fprintf(stderr, "Done para\n");

    return TREE_SUCCESS;
}

tree_errors_e   link_left_node(long int data, tree_node_s *current_node) {
    //assert(current_node->parent && "wrong parent pointer");

    tree_node_s *created_node = tree_node_init(data, current_node);
    if (created_node->data == 2989) {
        fprintf(stderr, "ERROR null data in created_node\n\tin link_right_node\n");
        return TREE_POINTERS_TRUBBLE;
    }

    current_node->left = created_node;

    return TREE_SUCCESS;
}

tree_errors_e delete_tree(tree_node_s *current){
    assert(current);

    while (current->left != NULL || current->right != NULL) {
        if (current->left != NULL) {
            delete_tree(current->left);
        }
        if (current->right != NULL) {
            delete_tree(current->right);
        }
    }
    tree_errors_e res_delete = tree_node_delete(current);

    if (res_delete != TREE_SUCCESS) {
        fprintf(stderr, "Error: trubble with deleting node\n\tin delete_tree");
        return TREE_DELETE_TROUBLE;
    }

    return TREE_SUCCESS;
}

tree_errors_e   create_new_node(long int data_for_new_node, tree_node_s *current) {
    int f = 0;
    tree_errors_e res_link = TREE_SUCCESS;

    while (f == 0) {
        if (data_for_new_node <= current->data) {
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

tree_errors_e node_dump(tree_node_s *current_node) {
    assert(current_node && "zero pointer to current_node\n");

    FILE *dump_file_pointer = fopen(DEBUG_FILE_NAME, "a");
    if (dump_file_pointer == NULL) {
        fprintf(stderr, "ERROR truble with openning dump file\n\tin node_dump\n");
        return TREE_POINTERS_TRUBBLE;
    }

    int i = 1;

    long int left;
    long int right;

    if (current_node->left != NULL) {
        left = current_node->left->data;
    }
    else {
        left = 0;
    }
    if (current_node->right != NULL) {
        right = current_node->right->data;
        // fprintf(stderr, "current_node->data = <%d>\n");
    }
    else {
        right = 0;
    }
    fprintf(dump_file_pointer, "NODE_DUMP\n");
    fprintf(dump_file_pointer, "digraph{\n\trankdir=TB;\n\tnode [shape=Mrecord];\n\n");
    fprintf(dump_file_pointer, "\tknot_%d [ style=filled, fillcolor=\"#FFC0C0\",  label=\"{ <data> data %ld | { <left> left %ld | <right> right %ld }} \"];\n", i, current_node->data, left, right);
    fprintf(dump_file_pointer, "}");
    fprintf(dump_file_pointer, "\nEND_OF_NODE_DUMP\n\n\n\n");

    system("dot -Tsvg dump.dot -o dump_comp.svg");
    fclose(dump_file_pointer);
    return TREE_SUCCESS;
}

tree_errors_e one_node_dump(tree_node_s *current_node, FILE *df_ptr, int level) {
    assert(df_ptr && "ERROR: wrong pointer to dump file in one_node_dump\n");
    assert(current_node && "ERROR wrong pointer to current_node(root node expected\n)");

    long int left;
    long int right;

    if (current_node->left != NULL) {
        left = current_node->left->data;
    }
    else {
        left = 0;
    }

    if (current_node->right != NULL) {
        right = current_node->right->data;
    }
    else {
        right = 0;
    }
    if (current_node->parent != NULL) {
        fprintf(df_ptr, "\tknot_%ld [ style=filled, fillcolor=\"#C0FFC0\",  label=\"{ <data> data %ld | { <left> left %ld | <right> right %ld }} \"];\n", current_node->data, current_node->data, left, right);
        fprintf(df_ptr, "\tknot_%ld -> knot_%ld;\n\n", current_node->data, current_node->parent->data);
    }
    else {
        long int zero = 0;
        fprintf(df_ptr, "\tknot_%ld [ style=filled, fillcolor=\"#C0FFFF\",  label=\"{ <data> data %ld | { <left> left %ld | <right> right %ld }} \"];\n", current_node->data, current_node->data, left, right);
        fprintf(df_ptr, "\tknot_%ld -> knot_%ld;\n\n", current_node->data, zero);
    }

    return TREE_SUCCESS;
}

tree_errors_e tree_dump(tree_node_s *current_node, FILE *df_ptr, int level) {
    assert(current_node && "Error in tree dump - zero pointer input\n");
    assert(df_ptr && "Wrong pointer to file for dump\n");

    fprintf(stderr, "wetn into tree_dump with node %ld\n", current_node->data);

    if (current_node->left != NULL) {
        tree_errors_e inside_result = tree_dump(current_node->left, df_ptr, level++);
        if (inside_result != TREE_SUCCESS) {
            fprintf(stderr, "ERROR: troubles in reqursion tree_dump\n\ttXlib соболезнует...\n");
            return TREE_DUMP_TROUBLE;
        } 
    }
    if (current_node->right != NULL) {
        tree_errors_e inside_result = tree_dump(current_node->right, df_ptr, level++);
        if (inside_result != TREE_SUCCESS) {
            fprintf(stderr, "ERROR: troubles in reqursion tree_dump left undertree\n\ttXlib соболезнует...\n");
            return TREE_DUMP_TROUBLE;
        }
    }
    if (current_node->left == NULL && current_node->right == NULL) {
        tree_errors_e res_dump = one_node_dump(current_node, df_ptr, level++);
        return res_dump;
    }

    tree_errors_e res_dump = one_node_dump(current_node, df_ptr, level++);
    return res_dump;
}


tree_errors_e wrap_tree_dump(tree_node_s *current_node) {
    assert(current_node && "Error in tree dump - zero pointer input");

    FILE *clear_pointer = fopen(DUMP_FILE_NAME, "w");//NOTE: clear file
    fclose(clear_pointer);

    FILE *df_ptr = fopen(DUMP_FILE_NAME, "a");
    if (df_ptr == NULL) {
        fprintf(stderr, "ERROR: did not open file for graph dump\n");
        return TREE_OPEN_FILE_TROUBLE;
    }

    int level = 1;
    fprintf(df_ptr, "digraph{\n\trankdir=TB;\n\tnode [shape=Mrecord];\n\n");

    tree_errors_e inside_result = tree_dump(current_node, df_ptr, level);
    if (inside_result != TREE_SUCCESS) {
        fprintf(stderr, "ERROR: troubles in reqursion tree_dump left undertree\n\ttXlib соболезнует...\n\tIn wrap_tree_dump\n");
        return TREE_DUMP_TROUBLE;
    }

    fprintf(df_ptr, "}");

    int res_system = system("dot -Tsvg dump.dot -o dump_comp.svg");
    printf("res system %d\n", res_system);
    fclose(df_ptr);
    return TREE_SUCCESS;
}

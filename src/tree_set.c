#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "tree_set.h"
#include "string.h"

typedef struct node {
    void *value;
    node_t *left;
    node_t *right;
} node_t;

typedef struct tree_set {
    node_t *root;
    size_t size;
    compar_t compar;
} tree_set_t;

size_t num_children(node_t *node) {
    return (node->left != NULL) + (node->right != NULL);
}

int compare_num(int *a, int *b) {
    // assert(*a != NULL);
    return *a - *b;
}

node_t *tree_node_init(void *value) {
    node_t *node = malloc(sizeof(node_t));
    node->left = NULL;
    node->right = NULL;
    node->value = value;
    return node;
}

tree_set_t *tree_set_comp_init(compar_t compar) {
    tree_set_t *set = malloc(sizeof(tree_set_t));
    assert(set != NULL); // check that memory was allocated
    set->root = NULL;
    set->size = 0;
    set->compar = compar;
    return set;
}

tree_set_t *tree_set_str_init() {
    return tree_set_comp_init((compar_t) strcmp);
}

tree_set_t *tree_set_init() {
    return tree_set_comp_init((compar_t) compare_num);
}

void tree_node_free(node_t *node) {
    if (node->left != NULL) {
        tree_node_free(node->left);
    }
    if (node->right != NULL) {
        tree_node_free(node->right);
    }
    free(node->value);
    free(node);
}

void tree_set_free(tree_set_t *set) {
    if (set->root != NULL) {
        tree_node_free(set->root);
    }
    free(set);
}

size_t tree_set_size(tree_set_t *set) {
    return set->size;
}

bool tree_set_is_empty(tree_set_t *set) {
    return set->size == 0;
}

bool node_contains(node_t *curr, void *value, compar_t compar) {
    int comparison = compar(value, curr->value);
    if (comparison < 0) {
        // base case
        if (curr->left == NULL) {
            return false;
        }
        else {
            return node_contains(curr->left, value, compar);
        }
    }
    else if (comparison > 0) {
        // base case
        if (curr->right == NULL) {
            return false;
        }
        else {
            return node_contains(curr->right, value, compar);
        }
    }
    return true;
}

bool tree_set_contains(tree_set_t *set, void *element) {
    if (set->size == 0) {
        return false;
    }
    return node_contains(set->root, element, set->compar);
}

void node_add(tree_set_t *set, node_t *curr, void *value, compar_t compar) {
    int comparison = compar(value, curr->value);
    if (comparison < 0) {
        // base case
        if (curr->left == NULL) {
            node_t *new_node = tree_node_init(value);
            curr->left = new_node;
        }
        else {
            node_add(set, curr->left, value, compar);
        }
    }
    else if (comparison > 0) {
        // base case
        if (curr->right == NULL) {
            node_t *new_node = tree_node_init(value);
            curr->right = new_node;
        }
        else {
            node_add(set, curr->right, value, compar);
        }
    }
    else {
        set->size--;
    }
}

void tree_set_add(tree_set_t *set, void *element) {
    if (set->size == 0) {
        set->root = tree_node_init(element);
    }
    else {
        node_add(set, set->root, element, set->compar);
    }
    set->size++;
}

node_t *find_max(node_t *to_remove, node_t *curr, node_t *prev) {
    if (curr->right == NULL) {
        if (to_remove == prev) {
            prev->left = curr->left;
        }
        else {
            prev->right = curr->left;
        }
        return curr;
    }
    return find_max(to_remove, curr->right, curr);
}

void replace_root(tree_set_t *set) {
    size_t children = num_children(set->root);
    switch(children) {
    case 0:
        // case for zero children (leaf)
        set->root = NULL;
        break;
    case 1:
        // case for one child
        if (set->root->left == NULL) {
            set->root = set->root->right;
        }
        else {
            set->root = set->root->left;
        }
        break;
    default:
        // case when two children are present
        node_t *old_root = set->root;
        set->root = find_max(set->root, set->root->left, set->root);
        set->root->left = old_root->left;
        set->root->right = old_root->right;
        break;
    }
}

void replace_node_left(node_t *to_remove, node_t *parent) {
    size_t children = num_children(to_remove);
    switch(children) {
    case 0:
        // case for zero children (leaf)
        parent->left = NULL;
        break;
    case 1:
        // case for one child
        if (to_remove->left == NULL) {
            parent->left = to_remove->right;
        }
        else {
            parent->left = to_remove->left;
        }
        break;
    default:
        // case when two children are present
        parent->left = find_max(to_remove, to_remove->left, to_remove);
        parent->left->left = to_remove->left;
        parent->left->right = to_remove->right;
        break;
    }
}

void replace_node_right(node_t *to_remove, node_t *parent) {
    size_t children = num_children(to_remove);
    switch(children) {
    case 0:
        parent->right = NULL; 
        break;
    case 1:
        if (to_remove->left == NULL) {
            parent->right = to_remove->right;
        }
        else {
            parent->right = to_remove->left;
        }
        break;
    default:
        parent->right = find_max(to_remove, to_remove->left, to_remove);
        parent->right->left = to_remove->left;
        parent->right->right = to_remove->right;
        break;
    }
}

// void replace_node(node_t *to_remove, node_t *parent, char side) {
//     size_t children = num_children(to_remove);
//     if (side == 'l') {
//         switch(children) {
//         case 0:
//             // case for zero children (leaf)
//             parent->left = NULL; 
//             break;
//         case 1:
//             // case for one child
//             if (to_remove->left == NULL) {
//                 parent->left = to_remove->right;
//             }
//             else {
//                 parent->left = to_remove->left;
//             }
//             break;
//         default:
//             // case when two children are present
//             parent->left = find_max(to_remove->left, to_remove);
//             break;
//         }
//     }
//     else {
//         switch(children) {
//         case 0:
//             parent->right = NULL; 
//             break;
//         case 1:
//             if (to_remove->right == NULL) {
//                 parent->right = to_remove->right;
//             }
//             else {
//                 parent->right = to_remove->left;
//             }
//             break;
//         default:
//             parent->right = find_max(to_remove, NULL);
//             break;
//         }
//     }
    
// }

void *remove_node(tree_set_t *set, node_t *curr, node_t *prev, void *value, compar_t compar) {
    int comparison = compar(value, curr->value);
    if (comparison < 0) {
        assert(curr->left != NULL);
        return remove_node(set, curr->left, curr, value, compar);
    }
    else if (comparison > 0) {
        assert(curr->right != NULL);
        return remove_node(set, curr->right, curr, value, compar);
    }
    // base case
    else {
        void *ptr_removed = curr->value;
        // first check if prev is NULL
        if (prev == NULL) {
            replace_root(set);
        }
        else {
            // check whether current node is left or right branch
            if (prev->left == curr) {
                replace_node_left(curr, prev);
            }
            else {
                replace_node_right(curr, prev);
            }
        }
        free(curr);
        return ptr_removed;
    }
}

void *tree_set_remove(tree_set_t *set, void *element) {
    assert(set->size != 0);
    void *value = remove_node(set, set->root, NULL, element, set->compar);
    set->size--;
    return value;
}

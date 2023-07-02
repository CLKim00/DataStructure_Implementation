#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct node {
    int data;
    struct node *right_child;
    struct node *left_child;
};

typedef struct {
    struct node *root;
} BST;

bool isEmpty(BST *bst);
void makeEmpty(BST *bst);
void inOrder(BST *bst, struct node *root);
void preOrder(BST *bst, struct node *root);
void postOrder(BST *bst, struct node *root);
bool contains(BST *bst, int data);
struct node* makeNode(int data);
void put(BST *bst, int data);
struct node* minValueNode(struct node* node);
void delete(BST *bst, int data);

int main() {
    BST bst;
    bst.root = NULL;

    put(&bst, 6);
    put(&bst, 2);
    put(&bst, 7);
    put(&bst, 1);
    put(&bst, 4);
    put(&bst, 3);
    put(&bst, 5);

    printf("Pre-order: ");
    preOrder(&bst, bst.root);
    printf("\n");

    printf("In-order: ");
    inOrder(&bst, bst.root);
    printf("\n");

    printf("Post-order: ");
    postOrder(&bst, bst.root);
    printf("\n");

    return 0;
}

bool isEmpty(BST *bst) {
    return bst->root == NULL;
}

void makeEmpty(BST *bst) {
    if (bst->root != NULL) {
        makeEmpty(&(BST){bst->root->left_child});
        makeEmpty(&(BST){bst->root->right_child});
        free(bst->root);
    }
    bst->root = NULL;
}

void inOrder(BST *bst, struct node *root) {
    if (root != NULL) {
        inOrder(bst, root->left_child);
        printf("%d ", root->data);
        inOrder(bst, root->right_child);
    }
}

void preOrder(BST *bst, struct node *root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preOrder(bst, root->left_child);
        preOrder(bst, root->right_child);
    }
}

void postOrder(BST *bst, struct node *root) {
    if (root != NULL) {
        postOrder(bst, root->left_child);
        postOrder(bst, root->right_child);
        printf("%d ", root->data);
    }
}

bool contains(BST *bst, int data) {
    struct node *current = bst->root;
    while (current != NULL) {
        if (current->data == data) {
            return true;
        } else if (data < current->data) {
            current = current->left_child;
        } else {
            current = current->right_child;
        }
    }
    return false;
}

struct node *makeNode(int data) {
    struct node *newNode = malloc(sizeof(struct node));
    newNode->data = data;
    newNode->left_child = NULL;
    newNode->right_child = NULL;
    return newNode;
}

void put(BST *bst, int data) {
    struct node *parent = NULL;
    struct node *current = bst->root;
    while (current != NULL) {
        parent = current;
        if (data < current->data) {
            current = current->left_child;
        } else if (data > current->data) {
            current = current->right_child;
        } else {
            return;  
        }
    }
    if (parent == NULL) { 
        bst->root = makeNode(data);
    } else if (data < parent->data) {
        parent->left_child = makeNode(data);
    } else {
        parent->right_child = makeNode(data);
    }
}

struct node *minValueNode(struct node* node) {
    struct node *current = node;

    while (current && current->left_child != NULL)
        current = current->left_child;

    return current;
}

void delete(BST *bst, int data) {
    struct node **x = &bst->root;
    while (*x != NULL) {
        if ((*x)->data == data) {
            struct node *old = *x;
            if ((*x)->left_child == NULL) {
                *x = (*x)->right_child;
            } else if ((*x)->right_child == NULL) {
                *x = (*x)->left_child;
            } else {
                struct node *minNode = (*x)->right_child;
                while (minNode->left_child != NULL) {
                    minNode = minNode->left_child;
                }
                minNode->left_child = (*x)->left_child;
                *x = (*x)->right_child;
            }
            free(old);
            return;
        } else if (data < (*x)->data) {
            x = &(*x)->left_child;
        } else {
            x = &(*x)->right_child;
        }
    }
}

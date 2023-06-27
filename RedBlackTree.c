#include <stdio.h>
#include <stdlib.h>

// Structure for a red-black tree node
struct RBNode {
    int data;
    int color; // 0 for black, 1 for red
    struct RBNode* left;
    struct RBNode* right;
    struct RBNode* parent;
};

// Structure for a red-black tree
struct RBTree {
    struct RBNode* root;
    struct RBNode* nil; // Sentinel node (black, null-like node)
};

// Function to create a new red-black tree
struct RBTree* createRBTree() {
    struct RBTree* tree = (struct RBTree*)malloc(sizeof(struct RBTree));

    // Create the sentinel node
    tree->nil = (struct RBNode*)malloc(sizeof(struct RBNode));
    tree->nil->data = 0;
    tree->nil->color = 0;
    tree->nil->left = NULL;
    tree->nil->right = NULL;
    tree->nil->parent = NULL;

    // Set the sentinel node as the root initially
    tree->root = tree->nil;

    return tree;
}

// Function to rotate left at a given node
void rotateLeft(struct RBTree* tree, struct RBNode* node) {
    struct RBNode* rightChild = node->right;
    node->right = rightChild->left;

    if (rightChild->left != tree->nil) {
        rightChild->left->parent = node;
    }

    rightChild->parent = node->parent;

    if (node->parent == tree->nil) {
        tree->root = rightChild;
    } else if (node == node->parent->left) {
        node->parent->left = rightChild;
    } else {
        node->parent->right = rightChild;
    }

    rightChild->left = node;
    node->parent = rightChild;
}

// Function to rotate right at a given node
void rotateRight(struct RBTree* tree, struct RBNode* node) {
    struct RBNode* leftChild = node->left;
    node->left = leftChild->right;

    if (leftChild->right != tree->nil) {
        leftChild->right->parent = node;
    }

    leftChild->parent = node->parent;

    if (node->parent == tree->nil) {
        tree->root = leftChild;
    } else if (node == node->parent->left) {
        node->parent->left = leftChild;
    } else {
        node->parent->right = leftChild;
    }

    leftChild->right = node;
    node->parent = leftChild;
}

// Function to fix the red-black tree after insertion
void fixInsert(struct RBTree* tree, struct RBNode* node) {
    while (node->parent->color == 1) {
        if (node->parent == node->parent->parent->left) {
            struct RBNode* uncle = node->parent->parent->right;

            if (uncle->color == 1) {
                node->parent->color = 0;
                uncle->color = 0;
                node->parent->parent->color = 1;
                node = node->parent->parent;
            } else {
                if (node == node->parent->right) {
                    node = node->parent;
                    rotateLeft(tree, node);
                }

                node->parent->color = 0;
                node->parent->parent->color = 1;
                rotateRight(tree, node->parent->parent);
            }
        } else {
            struct RBNode* uncle = node->parent->parent->left;

            if (uncle->color == 1) {
                node->parent->color = 0;
                uncle->color = 0;
                node->parent->parent->color = 1;
                node = node->parent->parent;
            } else {
                if (node == node->parent->left) {
                    node = node->parent;
                    rotateRight(tree, node);
                }

                node->parent->color = 0;
                node->parent->parent->color = 1;
                rotateLeft(tree, node->parent->parent);
            }
        }
    }

    tree->root->color = 0;
}

// Function to insert a value into the red-black tree
void insert(struct RBTree* tree, int value) {
    struct RBNode* newNode = (struct RBNode*)malloc(sizeof(struct RBNode));
    newNode->data = value;
    newNode->left = tree->nil;
    newNode->right = tree->nil;
    newNode->parent = tree->nil;
    newNode->color = 1; // New nodes are always colored red

    struct RBNode* current = tree->root;
    struct RBNode* parent = tree->nil;

    while (current != tree->nil) {
        parent = current;
        if (value < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    newNode->parent = parent;

    if (parent == tree->nil) {
        tree->root = newNode;
    } else if (value < parent->data) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    fixInsert(tree, newNode);
}

// Function to recursively print the red-black tree in-order
void inOrderTraversal(struct RBTree* tree, struct RBNode* node) {
    if (node != tree->nil) {
        inOrderTraversal(tree, node->left);
        printf("%d ", node->data);
        inOrderTraversal(tree, node->right);
    }
}

// Function to print the red-black tree
void printRBTree(struct RBTree* tree) {
    if (tree->root == tree->nil) {
        printf("Empty tree.\n");
        return;
    }

    printf("Red-Black Tree (in-order traversal): ");
    inOrderTraversal(tree, tree->root);
    printf("\n");
}

// Driver code
int main() {
    struct RBTree* tree = createRBTree();

    insert(tree, 10);
    insert(tree, 20);
    insert(tree, 30);
    insert(tree, 40);
    insert(tree, 50);
    insert(tree, 25);

    printf("Red-Black Tree after insertions:\n");
    printRBTree(tree);

    return 0;
}

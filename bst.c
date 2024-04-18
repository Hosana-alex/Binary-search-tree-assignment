#include <stdio.h>
#include <stdlib.h>

// Define the structure for the BST node
typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* bst_construct(int in_order[], int post_order[], int start, int end, int* pIndex);
int search(int array[], int start, int end, int value);
Node* newNode(int data);
void printDFS(Node* node);

// Function to construct BST from in-order and post-order traversals
Node* bst_construct(int in_order[], int post_order[], int start, int end, int* pIndex) {
    if (start > end) {
        return NULL;
    }

    // The last element in post_order is the root from the current segment
    Node* node = newNode(post_order[*pIndex]);
    (*pIndex)--;

    if (start == end) {
        return node;
    }

    // Find the index of this node in in_order traversal
    int iIndex = search(in_order, start, end, node->data);

    // Using index in Inorder traversal, construct right and then left subtree
    node->right = bst_construct(in_order, post_order, iIndex + 1, end, pIndex);
    node->left = bst_construct(in_order, post_order, start, iIndex - 1, pIndex);

    return node;
}

// Function to create a new node
Node* newNode(int data) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}

// Function to find the index of value in array[start...end]
int search(int array[], int start, int end, int value) {
    int i;
    for (i = start; i <= end; i++) {
        if (array[i] == value) {
            return i;
        }
    }
    return -1;
}

// Function to print nodes in DFS manner
void printDFS(Node* node) {
    if (node == NULL) {
        return;
    }
    printf("%d ", node->data);
    printDFS(node->left);
    printDFS(node->right);
}

int main() {
    int in_order[] = {5, 10, 15, 20, 25, 30, 45};
    int post_order[] = {5, 15, 10, 25, 45, 30, 20};
    int n = sizeof(in_order) / sizeof(in_order[0]);
    int postIndex = n - 1;

    Node* root = bst_construct(in_order, post_order, 0, n - 1, &postIndex);

    printf("DFS of constructed BST: \n");
    printDFS(root);
    return 0;
}
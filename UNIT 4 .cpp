#include <iostream>
#include <algorithm>
using namespace std;
struct Node {
    int key, h;
    Node *left, *right;

    Node(int k) {
        key = k;
        h = 1;
        left = right = NULL;
    }
};
// BST insertion
Node* insertBST(Node* root, int key) {
    if (root == NULL)
        return new Node(key);
    if (key < root->key)
        root->left = insertBST(root->left, key);
    else
        root->right = insertBST(root->right, key);
    return root;
}
// AVL functions
int height(Node* n) {
    return n == NULL ? 0 : n->h;
}
void update(Node* n) {
    n->h = 1 + max(height(n->left), height(n->right));
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    y->left = x->right;
    x->right = y;
    update(y);
    update(x);
    return x;
}
Node* leftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;
    update(x);
    update(y);
    return y;
}
Node* insertAVL(Node* root, int key) {
    if (root == NULL)
        return new Node(key);
    if (key < root->key)
        root->left = insertAVL(root->left, key);
    else if (key > root->key)
        root->right = insertAVL(root->right, key);
    else
        return root;
    update(root);
    int balance = height(root->left) - height(root->right);
    if (balance > 1 && key < root->left->key)
        return rightRotate(root);
    if (balance < -1 && key > root->right->key)
        return leftRotate(root);
    if (balance > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}
// Calculate BST height
int treeHeight(Node* root) {
    if (root == NULL)
       return 0;
    return 1 + max(treeHeight(root->left),
                   treeHeight(root->right));
}
// Display search path
void searchPath(Node* root, int key) {
    Node* curr = root;
    while (curr != NULL) {
        cout << curr->key << " ";
        if (curr->key == key) {
            cout << "-> Found\n";
            return;
        }
        if (key < curr->key)
            curr = curr->left;
        else
            curr = curr->right;
    }
    cout << "-> Not Found\n";
}
int main() {
    Node *bst = NULL, *avl = NULL;
    int keys[] = {
        10, 20, 30, 40, 50,
        60, 70, 80, 90, 100,
        110, 120, 130, 140, 150
    };

    int n = sizeof(keys) / sizeof(keys[0]);
    for (int i = 0; i < n; i++) {
        bst = insertBST(bst, keys[i]);
        avl = insertAVL(avl, keys[i]);
    }
    cout << "Number of keys: " << n << "\n";
    cout << "BST Height: " << treeHeight(bst) << "\n";
    cout << "AVL Height: " << height(avl) << "\n";
    int key;
    cout << "\nEnter key to search: ";
    cin >> key;
    cout << "\nBST Search Path: ";
    searchPath(bst, key);
    cout << "AVL Search Path: ";
    searchPath(avl, key);
    return 0;
}


#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

struct Node {
    string word;
    string meaning;
    Node* left;
    Node* right;
    int height;

    Node(string w, string m) {
        word = w;
        meaning = m;
        left = right = nullptr;
        height = 1;
    }
};

class Dictionary {
private:
    Node* root;
    int rotations;

    int height(Node* node) {
        return (node == nullptr) ? 0 : node->height;
    }

    int getBalance(Node* node) {
        if (node == nullptr)
            return 0;
        return height(node->left) - height(node->right);
    }

    // Right rotation
    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = 1 + max(height(y->left),
                            height(y->right));
        x->height = 1 + max(height(x->left),
                            height(x->right));

        rotations++;
        return x;
    }

    // Left rotation
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = 1 + max(height(x->left),
                            height(x->right));
        y->height = 1 + max(height(y->left),
                            height(y->right));

        rotations++;
        return y;
    }

    Node* insert(Node* node, string word, string meaning) {
        // Normal BST insertion
        if (node == nullptr)
            return new Node(word, meaning);

        if (word < node->word)
            node->left = insert(node->left, word, meaning);
        else if (word > node->word)
            node->right = insert(node->right, word, meaning);
        else {
            // Update meaning if word already exists
            node->meaning = meaning;
            return node;
        }

        // Update height
        node->height = 1 + max(height(node->left),
                               height(node->right));

        int balance = getBalance(node);

        // LL case
        if (balance > 1 && word < node->left->word)
            return rightRotate(node);

        // RR case
        if (balance < -1 && word > node->right->word)
            return leftRotate(node);

        // LR case
        if (balance > 1 && word > node->left->word) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // RL case
        if (balance < -1 && word < node->right->word) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node* search(Node* node, string word) {
        if (node == nullptr || node->word == word)
            return node;

        if (word < node->word)
            return search(node->left, word);

        return search(node->right, word);
    }

    void inorder(Node* node) {
        if (node == nullptr)
            return;

        inorder(node->left);
        cout << node->word << " : "
             << node->meaning << endl;
        inorder(node->right);
    }

public:
    Dictionary() {
        root = nullptr;
        rotations = 0;
    }

    void insertWord(string word, string meaning) {
        int oldRotations = rotations;
        root = insert(root, word, meaning);

        cout << "Word inserted/updated successfully.\n";
        cout << "Rotations in this insertion: "
             << rotations - oldRotations << endl;
    }

    void searchWord(string word) {
        Node* result = search(root, word);

        if (result != nullptr) {
            cout << "Word: " << result->word << endl;
            cout << "Meaning: " << result->meaning << endl;
        } else {
            cout << "Word not found in dictionary.\n";
        }
    }

    void displayDictionary() {
        if (root == nullptr) {
            cout << "Dictionary is empty.\n";
            return;
        }

        cout << "\nDictionary in alphabetical order:\n";
        inorder(root);
    }

    void displayRotations() {
        cout << "Total rotations performed: "
             << rotations << endl;
    }
};

int main() {
    Dictionary dict;
    int choice;
    string word, meaning;

    do {
        cout << "\n===== DICTIONARY USING AVL TREE =====\n";
        cout << "1. Insert a word\n";
        cout << "2. Search for a word\n";
        cout << "3. Display dictionary (Inorder)\n";
        cout << "4. Count rotations\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";

        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter word: ";
                cin >> word;

                cout << "Enter meaning: ";
                getline(cin >> ws, meaning);

                dict.insertWord(word, meaning);
                break;

            case 2:
                cout << "Enter word to search: ";
                cin >> word;

                dict.searchWord(word);
                break;

            case 3:
                dict.displayDictionary();
                break;

            case 4:
                dict.displayRotations();
                break;

            case 5:
                cout << "Exiting dictionary application.\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}

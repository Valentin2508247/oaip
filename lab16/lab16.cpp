#include <iostream>

using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    Node* parent;
};

struct Tree {
    Node* root;
    int size = 0;

    void add(int value)
    {
        if (size == 0)
        {
            root = new Node();
            root->key = value;
            size++;
        }
        else {
            add(root, value);
        }
    }

    void add(Node* parent, int value) {
        if (parent->key > value) {
            // left
            if (parent->left == NULL)
            {
                Node* node = new Node();
                node->key = value;
                node->parent = parent;
                parent->left = node;
                size++;
                return;
            }
            else {
                add(parent->left, value);
            }
        }
        else {
            //right
            if (parent->right == NULL)
            {
                Node* node = new Node();
                node->key = value;
                node->parent = parent;
                parent->right = node;
                size++;
                return;
            }
            else {
                add(parent->right, value);
            }
        }
    }

    void deleteNode(int key) {
        if (size == 0)
            return ;
        if (size == 1) {
            if (root->key == key)
            {
                root = NULL;
                size--;
                return;
            }
            else {
                return;
            }
        }
        return deleteNode(root, key);
    }

    void deleteNode(Node* parent, int key) {
        if (parent == NULL)
            return;
        else if (parent->key == key) {
            if (parent->left == NULL && parent->right == NULL) {
                // all children are null
                Node* p = parent->parent;
                if (key < p->key)
                {
                    p->left = NULL;
                    delete parent;
                    size--;
                    return;
                }
                else {
                    p->right = NULL;
                    delete parent;
                    size--;
                    return;
                }
            }
            else if (parent->left == NULL) {
                Node* child = parent->right;
                parent->left = child->left;
                parent->right = child->right;
                parent->key = child->key;
                delete child;
            }
            else if (parent->right == NULL)
            {
                Node* child = parent->left;
                parent->left = child->left;
                parent->right = child->right;
                parent->key = child->key;
                delete child;
            }
            else {
                Node* m = findMin(parent->right);
                parent->key = m->key;
                deleteNode(m, m->key);
            }
        }
        else if (key < parent->key) {
            return deleteNode(parent->left, key);
        }
        else {
            return deleteNode(parent->right, key);
        }
    }

    Node* findMin(Node* node) {
        if (node == NULL)
            return NULL;
        if (node->left == NULL)
            return node;
        return findMin(node->left);

    }

    Node* find(int key) {
        
        return find(root, key);
    }

    Node* find(Node* parent, int key) {
        if (parent == NULL)
            return NULL;
        if (parent->key == key)
            return parent;
        if (parent->key > key)
            return find(parent->left, key);
        if (parent->key < key)
            return find(parent->right, key);
    }

    //прямой Root -> Left -> Right
    void printRootLR() {
        printRootLR(root, 0);
    }

    void printRootLR(Node* parent, int depth) {
        if (parent == NULL)
            return;
        for (int i = 0; i < depth; i++)
            cout << '|';
        cout << parent->key << endl;

        printRootLR(parent->left, depth + 1);
        printRootLR(parent->right, depth + 1);
    }

    //обратный Left -> Right -> Root
    void printLRRoot() {
        printLRRoot(root, 0);
    }

    void printLRRoot(Node* parent, int depth) {
        if (parent == NULL)
            return;

        printLRRoot(parent->left, depth + 1);
        printLRRoot(parent->right, depth + 1);
        for (int i = 0; i < depth; i++)
            cout << '|';
        cout << parent->key << endl;
    }

    //сортированный Left -> Root - > Right
    void printLRootR() {
        printLRootR(root, 0);
    }

    void printLRootR(Node* parent, int depth) {
        if (parent == NULL)
            return;
        
        printLRootR(parent->left, depth + 1);

        for (int i = 0; i < depth; i++)
            cout << '|';
        cout << parent->key << endl;

        printLRootR(parent->right, depth + 1);
    }

    void deleteTree() {
        deleteTree(root);
    }

    void deleteTree(Node* parent) {
        if (parent == NULL)
            return;
        deleteTree(parent->left);
        deleteTree(parent->right);
        delete parent;
    }

    int task() {
        return task(root);
    }

    int task(Node* parent) {
        if (parent == NULL)
            return 0;
        if (parent->left != NULL && parent->right != NULL) {
            return 1 + task(parent->left) + task(parent->right);
        }
        else
            return task(parent->left) + task(parent->right);
    }
};

int main()
{
    Tree* tree = new Tree();

    // init tree
    tree->add(5);
    tree->add(3);
    tree->add(7);
    tree->add(1);
    tree->add(4);
    tree->add(6);
    tree->add(9);
    tree->add(-1);
    tree->add(2);
    tree->add(8);
    tree->add(10);
   
    cout << "Pre-order:" << endl;
    tree->printRootLR();
    cout << endl;

    cout << "Post-order:" << endl;
    tree->printLRRoot();
    cout << endl;

    cout << "Sorted order:" << endl;
    tree->printLRootR();
    cout << endl;

    // task
    int count = tree->task();
    cout << "Roots with 2 children:" << count << "\n\n";

    //find
    Node* node = tree->find(9);
    if (node == NULL)
        cout << "Element not found.\n";
    else
        cout << "Element "<< node->key << " found\n";

    cout << "Tree before deletions:\n";
    tree->printRootLR();
    tree->deleteNode(-1);
    tree->deleteNode(7);
    tree->deleteNode(9);
    tree->deleteNode(10);
    tree->deleteNode(5);

    cout << "\nTree after deletions:\n";
    tree->printRootLR();

    tree->deleteTree();
    delete tree;
}

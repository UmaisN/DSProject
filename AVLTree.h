#pragma once
#include <iostream>
using namespace std;

template<class T>
class Node {
public:
    T key;
    int height;
    Node* left;
    Node* right;
    Node() {
        key = -1;
        left = NULL;
        right = NULL;
        height = 0;
    }
    Node(T value) {
        key = value;
        left = NULL;
        right = NULL;
        height = 0;
    }
};

template<class T>
class AVL
{
public:
    Node<T>* root;

    AVL() {
        root = NULL;
    }
    int max(int a, int b) { //Calculates length of left and right branches
        if (a > b) {
            return a;
        }
        else {
            return b;
        }
    }

    template<class T>
    int getHeight(Node<T>* node) { //Returns height of node
        if (node == NULL) {
            return -1;
        }
        else {
            return node->height;
        }
    }

    template<class T>
    int getBalanceFactor(Node<T>* node) { //getting bf
        return getHeight(node->left) - getHeight(node->right);
    }

    void display() { //Displays Tree
        cout << endl;
        display(root);
        cout << endl;
    }
    
    template<class T>
    void display(Node<T>* start) { //Displays Function Extension
        if (start == NULL) {
            return;
        }
        else {
            display(start->left);
            cout << start->key << ",";
            display(start->right);
        }
    }

    template<class T>
    Node<T>* rightRotate(Node<T>* node) { //Right Rotator, remove comments dashes to check if it is working
        //cout << "Right Rotating node " << node->key << endl;
        Node<T>* n2 = node->left;
        node->left = n2->right;
        n2->right = node;
        n2->height = max(getHeight(n2->left), getHeight(n2->right)) + 1;
        node->height = max(getHeight(node->left), getHeight(node->right))+1;
        //cout << "Returning node " << n2->key << " as Parent" << endl;
        return n2;
    }
    template<class T>
    Node<T>* leftRotate(Node<T>* node) { //Left Rotator, remove comments dashes to check if it is working
        //cout << "Left Rotating node " << node->key << endl;
        Node<T>* n2 = node->right;
        node->right = n2->left;
        n2->left = node;
        n2->height = max(getHeight(n2->left), getHeight(n2->right)) + 1;
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
        //cout << "Returning node " << n2->key << " as Parent" << endl;
        return n2;
    }

    template<class T>
    void insert(T key) { //Inserts data into tree
        root = insert(root, key);
    }
    template<class T>
    Node<T>* insert(Node<T>* start, T key) { //Insert function extension
        if (start == NULL) {
            start = new Node<T>(key);
        }
        else if (key < start->key) {
            start->left = insert(start->left, key);
            int bf = getBalanceFactor(start);
            if (bf == 2 || bf == -2) {
                if (start->left->key > key) {
                    start = rightRotate(start);
                }
            }
        }
        else if (key > start->key) {
            start->right = insert(start->right, key);
            int bf = getBalanceFactor(start);
            if (bf == 2 || bf == -2) {
                if (start->right->key < key) {
                    start = leftRotate(start);
                }
            }
        }
        start->height = max(getHeight(start->left), getHeight(start->right))+1;
        return start;
    }

    //-------------------------------------------------------------------------------
    //Display Modes
    /*
* Inorder Traversal of AVL Tree
*/
    template<class T>
    void inorder(Node<T>* tree)
    {
        if (tree == NULL)
            return;
        inorder(tree->left);
        cout << tree->key << " ";
        inorder(tree->right);
    }
    /*
    * Preorder Traversal of AVL Tree
    */
    template<class T>
    void preorder(Node<T>* tree)
    {
        if (tree == NULL)
            return;
        cout << tree->key << " ";
        preorder(tree->left);
        preorder(tree->right);
    }
    /*
    * Postorder Traversal of AVL Tree
    */
    template<class T>
    void postorder(Node<T>* tree)
    {
        if (tree == NULL)
            return;
        postorder(tree->left);
        postorder(tree->right);
        cout << tree->key << " ";
    }
    //------------------------------------
    //MinVal Node
    template<class T>
    Node<T>* minValueNode(Node<T>* node)
    {
        Node<T>* current = node;

        /* loop down to find the leftmost leaf */
        while (current->left != NULL)
            current = current->left;

        return current;
    }

    //Deletion
    template<class T>
    Node<T>* deleteNode(Node<T>* root, T key)
    {

        // STEP 1: PERFORM STANDARD BST DELETE  
        if (root == NULL)
            return root;

        // If the key to be deleted is smaller  
        // than the root's key, then it lies 
        // in left subtree  
        if (key < root->key)
            root->left = deleteNode(root->left, key);

        // If the key to be deleted is greater  
        // than the root's key, then it lies  
        // in right subtree  
        else if (key > root->key)
            root->right = deleteNode(root->right, key);

        // if key is same as root's key, then  
        // This is the node to be deleted  
        else
        {
            // node with only one child or no child  
            if ((root->left == NULL) ||
                (root->right == NULL))
            {
                Node<T>* temp = root->left ?
                    root->left :
                    root->right;

                // No child case  
                if (temp == NULL)
                {
                    temp = root;
                    root = NULL;
                }
                else // One child case  
                    *root = *temp; // Copy the contents of  
                                   // the non-empty child  
                free(temp);
            }
            else
            {
                // node with two children: Get the inorder  
                // successor (smallest in the right subtree)  
                Node<T>* temp = minValueNode(root->right);

                // Copy the inorder successor's  
                // data to this node  
                root->key = temp->key;

                // Delete the inorder successor  
                root->right = deleteNode(root->right,
                    temp->key);
            }
        }

        // If the tree had only one node 
        // then return  
        if (root == NULL)
            return root;

        // STEP 2: UPDATE HEIGHT OF THE CURRENT NODE  
        root->height = 1 + max(getHeight(root->left),
            getHeight(root->right));

        // STEP 3: GET THE BALANCE FACTOR OF  
        // THIS NODE (to check whether this  
        // node became unbalanced)  
        int balance = getBalanceFactor(root);

        // If this node becomes unbalanced,  
        // then there are 4 cases  

        // Left Left Case  
        if (balance > 1 &&
            getBalanceFactor(root->left) >= 0)
            return rightRotate(root);

        // Left Right Case  
        if (balance > 1 &&
            getBalanceFactor(root->left) < 0)
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        // Right Right Case  
        if (balance < -1 &&
            getBalanceFactor(root->right) <= 0)
            return leftRotate(root);

        // Right Left Case  
        if (balance < -1 &&
            getBalanceFactor(root->right) > 0)
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }
    ~AVL() {
        delete root;
    }
};
#pragma once
#include <iostream>
using namespace std;

template<class T, class S>
class Node {
public:
    S data;
    T key;
    int height;
    Node* left;
    Node* right;
    Node() {
        data = NULL;
        key = -1;
        left = NULL;
        right = NULL;
        height = 0;
    }
    Node(T value, S dat) {
        data = dat;
        key = value;
        left = NULL;
        right = NULL;
        height = 0;
    }
};

template<class T,class S>
class AVL
{
public:
    Node<T,S>* root;
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

    template<class T,class S>
    int getHeight(Node<T,S>* node) { //Returns height of node
        if (node == NULL) {
            return -1;
        }
        else {
            return node->height;
        }
    }

    template<class T,class S>
    int getBalanceFactor(Node<T,S>* node) { //getting bf
        return getHeight(node->left) - getHeight(node->right);
    }

    void display() { //Displays Tree
        cout << endl;
        display(root);
        cout << endl;
    }
    
    template<class T,class S>
    void display(Node<T,S>* start) { //Displays Function Extension
        if (start == NULL) {
            return;
        }
        else {
            display(start->left);
            cout << "(";
            cout << start->key << ",";
            cout << start->data << "),";
            display(start->right);
        }
    }

    template<class T,class S>
    Node<T,S>* rightRotate(Node<T,S>* node) { //Right Rotator, remove comments dashes to check if it is working
        //cout << "Right Rotating node " << node->key << endl;
        Node<T,S>* n2 = node->left;
        node->left = n2->right;
        n2->right = node;
        n2->height = max(getHeight(n2->left), getHeight(n2->right)) + 1;
        node->height = max(getHeight(node->left), getHeight(node->right))+1;
        //cout << "Returning node " << n2->key << " as Parent" << endl;
        return n2;
    }
    template<class T,class S>
    Node<T,S>* leftRotate(Node<T,S>* node) { //Left Rotator, remove comments dashes to check if it is working
        //cout << "Left Rotating node " << node->key << endl;
        Node<T,S>* n2 = node->right;
        node->right = n2->left;
        n2->left = node;
        n2->height = max(getHeight(n2->left), getHeight(n2->right)) + 1;
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
        //cout << "Returning node " << n2->key << " as Parent" << endl;
        return n2;
    }

    /* How should you be inserting in main?
        AVL<int> obj;
	    obj.root = obj.insert(obj.root, 1);
	    obj.root = obj.insert(obj.root, 2);
	    obj.root = obj.insert(obj.root, 3);
	    obj.preorder(obj.root);
	    cout << endl;
                                                */

    template<class T,class S>
    void insert(T key,S data) 
    { //Inserts data into tree
        root = insert(root, key,data);
    }
    template<class T,class S>
    Node<T,S>* insert(Node<T,S>* start, T key,S data) { //Insert function extension
        if (start == NULL) {
            start = new Node<T,S>(key,data);
        }
        else if (key < start->key) {
            start->left = insert(start->left, key,data);
            int bf = getBalanceFactor(start);
            if (bf == 2 || bf == -2) {
                if (start->left->key > key) {
                    start = rightRotate(start);
                }
            }
        }
        else if (key > start->key) {
            start->right = insert(start->right, key,data);
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
    template<class T,class S>
    void inorder(Node<T,S>* tree)
    {
        if (tree == NULL)
            return;
        inorder(tree->left);
        cout << "(";
        cout << tree->key << "," << tree->data << ") ";
        inorder(tree->right);
    }
    /*
    * Preorder Traversal of AVL Tree
    */
    template<class T,class S>
    void preorder(Node<T,S>* tree)
    {
        if (tree == NULL)
            return;
        cout << "(";
        cout << tree->key << "," << tree->data << ") ";
        preorder(tree->left);
        preorder(tree->right);
    }
    /*
    * Postorder Traversal of AVL Tree
    */
    template<class T,class S>
    void postorder(Node<T,S>* tree)
    {
        if (tree == NULL)
            return;
        postorder(tree->left);
        postorder(tree->right);
        cout << "(";
        cout << tree->key << "," << tree->data << ") ";
    }
    //------------------------------------
    //MinVal Node
    template<class T,class S>
    Node<T,S>* minValueNode(Node<T,S>* node)
    {
        Node<T,S>* current = node;

        /* loop down to find the leftmost leaf */
        while (current->left != NULL)
            current = current->left;

        return current;
    }

    /*How should you be deleting in main?
       	obj.root = obj.deleteNode(obj.root, 11);
	    obj.root = obj.deleteNode(obj.root, 10);
	    obj.root = obj.deleteNode(obj.root, 9);
	    obj.root = obj.deleteNode(obj.root, 6);
	    obj.preorder(obj.root);
	    cout << endl; 
                                                    */

    template<class T>
    void deleteNode(T key) { //Deletes data from tree
        root = deleteNode(root, key);
    }

    //Delete Node Extension
    template<class T,class S>
    Node<T,S>* deleteNode(Node<T,S>* root, T key)
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
                Node<T,S>* temp = root->left ?
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
                Node<T,S>* temp = minValueNode(root->right);

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

    //Search Function
    template <class T,class S>
    Node<T,S>* searchNode(T key) {
        Node<T,S>* trav = root;
        while (trav != nullptr)
        {
            if (trav->key == key)
            {
                return trav;
            }
            else if (key < trav->key)
            {
                trav = trav->left;
            }
            else
            {
                trav = trav->right;
            }
        }
        return nullptr;
    }

    ~AVL() {
        delete root;
    }
};
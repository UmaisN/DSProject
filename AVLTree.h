#pragma once
#include "LinkedList.h"
#include "InfInt.h"
#include "Hashing.h"
#include <iostream>
using namespace std;

//Function to return ascii of a string
int string_ascii(string str)
{
    int sum = 0; //variable to hold sum of ascii's

    int length = str.length();//getting length of the string

    int mul = 1;//multiplicand

    //Loop runs until string ends
    for (int c = 0; c < length; ++c)
    {
        int tmp = str[c] * mul;//multiplying ascii with the characters position
        sum += tmp;

        mul++;//incrementing multiplicand
    }

    return sum; //sum of ascii returned
}


template<class T, class S>
class Node {
public:
    S data;
    T key;
    S original_key;
    int height;
    InfInt hashed_key;//infint variable to store hashed key of node

    int line_no;  //variable to store the line number at which the data is stored

    Node* left;
    Node* right;

    Node* next;  //pointer to point to linked list of duplicates

    Node() {
        data = NULL;
        key = -1;
        left = NULL;
        right = NULL;
        height = 0;
    }
    Node(S value, S dat, InfInt hash_k) {
        data = dat;
        original_key = value;
        key = string_ascii(value); //storing ascii of original_key in key
        //hashed_key = hash_value(value,)
        left = NULL;
        right = NULL;
        height = 0;
        hashed_key = hash_k;
    }

    //Function to link nodes with a similar key
    void add_duplicate(S key1, S data, InfInt hash_k)
    {
        T ascii_sum = string_ascii(key1);//storing ascii of new entry

        //duplicate only added if keys of both nodes match
        if (this->key == ascii_sum)
        {
            Node<T, S>* nodeptr = new Node(key1, data, hash_k);//new node created 

            Node<T, S>* ptr = this;//ptr for loop
            Node<T, S>* ptr2 = NULL;

            //This loop iterates over linked list of duplicates until end is reached
            while (ptr != NULL)
            {
                ptr2 = ptr;
                ptr = ptr->next;
            }

            //New node is inserted at the end of the linked list

            ptr2->next = nodeptr;//duplicate node linked to this node
        }
    }

    string display()
    {
        string str;  //string to store info of node, if duplicates exists then their info will also be appended

        str.push_back('(');
        str.append(this->original_key);//eppending info og current data
        str.push_back(',');
        str.append(this->data);
        str.push_back(')');

        //Now iterating over linked list of duplicates(nodes with similar keys) if they exist

        Node<T, S>* nodeptr = next;//initializing nodeptr with next pointer

        while (nodeptr != NULL)
        {
            str.append(" , ");
            str.push_back('(');
            str.append(nodeptr->original_key);
            str.push_back(',');
            str.append(nodeptr->data);
            str.push_back(')');

            nodeptr = nodeptr->next;
        }

        return str;
    }

};

template<class T, class S>
class AVL
{
private:
    int ID_space;
    string file_name;//every avl has its own unique file to store data in
public:
    Node<T, S>* root;
    AVL() {
        root = NULL;
        ID_space = -1;
        file_name = "";
    }
    void set_IDspace(int id_sp)
    {
        ID_space = id_sp;
    }

    int max(int a, int b) { //Calculates length of left and right branches
        if (a > b) {
            return a;
        }
        else {
            return b;
        }
    }

    //template<class T,class S>
    int getHeight(Node<T, S>* node) { //Returns height of node
        if (node == NULL) {
            return -1;
        }
        else {
            return node->height;
        }
    }

    // template<class T,class S>
    int getBalanceFactor(Node<T, S>* node) { //getting bf
        return getHeight(node->left) - getHeight(node->right);
    }

    void display() { //Displays Tree
        cout << endl;
        display(root);
        cout << endl;
    }

    //template<class T,class S>
    void display(Node<T, S>* start) { //Displays Function Extension
        if (start == NULL) {
            return;
        }
        else {
            display(start->left);
            cout << "(";
            cout << start->key << ",";
            cout << start->original_key << ",";
            cout << start->data << "),";
            display(start->right);
        }
    }

    //template<class T,class S>
    Node<T, S>* rightRotate(Node<T, S>* node) { //Right Rotator, remove comments dashes to check if it is working
        //cout << "Right Rotating node " << node->key << endl;
        Node<T, S>* n2 = node->left;
        node->left = n2->right;
        n2->right = node;
        n2->height = max(getHeight(n2->left), getHeight(n2->right)) + 1;
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
        //cout << "Returning node " << n2->key << " as Parent" << endl;
        return n2;
    }
    //template<class T,class S>
    Node<T, S>* leftRotate(Node<T, S>* node) { //Left Rotator, remove comments dashes to check if it is working
        //cout << "Left Rotating node " << node->key << endl;
        Node<T, S>* n2 = node->right;
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

                                                // template<class T,class S>
    void insert(S key, S data)
    { //Inserts data into tree
        root = insert(root, key, data);
    }
    //  template<class T,class S>
    Node<T, S>* insert(Node<T, S>* start, S key1, S data) { //Insert function extension

        T key = string_ascii(key1);

        InfInt hash_k = hash_value(key1, ID_space);//getting hash of key

        if (start == NULL) {
            start = new Node<T, S>(key1, data, hash_k);
        }
        else if (key < start->key) {
            start->left = insert(start->left, key1, data);
            int bf = getBalanceFactor(start);
            if (bf == 2 || bf == -2) {
                if (start->left->key > key) {
                    start = rightRotate(start);
                }
            }
        }
        else if (key > start->key) {
            start->right = insert(start->right, key1, data);
            int bf = getBalanceFactor(start);
            if (bf == 2 || bf == -2) {
                if (start->right->key < key) {
                    start = leftRotate(start);
                }
            }
        }
        else
        {
            //start.duplictae
            start->add_duplicate(key1, data, hash_k);
        }

        start->height = max(getHeight(start->left), getHeight(start->right)) + 1;
        return start;
    }

    //-------------------------------------------------------------------------------
    //Display Modes
    /*
* Inorder Traversal of AVL Tree
*/
// template<class T,class S>
    void inorder(Node<T, S>* tree)
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
    //template<class T,class S>
    void preorder(Node<T, S>* tree)
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
    // template<class T,class S>
    void postorder(Node<T, S>* tree)
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
   // template<class T,class S>
    Node<T, S>* minValueNode(Node<T, S>* node)
    {
        Node<T, S>* current = node;

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

                                                    // template<class T>
    void deleteNode(S key) { //Deletes data from tree

        T key1 = string_ascii(key);

        root = deleteNode(root, key1);
    }

    //Delete Node Extension..
    //template<class T,class S>
    Node<T, S>* deleteNode(Node<T, S>* root, T key)
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
                Node<T, S>* temp = root->left ?
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
                Node<T, S>* temp = minValueNode(root->right);

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
    //template <class T,class S>
    Node<T, S>* searchNode(S key1) {

        T key = string_ascii(key1);//getting ascii value of searched key

        Node<T, S>* trav = root;
        while (trav != nullptr)
        {
            if (trav->key == key)
            {

                //cout << trav->key << " " << trav->original_key << " " << trav->data << endl;
                //This was witten just to check functionality of search function
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
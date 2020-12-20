#pragma once
#include"AVLTree.h"
#include"Hashing.h"
#include<iostream>
using namespace std;

//First Creating a Machine node 
template<class T, class S>
class Machine_node
{
private:

	InfInt ID;			//Every machine has a Unique ID
	string Hex_ID;		//Variable to store Unique ID's hexa form

	AVL<T, S> Data_Tree;//An AVL tree to index keys and stores associated data alongside

	//F_Table FT; //Routing table to maintain address/pointers to other machine nodes.
			//Each routing table entry [i] contains the shortcut / pointer to the distant node.

public:

};

//Defining Finger Table node class 
template<class T, class S>
class FT_node
{
private:

	Machine_node<T, S>* Machine_ptr;//Each node will have a pointer to a machine node



	Machine_node<T, S>* next;//pointer to next machine in linked list
	Machine_node<T, S>* prev;//pointer to previous machine in linked list

public:


};



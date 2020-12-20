#pragma once
#include"AVLTree.h"
#include"Hashing.h"
#include<iostream>
using namespace std;

//Writing class prototype before Machine node class
template<class T, class S>
class F_Table;

//First Creating a Machine node 
template<class T, class S>
class Machine_node
{
private:

	InfInt ID;			//Every machine has a Unique ID

	AVL<T, S> Data_Tree;//An AVL tree to index keys and stores associated data alongside

	F_Table<T, S> FT; //Routing table to maintain address/pointers to other machine nodes.
			//Each routing table entry [i] contains the shortcut / pointer to the distant node.

	Machine_node<T, S>* next;//pointer to next machine for circular linked list in DHT 

public:

	Machine_node() 
	{
		ID = -1;//by default ID of a mchine will be -1
				//will change when a new ID is assigned

		next = NULL;
	}

};

//Now declaring Distributed Hash table class(DHT)
template<class T, class S>
class DHT
{
private:
	//Since we will have a circular singly linked list of Machines, we are only required to have a head.
	
	Machine_node<T, S> head;//head of linked list declared here.

public:

	DHT() 
	{
		head = NULL;
	}


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

	FT_node() 
	{
		Machine_ptr = NULL;
		next = NULL;
		prev = NULL;
	}
};


//Defining Finger Table class which is a doubly linked list of FT_nodes
template<class T, class S>
class F_Table 
{
private:
	FT_node<T, S>* head; //head of linked list
	FT_node<T, S>* tail; //tail of linked list
public:

	F_Table() 
	{
		head = NULL;
		tail = NULL;
	}

};



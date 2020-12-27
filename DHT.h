#pragma once
#include"AVLTree.h"
#include"Hashing.h"
#include"InfInt.h"
#include<ctime>
#include<cmath>
#include<iostream>
#include<fstream>
using namespace std;

//Writing class prototype before Machine node class
template<class T, class S>
class F_Table;

//Writing class prototype of Distributed Hash table (DHT) before defining Machine node class
template<class T, class S>
class DHT;

//First Creating a Machine node 
template<class T, class S>
class Machine_node
{
public:

	string ID_str;   //string ID which user entered

	InfInt ID;			//Every machine has a Unique ID

	int ID_space;    //variable to store identifier space 

	AVL<T, S> Data_Tree;//An AVL tree to index keys and stores associated data alongside

	F_Table<T, S> FT; //Routing table to maintain address/pointers to other machine nodes.
			//Each routing table entry [i] contains the shortcut / pointer to the distant node.

	Machine_node<T, S>* next;//pointer to next machine for circular singly linked list in DHT 
	Machine_node<T, S>* prev;
	//-----------------------------defining functions-------------------------------//

	Machine_node()
	{
		ID = -1;//by default ID of a mchine will be -1
				//will change when a new ID is assigned

		ID_space = -1;

		next = NULL;
		prev = NULL;
	}

	//Paramterized constructor which takes machine's id as string, its Hahsed ID and the Identifier space bits
	Machine_node(string machine_id, InfInt id, int id_space)
	{
		ID_space = id_space;  //setting id space

		ID_str = machine_id;

		ID = id;//hashed iD is stored in "ID"


		//appending strings to make filename
		string filestr = "";

		if (machine_id == "")//creating unique string machines with empty string
		{

			for (InfInt c = 0; c < ID; ++c) //loop to create a unique string for every machine file
			{
				filestr += 1;
			}
			filestr.append("Machine ");
			filestr.append(filestr);
			filestr.append(".txt");

		}
		else
		{
			filestr.append(ID_str);
			filestr.append(".txt");
		}

		//------------------------------------------------------------------------------------------------//

		//->Creating a new file so that if there was a file with a similar name before it would be deleted.

		ofstream file(filestr, ios::out);
		file.close();//closing file

		//------------------------------------------------------------------------------------------------//

		Data_Tree.set_AVL_specs(filestr, ID_space);//setting AVL tree specs(i.e. filename and ID space)

		next = NULL;//initializing next pointer to NULL
		prev = NULL;
	}

	//Function to insert data in machine
	void insert(S key, S Data)
	{
		this->Data_Tree.insert(key, Data);//calling AVL tree insert function
	}

	//Function to display all the Data of the AVL Tree
	void display_data()
	{
		this->Data_Tree.display();//calling AVL tree display function
	}

	//Function to update finger table of Machine node, takes DHT object as paramter
	void update_FT(DHT<T, S> machine_list)
	{
		this->FT.Update_F_Table(machine_list, this->ID);//caliing function of F_Table
	}

};

//Now declaring Distributed Hash table class(DHT)
template<class T, class S>
class DHT
{
private:
	//Since we will have a circular singly linked list of Machines, we are only required to have a head.

	Machine_node<T, S>* head;//head of linked list declared here.
	Machine_node<T, S>* tail;

	int ID_space;        //variable to hold number of bits of Identifier space

	//-------------------------------------------------------------------------------------------------//
	//->Making Machine_node & F_Table a friend class so they can have access to DHT's private members
	//->The pusrpose of doing this is so that both these classes can access Machine linked list of DHT.
	friend class F_Table<T, S>;
	friend class Machine_node<T, S>;
	//-------------------------------------------------------------------------------------------------//

	//-------------------------PRIVATE MEMBER FUNCTION----------------------------------//
	//Function to display all machines
	void Update_Finger_Tables()
	{
		Machine_node<T, S>* nodeptr = head;//pointer to iterate over linked list of machines

		bool loop_flag = false;//Flag variable to make sure loop doesnt iterarte more than once over the list
							   //because its a circular list

		while (nodeptr != head || loop_flag == false)
		{
			nodeptr->FT.clear_FT();

			nodeptr->update_FT(*this);


			//Updating condition variables
			nodeptr = nodeptr->next;
			loop_flag = true;
		}
	}
	//----------------------------------------------------------------------------------//

	//Function to check repeatition of hash ID 
	//If it repeats it returns true else false
	bool check_ID(InfInt hash_ID)
	{
		if (this->head != NULL)
		{
			Machine_node<T, S>* nodeptr = head;//pointer to iterate over linked list of machines

			bool loop_flag = false;//Flag variable to make sure loop doesnt iterarte more than once over the list
						   //because its a circular list

			while (nodeptr != head || loop_flag == false)
			{
				if (nodeptr->ID == hash_ID)
				{
					return true;//True returned on finding a match
				}

				nodeptr = nodeptr->next;
				loop_flag = true;
			}
		}

		return false;//if no match found false returned.
	}

	//Function to check repeatition of hash ID 
	//If it repeats it returns true else false
	Machine_node<T, S>* search_ID(InfInt hash_ID)
	{
		if (this->head != NULL)
		{
			Machine_node<T, S>* nodeptr = head;//pointer to iterate over linked list of machines

			bool loop_flag = false;//Flag variable to make sure loop doesnt iterarte more than once over the list
						   //because its a circular list

			while (nodeptr != head || loop_flag == false)
			{
				if (nodeptr->ID == hash_ID)
				{
					return nodeptr;//ptr returned on finding a match
				}

				nodeptr = nodeptr->next;
				loop_flag = true;
			}
		}

		return NULL;//if no match found NULL returned.
	}


	//This function takes machine node pointer and key value pair,
	//Insertion can be done from any machine.
	//(Finger table used to navigate to correct machine).
	void machine_insertdata(Machine_node<T, S>* mach_node, S str_key, S str_data)
	{
		cout << "->Query arrived at " << mach_node->ID_str << "(" << mach_node->ID << ")." << endl;

		InfInt hash_str = hash_value(str_key, this->ID_space);//hashing the key and storing its value to match with machine ID hash

		//--------------------------------FINDING SIZE OF FT TABLE--------------------------------------------//

		//Storing maximium number of machines which can be registered on DHT by doing 2^ID_space.
		static InfInt total_machines = InfIntpow(2, this->ID_space);

		//Variable to store total number of FT entries which will be log2(total_machines).
		static InfInt FT_size = log2(total_machines);

		//---------------------------------------------------------------------------------------------------//

		int index = 1;


		for (InfInt c = 0; c < FT_size; ++c) //Looping over FT linked list
		{
			//nodeptr = mach_node->FT.get_at(index);//retrieving machine node at the FT table of mach_node.

			InfInt x = index;
			if (x == FT_size - 1)
			{	//If loop reaches last index then query is forwarded to last index
				machine_insertdata(mach_node->FT.get_at(index), str_key, str_data);

				return;
			}
			else if (hash_str > mach_node->ID && mach_node->next == this->head)
			{
				cout << "Data inserted at " << mach_node->ID_str << "(" << mach_node->ID << ")." << endl;

				mach_node->insert(str_key, str_data);//Key value pair inserted at the machine

				return;
			}
			//If inserted keys hash is equal to mach_node ID then its inserted on the machine
			else if (hash_str == mach_node->ID || mach_node == mach_node->next)
			{
				cout << "Data inserted at " << mach_node->ID_str << "(" << mach_node->ID << ")." << endl;

				mach_node->insert(str_key, str_data);//Key value pair inserted at the machine

				return;
			}
			else if (hash_str > mach_node->ID && hash_str <= mach_node->FT.get_at(1)->ID)
			{	//p < eand e <= FTp[1].In this case, the search request is forwarded to the machine
				//	FTp[1], i.e., first entry of routing table entry.

				Machine_node<T, S>* tmp = mach_node->FT.get_at(1);//setting tmp pointer to FTp[1].

				//inserting data at Ftp[1].
				cout << "->Query arrived at " << tmp->ID_str << "(" << tmp->ID << ")." << endl;
				cout << "Data inserted at " << tmp->ID_str << "(" << tmp->ID << ")." << endl;

				tmp->insert(str_key, str_data);

				return;
			}
			else if (hash_str > mach_node->FT.get_at(index)->ID && hash_str <= mach_node->FT.get_at(index + 1)->ID)
			{
				//FTp[j] < e <= FTp[ j+1]. In this case the search request is forwarded to the machine FTp[j].

				machine_insertdata(mach_node->FT.get_at(index), str_key, str_data);

				return;
			}


			index++;
		}

	}

	//This function takes machine node pointer and key value pair,
	//Insertion can be done from any machine.
	//(Finger table used to navigate to correct machine).
	void machine_searchdata(Machine_node<T, S>* mach_node, S str_key)
	{
		cout << "->Query arrived at " << mach_node->ID_str << "(" << mach_node->ID << ")." << endl;

		InfInt hash_str = hash_value(str_key, this->ID_space);//hashing the key and storing its value to match with machine ID hash

		//--------------------------------FINDING SIZE OF FT TABLE--------------------------------------------//

		//Storing maximium number of machines which can be registered on DHT by doing 2^ID_space.
		static InfInt total_machines = InfIntpow(2, this->ID_space);

		//Variable to store total number of FT entries which will be log2(total_machines).
		static InfInt FT_size = log2(total_machines);

		//---------------------------------------------------------------------------------------------------//

		int index = 1;


		for (InfInt c = 0; c < FT_size; ++c) //Looping over FT linked list
		{
			//nodeptr = mach_node->FT.get_at(index);//retrieving machine node at the FT table of mach_node.

			InfInt x = index;
			if (x == FT_size - 1)
			{	//If loop reaches last index then query is forwarded to last index
				machine_searchdata(mach_node->FT.get_at(index), str_key);

				return;
			}

			//If inserted keys hash is equal to mach_node ID then its inserted on the machine
			else if (hash_str == mach_node->ID)
			{
				cout << "->Looking for searched key at " << mach_node->ID_str << "(" << mach_node->ID << ")." << endl;

				Node<T, S>* search = mach_node->Data_Tree.searchNode(str_key);//searching given key at AVL of mach node

				if (search == NULL)
				{
					cout << "\nYour search did not match any Key in data ! " << endl;
				}
				else
				{
					cout << "\nSEARCHED MACTHED !\n\nData : \n\n";
					cout << search->display();//if search found then AVL node info is displayed
					cout << endl;
				}

				return;
			}
			else if (hash_str > mach_node->ID && hash_str <= mach_node->FT.get_at(1)->ID)
			{	//p < eand e <= FTp[1].In this case, the search request is forwarded to the machine
				//	FTp[1], i.e., first entry of routing table entry.

				Machine_node<T, S>* tmp = mach_node->FT.get_at(1);//setting tmp pointer to FTp[1].

				//inserting data at Ftp[1].
				cout << "->Query arrived at " << tmp->ID_str << "(" << tmp->ID << ")." << endl;
				cout << "->Looking for searched key at " << tmp->ID_str << "(" << tmp->ID << ")." << endl;

				Node<T, S>* search = tmp->Data_Tree.searchNode(str_key);//searching given key at AVL of mach node

				if (search == NULL)
				{
					cout << "\nYour search did not match any Key in data ! " << endl;
				}
				else
				{
					cout << "\nSEARCHED MACTHED !\n\nData : \n\n";
					cout << search->display();//if search found then AVL node info is displayed
					cout << endl;
				}
				return;
			}
			else if (hash_str > mach_node->FT.get_at(index)->ID && hash_str <= mach_node->FT.get_at(index + 1)->ID)
			{
				//FTp[j] < e <= FTp[ j+1]. In this case the search request is forwarded to the machine FTp[j].

				machine_searchdata(mach_node->FT.get_at(index), str_key);

				return;
			}


			index++;
		}

	}

	//This function takes machine node pointer and key ,
	//Insertion can be done from any machine.
	//(Finger table used to navigate to correct machine).
	void machine_removedata(Machine_node<T, S>* mach_node, S str_key)
	{
		cout << "->Query arrived at " << mach_node->ID_str << "(" << mach_node->ID << ")." << endl;

		InfInt hash_str = hash_value(str_key, this->ID_space);//hashing the key and storing its value to match with machine ID hash

		//--------------------------------FINDING SIZE OF FT TABLE--------------------------------------------//

		//Storing maximium number of machines which can be registered on DHT by doing 2^ID_space.
		static InfInt total_machines = InfIntpow(2, this->ID_space);

		//Variable to store total number of FT entries which will be log2(total_machines).
		static InfInt FT_size = log2(total_machines);

		//---------------------------------------------------------------------------------------------------//

		int index = 1;


		for (InfInt c = 0; c < FT_size; ++c) //Looping over FT linked list
		{
			//nodeptr = mach_node->FT.get_at(index);//retrieving machine node at the FT table of mach_node.

			InfInt x = index;
			if (x == FT_size - 1)
			{	//If loop reaches last index then query is forwarded to last index
				machine_removedata(mach_node->FT.get_at(index), str_key);

				return;
			}

			//If inserted keys hash is equal to mach_node ID then its inserted on the machine
			else if (hash_str == mach_node->ID)
			{
				cout << "->Looking for searched key at " << mach_node->ID_str << "(" << mach_node->ID << ")." << endl;

				Node<T, S>* search = mach_node->Data_Tree.searchNode(str_key);//searching given key at AVL of mach node

				if (search == NULL)
				{
					cout << "\nYour search did not match any Key in data ! " << endl;
				}
				else
				{
					cout << "\nKEY MACTHED !\n\nData : \n\n";
					cout << search->display();//if search found then AVL node info is displayed
					cout << endl;
					mach_node->Data_Tree.deleteNode(str_key);//now deleting
					cout << "\nKey deleted successfully !" << endl;
				}

				return;
			}
			else if (hash_str > mach_node->ID && hash_str <= mach_node->FT.get_at(1)->ID)
			{	//p < eand e <= FTp[1].In this case, the search request is forwarded to the machine
				//	FTp[1], i.e., first entry of routing table entry.

				Machine_node<T, S>* tmp = mach_node->FT.get_at(1);//setting tmp pointer to FTp[1].

				//inserting data at Ftp[1].
				cout << "->Query arrived at " << tmp->ID_str << "(" << tmp->ID << ")." << endl;
				cout << "->Looking for searched key at " << tmp->ID_str << "(" << tmp->ID << ")." << endl;

				Node<T, S>* search = tmp->Data_Tree.searchNode(str_key);//searching given key at AVL of mach node

				if (search == NULL)
				{
					cout << "\nYour search did not match any Key in data ! " << endl;
				}
				else
				{
					cout << "\nKEY MACTHED !\n\nData : \n\n";
					cout << search->display();//if search found then AVL node info is displayed
					cout << endl;
					tmp->Data_Tree.deleteNode(str_key);//now deleting
					cout << "\nKey deleted successfully !" << endl;
				}
				return;
			}
			else if (hash_str > mach_node->FT.get_at(index)->ID && hash_str <= mach_node->FT.get_at(index + 1)->ID)
			{
				//FTp[j] < e <= FTp[ j+1]. In this case the search request is forwarded to the machine FTp[j].

				machine_removedata(mach_node->FT.get_at(index), str_key);

				return;
			}


			index++;
		}

	}


	//--------------------------------------------------------------------------------------------------------//

	//This function will take two parameters.
	//FIRST PARAMETER  = Old machine node's avl tree root.
	//SECOND PARAMETER = AVL tree obj of old machine.
	//THIRD PARAMETER  = Newly added machine's node pointer.
	//FOURTH PARAMETER = Old machine's node pointer.
	void insert_postorder(Node<T, S>*& tree_node, AVL<T, S>& tree, Machine_node<T, S>*& new_mach, Machine_node<T, S>*& old_mach)
	{
		if (tree_node == NULL)
			return;

		insert_postorder(tree_node->left, tree, new_mach, old_mach);
		insert_postorder(tree_node->right, tree, new_mach, old_mach);


		if (tree_node->hashed_key <= new_mach->ID && tree_node->hashed_key > old_mach->ID)
		{

			new_mach->insert(tree_node->original_key, tree_node->data);//inserting in new machine

			tree.deleteNode(tree_node->original_key);//deleting current node from old machine
		}

	}

	//This Function takes two neighboring machine node pointers as Paremeters and balances their AVL trees
	//The first parametr in this case is the newly inserted node which will get its appropriate data from next 
	//machine node, which supposedly has its data.-----------------------------------------------------------//
	void update_trees_insert(Machine_node<T, S>* mach_node1, Machine_node<T, S>* mach_node2)
	{	//(new_mach, new_mach->next);

		if (mach_node1 != mach_node1->next)
			this->insert_postorder(mach_node2->Data_Tree.root, mach_node2->Data_Tree, mach_node1, mach_node2);
	}
	//---------------------------------------------------------------------------------------------------------//
	//This function will take two parameters.
	//FIRST PARAMETER  = Deleted machine node's avl tree root.
	//SECOND PARAMETER = AVL tree obj of old machine.
	//THIRD PARAMETER  = Newly added machine's node pointer.
	//FOURTH PARAMETER  = Old machine's node pointer.
	void delete_postorder(Node<T, S>*& tree_node, AVL<T, S>& tree, Machine_node<T, S>*& next_mach, Machine_node<T, S>*& old_mach)
	{
		if (tree_node == NULL)
			return;

		delete_postorder(tree_node->left, tree, next_mach, old_mach);
		delete_postorder(tree_node->right, tree, next_mach, old_mach);

		//All data on the old node(Node to be deleted) will be pushed to the next neighboring node
		//and will be deleted from here.

		next_mach->insert(tree_node->original_key, tree_node->data);//Inserting in new machine.

		tree.deleteNode(tree_node->original_key);//Deleting current node from old machine.

	}

public:

	DHT()
	{
		head = NULL;
		tail = NULL;
		cout << "hello" << endl;
	}

	DHT(int id_space)
	{
		head = NULL;
		tail = NULL;
		this->ID_space = id_space;
	}


	//This function is public and takes machine ID string to insert data in system from any machine.
	//Takes key, value pairs as a parameter.
	void insert_from_machine(string machine_id, string str_key, string str_data)
	{
		InfInt hash_key = hash_value(machine_id, this->ID_space);//hashing the given ID of Machine

		Machine_node<T, S>* mach_ptr = this->search_ID(hash_key);//looking for derived hash key in Machine List

		//If machine with the given ID is found then Insertion starts from their
		if (mach_ptr != NULL)
		{
			//Recursive function called which looks for the right
			//right machine to add data to, but the search starts from the
			//given machine.
			this->machine_insertdata(mach_ptr, str_key, str_data);

		}
		else
		{
			//If mach_ptr == NULL, it means search in Machine list failed to locate any machine with given ID
			//Therefore prompt user that no Machine exists with that Data

			cout << "No Machine registered with the given ID" << endl;
		}
	}

	//This function is public and takes machine ID string to insert data in system from any machine.
	//Takes key, value pairs as a parameter.
	void delete_machine(string machine_id)
	{
		InfInt hash_key = hash_value(machine_id, this->ID_space);//hashing the given ID of Machine

		Machine_node<T, S>* mach_ptr = this->search_ID(hash_key);//looking for derived hash key in Machine List

		//If there is only one machine in system then no need to adjust AVL
		if (mach_ptr == mach_ptr->next)
		{
			//delete mach_ptr;
			mach_ptr = NULL;
			this->head = NULL;
		}
		//If machine with the given ID is found then deletion starts from their
		else if (mach_ptr != NULL)
		{
			//Recursive function called which looks for the right
			//right machine to delete from DHT
			this->delete_postorder(mach_ptr->Data_Tree.root, mach_ptr->Data_Tree, mach_ptr->next, mach_ptr);

			//Now that AVL data has been moved to the next machine's data.
			//We will remove mach_ptr from linked list
			Machine_node<T, S>* nodeptr = this->head;

			//Iterating over machine linked list.
			while (nodeptr->next != this->head)
			{
				//Creating a link between mach->prev and mach->next
				if (nodeptr->next == mach_ptr)
				{
					nodeptr->next = mach_ptr->next; //link made, and mach_ptr removed from list
					break;
				}
			}
		}
		else
		{
			//If mach_ptr == NULL, it means search in Machine list failed to locate any machine with given ID
			//Therefore prompt user that no Machine exists with that Data

			cout << "No Machine registered with the given ID" << endl;
		}
	}

	//This function is public and takes machine ID string to seacrh data in system from any machine.
	//Takes key as a parameter.
	void search_from_machine(string machine_id, string str_key)
	{
		InfInt hash_key = hash_value(machine_id, this->ID_space);//hashing the given ID of Machine

		Machine_node<T, S>* mach_ptr = this->search_ID(hash_key);//looking for derived hash key in Machine List

		//If machine with the given ID is found then Insertion starts from their
		if (mach_ptr != NULL)
		{
			//Recursive function called which looks for the right
			//right machine to add data to, but the search starts from the
			//given machine.
			this->machine_searchdata(mach_ptr, str_key);

		}
		else
		{
			//If mach_ptr == NULL, it means search in Machine list failed to locate any machine with given ID
			//Therefore prompt user that no Machine exists with that Data

			cout << "No Machine registered with the given ID" << endl;
		}
	}

	//This function is public and takes machine ID string to remove data in system from any machine.
	//Takes key as a parameter.
	void remove_from_machine(string machine_id, string str_key)
	{
		InfInt hash_key = hash_value(machine_id, this->ID_space);//hashing the given ID of Machine

		Machine_node<T, S>* mach_ptr = this->search_ID(hash_key);//looking for derived hash key in Machine List

		//If machine with the given ID is found then Insertion starts from their
		if (mach_ptr != NULL)
		{
			//Recursive function called which looks for the right
			//right machine to add data to, but the search starts from the
			//given machine.
			this->machine_removedata(mach_ptr, str_key);

		}
		else
		{
			//If mach_ptr == NULL, it means search in Machine list failed to locate any machine with given ID
			//Therefore prompt user that no Machine exists with that Data

			cout << endl;
			cout << "No Machine registered with the given ID\n" << endl;
		}
	}


	//Function to insert a new machine into DHT, takes machine ID string as a parameter
	void insert_machine(string machine_id)
	{

		InfInt hash_id = hash_value(machine_id, this->ID_space);

		if (this->check_ID(hash_id) == true)
			return;


		Machine_node<T, S>* new_mach = new Machine_node<T, S>(machine_id, hash_id, this->ID_space);
		//new_mach->next = NULL;

		if (head == NULL) //if list was empty head points to new machine
		{
			head = new_mach;
			new_mach->next = head;
		}
		else if (head->next == head) //Handling second entry[When there is only one machine].
		{
			//If head ID is less than new mach's ID
			if (head->ID < new_mach->ID)
			{
				head->next = new_mach;//head newx to new mach
				new_mach->next = head;//new mach next to head because list is circular
				//new_mach->prev = head;
				//tail = new_mach;
			}
			else //if new mach ID < head ID
			{
				//tail = head;
				//head->prev = new_mach;
				head->next = new_mach;
				new_mach->next = head;
				head = new_mach;

			}
		}
		else
		{
			Machine_node<T, S>* nodeptr = head;//initializing a new pointer with list head
			Machine_node<T, S>* nodeptr2 = head->next;

			while (nodeptr2 != head)
			{
				if (new_mach->ID > nodeptr->ID && new_mach->ID < nodeptr2->ID)
				{
					//Inserting new_mach between nodeptr & nodeptr2 if its ID is in b/w both.

					new_mach->next = nodeptr2;
					nodeptr2->prev = new_mach;
					nodeptr->next = new_mach;
					new_mach->prev = nodeptr;

					break;
				}
				else if (new_mach->ID > nodeptr2->ID && nodeptr2->next == head)
				{
					//If end of list is reached and node still not inserted then node will be inserted at last. 

					new_mach->next = head;
					nodeptr2->next = new_mach;
					new_mach->prev = nodeptr2;
					tail = new_mach;

					break;
				}

				nodeptr = nodeptr->next;//Updating nodeptr
				nodeptr2 = nodeptr2->next;
			}
		}


		this->update_trees_insert(new_mach, new_mach->next);

		this->Update_Finger_Tables();//Updating finger tables
	}

	//This function takes machine is string and displays its info according to 2nd parameter
	//If option = 1(print routing table of machine) then, and if option = 2(print AVL tree,line_num & file location)
	void display_a_machine(string str_id, int option)
	{
		InfInt hash_id = hash_value(str_id, this->ID_space);//finding out hash of inserted str_id

		Machine_node<T, S>* nodeptr = this->search_ID(hash_id);

		//If ID found on DHT then machine info displayed
		if (nodeptr != NULL)
		{
			cout << "\nMachine ID = " << nodeptr->ID_str << " (" << nodeptr->ID << ")" << endl;
			if (option == 1)
			{
				cout << "Routing Table : ";
				nodeptr->FT.display_FT();
			}
			else if (option == 2)
			{
				cout << "\nAVL : ";
				if (nodeptr->Data_Tree.root != NULL)
					nodeptr->Data_Tree.display();
				else
					cout << "AVL Tree is empty\n";
				cout << endl;
				cout << "File location : .\\" << nodeptr->ID_str << ".txt\n" << endl;
			}
		}
		else //nodeptr == NULL it means ID not found, User will be given a prompt
		{
			cout << endl;
			cout << "Machine ID not Registered on DHT" << endl;
			cout << endl;
		}

	}

	//Function to display all machines
	void display_machines()
	{
		Machine_node<T, S>* nodeptr = head;//pointer to iterate over linked list of machines

		bool loop_flag = false;//Flag variable to make sure loop doesnt iterarte more than once over the list
					   //because its a circular list

		while (nodeptr != head || loop_flag == false)
		{
			cout << nodeptr->ID_str << "prev : ";// << nodeptr->prev->ID;
			nodeptr->FT.display_FT();

			nodeptr = nodeptr->next;
			loop_flag = true;
		}
		cout << endl;
	}

};


//Defining Finger Table node class 
template<class T, class S>
class FT_node
{
public:

	Machine_node<T, S>* Machine_ptr;//Each node will have a pointer to a machine node(NODE DATA).

	FT_node<T, S>* next;//pointer to next machine in linked list.
	FT_node<T, S>* prev;//pointer to previous machine in linked list.

	FT_node()
	{
		Machine_ptr = NULL;
		next = NULL;
		prev = NULL;
	}

	//Parameterized constructor
	FT_node(Machine_node<T, S>* machine_node)
	{
		Machine_ptr = machine_node;
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

	//The following function gets the machine_node stored at the given index of FT linked list
	Machine_node<T, S>* get_at(int index)
	{
		int count = 1;

		FT_node<T, S>* nodeptr = this->head;//initializing a ptr with head for iteration

		while (nodeptr != NULL)
		{
			if (index == count)
			{
				return nodeptr->Machine_ptr;//If index found, then machine ptr at that index returned
			}

			count++;//inc count
			nodeptr = nodeptr->next;//updating nodeptr
		}
	}

	//Function to insert machine pointer into FT linked list(Takes machine node pointer as parameter)
	void insert(Machine_node<T, S>* mach_node)
	{
		//Creating new FT_node with a new machine pointer.
		FT_node<T, S>* newnode = new FT_node<T, S>(mach_node);
		newnode->next = NULL;
		newnode->prev = NULL;


		if (head == NULL) //If linked list is empty then head and tail will point to newnode.
		{
			head = newnode;
			tail = newnode;
		}
		else //newnode will be inserted at the end of linked list
		{

			tail->next = newnode;//tails next will point to newnode
			newnode->prev = tail;//newnodes prev will point to ex tail
			tail = newnode;		 //newnode will become the new tail
		}


	}

	//Following function takes a Machine linked list 
	//& its machines hashed ID as a parameter and
	//updates the Machines Finger Table.
	void Update_F_Table(DHT<T, S> machine_list, InfInt machine_ID)
	{

		//Storing maximium number of machines which can be registered on DHT by doing 2^ID_space.
		InfInt total_machines = InfIntpow(2, machine_list.ID_space);

		//Variable to store total number of FT entries which will be log2(total_machines).
		InfInt FT_size = log2(total_machines);

		Machine_node<T, S>* mach_ptr = machine_list.head;//initializing a pointer with head of machine linked list

		if (mach_ptr == NULL) //doing nothing and returning if Machine Linked list is empty
		{
			return;
		}
		else
		{
			int index = 1;  //variable to store index of Finger Table node
						//Indexing will start from 1 (NOT FROM 0).

			InfInt succ;//variable to store to store shortcut pointer to other machine[succ(ID + 2^(i-1))]

			//Loop to set all indexes of Finger Table.
			for (InfInt c = 0; c < FT_size; ++c)
			{

				succ = machine_ID + InfIntpow(2, index - 1); //[succ(ID + 2 ^ (i - 1))]

				if (succ >= total_machines)
				{
					succ = succ % total_machines;
				}

				//cout << "succ : "<<machine_ID<<" " << succ << endl;

				mach_ptr = machine_list.head;//setting mach_ptr to head of linked list

				//initializing a 2nd pointer with head of machine linked list
				Machine_node<T, S>* mach_ptr2 = machine_list.head->next;

				bool succ_set = false;//Flag to hold status of wether or not new FT node inserted.

				//Iterating over linked list of machines until the head is reached again
				while (mach_ptr2 != machine_list.head)
				{
					if (succ <= mach_ptr->ID)
					{
						this->insert(mach_ptr);//inserting machine pointer in Finger table.
						succ_set = true;
						break;
					}

					mach_ptr = mach_ptr->next;//Updating mach_ptr
					mach_ptr2 = mach_ptr2->next;

				}

				//If new FT node not inserted then
				if (succ_set == false)
				{
					succ = 0;

					mach_ptr = machine_list.head;//setting mach_ptr to head of linked list

					//re-setting both ptrs
					mach_ptr = machine_list.head;
					mach_ptr2 = machine_list.head->next;

					//Iterating over linked list of machines until the head is reached again
					while (mach_ptr2 != machine_list.head)
					{
						if (succ <= mach_ptr->ID)
						{
							this->insert(mach_ptr);//inserting machine pointer in Finger table.
							break;
						}

						mach_ptr = mach_ptr->next;//Updating mach_ptr
						mach_ptr2 = mach_ptr2->next;
					}

				}

				index++; //Incrementing index of Finger Table

			}
		}

	}

	//This function clears the FT of a machine node 
	void clear_FT()
	{
		this->head = NULL;
	}

	//Function to display finger table of a Machine node.
	void display_FT()
	{
		FT_node<T, S>* nodeptr = head; //Pointer to iterate of FT linked list(initializing with head).

		while (nodeptr != NULL)
		{
			cout << nodeptr->Machine_ptr->ID;//Displaying the ID of machine node stored in FTP index

			if (nodeptr->next != NULL)
			{
				cout << " , ";
			}

			nodeptr = nodeptr->next;//Updating nodeptr
		}
		cout << endl;
	}

};

string gen_random(const int len) {

	string tmp_s;
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";

	srand((unsigned)time(NULL));

	tmp_s.reserve(len);

	for (int i = 0; i < len; ++i)
		tmp_s += alphanum[rand() % (sizeof(alphanum) - 1)];


	return tmp_s;

}


#pragma once

#include<iostream>
using namespace std;

class node
{
public:
	int data;
	node* next;

	node()
	{
		data = 0;
		next = NULL;
	}

	node(int d)
	{
		data = d;
		next = NULL;
	}



};

class linkedlist
{
public:
	node* head;

	linkedlist()
	{
		head = NULL;
	}


	void insert_at_beg(int d)
	{

		node* newnode = new node(d);


		if (head == NULL)//If list is empty
		{
			head = newnode;
		}
		else
		{
			node* temp = head;
			head = newnode;
			newnode->next = temp;
		}
	}

	void insert_at_end(int d)
	{
		node* newnode = new node(d);

		node* temp = head;

		while (temp->next != nullptr)
		{
			temp = temp->next;
		}

		temp->next = newnode;
	}


	void insert_at_position(int d, int index)
	{
		node* newnode = new node(d);
		node* temp = head;
		int count = 0;

		if (index != 0)
		{
			while ((index >= 0) && (count != index - 1) && (temp->next != NULL))
			{
				temp = temp->next;
				count++;
			}
			node* swap = temp->next;
			temp->next = newnode;
			newnode->next = swap;
		}
		else
		{
			insert_at_beg(d);
		}

	}

	void delete_from_start()
	{
		if (head != NULL)
		{
			node* temp = head;
			head = head->next;
			delete temp;
		}
	}

	void delete_from_end()
	{
		if (head != NULL)
		{
			node* temp = head;
			while ((temp->next)->next != nullptr)
			{
				temp = temp->next;
			}

			node* temp2 = temp->next;
			delete temp2;
			temp->next = NULL;
		}
	}

	void delete_from_middle(int index)
	{
		node* temp = head;
		int count = 0;

		if (index == 0)
		{
			delete_from_end();
		}
		else
		{
			while ((count != index - 1) && (temp->next != NULL))
			{
				temp = temp->next;
			}

			if (temp->next != NULL)
			{
				node* del = temp->next;
				temp->next = (temp->next)->next;
				delete del;
			}
			else
			{
				delete_from_end();
			}

		}
	}



	bool search(int value)
	{
		bool flag = false;
		node* temp = head;
		while (temp != NULL)
		{
			if (temp->data == value)
			{
				flag = true;
				break;

			}
			temp = temp->next;
		}

		return flag;

	}

	void display()
	{
		node* temp = head;

		while (temp != NULL)
		{
			cout << temp->data << " ";
			temp = temp->next;
		}
	}

	~linkedlist()
	{
		node* temp = head;
		while (temp != NULL)
		{
			node* del = temp;
			temp = temp->next;
			delete del;
		}
		head = NULL;

	}


};
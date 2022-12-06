#pragma once

#include <iostream>
#include <vector>

template <typename T>
class ListNode 
{
public:
	size_t index;
	T value;
	ListNode* next;
	ListNode(T value, size_t index) 
	{
		this->index = index;
		this->value = value;
		this->next = nullptr;
	}
};

template<typename T>
class List
{
private:
	ListNode<T>* head;
	int length;

public:
	List(int length = 0) 
	{
		this->length = length;
		this->head = nullptr;
	}

	void print()
	{
		ListNode<T>* temp = head;

		while (temp)
		{
			std::cout << "index = " << temp->index << "; value = " << temp->value << "; " << std::endl;
			temp = temp->next;
		}

		std::cout << "\n";
	}

	int getSize() 
	{
		return this->length;
	}

	T operator[](size_t index) 
	{
		ListNode<T>* temp = head;
		while (temp) 
		{
			if (temp->index > index)			return T();
			else if (temp->index == index)		return temp->value;


			temp = temp->next;
		}

		return T();
	}

	std::vector<int> getIndexes(int value) 
	{
		std::vector<int> result(0);
		ListNode<T>* temp = head;
		while (temp) 
		{
			if (temp->value == value)
			{
				result.push_back(temp->index);
			}
			temp = temp->next;
		}
		return result;
	}

	void addToList(T value, int index)
	{
		ListNode<T>* temp;
		temp = this->head;

		if (!head)
		{
			this->head = new ListNode<T>(value, index);
		}
		else if (index == temp->index)
		{
			temp->value = value;
		}
		else if (index < temp->index)
		{
			this->head = new ListNode<T>(value, index);
			this->head->next = temp;
		}
		else
		{
			while (temp->next)
			{
				if (temp->next->index > index)
				{
					ListNode<T>* new_node = new ListNode<T>(value, index);
					new_node->next = temp->next;
					temp->next = new_node;
					return;
				}
				else if (temp->next->index == index)
				{
					temp->next->value = value;
					return;
				}
				temp = temp->next;
			}
			temp->next = new ListNode<T>(value, index);
		}
	}

	~List()
	{
		ListNode<T>* temp = this->head;
		while (temp)
		{
			ListNode<T>* deleted = temp;
			temp = temp->next;

			delete deleted;
		}
	}
};

template<typename T>
class Matrix
{
private:
	int height;
	int length;
	ListNode<T>* head;

public:
	Matrix() 
	{
		this->length = 0;
		this->height = 0;
		this->head = nullptr;
	}

	Matrix(size_t height, size_t length) :Matrix()
	{
		this->height = height;
		this->length = length;
	}

	size_t getHeight() {
		return this->height;
	}
	size_t getLength() {
		return this->length;
	}

	~Matrix()
	{
		ListNode<T>* temp = head;

		while (temp)
		{
			ListNode<T>* deleted = temp;
			temp = temp->next;
			delete deleted;
		}
	}

	Matrix(const Matrix& copy) {
		this->length = copy.length;
		this->height = copy.height;
		this->head = nullptr;
		if (!copy.head)
		{
			return;
		}

		ListNode<T>* copy_current = copy.head;
		this->head = new ListNode<T>(copy.head->value, copy.head->index);
		ListNode<T>* new_current = this->head;

		while (copy_current->next) {
			new_current->next = new ListNode<T>(copy_current->next->value, copy_current->next->index);

			copy_current = copy_current->next;
			new_current = new_current->next;
		}

	}
	void addValue(T value, size_t i, size_t j) 
	{
		ListNode<T>* temp = this->head;

		size_t index = (i * this->length) + j;
		if (!head)		
			this->head = new ListNode<T>(value, index);
		else if (index < temp->index) 
		{
			this->head = new ListNode<T>(value, index);
			this->head->next = temp;
		}
		else if (index == temp->index) 
		{
			temp->value = value;
		}
		else 
		{
			while (temp->next) 
			{
				if (temp->next->index == index)
				{
					temp->next->value = value;
					return;
				}
				else if (temp->next->index > index) 
				{
					ListNode<T>* new_node = new ListNode<T>(value, index);
					new_node->next = temp->next;
					temp->next = new_node;
					return;
				}

				temp = temp->next;
			}
			temp->next = new ListNode<T>(value, index);
		}
	}

	T getT(size_t i, size_t j)
	{
		ListNode<T>* temp = head;

		size_t index = (i * this->length) + j;
		while (temp)
		{
			if (temp->index > index)		  return T();
			else if (temp->index == index)    return temp->value;

			temp = temp->next;
		}
		return T();
	}

	void print()
	{
		ListNode<T>* temp = this->head;
		for (size_t i = 0; i < this->length * this->height; i++)
		{
			if (!(i % this->length) && (i > 0))		std::cout << std::endl;
			if (temp)
			{
				if (temp->index == i)
				{
					std::cout << temp->data << "\t";
					temp = temp->next;
				}
			}
			std::cout << 0 << "\t";
		}

		std::cout << std::endl;
	}


	ListNode<T>* getHead() {
		return this->head;
	}
};

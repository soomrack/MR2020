#include <ctime>
#include <iostream>
#include <string>
using namespace std;

class List
{
	class Node
	{
	public:
		int data;
		Node* next;

		Node(int t = 0, Node* n = nullptr);
	};
	Node* head;
	int size;

public:
	List();
	~List();
	void pushBack(int value);
	void pushFront(int value);
	int getSize() const;
	int& operator[] (int);
	void popFront();
	void popBack();
	void clear();
	void insert(int value, int index);
	void removeAt(int index);
};


void show(List&);





int main()
{
	
	List list;
	for (int i = 0; i < 5; i++) list.pushBack(i);
	show(list);
	list.popBack();
	list.popFront();
    list.insert(5, 2);
	list[1] = 777;
	show(list);
	
}





List::Node::Node(int t, Node* n)
{
	data = t;
	next = n;
}

List::List()
{
	size = 0;
	head = nullptr;
}

List::~List()
{
	clear();
}

void List::pushBack(int value)
{
	if (head == nullptr)
		head = new Node(value);
	else
	{
		for (Node* current = head; ; current = current->next)
			if (current->next == nullptr)
			{
				current->next = new Node(value);
				break;
			}
	}
	size++;
}

void List::pushFront(int value)
{
	head = new Node(value, head);
	size++;
}

int List::getSize() const
{
	return size;
}

int& List::operator[](int index)
{
	if (index > size - 1 || index < 0)
	{
		string message = "Недопустимый индекс ";
		message.append(to_string(index));
		throw out_of_range(message);
	}
	Node* current = head;
	for (int i = 0; i < index; i++)
		current = current->next;
	return current->data;
}

void List::popFront()
{
	if (size <= 0) return;
	Node* temp = head;
	head = head->next;
	delete temp;
	size--;
}

void List::popBack()
{
	removeAt(size - 1);
}

void List::clear()
{
	while (size) popFront();
}

void List::insert(int value, int index)
{
	if (index > size || index < 0)
	{
		string message = "Недопустимый индекс ";
		message.append(to_string(index));
		throw out_of_range(message);
	}
	if (index == 0) pushFront(value);
	else
	{
		Node* previous = head;
		for (int i = 0; i < index - 1; i++)
			previous = previous->next;
		previous->next = new Node(value, previous->next);
		size++;
	}
}

void List::removeAt(int index)
{
	if (index > size - 1 || index < 0)
	{
		string message = "Недопустимый индекс ";
		message.append(to_string(index));
		throw out_of_range(message);
	}
	if (index == 0) popFront();
	else
	{
		Node* previous = head;
		for (int i = 0; i < index - 1; i++)
			previous = previous->next;
		Node* temp = previous->next;
		previous->next = temp->next;
		delete temp;
		size--;
	}
}

void show(List& list)
{
	cout << "size = " << list.getSize() << endl;
	for (int i = 0; i < list.getSize(); i++) cout << list[i] << "  ";
	cout << endl;
}







#include <iostream>
#include <string>


class Node{
public:
    int value;
    Node *next;
public:
    Node(int value = 0, Node *next = nullptr);

};

Node::Node(int value, Node* next)
{
	this->value = value;
	this->next = next;
}


class List;

class Iterator {
private:
    Node *current;
    Node *prev;
    List *list;
public:
    Iterator next();
    int get_value();
    void set_value(const int value);
public:
    void insert(const int value); 
    void del();  
public:
    Iterator(List & lst);
};

class List {
private:

    friend class Iterator;
    Node *root;
    int size;

public:
    Iterator begin();
public:
    List();
    ~List();
    void popFront();
	void popBack();
	void clear();
    // int& operator[] (int);
    void pushBack(int value);
    int getSize() const;
};


List::List(){
    size = 0;
    root = nullptr;
}

List::~List()
{
	clear();
}

void List::clear()
{
	while (root!=nullptr) popFront();
}

void List::popFront()
{
	if (root == nullptr) return;
	Node* temp = root;
	root = root->next;
	delete temp;
	size--;
}

void List::pushBack(int value)
{
	if (root == nullptr)
		root = new Node(value);
	else
	{
        Node* current = root;
		while (current->next == nullptr)
			{
				current->next = new Node(value);
				break;
			}
	}
	size++;
}


int List::getSize() const
{
	return size;
}


Iterator List::begin(){
    Iterator tmp(*this);
    
    return tmp;
}


Iterator::Iterator(List & lst){
    current = lst.root;
    prev = nullptr;
    list = &lst;
}


Iterator Iterator::next(){
    if (this->current->next == nullptr){
        this->prev = this->current;
        this->current = this->list->root;
        return *this;
    }
    else{
        this->prev = this->current;
        this->current = this->current->next;
        return *this;
    }
    
}

int Iterator::get_value(){
    return current->value;
}

void Iterator::set_value(const int value){
    if (current != nullptr){
        current->value = value;
    }
    
}

void Iterator::insert(const int value){
    Node* previous = current;
	previous->next = new Node(value, previous->next);
	list->size++;
}

void Iterator::del(){
    Node* temp = this->current;
    if(temp->next == nullptr){
        prev->next = temp->next;
        current = list->root;
    }
    else{

        prev->next = temp->next;
        current = temp->next;
    }

    delete temp;
    list->size--;
} 


int main() {
    //Потестим
    Node nd;
    
    List list;
    list.pushBack(1);
    list.pushBack(2);
    list.pushBack(3);
    list.pushBack(4);
  
    Iterator it = list.begin();
    it.next();
    it.next();
    it.next();
    it.next();
    it.next();
    int a = it.get_value();
    it.set_value(100);
    int b = it.get_value();
    
    it.next();
    it.insert(10);
    it.del();
    it.del();


 
    return 0;
}
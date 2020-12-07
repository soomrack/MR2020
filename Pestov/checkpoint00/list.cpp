/* 
Реализация linked list 
Я не очень понял зачем нужен Iterator и как он должен взаимодействовать со связным списком.
Но я реализовал все методы класса Iterator и написал методы для работы со связным списком.

Кроме этого файла есть другой. В нем реализован односвзяный список так как я себя это представляю. 
Этого достаточно для удобной работы со связным списком. 
Но на самом деле в реальных проектах всегда лучше использовать List из стандартной библиотеки.
*/


#include <iostream>
#include <string>


class Node{
public:
    int value;
    Node *next;
public:
    // Node();
    // Node(const int value);
    // Вместо создания конструктора для каждого набора параметров я просто задам дефолтные значения
    
    Node(int value = 0, Node *next = nullptr);
    // ~Node();
    // Удалить ноду можно и деструтором который создасться автоматически
    
};

Node::Node(int value, Node* next)
{
	this->value = value;
	this->next = next;
}




// объявим класс List, чтобы использовать в классе Iterator
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
    void insert(const int value);  // insert new node after current
    void del();  // delete current node
public:
    Iterator(List & lst);
    // ~Iterator();
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
// Создадим основные тестовые вызовы методов
//  
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
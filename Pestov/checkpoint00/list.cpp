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
    // Я не могу передвать конст некст потому что я должен присвоить Node*
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
// если я правильно помню - модификатор доступа friend дает классу 
// итератор доступ к приватным полям класса Лист

    friend class Iterator;
// root - first element
    Node *root;
    int Size;

public:
// а это тогда что - начало итератора
    Iterator begin();
public:
    List();
    ~List();
    void popFront();
	void popBack();
	void clear();
    int& operator[] (int);
    void pushBack(int value);
    int getSize() const;
};








List::List(){
    Size = 0;
    root = nullptr;
}

List::~List()
{
	clear();
}

void List::clear()
{
	while (Size) popFront();
}

void List::popFront()
{
	if (Size <= 0) return;
	Node* temp = root;
	root = root->next;
	delete temp;
	Size--;
}

void List::pushBack(int value)
{
	if (root == nullptr)
		root = new Node(value);
	else
	{
		for (Node* current = root; ; current = current->next)
			if (current->next == nullptr)
			{
				current->next = new Node(value);
				break;
			}
	}
	Size++;
}




int List::getSize() const
{
	return Size;
}


int& List::operator[](int index)
{
	if (index > Size - 1 || index < 0)
	{
		std::string message = "Недопустимый индекс ";
		message.append(std::to_string(index));
		throw std::out_of_range(message);
	}
	Node* current = root;
	for (int i = 0; i < index; i++)
		current = current->next;
	return current->value;
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
    current->value = value;
}

void Iterator::insert(const int value){
    Node* previous = current;
	previous->next = new Node(value, previous->next);
	list->Size++;
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
    list->Size--;
} 










void show(List& list)
{
	std::cout << "size = " << list.getSize() << std::endl;
	for (int i = 0; i < list.getSize(); i++) std::cout << list[i] << "  ";
	std::cout << std::endl;
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
    show(list);
    Iterator it = list.begin();
    it.next();
    it.next();
    it.next();
    it.next();
    it.next();
    int a = it.get_value();
    it.set_value(100);
    int b = it.get_value();
    
    show(list);
    it.next();
    it.insert(10);
    it.del();
    it.del();
    
    show(list);

 
    return 0;
}

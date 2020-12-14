
#include "List.h"
const int ERROR = 1;

Node::Node() {
    next = nullptr;
}
Node::Node(const int data) {
    this->data = data;
    next = nullptr;
}
Node::Node(const int data, Node *next) {
    this->data = data;
    this->next = next;
}
Node::~Node(){
    this->next = nullptr;
}
List::List() {
    size = 0;
    head = nullptr;
}
List::~List() {
    Iterator delll(*this);
    while(head) {
        delll.del();
    }
}
Iterator::Iterator(List &list_boss) {
    this->list_boss = &list_boss;
    current = list_boss.head;
    prev = nullptr;
}
Iterator::~Iterator() {
    prev = nullptr;
}

Iterator List::begin() {
    Iterator head_of_list = *this;
    return head_of_list;
}

Iterator Iterator::next() {
    if (current->next == nullptr) {
        prev = nullptr;
        current = nullptr;
        return *this;
    }
    prev = current;
    current = current->next;
    return *this;
}

int Iterator::get_data() {
    return current->data;
}

void Iterator::set_data(const int data) {
    current->data = data;
}

void Iterator :: insert(const int data) {
    if (current == nullptr) {
        printf("You trying to insert node after null node!\n");
        return;
    }
    Node* new_node = new Node(data);
    new_node->next = current->next;
    current->next = new_node;
    list_boss->size++;
}

void Iterator :: del() {
    if(current == nullptr) {
        printf("You trying to delete null node!\n");
        return;
    }
    if(list_boss->head == current) {
        list_boss->head = current->next;
        delete current; // удаляем голову
        current = list_boss->head;
        list_boss->size--;
        return;
    }
    // удаляем не голову
    prev->next = current->next;
    delete current;
    list_boss->size--;
    current = prev->next;
}

void List :: push_back(const int data) {
    Node* new_node = new Node(data);
    Node *tail = head;
    // List пустой
    if (head == nullptr) {
        head = new_node;
        size++;
        return;
    }
    // List не пустой, ищем последний элемент
    while (tail->next) {
        tail = tail->next;
    }
    tail->next = new_node;
    size++;
}

void List::Print_list() {
    if(head == nullptr) {
        printf("List is empty!\n");
        return;
    }
    Node * node_to_print = head;
    for (int i = 1; i <= size; i++) {
        printf("%d element - %d\n", i, node_to_print->data);
        node_to_print = node_to_print->next;
    }
}
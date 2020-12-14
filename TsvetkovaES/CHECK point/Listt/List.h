#ifndef UNTITLED_LIST_H
#define UNTITLED_LIST_H
#include <iostream>

class Node {
public:
    int data;
    Node *next;
public:
    Node();
    Node(const int data);
    Node(const int data, Node *next);
    ~Node();
};

class List;

class Iterator {
private:
    Node *current;
    Node *prev;
    List *list_boss;
public:
    Iterator next();
    int get_data();
    void set_data(const int data);
public:
    void insert(const int data);  // insert new node after current
    void del();  // delete current node
public:
    Iterator();
    Iterator(List &list_boss);
    ~Iterator();
};


class List {
private:
    friend class Iterator;
    Node *head;
    int size;
public:
    Iterator begin();
    void push_back(const int data);
    void Print_list();
public:
    List();
    ~List();
};

#endif //UNTITLED_LIST_H
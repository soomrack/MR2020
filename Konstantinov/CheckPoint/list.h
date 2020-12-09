//
// Created by alex on 09.12.2020.
//

#ifndef CPP_CHECKPOINT_LIST_H
#define CPP_CHECKPOINT_LIST_H

#include <iostream>


class List_Node {
public:
    int value;
    List_Node *next;
public:
    List_Node();
    List_Node(int value);
    List_Node(int value, List_Node *next);
    ~List_Node();
};

class List;

class Iterator {
private:
    List_Node *current;
    List_Node *prev;
public:
    void next();
    int get_value();
    void set_value(const int value);
public:
    void insert(const int value);  // insert new node after current
    void del();  // delete current node
public:
    explicit Iterator(List &list);
    ~Iterator();
};


class List {
private:
    friend class Iterator;
    List_Node *root;
public:
    Iterator begin();
public:
    List();
    ~List();
};


#endif //CPP_CHECKPOINT_LIST_H

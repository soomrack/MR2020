#include <iostream>


class Node {
public:
    int value;
    Node *next;
public:
    Node();
    Node(const int value);
    Node(const int value, const Node *next);
    ~Node();
};


class Iterator {
private:
    Node *current;
    Node *prev;
public:
    Iterator next();
    int get_value();
    void set_value(const int value);
public:
    void insert(const int value);  // insert new node after current
    void del();  // delete current node
public:
    Iterator();
    ~Iterator();
};


class List {
private:
    friend class Iterator;
    Node *root;
public:
    Iterator begin();
public:
    List();
    ~List();
};



int main() {
    std::cout << "The end." << std::endl;
}
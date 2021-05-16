#ifndef UNTITLED2_REDBLACKTREE_H
#define UNTITLED2_REDBLACKTREE_H

enum COLOR { RED, BLACK };

class Node {
public:
    int data;
    int key;
    COLOR color;
    Node *left, *right, *parent;
public:
    Node();
    Node(int data, int key);
    ~Node();
};

class RBTree {
public:
    Node *root;
private:
    bool isLeft(Node* node);  // Является ли узел левым ребёнокм своего родителя
    bool checkDoubleBlack(Node* node1, Node* node2);  // Функция проверяет условие "двойного чёрного"
    Node* searchSuccessor(Node* node);  // Функция поиска узла, который займёт место удаляемого
    Node* searchSibling(Node* node);  // Функция находит брата узла
    void swapData(Node* node1, Node* node2);  // Функция переставляет местами данные
    void leftRotate(Node* node);  // Левое вращение - меняет положение узлов
    void rightRotate(Node* node);  // Правое вращение - меняет положение узлов
    void fixDoubleBlack(Node* node);  // Функция перестраивающая дерево при "двойном чёрном"
    void fixSiblingHasRedChild(Node* sibling);  // Подфункция функции fixDoubleBlack для случая SiblingIsBlack
    void deleteLeaf(Node* delNode);   // Функция удаления листа
    void deleteNodeWithOneChild(Node* delNode);  // Функция удаления узла с одним потомком
public:
    void deleteNode(Node* node);  // Удаление заданного узла
    void del(int key);  // Удаления узла по ключу
    Node* search(int key);  // Поиск узла по ключу
public:
    RBTree();
    ~RBTree();
};


#endif //UNTITLED2_REDBLACKTREE_H

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
    Node *root;
private:
    static bool isLeft(Node* node);  // Является ли узел левым ребёнокм своего родителя
    static bool checkDoubleBlack(Node* node1, Node* node2);  // Функция проверяет условие "двойного чёрного"
    static Node* searchSuccessor(Node* node);  // Функция поиска узла, который займёт место удаляемого
    static Node* searchSibling(Node* node);  // Функция находит брата узла
    static void swapData(Node* delNode, Node* successor);  // Функция переставляет местами данные
    static void leftRotate(Node* node, Node* root);
    static void rightRotate(Node* node, Node* root);
    static void fixDoubleBlack(Node* node, Node* root);  // Функция перестраивающая дерево при "двойном чёрном"
    static void fixSiblingHasRedChild(Node* sibling, Node* root);  // Подфункция функции fixDoubleBlack
    static void deleteLeaf(Node* delNode, Node* root);  // Функция удаления листа
    static void deleteNodeWithOneChild(Node* delNode, Node* root);  // Функция удаления узла с одним потомком
public:
    void deleteNode(Node* node);  // Удаляет переданный узел
public:
    RBTree();
    ~RBTree();
};


#endif //UNTITLED2_REDBLACKTREE_H

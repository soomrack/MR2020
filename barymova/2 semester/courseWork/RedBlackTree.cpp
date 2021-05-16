#include "RedBlackTree.h"
#include <iostream>

Node::Node() {
    left = nullptr;
    right = nullptr;
    color = RED;
}

Node::Node(int data, int key) {
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    color = RED;
    this->key = key;
    this->data = data;
}

Node::~Node() {
    delete left;
    delete right;
}

RBTree::RBTree() {
    root = nullptr;
}

RBTree::~RBTree() {
    delete root;
}

// Является ли узел левым ребёнокм своего родителя
bool RBTree::isLeft(Node *node) {
    return node->parent->left == node;
}

// Функция проверяет условие "двойного чёрного"
bool RBTree::checkDoubleBlack(Node* node1, Node* node2) {
    return (node1 == nullptr or node1->color == BLACK) and
           (node1 == nullptr or node2->color == BLACK);
}

// Функция поиска узла, который займёт место удаляемого
Node* RBTree::searchSuccessor(Node *node) {
    // Если у удаляемого узла два потомка,
    // то его заменит узел с наименьшим ключом в правом поддереве
    if ((node->left != nullptr) and (node->right != nullptr)) {
        node = node->right;
        while (node->left != nullptr) {
            node = node->left;
        }
    }

    // Если удаляемый узел - лист,
    // то возвращаем пустой указатель
    if ((node->left == nullptr) and (node->right == nullptr)) {
        return nullptr;
    }

    // Если у удаляемого узла есть один потомок,
    // то возвращаем его
    if (node->left != nullptr) {
        return node->left;
    } else {
        return node->right;
    }
}

// Функция находит брата узла
Node* RBTree::searchSibling(Node *node) {
    if (node->parent == nullptr) {
        return nullptr;
    }

    if (isLeft(node)) {
        return node->parent->right;
    } else {
        return node->parent->left;
    }
}

// Функция переставляет местами значения узлов
void RBTree::swapData(Node* delNode, Node* successor) {
    int temp = delNode->data;
    delNode->data = successor->data;
    successor->data = temp;
}

void RBTree::leftRotate(Node* node, Node* root) {
    Node *pivot = node->right;  // Правый ребёнок node встанет на место node
    Node* parent = node->parent;

    // Переставляем node и pivot
    if (node == root) {
        root = pivot;
    } else {
        if (isLeft(node)) {
            parent->left = pivot;
        } else {
            parent->right = pivot;
        }
    }
    pivot->parent = parent;
    pivot->left = node;

    // Левоый ребёнок pivot становится правым ребёнком node
    node->right = pivot->left;
    if (pivot->left != nullptr) {
        pivot->left->parent = node;
    }
}

void RBTree::rightRotate(Node* node, Node* root) {
    Node *pivot = node->left;  // Левый ребёнок node встанет на место node
    Node* parent = node->parent;

    // Переставляем node и pivot
    if (node == root) {
        root = pivot;
    } else {
        if (isLeft(node)) {
            parent->left = pivot;
        } else {
            parent->right = pivot;
        }
    }
    pivot->parent = parent;
    pivot->right = node;

    // Правый ребёнок pivot становится левым ребёнком node
    node->left = pivot->right;
    if (pivot->right != nullptr) {
        pivot->right->parent = node;
    }
}

// Подфункция функции fixDoubleBlack
void RBTree::fixSiblingHasRedChild(Node* sibling, Node* root) {
    Node* parent = sibling->parent;
    if (sibling->left != nullptr and sibling->left->color == RED) {
        if (isLeft(sibling)) {
            // left left
            sibling->left->color = sibling->color;
            sibling->color = parent->color;
            rightRotate(parent, root);
        } else {
            // right left
            sibling->left->color = parent->color;
            rightRotate(sibling, root);
            leftRotate(parent, root);
        }
    } else {
        if (isLeft(sibling)) {
            // left right
            sibling->right->color = parent->color;
            leftRotate(sibling, root);
            rightRotate(parent, root);
        } else {
            // right right
            sibling->right->color = sibling->color;
            sibling->color = parent->color;
            leftRotate(parent, root);
        }
    }
    parent->color = BLACK;
}

// Функция перестраивающая дерево при "двойном чёрном"
void RBTree::fixDoubleBlack(Node *BBNode, Node* root) {
    // Если достигли корня - задача выполнена
    if (BBNode == root) {
        return;
    }

    Node* sibling = searchSibling(BBNode);
    Node* parent = BBNode->parent;

    // Если нет брата, "двойной чёрный" перемещается на родителя
    if (sibling == nullptr) {
        fixDoubleBlack(parent, root);
        return;
    }

    // Если есть брат
    if (sibling->color == RED) {  // sibling - красный
        parent->color = RED;
        sibling->color = BLACK;
        if (isLeft(sibling)) {
            rightRotate(parent, root);
        } else {
            leftRotate(parent, root);
        }
        fixDoubleBlack(BBNode, root);
    } else {    // sibling - чёрный
        if (checkDoubleBlack(sibling->left, sibling->right)) {  // Оба потомка sibling чёрные
            sibling->color = RED;
            if (parent->color == BLACK)
                fixDoubleBlack(parent, root);
            else
                parent->color = BLACK;
        } else {  // У sibling есть красные потомки
            fixSiblingHasRedChild(sibling, root);
        }
    }
}

// Функция удаления листа
void RBTree::deleteLeaf(Node* delNode, Node* root) {
    Node* parent = delNode->parent;
    Node* successor = searchSuccessor(delNode);  // Находим узел, который займёт место delNode
    bool isDoubleBlack = checkDoubleBlack(delNode, successor);

    if (delNode == root) {  // Если delNode является корнем дерева
        root = nullptr;
    } else {
        if (isDoubleBlack) {      // Если delNode - чёрный
            fixDoubleBlack(delNode, root);
        } else {                  // Если delNode - красный
            searchSibling(delNode)->color = RED;
        }

        // Обнуляем ссылки в дереве на удаляемый узел
        if (parent->left == delNode) {
            parent->left = nullptr;
        } else {
            parent->right = nullptr;
        }
    }
    delete delNode;
}

// Функция удаления узла с одним потомком
void RBTree::deleteNodeWithOneChild(Node* delNode, Node* root) {
    Node* parent = delNode->parent;
    Node* successor = searchSuccessor(delNode);  // Находим узел, который займёт место delNode
    bool isDoubleBlack = checkDoubleBlack(delNode, successor);

    if (delNode == root) {  // Если delNode является корнем дерева
        delNode->data = successor->data;
        delNode->left = delNode->right = nullptr;
        delete successor;
    } else {  // Если delNode не корень
        // Меняем ссылки
        if (isLeft(delNode)) {
            parent->left = successor;
        } else {
            parent->right = successor;
        }
        successor->parent = parent;

        // Удаляем узел
        delete delNode;

        if (isDoubleBlack) {  // delNode и successor чёрные
            fixDoubleBlack(successor, root);
        } else {              // Или delNode, или successor красный
            // Делаем новый узел чёрным
            successor->color = BLACK;
        }
    }
}

// Удаляет переданный узел
void RBTree::deleteNode(Node *delNode) {
    Node* successor = searchSuccessor(delNode);  // Находим узел, который займёт место delNode

    if (successor == nullptr) {  // Если delNode - лист
        deleteLeaf(delNode, this->root);
    } else if (delNode->left == nullptr or delNode->right == nullptr) {  // Если у delNode один потомок
        deleteNodeWithOneChild(delNode, this->root);
    } else {  // Если у delNode два потомка
        swapData(delNode, successor);
        deleteNode(successor);
    }
}

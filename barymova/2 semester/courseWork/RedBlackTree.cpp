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

// Левое вращение - меняет положение узлов
void RBTree::leftRotate(Node* node) {
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

// Правое вращение - меняет положение узлов
void RBTree::rightRotate(Node* node) {
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
void RBTree::fixSiblingHasRedChild(Node* sibling) {
    Node* parent = sibling->parent;
    if (sibling->left != nullptr and sibling->left->color == RED) {
        if (isLeft(sibling)) {
            // left left
            sibling->left->color = sibling->color;
            sibling->color = parent->color;
            rightRotate(parent);
        } else {
            // right left
            sibling->left->color = parent->color;
            rightRotate(sibling);
            leftRotate(parent);
        }
    } else {
        if (isLeft(sibling)) {
            // left right
            sibling->right->color = parent->color;
            leftRotate(sibling);
            rightRotate(parent);
        } else {
            // right right
            sibling->right->color = sibling->color;
            sibling->color = parent->color;
            leftRotate(parent);
        }
    }
    parent->color = BLACK;
}

// Функция перестраивающая дерево при "двойном чёрном"
void RBTree::fixDoubleBlack(Node *BBNode) {
    // Если достигли корня - задача выполнена
    if (BBNode == root) {
        return;
    }

    Node* sibling = searchSibling(BBNode);
    Node* parent = BBNode->parent;

    // Если нет брата, "двойной чёрный" перемещается на родителя
    if (sibling == nullptr) {
        fixDoubleBlack(parent);
        return;
    }

    // Если есть брат
    if (sibling->color == RED) {  // sibling - красный
        parent->color = RED;
        sibling->color = BLACK;
        if (isLeft(sibling)) {
            rightRotate(parent);
        } else {
            leftRotate(parent);
        }
        fixDoubleBlack(BBNode);
    } else {    // sibling - чёрный
        if (checkDoubleBlack(sibling->left, sibling->right)) {  // Оба потомка sibling чёрные
            sibling->color = RED;
            if (parent->color == BLACK)
                fixDoubleBlack(parent);
            else
                parent->color = BLACK;
        } else {  // У sibling есть красные потомки
            fixSiblingHasRedChild(sibling);
        }
    }
}

// Функция удаления листа
void RBTree::deleteLeaf(Node* delNode) {
    Node* parent = delNode->parent;
    Node* successor = searchSuccessor(delNode);  // Находим узел, который займёт место delNode
    bool isDoubleBlack = checkDoubleBlack(delNode, successor);

    if (delNode == root) {  // Если delNode является корнем дерева
        root = nullptr;
    } else {
        if (isDoubleBlack) {      // Если delNode - чёрный
            fixDoubleBlack(delNode);
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
void RBTree::deleteNodeWithOneChild(Node* delNode) {
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
            fixDoubleBlack(successor);
        } else {              // Или delNode, или successor красный
            // Делаем новый узел чёрным
            successor->color = BLACK;
        }
    }
}

// Ищет узел по заданному ключу
Node* RBTree::search(int key) {
    Node *temp = RBTree::root;
    while (temp != nullptr) {
        if (key < temp->key) {  // Если искомое меньше найденного
            if (temp->left == nullptr) {  // Если нет левого потомка,
                break;                    // temp - ближайший по знач ключа
            } else {
                temp = temp->left;        // проверяем левого потомка найденного узла
            }
        } else if (key == temp->key) {  //Значения равны - нашли нужный ключ
            break;
        } else {  // Если искомое больше найденного
            if (temp->right == nullptr) {  // Если нет правого потомка,
                break;                     // temp - ближайший по знач ключа
            } else {
                temp = temp->right;  // проверяем правого потомка найденного узла
            }
        }
    }
    return temp;
}

// Удаляет переданный узел
void RBTree::deleteNode(Node *delNode) {
    Node* successor = searchSuccessor(delNode);  // Находим узел, который займёт место delNode

    if (successor == nullptr) {  // Если delNode - лист
        deleteLeaf(delNode);
    } else if (delNode->left == nullptr or delNode->right == nullptr) {  // Если у delNode один потомок
        deleteNodeWithOneChild(delNode);
    } else {  // Если у delNode два потомка
        swapData(delNode, successor);
        deleteNode(successor);
    }
}

void RBTree::del(int key) {
    if (RBTree::root == nullptr) {  // Деревое пустое, нечего удалять
        return;
    }

    // Ищем узел с таким же или ближайшим ключом
    Node *node = search(key);
    if (node->key != key) {
        std::cout << "Нет узлов с значением: " << key << std::endl;
        return;
    }

    // Передаём узел в функцию удаления узла
    deleteNode(node);
}


#include <iostream>

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
    Node* searchUncle(Node* node);  // Функция находит дядю узла
    void swapColors(Node* node1, Node* node2);  // Функция переставляет местами значения цветов
    void swapData(Node* node1, Node* node2);  // Функция переставляет местами данные
    void leftRotate(Node* node);
    void rightRotate(Node* node);
    void fixDoubleBlack(Node* node);  // Функция перестраивающая дерево при "двойном чёрном"
    void fixSiblingHasRedChild(Node* sibling);  // Подфункция функции fixDoubleBlack для случая SiblingIsBlack
    void deleteLeaf(Node* delNode);   // Функция удаления листа
    void deleteNodeWithOneChild(Node* delNode);  // Функция удаления узла с одним потомком
    void fixRedRed(Node* node);  // Устраняет "двойной красный"
public:
    void deleteNode(Node* node);
    void del(int key);
    void insert(int data, int key);
    Node* search(int key);
public:
    RBTree();
    ~RBTree();
};

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
    this->root = nullptr;
}

RBTree::~RBTree() {
    delete RBTree::root;
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

// Функция находит дядю узла
Node* RBTree::searchUncle(Node* node) {
    Node* parent = node->parent;

    if (parent == nullptr or parent->parent == nullptr) {
        return nullptr;
    }

    if (isLeft(parent)) {
        return parent->parent->right;
    } else {
        return parent->parent->left;
    }
}

// Функция переставляет местами значения узлов
void RBTree::swapData(Node* node1, Node* node2) {
    int temp = node1->data;
    node1->data = node2->data;
    node2->data = temp;
}

// Функция переставляет местами значения цветов
void RBTree::swapColors(Node *node1, Node *node2) {
    COLOR temp;
    temp = node1->color;
    node1->color = node2->color;
    node2->color = temp;
}

void RBTree::leftRotate(Node* node) {
    Node *pivot = node->right;  // Правый ребёнок node встанет на место node
    Node* parent = node->parent;

    pivot->parent = parent;
    // Переставляем node и pivot
    if (node == RBTree::root) {
        RBTree::root = pivot;
    } else {
        if (isLeft(node)) {
            parent->left = pivot;
        } else {
            parent->right = pivot;
        }
    }

    // Левоый ребёнок pivot становится правым ребёнком node
    node->right = pivot->left;
    if (pivot->left != nullptr) {
        pivot->left->parent = node;
    }
    node->parent = pivot;
    pivot->left = node;
}

void RBTree::rightRotate(Node* node) {
    Node *pivot = node->left;  // Левый ребёнок node встанет на место node
    Node* parent = node->parent;

    pivot->parent = parent;
    // Переставляем node и pivot
    if (node == RBTree::root) {
        RBTree::root = pivot;
    } else {
        if (isLeft(node)) {
            parent->left = pivot;
        } else {
            parent->right = pivot;
        }
    }

    // Правый ребёнок pivot становится левым ребёнком node
    node->left = pivot->right;
    if (pivot->right != nullptr) {
        pivot->right->parent = node;
    }
    node->parent = pivot;
    pivot->right = node;
}

// Подфункция функции fixDoubleBlack для случая SiblingIsBlack
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

void RBTree::fixDoubleBlack(Node *BBNode) {
    // Если достигли корня - задача выполнена
    if (BBNode == RBTree::root) {
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
    if (sibling->color == RED) {
        parent->color = RED;
        sibling->color = BLACK;
        if (isLeft(sibling)) {
            // left case
            rightRotate(parent);
        } else {
            // right case
            leftRotate(parent);
        }
        fixDoubleBlack(BBNode);
    } else {  // Sibling black
        if (checkDoubleBlack(sibling->left, sibling->right)) {  // 2 black children
            sibling->color = RED;
            if (parent->color == BLACK)
                fixDoubleBlack(parent);
            else
                parent->color = BLACK;
        } else {
            fixSiblingHasRedChild(sibling);
        }
    }

}

// Функция удаления листа
void RBTree::deleteLeaf(Node* delNode) {
    Node* parent = delNode->parent;
    Node* successor = searchSuccessor(delNode);  // Находим узел, который займёт место delNode
    bool isDoubleBlack = checkDoubleBlack(delNode, successor);

    if (delNode == RBTree::root) {  // Если delNode является корнем дерева
        RBTree::root = nullptr;
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

    if (delNode == RBTree::root) {
        delNode->data = successor->data;
        delNode->left = delNode->right = nullptr;
        delete successor;
    } else {
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

// Устраняет "двойной красный"
void RBTree::fixRedRed(Node* node) {

    if (node == RBTree::root) {  // Если достигли корня, перекрашиваем его
        node->color = BLACK;
        return;
    }

    // Создаём указатели на ближайших "родственников"
    Node *parent = node->parent;
    Node* grandparent;
    Node* uncle;
    if (parent == nullptr) {
        grandparent = nullptr;
        uncle = nullptr;
    } else {
        grandparent = parent->parent;
        uncle = searchUncle(node);
    }

    if (parent != nullptr && parent->color == RED) {
        if (uncle != nullptr && uncle->color == RED) {  // Есть красный дядя
            // Перекрашиваем, проверяем grandparent
            parent->color = BLACK;
            uncle->color = BLACK;
            grandparent->color = RED;
            fixRedRed(grandparent);
        } else {  // Нет красного дяди
            if (isLeft(parent)) {
                if (isLeft(node)) {  //parent и node находятся слева
                    swapColors(parent, grandparent);
                } else {  //parent слева, node справа
                    leftRotate(parent);
                    swapColors(node, grandparent);
                }
                rightRotate(grandparent);
            } else {
                if (isLeft(node)) {  //parent справа, node слева
                    rightRotate(parent);
                    swapColors(node, grandparent);
                } else {  //parent и node находятся справа
                    swapColors(parent, grandparent);
                }
                leftRotate(grandparent);
            }
        }
    }
}

void RBTree::deleteNode(Node *delNode) {
    Node* successor = searchSuccessor(delNode);  // Находим узел, который займёт место delNode

    if (successor == nullptr) {
        // Если delNode - лист
        deleteLeaf(delNode);
    } else if (delNode->left == nullptr or delNode->right == nullptr) {
        // Если у delNode один потомок
        deleteNodeWithOneChild(delNode);
    } else {
        // Если у delNode два потомка
        swapData(delNode, successor);
        deleteNode(successor);
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

void RBTree::insert(int data, int key) {
    Node *newNode = new Node(data, key);
    if (RBTree::root == nullptr) {  // Если корень пустой, то вставляем знач на его место
        newNode->color = BLACK;
        RBTree::root = newNode;
    } else {
        // Проверяем, нет ли уже такого значения
        Node *temp = search(data);  // Ищем ближайшее значение
        if (temp->data == data) {
            return;                // Значение уже занято, досрочно выходим из ф-ии
        }

        // Вставляем узел рядом с ближайшим по ключу
        newNode->parent = temp;

        if (key < temp->key) {
            temp->left = newNode;
        } else {
            temp->right = newNode;
        }

        // По умолчанию новый узел - красный,
        // поэтому после вставки проверяем структуру дерева
        fixRedRed(newNode);
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

static void testInsert(RBTree tree, int arr[], int size) {
    for (int i = 0; i < size; ++i) {
        tree.insert(arr[i], arr[i]);
        std::cout << arr[i] << std::endl;
    }
}

static void testDel(RBTree tree, int arr[], int size) {
    for (int i = 0; i < size; ++i) {
        tree.del(arr[i]);
        std::cout << arr[i] << std::endl;
    }
}

int main() {
    RBTree testTree;

//    int test1[10] = {3, 61, 60, 66, 77, 32, 82, 56, 27, 93};
//    testInsert(testTree, test1, 10);
//    testDel(testTree, test1, 10);

//    int test2[20] = {51, 14, 64, 62, 56, 69, 73, 45, 79, 64, 98, 80, 12, 77, 97, 31, 12, 37, 85, 62};
//    testInsert(testTree, test2, 20);
//    testDel(testTree, test2, 20);

//    int test3[50] = {56, 60, 93, 20, 41, 90, 19, 63, 18, 78,
//                     75, 68, 53,  9, 96, 70,  2, 83, 68, 13,
//                     60, 88, 56, 45, 55, 75, 99, 74, 81, 88,
//                     23, 58, 43, 82, 50, 63, 23, 40, 81, 86,
//                     58, 56, 53, 10, 65, 48, 80, 66, 31, 47
//    };
//    testInsert(testTree, test3, 50);
//    testDel(testTree, test3, 50);

//    int test4[100] = { 56,  60,  93,  20,  41,  90,  19,  63,  18,  78,  75,  68,  53,   9,  96,  70,   2,  83,  68,  13,
//                      140, 601, 242, 393, 227, 200, 194, 557, 750, 707, 291, 733, 387, 641, 380, 917, 840,  35, 365, 384,
//                      477, 109, 577, 253, 102, 885, 163, 235, 717, 480, 238, 856,  81, 479, 249, 307, 678, 442, 864, 427,
//                      148, 154, 159, 535, 795, 539, 451, 634, 573, 815,  17,  50, 923, 594, 303,  25, 478, 465, 259, 194,
//                      945, 496,  49,  25, 975, 298, 332, 652, 739, 195,  79, 886, 348, 238, 420, 142, 776, 871, 775, 349
//    };
//    testInsert(testTree, test4, 100);
//    testDel(testTree, test4, 100);

//    int test5[200] = {    3,  34, 362, 190, 732, 703, 175, 899, 392, 975, 851, 893, 554, 812, 679, 363, 376, 179, 232, 225,
//                        358, 401,  66, 733, 585, 255, 418, 728, 581, 506, 837, 583, 540, 198, 772, 271, 901, 946, 170, 293,
//                        921,  21, 185, 474, 833, 863, 836, 208,  42,  68, 433, 399, 468, 498, 132,  52, 753, 549, 780, 333,
//                        495, 617, 916, 594, 814, 687, 865, 715, 633,  35,   7, 553, 191,  26, 887,  54, 862,  95,  96, 929,
//                        527,  55, 397,  24, 626, 449, 777, 228, 109, 229, 844, 823, 658, 711, 688, 372, 344, 722, 379, 897,
//                        570, 923, 664, 624, 784, 758, 719, 713, 284, 213, 110, 308, 839, 558,  84,  13, 786, 193, 241, 629,
//                        217,  64, 287, 928, 751, 659, 473,  37, 167, 249, 607,  89, 912, 230, 873, 669, 948, 953, 161, 695,
//                        260, 999, 252, 343,  11, 536, 666, 752, 315, 952,  65, 610, 950, 537, 647, 116, 253, 205, 697, 482,
//                         77, 366, 429, 662, 319, 590, 356, 578, 588, 608, 599, 644, 456, 850, 310, 164, 261, 886, 871, 835,
//                        765, 517, 951, 550, 769, 155, 247, 251, 613, 680, 894, 931, 269, 509, 857, 455, 500, 885, 304, 810
//    };
//    testInsert(testTree, test5, 200);
//    testDel(testTree, test5, 200);

    std::cout << "Hello, World!" << std::endl;
    return 0;
}

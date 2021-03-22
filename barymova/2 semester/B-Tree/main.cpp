#include <iostream>

const int t = 2;
struct BNode {
    int keys[2 * t];
    //int data[2 * t];
    BNode* children[2 * t + 1];
    BNode* parent;
    int countKeys;     //текущее количество ключей
    int countChildren; //текущее количество детей
    bool leaf;         //является ли узел листом
};

class Tree {
private:
    BNode* root;
    void insertToNode(int key, BNode* node); //Вставка ключа в уже известный узел
    void sortKeys(BNode* node);              //Сортировка ключей в узле
    void restruct(BNode *node);              //Перестраивание дерева, если какой-то из узлов заполнен


public:
    Tree();
    ~Tree();
    void insert(int key);
    bool search(int key);
};

Tree::Tree() {
    root = nullptr;
}

Tree::~Tree() {
    //здесь будет удаление дерева
}

void Tree::insertToNode(int key, BNode* node) {
    node->keys[node->countKeys] = key; //вставляем новый ключ
    node->countKeys++; //увеличиваем текущее количество ключей
    sortKeys(node); //сортируем ключи в узле
}

void Tree::sortKeys(BNode* node) { //Сортировка вставками
    for (int i = 1; i < node->countKeys; i++){
        int temp = node -> keys[i];
        int j = i;
        while (j > 0 && node->keys[j - 1] > temp){
            node->keys[j] = node->keys[j - 1];
            j--;
        }
        node->keys[j] = temp;
    }
}

void Tree::insert(int key) {
    if (root == nullptr) {          //Если дерево пустое
        BNode* newRoot = new BNode; //создаём новый корень
        root = newRoot;
        newRoot -> keys[0] = key;   //вставляем ключ и заполняем нач. знач-и остальные параметры
        newRoot->countKeys = 1;
        for (int j = 1; j <= (2 * t - 1); j++) {
            newRoot -> keys[j]=0;
        }
        for (int i=0; i<=(2*t); i++) {
            newRoot->children[i] = nullptr;
        }
        newRoot->countChildren = 0;
        newRoot->leaf = true;
        newRoot->parent = nullptr;
    } else {                        //Если дерево не пустое, то ищем нужный узел
        BNode* ptrToNode = root;
        while (!ptrToNode->leaf){   //перебираем узлы дерева, пока не дошли до листа
            for (int i = 0; i < 2 * t; i++){ //перебираем ключи в каждом узле
                if (ptrToNode->keys[i] == 0) {  //Если встретили пустой ключ
                    break;                      //дальше нечего проверять
                } else if (ptrToNode->keys[i] > key) { //Если вставляемый ключ меньше ключа в узле
                    ptrToNode = ptrToNode->children[i]; //то смотрим ребёнка узла
                    break;
                } else if (ptrToNode->keys[i + 1] == 0) { //Это выполнится, если элемент относится к крайнему правому узлу
                    ptrToNode = ptrToNode->children[i + 1];
                }
            }
        }
        //Вставляем ключ
        insertToNode(key, ptrToNode);

        //Перестраиваем дерево при необходимости
        while (ptrToNode->countKeys == 2 * t){
            if (ptrToNode == root){
                restruct(ptrToNode);
                break;
            } else {
                restruct(ptrToNode);
                ptrToNode = ptrToNode->parent;
            }
        }
    }
}

void Tree::restruct(BNode *node) {
    //Здесь будет функция, перестраивающая дерево
}

bool Tree::search(int key) {
    //Здесь будет функция поиска по ключу
}

int main() {
    return 0;
}

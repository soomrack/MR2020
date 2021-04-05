#include <iostream>
#include <cstdlib> // for min

const int T = 2;

struct BNode {
    int keys[2 * T - 1];
    int data[2 * T - 1];
    BNode* children[2 * T];
    BNode* parent;
    int countKeys;     //текущее количество ключей
    int countChildren; //текущее количество детей
    bool leaf;         //является ли узел листом
};

class Tree {
private:
    BNode* root;
    void insertToNode(int key, int data, BNode* node); // Вставка ключа в уже известный узел
    void sortKeys(BNode* node);              // Сортировка ключей в узле
    void split(BNode *node);                 // Перестраивание дерева, если какой-то из узлов заполнен
    bool searchKey(int key, BNode *node);    // Поиск по ключу. Имеет более удобный интерфейс, чем search()
public:
    Tree();
    ~Tree();
    void insert(int key, int data);
    bool search(int key);
};

Tree::Tree() {
    root = nullptr;
}

Tree::~Tree() {
    //здесь будет удаление дерева
}

void Tree::insertToNode(int key, int data, BNode* node) {
    node->keys[node->countKeys] = key; //вставляем новый ключ
    node->data[node->countKeys] = data; //вставляем данные
    node->countKeys++; //увеличиваем текущее количество ключей
    sortKeys(node); //сортируем ключи в узле
}

void Tree::sortKeys(BNode* node) { //Сортировка вставками
    for (int i = 0; i < node->countKeys; i++) {
        int tempKey = node->keys[i];
        int tempData = node->data[i];
        int j = i;
        while (j > 0 && node->keys[j - 1] > tempKey) {
            node->keys[j] = node->keys[j - 1];
            node->data[j] = node->data[j - 1];
            j--;
        }
        node->keys[j] = tempKey;
        node->data[j] = tempData;
    }
}

void Tree::insert(int key, int data) {
    if (root == nullptr) {          // Если дерево пустое
        BNode* newRoot = new BNode; // создаём новый корень
        root = newRoot;
        newRoot->countKeys = 0;     // Обнуляем всё
        for (int i = 0; i < (2 * T - 1); i++) {
            newRoot -> keys[i] = 0;
            newRoot -> data[i] = 0;
            newRoot->children[i] = nullptr;
        }
        newRoot->children[2 * T - 1] = nullptr;
        newRoot->countChildren = 0;
        newRoot->leaf = true;
        newRoot->parent = nullptr;
        insertToNode(key, data, newRoot); // вставляем данные
    } else {                        //Если дерево не пустое, то ищем нужный узел
        BNode* ptrToNode = root;
        while (!ptrToNode->leaf) {   //перебираем узлы дерева, пока не дошли до листа
            for (int i = 0; i < 2 * T; i++) { //перебираем ключи в каждом узле
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
        insertToNode(key, data, ptrToNode);

        //Перестраиваем дерево при необходимости
        while (ptrToNode->countKeys == 2 * T) {
            if (ptrToNode == root) {
                split(ptrToNode);
                break;
            } else {
                split(ptrToNode);
                ptrToNode = ptrToNode->parent;
            }
        }
    }
}

void Tree::split(BNode *node) {
    // Исходный узел разбиваем на 2. В первый перейдёт первая половина ключей и детей,
    // во второй - вторая. Если исходный узел - корневой, то он остаётся с ключом Т,
    // а новые два становятся его детьми. Если не корневой, то новые два встают на его место.

    // Первый новый узел
    BNode *child1 = new BNode;
    for (int i = 0; i < T - 1; i++) { // Копируем первую половину данных из исх в нов узел
        child1->keys[i] = node->keys[i];
        child1->data[i] = node->data[i];
    }
    for (int i = T; i < 2 * T - 1; i++) { // Вторую половину нового узла заполняем 0
        child1->keys[i] = 0;
        child1->data[i] = 0;
    }
    child1->countKeys = T - 1; // устанавливаем количество ключей в новом узле
    if (node->countChildren != 0) {        // Если в исх узле есть дети
        for (int i = 0; i < T; i++) {      // переносим первую половину в вновый узел
            child1->children[i] = node->children[i];
            child1->children[i]->parent = child1;
        }
        for (int i = T; i < 2 * T; i++) {  // вторую половину оставляем пустой
            child1->children[i] = nullptr;
        }
        child1->leaf = false;
        child1->countChildren = __min(T, node->countChildren);  // Устанавливаем количество детей
    } else {                            // Если нет детей
        child1->leaf = true;
        child1->countChildren = 0;
        for (int i = 0; i < 2 * T; i++) {
            child1->children[i] = nullptr;
        }
    }

    // Второй новый узел
    BNode *child2 = new BNode;
    for (int i = 0; i < T; i++) {
        child2->keys[i] = node->keys[i + T];
        child1->data[i] = node->data[i + T];
    }
    for (int i = T; i < 2 * T - 1; i++) {
        child2->keys[i] = 0;
        child1->data[i] = 0;
    }
    child2->countKeys = T - 1;
    if (node->countChildren > T) {
        for (int i = 0; i < T; i++){
            child2->children[i] = node->children[i + T];
            child2->children[i]->parent = child2;
        }
        for (int i = T; i < 2 * T; i++) {
            child2->children[i] = nullptr;
        }
        child2->leaf = false;
        child2->countChildren = node->countChildren % T; //количество сыновей
    } else {
        child2->leaf = true;
        child2->countChildren = 0;
        for (int i = 0; i < 2 * T; i++) {
            child2->children[i] = nullptr;
        }
    }

    // Родитель новых узлов
    if (node->parent == nullptr){ // Если у исходного узла родителя нет, то исх - корень
        node->keys[0] = node->keys[T - 1];
        node->data[0] = node->data[T - 1];
        node->countKeys = 1;
        for (int i = 1; i < 2 * T - 1; i++)  {
            node->keys[i] = 0;
            node->data[i] = 0;
        }
        node->children[0] = child1;
        node->children[1] = child2;
        child1->parent = node;
        child2->parent = node;
        node->countChildren = 2;
        for(int i = 2; i <= 2 * T; i++) {
            node->children[i] = nullptr;
        }
        node->leaf = false;
    } else { // Если исходный узел - не корень
        insertToNode(node->keys[T - 1],node->data[T - 1], node->parent);
        int prevNode = 0; // Индекс ссылки на прежний узел в массиве ссылок на детей
        for (int i = 0; i < 2 * T; i++){
            if (node->parent->children[i] == node) { // Ищем в родительском узле исходного ссылку на исходный узел
                node->parent->children[i] = nullptr; // и обнуляем её
                prevNode = i;
            }
        }
        for (int i = node->parent->countChildren; i > prevNode; i--) { // Сдвигаем ссылки на детей, чтобы освободить два места на нов
            node->parent->children[i] = node->parent->children[i - 1];
        }
        node->parent->children[prevNode] = child1;
        node->parent->children[prevNode + 1] = child2;
        child1->parent = node->parent;
        child2->parent = node->parent;
        node->parent->leaf = false;
        delete node;
    }
}

bool Tree::search(int key){
    return searchKey(key, this->root); //
}

bool Tree::searchKey(int key, BNode *node) {
    if (node == nullptr) { // Дошли до пустого узла - значит искомого ключа нет
        return false;
    }
    for (int i = 0; i < 2 * T - 1; i++) {
        if (key == node->keys[i]) { // Нашли нужный узел
            return true;
        }
        if (!node->leaf) {  // Если не лист
            if (key < node->keys[i]){ // Если искомый ключ меньше, чем текущий сравниваемый
                return searchKey(key, node->children[i]); // Смотрим ребёнка слева от него
            }
            if (node->keys[i] == 0) { // Если дошли до пустого ключа, то уже проверили весь узел
                return searchKey(key, node->children[i]); // Проверим ребёнка с бОльшими ключами
            }
        }
    }
    return false;
}

int main() {
    return 0;
}

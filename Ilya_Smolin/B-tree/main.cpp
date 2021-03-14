#include <iostream>
using namespace std;

const int t = 2;  //Степень Б-дерева

struct Node
{
    int keys [2*t]; //Массив ключей
    Node *sons [2*t+1]; //Массив указателей на потомков
    int countSons;
    int countKeys;
    Node *father; //Указатель на предка
    bool leaf;
};

class Tree {
private:
    Node *root;
    void insert_to_node(int key, Node *node);
    void sort(Node *node);
    void restruct(Node *node);
    void delete_node(Node *node);
    bool search_key(int key, Node *node);
    void remove(int key, Node *node);
    void removeFromNode(int key, Node *node);
    void removeLeaf(int key, Node *node);
    void left_connect(Node *node, Node *othernode);
    void right_connect(Node *node, Node *othernode);
    void repair(Node *node);

public:
    Tree();
    ~Tree();
    void insert(int key);
    bool search(int key);
    void remove(int key);
};

Tree::Tree() { root=nullptr; }

Tree::~Tree(){ if(root!=nullptr) delete_node(root); }

void Tree::delete_node(Node *node) //Рекурсивное удаление узла и всего, что к нему было привязано
{
    if (node != nullptr)
        for (int i = 0; i <= (2 * t - 1); i++)
        {
            if (node->sons[i] != nullptr)
                delete_node(node->sons[i]);
            else
            {
                delete(node);
                break;
            }
        }
}

void Tree::insert_to_node(int key, Node *node)
{
    node->keys[node->countKeys] = key;
    node->countKeys = node->countKeys + 1;
    sort(node);
}

void Tree::sort(Node *node)
{
    int m ;
    for (int i = 0; i < (2 * t - 1); i++)
        for (int j = i + 1; j <= (2 * t - 1); j++)
        {
            if ((node->keys[i] != 0) && (node->keys[j] != 0))
            {
                if ((node->keys[i]) > (node->keys[j]))
                {
                    m = node->keys[i];
                    node->keys[i] = node->keys[j];
                    node->keys[j] = m;
                }
            }
            else
                break;
        }
}

void Tree::insert(int key)
{
    if (root == nullptr)
    {
        Node *newRoot = new Node;
        newRoot->keys[0] = key;
        for (int j = 1; j <= (2 * t - 1); j++)
            newRoot->keys[j] = 0;
        for (int i = 0; i <= (2 * t); i++)
            newRoot->sons[i] = nullptr;
        newRoot->countKeys = 1;
        newRoot->countSons = 0;
        newRoot->leaf = true;
        newRoot->father = nullptr;
        root = newRoot;
    }
    else
    {
        Node *ptr = root;
        while (ptr->leaf == false)
        { //выбор ребенка до тех пор, пока узел не будет являться листом
            for (int i = 0; i <= (2 * t - 1); i++)
            { //перебираем все ключи
                if (ptr->keys[i] != 0)
                {
                    if (key < ptr->keys[i])
                    {
                        ptr = ptr->sons[i];
                        break;
                    }
                    if ((ptr->keys[i + 1] == 0)&&(key > ptr->keys[i]))
                    {
                        ptr = ptr->sons[i + 1]; //перенаправляем к самому последнему ребенку
                        break;
                    }
                }
                else
                    break;
            }
        }
        insert_to_node(key, ptr);

        while (ptr->countKeys == 2 * t)
        {
            if (ptr == root)
            {
                restruct(ptr); //Разбиение
                break;
            }
            else
            {
                restruct(ptr); //Разбиение
                ptr = ptr->father;
            }
        }
    }
}

void Tree::restruct(Node *node)
{
    if (node->countKeys < (2 * t - 1))
        return;

    //первый сын
    Node *child1 = new Node;
    int j = 0;
    for (; j <= t - 2; j++)
        child1->keys[j] = node->keys[j];
    for (j = t - 1; j <= (2 * t - 1); j++)
        child1->keys[j] = 0;
    child1->countKeys = t - 1; //количество ключей в узле
    if (node->countSons != 0)
    {
        for (int i = 0; i <= (t - 1); i++)
        {
            child1->sons[i] = node->sons[i];
            child1->sons[i]->father = child1;
        }
        for (int i = t; i <= (2 * t); i++)
            child1->sons[i] = nullptr;
        child1->leaf = false;
        child1->countSons = t - 1; //количество сыновей
    }
    else
    {
        child1->leaf = true;
        child1->countSons = 0;
        for (int i = 0; i <= (2 * t); i++)
            child1->sons[i] = nullptr;
    }

    //второй сын
    Node *child2 = new Node;
    for (int j = 0; j <= (t - 1); j++)
        child2->keys[j] = node->keys[j + t];
    for (j = t; j <= (2 * t - 1); j++)
        child2->keys[j] = 0;
    child2->countKeys = t; //количество ключей в узле
    if (node->countSons != 0)
    {
        for (int i = 0; i <= t; i++)
        {
            child2->sons[i] = node->sons[i + t];
            child2->sons[i]->father = child2;
        }
        for (int i = t + 1; i <= 2 * t; i++)
            child2->sons[i] = nullptr;
        child2->leaf = false;
        child2->countSons = t; //количество сыновей
    }
    else
    {
        child2->leaf = true;
        child2->countSons = 0;
        for (int i = 0; i <= 2 * t; i++)
            child2->sons[i] = nullptr;
    }

    //родитель
    if (node->father == nullptr)
    { //если родителя нет, то это корень
        node->keys[0] = node->keys[t - 1];
        for (int j = 1; j <= (2 * t - 1); j++)
            node->keys[j] = 0;
        node->sons[0] = child1;
        node->sons[1] = child2;
        for (int i = 2; i <= (2 * t); i++)
            node->sons[i] = nullptr;
        node->father = nullptr;
        node->leaf = false;
        node->countKeys = 1;
        node->countSons = 2;
        child1->father = node;
        child2->father = node;
    }
    else
    {
        insert_to_node(node->keys[t - 1], node->father);
        for (int i = 0; i <= (2 * t); i++)
            if (node->father->sons[i] == node)
                node->father->sons[i] = nullptr;
        for (int i = 0; i <= (2 * t); i++)
        {
            if (node->father->sons[i] == nullptr)
            {
                for (int j = (2 * t); j > (i + 1); j--)
                    node->father->sons[j] = node->father->sons[j - 1];
                node->father->sons[i + 1] = child2;
                node->father->sons[i] = child1;
                break;
            }
        }
        child1->father = node->father;
        child2->father = node->father;
        node->father->leaf = false;
        delete node;
    }
}

bool Tree::search(int key)
{
    return search_key(key, this->root);
}

bool Tree::search_key(int key, Node *node)
{
    if (node != nullptr)
    {
        if (node->leaf == false)
        {
            int i = 0;
            for (i = 0; i <= (2 * t - 1); i++)
            {
                if (node->keys[i] != 0)
                {
                    if(key == node->keys[i])
                        return true;
                    if (key < node->keys[i])
                    {
                        return search_key(key, node->sons[i]);
                        break;
                    }
                }
                else
                    break;
            }
            return search_key(key, node->sons[i]);
        }
        else
        {
            for (int j = 0; j <= (2 * t - 1); j++)
                if (key == node->keys[j])
                    return true;
            return false;
        }
    }
    else
        return false;
}

void Tree::removeFromNode (int key, Node *node) //Простой метод удаления ключа из узла
{
    for (int i = 0; i < node->countKeys; i++)
    {
        if (node->keys[i] == key)
        {
            for (int j = i; j < node->countKeys; j++)
            {
                node->keys[j] = node->keys[j + 1];
                node->sons[j] = node->sons[j + 1];
            }
            node->keys[node->countKeys - 1] = 0;
            node->sons[node->countKeys - 1] = node->sons[node->countKeys];
            node->sons[node->countKeys] = nullptr;
            break;
        }
    }
    node->countKeys--;
}

void Tree::left_connect(Node *node, Node *othernode)
{
    if (node == nullptr)
        return;
    for (int i = 0; i <= (othernode->countKeys - 1); i++)
    {
        node->keys[node->countKeys] = othernode->keys[i];
        node->sons[node->countKeys] = othernode->sons[i];
        node->countKeys = node->countKeys + 1;
    }
    node->sons[node->countKeys] = othernode->sons[othernode->countKeys];
    for (int j = 0; j <= node->countKeys; j++)
    {
        if (node->sons[j] == nullptr)
            break;
        node->sons[j]->father = node;
    }
    delete othernode;
}

void Tree::right_connect(Node *node, Node *othernode)
{
    if (node == nullptr)
        return;
    for (int i = 0; i <= (othernode->countKeys - 1); i++)
    {
        node->keys[node->countKeys] = othernode->keys[i];
        node->sons[node->countKeys + 1] = othernode->sons[i + 1];
        node->countKeys = node->countKeys + 1;
    }
    for (int j = 0; j <= node->countKeys; j++)
    {
        if (node->sons[j] == nullptr)
            break;
        node->sons[j]->father = node;
    }
    delete othernode;
}

void Tree::repair(Node *node){
    if ((node == root)&&(node->countKeys == 0))
    {
        if (root->sons[0] != nullptr)
        {
            root->sons[0]->father = nullptr;
            root = root->sons[0];
        }
        else
            delete root;
        return;
    }
    Node *ptr = node;
    int positionSon = 0;
    Node *parent = ptr->father;
    for (int j = 0; j <= parent->countKeys; j++)
    {
        if (parent->sons[j] == ptr)
        {
            positionSon = j; //позиция узла по отношению к родителю
            break;
        }
    }
    //если ptr-первый ребенок (самый левый)
    if (positionSon == 0)
    {
        insert_to_node(parent->keys[positionSon], ptr);
        left_connect(ptr, parent->sons [positionSon+1]);
        parent->sons[positionSon + 1] = ptr;
        parent->sons[positionSon] = nullptr;
        removeFromNode(parent->keys[positionSon], parent);
        if (ptr->countKeys == 2 * t)
        {
            while (ptr->countKeys == 2 * t)
            {
                if (ptr == root)
                {
                    restruct(ptr);
                    break;
                }
                else
                {
                    restruct(ptr);
                    ptr = ptr->father;
                }
            }
        }
        else
        if (parent->countKeys <= t - 2) repair(parent);
    }
    else
    {
        //если ptr-последний ребенок (самый правый)
        if (positionSon == parent->countKeys)
        {
            insert_to_node(parent->keys[positionSon - 1], parent->sons[positionSon - 1]);
            left_connect(parent->sons[positionSon - 1], ptr);
            parent->sons[positionSon] = parent->sons[positionSon - 1];
            parent->sons[positionSon - 1] = nullptr;
            removeFromNode(parent->keys[positionSon - 1], parent);
            Node *temp = parent->sons[positionSon];
            if (ptr->countKeys == 2 * t)
            {
                while (temp->countKeys == 2 * t)
                {
                    if (temp == root)
                    {
                        restruct(temp);
                        break;
                    }
                    else
                    {
                        restruct(temp);
                        temp = temp->father;
                    }
                }
            }
            else
            if (parent->countKeys <= t - 2) repair(parent);
        }
        else
        { //если ptr имеет братьев справа и слева
            insert_to_node(parent->keys[positionSon], ptr);
            left_connect(ptr, parent->sons[positionSon + 1]);
            parent->sons[positionSon + 1] = ptr;
            parent->sons[positionSon] = nullptr;
            removeFromNode(parent->keys[positionSon], parent);
            if(ptr->countKeys == 2 * t)
            {
                while (ptr->countKeys == 2 * t)
                {
                    if (ptr == root)
                    {
                        restruct(ptr);
                        break;
                    }
                    else
                    {
                        restruct(ptr);
                        ptr = ptr->father;
                    }
                }
            }
            else
            if (parent->countKeys <= t - 2)
                repair(parent);
        }
    }
}

void Tree::removeLeaf (int key, Node *node)
{
    if ((node == root)&&(node->countKeys == 1))
    {
        removeFromNode(key, node);
        root->sons[0] = nullptr;
        delete root;
        root = nullptr;
        return;
    }
    if (node == root)
    {
        removeFromNode(key, node);
        return;
    }
    if (node->countKeys > t - 1)
    {
        removeFromNode(key, node);
        return;
    }
    Node *ptr = node;
    int k1 = 0;
    int k2 = 0;
    int position = 0;
    int positionSon = 0;
    for (int i = 0; i <= node->countKeys - 1; i++)
    {
        if (key == node->keys[i])
        {
            position = i; //позиция ключа в узле
            break;
        }
    }
    Node *parent = ptr->father;
    for (int j = 0; j <= parent->countKeys; j++)
    {
        if (parent->sons[j] == ptr)
        {
            positionSon = j; //позиция узла по отношению к родителю
            break;
        }
    }
    //если ptr-первый ребенок (самый левый)
    if (positionSon == 0)
    {
        if (parent->sons[positionSon + 1]->countKeys > t - 1)
        { //если у правого брата больше, чем t-1 ключей
            k1 = parent->sons[positionSon + 1]->keys[0]; //k1 - минимальный ключ правого брата
            k2 = parent->keys[positionSon]; //k2 - ключ родителя, больше, чем удаляемый, и меньше, чем k1
            insert_to_node(k2, ptr);
            removeFromNode(key, ptr);
            parent->keys[positionSon] = k1; //меняем местами k1 и k2
            removeFromNode(k1, parent->sons[positionSon + 1]); //удаляем k1 из правого брата
        }
        else
        { //если у правого <u>единственного</u> брата не больше t-1 ключей
            removeFromNode(key, ptr);
            if (ptr->countKeys <= t - 2)
                repair(ptr);
        }
    }
    else
    {
        //если ptr-последний ребенок (самый правый)
        if (positionSon == parent->countKeys)
        {
            //если у левого брата больше, чем t-1 ключей
            if (parent->sons[positionSon - 1]->countKeys > t - 1)
            {
                Node *temp = parent->sons[positionSon - 1];
                k1 = temp->keys[temp->countKeys - 1]; //k1 - максимальный ключ левого брата
                k2 = parent->keys[positionSon - 1]; //k2 - ключ родителя, меньше, чем удаляемый и больше, чем k1
                insert_to_node(k2, ptr);
                removeFromNode(key, ptr);
                parent->keys[positionSon - 1] = k1;
                removeFromNode(k1, temp);
            }
            else
            { //если у <u>единственного</u> левого брата не больше t-1 ключей
                removeFromNode(key, ptr);
                if (ptr->countKeys <= t - 2)
                    repair(ptr);
            }
        }
        else
        { //если ptr имеет братьев справа и слева
            //если у правого брата больше, чем t-1 ключей
            if (parent->sons[positionSon + 1]->countKeys > t - 1)
            {
                k1 = parent->sons[positionSon + 1]->keys[0]; //k1 - минимальный ключ правого брата
                k2 = parent->keys[positionSon]; //k2 - ключ родителя, больше, чем удаляемый и меньше, чем k1
                insert_to_node(k2, ptr);
                removeFromNode(key, ptr);
                parent->keys[positionSon] = k1; //меняем местами k1 и k2
                removeFromNode(k1, parent->sons[positionSon + 1]); //удаляем k1 из правого брата
            }
            else
            {
                //если у левого брата больше, чем t-1 ключей
                if (parent->sons[positionSon - 1]->countKeys > t - 1)
                {
                    Node *temp = parent->sons[positionSon - 1];
                    k1 = temp->keys[temp->countKeys - 1]; //k1 - максимальный ключ левого брата
                    k2 = parent->keys[positionSon - 1]; //k2 - ключ родителя, меньше, чем удаляемый и больше, чем k1
                    insert_to_node(k2, ptr);
                    removeFromNode(key, ptr);
                    parent->keys[positionSon - 1] = k1;
                    removeFromNode(k1, temp);
                }
                else
                { //если у обоих братьев не больше t-1 ключей
                    removeFromNode(key, ptr);
                    if (ptr->countKeys <= t - 2) repair(ptr);
                }
            }
        }
    }
}

void Tree::remove(int key, Node *node)
{
    Node *ptr = node;
    int position = 0; //номер ключа
    for (int i = 0; i <= node->countKeys - 1; i++)
    {
        if (key == node->keys[i])
        {
            position = i;
            break;
        }
    }
    int positionSon = 0; //номер сына по отношению к родителю
    if (ptr->father != nullptr)
    {
        for (int i = 0; i <= ptr->father->countKeys; i++)
            if (ptr->sons[i] == ptr)
            {
                positionSon = i;
                break;
            }
    }
    //находим наименьший ключ правого поддерева
    ptr = ptr->sons[position + 1];
    int newkey = ptr->keys[0];
    while (ptr->leaf == false) ptr = ptr->sons[0];
    //если ключей в найденном листе не больше 1 - ищем наибольший ключ в левом поддереве
    //иначе - просто заменяем key на новый ключ, удаляем новый ключ из листа
    if (ptr->countKeys > t - 1)
    {
        newkey = ptr->keys[0];
        removeFromNode(newkey, ptr);
        node->keys[position] = newkey;
    }
    else
    {
        ptr = node;
        //ищем наибольший ключ в левом поддереве
        ptr = ptr->sons[position];
        newkey = ptr->keys[ptr->countKeys - 1];
        while (ptr->leaf == false)
            ptr = ptr->sons[ptr->countKeys];
        newkey = ptr->keys[ptr->countKeys - 1];
        node->keys[position] = newkey;
        if (ptr->countKeys > t - 1)
            removeFromNode(newkey, ptr);
        else
            //если ключей не больше, чем t-1 - перестраиваем
            removeLeaf(newkey, ptr);
    }
}

void Tree::remove(int key)
{
    Node *ptr = this->root;
    int position = 0;
    int positionSon = 0;
    int i = 0;
    if (search_key(key, ptr) == false)
        return;
    else
    {
        //ищем узел, в котором находится ключ для удаления
        for (i = 0; i <= ptr->countKeys - 1; i++)
        {
            if (ptr->keys[i] != 0)
            {
                if (key == ptr->keys[i])
                {
                    position = i;
                    break;
                }
                else
                {
                    if ((key < ptr->keys[i]))
                    {
                        ptr = ptr->sons[i];
                        positionSon = i;
                        i = -1;
                    }
                    else
                    {
                        if (i == (ptr->countKeys - 1))
                        {
                            ptr = ptr->sons[i + 1];
                            positionSon = i + 1;
                            i = -1;
                        }
                    }
                }
            }
            else
                break;
        }
    }
    if (ptr->leaf == true)
    {
        if (ptr->countKeys > t - 1)
            removeFromNode(key,ptr);
        else removeLeaf(key, ptr);
    }
    else
        remove(key, ptr);
}

int main()
{
    return 0;
}

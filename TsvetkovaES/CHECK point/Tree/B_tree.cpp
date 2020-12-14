
// Created by alena on 29.11.2020.
#include "B_tree.h"

Node::Node() {
    left = nullptr;
    right = nullptr;
}
Node::Node(const int key, const std::string data) {
    this->key = key;
    this->data = data;
    this->left = nullptr;
    this->right = nullptr;
}
Node::Node(const int key, const std::string data, Node *left, Node *right) {
    Node* new_node = new Node;
    new_node->key = key;
    new_node->data = data;
    new_node->left = left;
    new_node->right = right;
}
Node::~Node() {
    this->left = nullptr;
    this->right = nullptr;
}
Tree::Tree() {
    root = nullptr;
}
Tree::~Tree() {
    delete root;
}

bool Tree::insert(Node *& new_node, const int key, const std::string data) {
    if(new_node == nullptr) {
        new_node = new Node(key,data); // нашли свободное местечко - создали node
        return true;
    }
    if(key > new_node->key) {
        return insert(new_node->right, key, data); // ищем справа
    }
    else if(key < new_node->key) {
        return insert(new_node->left, key, data); // ищем слева
    }
    else { // Hи больше, ни меньше, значит равно...
        printf("The key %d is already in the tree!\n",key);
        // ...Key уже есть - вернём false
        return false;
    }
}

bool Tree::add(const int key, const std::string data) {
    if(root == nullptr) {
        root = new Node (key, data); // если дерево пусто
        return true;
    }
    return insert(root,key,data);
}

bool Tree::search(const int key, Node *&root, Node *&new_node, Node *&parent) {
    // Если у node вообще нет ключа, и
    // мы дошли до листа nullptr - возвращаем nullptr
    if(root == nullptr) {
        new_node = nullptr;
        return false;
    }
    if(key == root->key) {
        new_node = root;
        return true; // если нашли таки - возвращаем
    }
    else if(key > root->key) {
        parent = root;
        return search(key, root->right, new_node, parent); // ищем в сторону больших
    }
    else {
        parent = root;
        return search(key, root->left, new_node, parent); // ищем в сторону меньших
    }
}

std::string Tree::find(const int key) {
    if (!root) {
        printf("The tree is empty!\n");
        return "";
    }
    Node* parent = nullptr;
    Node* new_node;
    search(key, root, new_node, parent);
    if(new_node) {
        //printf("%s",new_node->data.c_str());
        return new_node->data;
    }
    else { // если нам вернули nullptr - ключа не нашлось
        printf("There is no key in the tree!\n");
        return "";
    }
}

bool Tree::del(const int key) {
    if (root == nullptr) {
        printf("The tree is empty!\n");
        return false;
    }
    Node* parent = nullptr;
    //Node* node_to_del = search(root, key, parent);
    Node* node_to_del;
    bool in_the_tree = search(key, root, node_to_del, parent);
    // если элемента по ключу не нашлось, нам вернули nullptr:
    if(in_the_tree == false) {
        printf("There is no key in the tree!\n");
        return false;
    }
    // если это просто листик (без детей вовсе):
    if (node_to_del->left == nullptr && node_to_del->right == nullptr) {
        if (parent->left == node_to_del && node_to_del!=root) {
            parent->left = nullptr;
        }
        else {
            parent->right = nullptr;
        }
        delete node_to_del;
        return true;
    } else
        // если один ребёнок:
    if(node_to_del->left == nullptr || node_to_del->right == nullptr) {
        Node* child = (node_to_del->left)? node_to_del->left: node_to_del->right;
        if(node_to_del == root) { // и такое бывает
            root = child;
        }
        else {
            if (node_to_del == parent->left) { // "подтягиваем" всю ветку с элемента к его родителю
                parent->left = child;
            }
            else {
                parent->right = child;
            }
        }
        delete node_to_del;
        return true;
    }
        // если два ребёнка:
    else {
        // минимальный элемент справа, ставим его
        Node *successor = search_min(node_to_del->right);
        // копируем данные этого элемента, затем его удаляем
        int key_of_del = successor->key;
        std::string data_of_del = successor->data;
        // вызываем функцию del, чтобы корректно удалить элемент successor
        // у него есть как минимум один ребёнок справа или вообще ноль детей
        del(key_of_del);
        // вместо node_to_del ставим данные successor
        node_to_del->key = key_of_del;
        node_to_del->data = data_of_del;
        return true;
    }
}
void Tree::Print_tree (Node* node, int h) { // нач. усл.: node = root, h=0
    if  (node) {
        Print_tree (node->right,h+1); // уходим в самое права
        for (int i=1; i<=h; i++) {
            printf("     ");
        }
        printf("%d (%s)\n", node->key, node->data.c_str());
        Print_tree (node->left,h+1);
    }
}
Node * Tree::search_min(Node *root) {
    Node* current = root;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}
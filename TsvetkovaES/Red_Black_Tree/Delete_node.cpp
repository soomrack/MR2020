#include "My_header.h"

bool Tree::del(const int key) {
    if (root == nullptr) {
        std::cout << termcolor::reset << "The tree is empty! Can't delete any node.\n";
        return false;
    }
    Node* node_to_del = search(key,root);
    // если элемента по ключу не нашлось, нам вернули nullptr:
    if(node_to_del == nullptr) {
        std::cout << termcolor::reset << "There is no node with " << key << " key. Can't delete node.\n";
        return false;
    }
    Node* parent = node_to_del->parent;
    // если это просто листик (без детей вовсе):
    if (node_to_del->left == nullptr && node_to_del->right == nullptr) {
        if (parent->left == node_to_del && node_to_del != root) {
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


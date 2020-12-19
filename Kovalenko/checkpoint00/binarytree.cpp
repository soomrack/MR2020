#include <iostream>

class Node {
public:
    int key;
    void *data;
    Node *left;
    Node *right;

    Node(int key, void* data) {
        this->data = data;
        this->key = key;
        left = nullptr;
        right = nullptr;
    }
};

class Tree {
public:
    Node *root;
    Tree() {
        root = nullptr;
    }
    void add(int key, void *data);//добавление элемента
    void del(int key);//удаление элемента
    Node *min(Node *root);//поиск минимального элемента
private:
    Node *prevNewNode(int key, Node *root);//подготовка к добалению элемента
    Node *prevSearch(int key, Node *root);//поиск предка
    Node *search(int key, Node *root);//поиск по дереву
};

Node *Tree::prevNewNode(int key, Node *root) {
    if (key < root->key) {
        if (root->left == nullptr) {
            return(root);
        }
        return(prevNewNode(key, root->left));
    }
    else {
        if (root->right == nullptr) {
            return(root);
        }
        return(prevNewNode(key, root->right));
    }
}

Node *Tree::prevSearch(int key, Node *root) {
    if ((key == root->left->key) || (key == root->right->key)) {
        return root;
    }
    if (key < root->key) {
        prevSearch(key, root->left);
    }
    else {
        prevSearch(key, root->right);
    }
}

Node *Tree::search(int key, Node *root) {
    if ((key == root->key) || (root == nullptr)) {
        return root;
    }
    if (key < root->key) {
        search(key, root->left);
    }
    else {
        search(key, root->right);
    }
}
void Tree::add(int key, void *data) {
    Node *child = new Node(key, data);
    if (root == nullptr) {
        root = child;
        return;
    }

    Node *prev = prevNewNode(key, child);

    if (key < prev->key) {
        prev->left = child;
    }
    else {
        prev->right = child;
    }
}
Node *Tree::min(Node *root) {
    Node *getMin = root;
    while (getMin->left != nullptr) {
        getMin = getMin->left;
    }
    return getMin;
}

void Tree::del(int key) {
    Node *delete_node = search(key, root);
    if (delete_node == nullptr) {
        return;
    }
    Node *parent_delete_node = prevSearch(key, root);
    //один из потомков не пустой
    if ((delete_node->left != nullptr) && (delete_node->right== nullptr)) {
        if (parent_delete_node->left == delete_node) {
            parent_delete_node->left = delete_node->left;
        }
        else {
            parent_delete_node->right = delete_node->left;
        }
        return;
    }
    if ((delete_node->left == nullptr) && (delete_node->right != nullptr)) {
        if (parent_delete_node->left == delete_node) {
            parent_delete_node->left = delete_node->right;
        }
        else {
            parent_delete_node->right = delete_node->right;
        }
        return;
    }
    //оба потомка пустые
    if ((delete_node->left == nullptr) && (delete_node->right == nullptr)) {
        if (parent_delete_node->left == delete_node) {
            parent_delete_node->left = nullptr;
        }
        else {
            parent_delete_node->right = nullptr;
        }
        return;
    }
    //оба потомка заполнены
    Node* temp = min(delete_node->right);
    if (temp == delete_node->right) {
        delete_node->key = temp->key;
        delete_node->data = temp->data;
        delete_node->right = temp->right;
        return;
    }
    else {
        delete_node->data = temp->data;
        delete_node->key = temp->key;
        del(temp->key);
        return;
    }

}

int main() {
    std::cout << "The end." << std::endl;
}
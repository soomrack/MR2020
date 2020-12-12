#include <iostream>
#include <string>

class Node {
public:
    int key;
    std::string data;
public:
    Node* left;
    Node* right;
public:
    Node();
    Node(const int key, const std::string data);
};

Node::Node() {
    this->key = NULL;
    this->data = "";
    this->left = nullptr;
    this->right = nullptr;
}

Node::Node(const int key, const std::string data) {
    this->key = key;
    this->data = data;
    this->left = nullptr;
    this->right = nullptr;
}

class Tree {
private:
    Node* root;
    Node* find_Node(Node* root, int key);
    Node* find_Parent(Node* root, int key);
    Node* min_Node(Node* root);
public:
    bool add(const int key, const std::string data);  // false if key already exists
    bool del(const int key);  // false if no key
    std::string find(const int key);  // return '' if no key
public:
    Tree();
    ~Tree();

};

Tree::Tree() {
    root = nullptr;
}

Tree::~Tree() {
    while (root != nullptr) { del(root->key); }
}

bool Tree::add(const int key, const std::string data) {
    if (root == nullptr) {
        root = new Node(key, data);
    }
    else {
        Node* child = new Node(key, data);
        Node* parent = find_Node(root, key);
        if (parent->key == key) {
            return false;
        }
        if (parent->key > key) {
            parent->left = child;
            return true;
        }

        parent->right = child;
        return true;

    }

}

Node* Tree::find_Node(Node* root, int key) {
    if (root->key == key) {
        return root;
    }
    else if (root->key < key) {
        if (root->right == nullptr)
            return root;
        return find_Node(root->right, key);
    }
    else {
        if (root->left == nullptr)
            return root;
        return find_Node(root->left, key);
    }
}

std::string Tree::find(const int key) {
    if (root == nullptr)
        return "";
    Node* node = find_Node(root, key);
    if (node->key == key) {
        return node->data;
    }
    else {
        return "";
    }
}

Node* Tree::find_Parent(Node* root, int key) {
    if (root->key < key) {
        if (root->right == nullptr)
            return nullptr;
        if (root->right->key == key) {
            return root;
        }
        return find_Parent(root->right, key);
    }
    if (root->key > key) {
        if (root->left == nullptr)
            return nullptr;
        if (root->left->key == key) {
            return root;
        }
        return find_Parent(root->left, key);
    }
    return nullptr;
}

Node* Tree::min_Node(Node* node) {
    if (node->left == nullptr) {
        return node;
    }
    else {
        return min_Node(node->left);
    }
}

bool Tree::del(const int key) {
    if (find(key) == "") {
        return false;
    }
    Node* node = find_Node(root, key);
    Node* parent = find_Parent(root, key);
    if ((node->left == nullptr) && (node->right == nullptr)) {
        if (node == root) {
            root = nullptr;
        }
        else if (parent->left == node) {
            parent->left = nullptr;
        }
        else {
            parent->right = nullptr;
        }
        delete node;
        return true;
    }
    if ((node->left == nullptr)) {
        if (node == root) {
            root = node->right;
        }
        else if (parent->left == node) {
            parent->left = node->right;
        }
        else {
            parent->right = node->right;
        }
        delete node;
        return true;
    }
    if ((node->right == nullptr)) {
        if (node == root) {
            root = node->left;
        }
        else if (parent->left == node) {
            parent->left = node->left;
        }
        else {
            parent->right = node->left;
        }
        delete node;
        return true;
    }

    Node* right_child = node->right;
    Node* minNode = min_Node(right_child);
    Node* minParent = find_Parent(root, minNode->key);
    int minkey = minNode->key;
    std::string mindata = minNode->data;
    del(minNode->key);
    node->key = minkey;
    node->data = mindata;
    return true;

}

struct stack_int {
    int64_t elem[100];
    int64_t top;
};

static void init_int(struct stack_int* stk) {
    stk->top = 0;
}

static void push_int(struct stack_int* stk, int64_t f) {
    stk->elem[stk->top] = f;
    stk->top++;

}

static int64_t pop_int(struct stack_int* stk) {
    int64_t elem;
    if ((stk->top) > 0)
    {
        stk->top--;
        elem = stk->elem[stk->top];
        return elem;
    }
    else
    {
        return 0;
    }
}

static int get(struct stack_int* stk) {
    if ((stk->top) > 0) {
        return stk->elem[stk->top - 1];
    }
    else {

        return 0;
    }
}

int main() {
    struct stack_int numbers;
    init_int(&numbers);
    Tree testTree;
    std::string information;
    std::string answer;
    int address;
    int i;
    std::cout << "Add?" << std::endl;
    std::cin >> answer;
    for (i = 0; answer == "yes"; i++) {
        std::cout << "Enter the data  ";
        std::cin >> information;
        std::cout << "Enter the memory cell number  ";
        std::cin >> address;
        testTree.add(address, information);
        push_int(&numbers, address);
        std::cout << "Add?" << std::endl;
        std::cin >> answer;
    }
    while (i > 0) {
        std::string str = testTree.find(get(&numbers));
        std::cout << "Data in from cell " << get(&numbers) << " : " << str << std::endl;
        pop_int(&numbers);
        i--;
    }
    std::cout << "The end." << std::endl;
    return 0;
}
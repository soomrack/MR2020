#include <iostream>

using namespace std;

const string  ELEMENT_NOT_FOUND = "";

class Node {
public:
    int KeyNode;
    string DataNode;
public:
    Node *LeftNode;
    Node *RightNode;
public:
    Node(const int key, const string data);
    Node(const int key, const string data, Node *left, Node *right);
    Node();
    ~Node();
};

class Tree {
private:
    Node *root;
    Node* findmin(Node* p) {return p -> LeftNode ? findmin(p -> LeftNode) : p;}
    Node *search (int key);
    Node *searchprev (int key);
public:
    bool add(const int key, const string data);  // false if key already exists
    bool del(const int key);  // false if no key
    std::string find(const int key);  // return '' if no key
public:
    Tree();
    ~Tree();
};

Node::Node() {
    LeftNode = nullptr;
    RightNode = nullptr;
}

Tree::Tree() {
    root = nullptr;
}

Node *Tree::search(int KeySearch) {
    Node *iterator = root;
    if (iterator == nullptr) {
        return iterator;
    }
    while (iterator -> KeyNode != KeySearch) {
        if (iterator -> KeyNode < KeySearch) {
            if (iterator -> RightNode == nullptr) {
                return nullptr;
            }
            iterator = iterator -> RightNode;
        }
        if (iterator -> KeyNode > KeySearch) {
            if (iterator -> LeftNode == nullptr) {
                return nullptr;
            }
            iterator = iterator -> LeftNode;
        }
    }
    return iterator;
}

Node *Tree::searchprev(int KeySearchPrev) {
    if (root == nullptr) {
        return nullptr;
    }

    Node *iterator = root;
    Node *prev = nullptr;
    while (iterator -> KeyNode != KeySearchPrev) {
        if (iterator -> KeyNode < KeySearchPrev) {
            if (iterator -> RightNode != nullptr) {
                prev = iterator;
                iterator = iterator -> RightNode;
            } else {
                return nullptr;
            }
        }
        if (iterator -> KeyNode > KeySearchPrev) {
            if (iterator -> LeftNode != nullptr) {
                prev = iterator;
                iterator = iterator -> LeftNode;
            } else {
                return nullptr;
            }
        }
    }
    return prev;
}

Node::Node(const int key, const string data) {
    this -> KeyNode = key;
    this -> DataNode = data;
    this -> LeftNode = nullptr;
    this -> RightNode = nullptr;
}

Node::Node(const int key, const string data, Node *left, Node *right) {
    this -> KeyNode = key;
    this -> DataNode = data;
    this -> LeftNode = left;
    this -> RightNode = right;
}

bool Tree::add(const int KeyAdd, const string DataAdd) {
    if (root == nullptr) {
        root = new Node(KeyAdd, DataAdd);
        return true;
    }
    Node *iterator = root;
    while (true) {
        if (iterator -> KeyNode < KeyAdd) {
            if (iterator -> RightNode == nullptr) {
                iterator -> RightNode = new Node (KeyAdd, DataAdd);
                return true;
            }
            iterator = iterator -> RightNode;
        }
        if (iterator -> KeyNode > KeyAdd) {
            if (iterator -> LeftNode == nullptr) {
                iterator -> LeftNode = new Node(KeyAdd, DataAdd);
                return true;
            }
            iterator = iterator -> LeftNode;
        }
        if (iterator -> KeyNode == KeyAdd) {
            return false;
        }
    }
}

bool Tree::del(const int KeyDel) {
    Node *nodetodelete = search(KeyDel);
    if (nodetodelete == nullptr)
        return false;
    Node *prev = searchprev(KeyDel);

    Node *nodetodelete_left = nodetodelete -> LeftNode;
    Node *nodetodelete_right = nodetodelete -> RightNode;

    if (nodetodelete == root) {
        if (nodetodelete_right != nullptr) {
            findmin(nodetodelete_right) -> LeftNode = nodetodelete_left;
            root = nodetodelete_right;
        } else {
            root = nodetodelete_left;
        }
        delete nodetodelete;
        return true;
    }
    if (nodetodelete_right != nullptr) {
        findmin(nodetodelete_right) -> LeftNode = nodetodelete_left;
        Node *prevright = prev -> RightNode;
        if (prevright -> KeyNode == nodetodelete -> KeyNode) {
            prev -> RightNode = nodetodelete_right;
        } else {
            prev -> LeftNode = nodetodelete_right;
        }
    } else {
        if (prev -> LeftNode == nodetodelete) {
            prev -> LeftNode = nodetodelete_left;
        } else {
            prev -> RightNode = nodetodelete_left;
        }
    }
    delete nodetodelete;
    return true;
}

string Tree::find(const int KeyFind) {
    Node *element = search(KeyFind);
    if (element == nullptr) {
        return ELEMENT_NOT_FOUND;
    }
    return (element -> DataNode);
}

Tree::~Tree() {
    delete root;
}

Node::~Node() {
    delete LeftNode;
    delete RightNode;
}

int main() {

    return 0;
}

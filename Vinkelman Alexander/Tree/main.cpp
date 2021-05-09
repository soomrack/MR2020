#include <iostream>
#include <string>

using namespace std;

class Nod {
public:
    int nod_key;
    string nod_data;
public:
    Nod *left;
    Nod *right;
public:
    Nod();
    Nod(int key, string data);
    Nod(int key, string data, Nod *left, Nod *right);
    ~Nod();
};

class Tree {
private:
    Nod *root;
    Nod *FindNod(Nod* root, int key);
    Nod *findParent (Nod * root, int key);
    Nod *findMin(Nod* root);
public:
    bool add(const int key, string data);  // false if key already exists
    bool del(const int key);
    string find(const int key);  // return '' if no key
public:
    Tree();
};

Nod::Nod() {
    left = nullptr;
    right = nullptr;
}

Nod::Nod(int key, string data) {
    this -> nod_key = key;
    this -> nod_data = data;
    left = nullptr;
    right = nullptr;
}

Nod::Nod(int key, string data, Nod *left, Nod *right) {
    this -> nod_key = key;
    this -> nod_data = data;
    this -> left = left;
    this -> right = right;
}

Nod::~Nod() {
    delete left;
    delete right;
}

Tree::Tree() {
    root = nullptr;
}

string Tree::find(const int key_find){
    Nod* nod = root;
    if (nod == nullptr) {
        return " ";
    }
    while (nod -> nod_key != key_find) {
        if (key_find > nod -> nod_key) {
            if (nod -> right == nullptr) {
                return " ";
            }
            nod = nod -> right;
        }
        if (key_find < nod -> nod_key) {
            if (nod -> left == nullptr) {
                return " ";
            }
            nod = nod -> left;
        }
    }
    return nod -> nod_data;
}

Nod* Tree::FindNod(Nod *root, int key) {
    if (root == nullptr) {
        return root;
    }
    if (root -> nod_key == key) {
        return root;
    }
    else if (root -> nod_key > key) {
        return FindNod(root -> left, key);
    }
    return FindNod(root -> right, key);
}

Nod* Tree::findParent(Nod *root, int key_parent){
    if (root -> nod_key <= key_parent) {
        if (root -> right == nullptr)
            return root;
        return findParent(root -> right, key_parent);
    }
    if (root -> nod_key > key_parent) {
        if (root -> left == nullptr)
            return root;
        return findParent(root -> left, key_parent);
    }
    return nullptr;
}

Nod* Tree::findMin (Nod *root) {
    Nod *min = root;
    while (min -> left != nullptr){
        min = min -> right;
    }
    return min;
}

bool Tree::add(const int key_add, string data) {
    Nod* child = new Nod (key_add,data);
    if (FindNod(root,key_add)!= nullptr) {
        return false;
    }
    if (root == nullptr){
        root = child;
        return true;
    }
    Nod* parent = findParent(root, key_add);
    if (key_add <= parent -> nod_key) {
        parent -> left = child;
    } else {
        parent -> right = child;
    }
    return true;
}

bool Tree::del(const int key_del){
    Nod* deletednod = FindNod(root, key_del);
    Nod* parentOfDeletednod = findParent(root, key_del);
    if (deletednod == nullptr) {
        return false;
    }
    if (deletednod -> left == nullptr && deletednod -> right == nullptr) {
        if (parentOfDeletednod -> left == deletednod) {
            parentOfDeletednod -> left = nullptr;
            delete deletednod;
            return true;
        }
        parentOfDeletednod -> right = nullptr;
        delete deletednod;
        return true;
    }
    if (deletednod -> left == nullptr && deletednod -> right != nullptr) {
        if (parentOfDeletednod -> left == deletednod) {
            parentOfDeletednod -> left = deletednod -> right;
            delete deletednod;
            return true;
        }
        parentOfDeletednod -> right = deletednod -> right;
        delete deletednod;
        return true;
    }
    if (deletednod -> left != nullptr && deletednod -> right == nullptr) {
        if (parentOfDeletednod->left == deletednod) {
            parentOfDeletednod -> left = deletednod -> left;
            delete deletednod;
            return true;
        }
        parentOfDeletednod -> right = deletednod -> left;
        delete deletednod;
        return true;
    }
    if ((deletednod -> left != nullptr) && (deletednod -> right != nullptr)) {
        Nod* temp = findMin(deletednod -> right);
        if (temp == deletednod -> right) {
            deletednod -> nod_key = temp -> nod_key;
            deletednod -> nod_data = temp -> nod_data;
            deletednod -> right = temp -> right;
            delete temp;
            return true;
        }
        deletednod -> nod_data = temp -> nod_data;
        deletednod -> nod_key = temp -> nod_key;
        del(temp -> nod_key);
        return true;
    }
};

int main() {

    return 0;
}

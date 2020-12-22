
#include <iostream>
#include <string>



class nod {
public:
    int key;
    std:: string data;
public:
    nod *left;
    nod *right;
public:
    nod();
    nod(int key, std :: string data);
    nod(int key, std :: string data, nod *left, nod *right);
    ~nod();
};


class Tree {
private:
    nod *root;
    nod *FindNod(nod* root, int key);
    nod *findParent (nod * root, int key);
    nod *findMin(nod* root);
public:
    bool add(const int key, std:: string data);  // false if key already exists
    bool del(const int key);
    std::string find(const int key);  // return '' if no key
public:
    Tree();
};

nod:: nod() {
    left = nullptr;
    right = nullptr;
}

nod ::nod(int key, std::string data) {
    this->key = key;
    this->data = data;
    left = nullptr;
    right = nullptr;
}

nod::nod( int key,  std::string data,  nod *left,  nod *right)
{
    this->key = key;
    this->data = data;
    this->left = left;
    this->right = right;
}

nod ::~nod() {
    delete left;
    delete right;
}

Tree::Tree() {
    root = nullptr;
}


std::string Tree::find(const int key){
    nod* nod = root;
    if (nod == nullptr)
        return " ";
    while (nod->key != key)
    {
        if (key > nod->key)
        {
            if (nod->right == nullptr)
                return " ";
            nod = nod->right;
        }
        if (key < nod->key)
        {
            if (nod->left == nullptr)
                return " ";
            nod = nod->left;
        }
    }
    return nod->data;
}

nod* Tree:: FindNod(nod *root, int key) {
    if (root == nullptr) return root;
    if (root->key == key) return root;
    else if (root->key > key) return FindNod(root->left, key);
    return FindNod(root->right, key);
}

nod* Tree :: findParent(nod *root, int key){
    if (root->key <= key) {
        if (root->right == nullptr)
            return root;
        return findParent(root->right, key);
    }
    if (root->key > key) {
        if (root->left == nullptr)
            return root;
        return findParent(root->left, key);
    }
    return nullptr;
}

nod* Tree :: findMin (nod *root) {
    nod *min = root;
    while (min->left != nullptr){
        min = min->right;
    }
    return min;
}

bool Tree ::add(const int key, std::string data) {
    nod* child = new nod (key,data);
    if (FindNod(root,key)!= nullptr)
        return false;
    if (root == nullptr){
        root = child;
        return true;
    }
    nod* parent = findParent(root, key);
    if (key <= parent->key)
        parent->left = child;
    else
        parent->right = child;
    return true;
}

bool Tree::del(const int key){
    nod* deletednod = FindNod(root,key);
    nod* parentOfDeletednod = findParent(root, key);
    if (deletednod == nullptr)
        return false;
    if (deletednod->left == nullptr && deletednod->right == nullptr)
    {
        if (parentOfDeletednod ->left == deletednod)
        {
            parentOfDeletednod ->left = nullptr;
            delete deletednod;
            return true;
        }
        parentOfDeletednod->right = nullptr;
        delete deletednod;
        return true;
    }
    if (deletednod->left == nullptr && deletednod->right != nullptr)
    {
        if (parentOfDeletednod->left == deletednod)
        {
            parentOfDeletednod->left = deletednod->right;
            delete deletednod;
            return true;
        }
        parentOfDeletednod->right = deletednod->right;
        delete deletednod;
        return true;
    }
    if (deletednod->left != nullptr && deletednod->right == nullptr)
    {
        if (parentOfDeletednod->left == deletednod)
        {
            parentOfDeletednod->left = deletednod->left;
            delete deletednod;
            return true;
        }
        parentOfDeletednod->right = deletednod->left;
        delete deletednod;
        return true;

    }
    if ((deletednod->left != nullptr) && (deletednod->right != nullptr))
    {
        nod* temp = findMin(deletednod->right);
        if (temp == deletednod->right)
        {
            deletednod->key = temp->key;
            deletednod->data = temp->data;
            deletednod->right = temp->right;
            delete temp;
            return true;
        }
        deletednod->data = temp->data;
        deletednod->key = temp->key;
        del(temp->key);
        return true;
    }
}; // false if no key


int main() {
    Tree testTree;
    testTree.add(33, "3");
    std::cout<<testTree.find(33)<<std::endl;
    std::cout << "The end." << std::endl;
}


                   
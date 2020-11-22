#include <iostream>
#include <string>

// Binary search tree


class Node {
public:
    int key;
    std:: string data;
public:
    Node *left;
    Node *right;
public:
    Node(const int key, std :: string data){
        this->key = key;
        this->data = data;
        left = nullptr;
        right = nullptr;
    };
};
class Tree {
private:
    Node *root;
    Node* lookForNode(Node* root, int key)
    {
        if (root == nullptr) return root;
        if (root->key == key) return root;
        else if (root->key > key) return lookForNode(root->left, key);
        else return lookForNode(root->right, key);
    }
    Node* findParent  (Node * root, int key) {
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
    Node* min(Node* root)
    {
        Node* findMin = root;
        while (findMin->left != nullptr)
        {
            findMin = findMin->left;
        }
        return findMin;
    }
public:
    bool add(const int key, std:: string data) {
        Node* child = new Node (key,data);
        if (root == nullptr){
            root = child;
            return false;
        }
        Node* parent = findParent(root, key);
        if (key <= parent->key)
            parent->left = child;
        else
            parent->right = child;
        return true;
    };  // false if key already exists
    bool del(const int key){
        Node* deletedNode = lookForNode(root,key);
        Node* parentOfDeletedNode = findParent(root, key);
        if (deletedNode == nullptr)
            return false;
        if (deletedNode->left == nullptr && deletedNode->right == nullptr)
        {
            if (parentOfDeletedNode ->left == deletedNode)
            {
                parentOfDeletedNode ->left = nullptr;
            }
            else
            {
                parentOfDeletedNode->right = nullptr;
            }
            return true;
        }
        if (deletedNode->left == nullptr && deletedNode->right != nullptr)
        {
            if (parentOfDeletedNode->left == deletedNode)
            {
                parentOfDeletedNode->left = deletedNode->right;
            }
            else
            {
                parentOfDeletedNode->right = deletedNode->right;
            }
            return true;
        }
        if (deletedNode->left != nullptr && deletedNode->right == nullptr)
        {
            if (parentOfDeletedNode->left == deletedNode)
            {
                parentOfDeletedNode->left = deletedNode->left;
            }
            else
            {
                parentOfDeletedNode->right = deletedNode->left;
            }
            return true;
        }
        if ((deletedNode->left != nullptr) && (deletedNode->right != nullptr)) // у удаляемого узла два ребенка
        {
            Node* temp = min(deletedNode->right);
            if (temp == deletedNode->right)
            {
                deletedNode->key = temp->key;
                deletedNode->data = temp->data;
                deletedNode->right = temp->right;
                delete temp;
            }
            else
            {
                deletedNode->data = temp->data;
                deletedNode->key = temp->key;
                del(temp->key);
            }
            return true;
        }
    }; // false if no key
    std::string find(const int key) {
        if (root == nullptr)
            return " ";
        if (root->key > key){
            root = root->left;
            return find(key);
        }
        else{
            root = root->right;
            return find (key);
        }
    };  // return '' if no key
public:
    Tree(){
        root = nullptr;
    };
};



int main() {
    std::cout << "The end." << std::endl;
}

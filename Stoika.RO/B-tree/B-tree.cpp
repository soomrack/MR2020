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
    Node(int key, std::string data) {
        this->key = key;
        this->data = data;
        left = nullptr;
        right = nullptr;
    };
};
class Tree {
private:
    Node* root;
    Node* checkNode(Node* root, int key)
    {
        if (root == nullptr) return root;
        if (root->key == key) return root;
        else if (root->key > key) return checkNode(root->left, key);
        else return checkNode(root->right, key);
    }

    Node* findParentWhenAdding(Node* root, int key) {
        if (root->key <= key) {
            if (root->right == nullptr)
                return root;
            return findParentWhenAdding(root->right, key);
        }
        if (root->key > key) {
            if (root->left == nullptr)
                return root;
            return findParentWhenAdding(root->left, key);
        }
        return nullptr;
    }

    Node* findParentWhenDeliting(Node* root, int key) {
        if (root->right->key == key) return root;
        if (root->left->key == key) return root;
        if (root->key <= key) return findParentWhenDeliting(root->right, key);
        return findParentWhenDeliting(root->left, key);
    };

    Node* min(Node* root)
    {
        if (root->left == nullptr)
            return root;
        else
            return min(root->left);
    }
public:
    bool add(const int key, std::string data) {
        Node* child = new Node(key, data);
        if (checkNode(root, key) != nullptr)
            return false;
        if (root == nullptr) {
            root = child;
            return true;
        }
        Node* parent = findParentWhenAdding(root, key);
        if (key <= parent->key)
            parent->left = child;
        else
            parent->right = child;
        return true;
    };

    bool del(const int key) {
        Node* deleteNode = checkNode(root, key);
        Node* ParentOfDeleteNode = findParentWhenDeliting(root, key);
        if (deleteNode == nullptr)
            return false;
        if (deleteNode->left == nullptr && deleteNode->right == nullptr)
        {
            if (ParentOfDeleteNode->left == deleteNode)
            {
                ParentOfDeleteNode->left = nullptr;
            }
            else
            {
                ParentOfDeleteNode->right = nullptr;
            }
            return true;
        }
        if (deleteNode->left == nullptr && deleteNode->right != nullptr)
        {
            if (ParentOfDeleteNode->left == deleteNode)
            {
                ParentOfDeleteNode->left = deleteNode->right;
            }
            else
            {
                ParentOfDeleteNode->right = deleteNode->right;
            }
            return true;
        }
        if (deleteNode->left != nullptr && deleteNode->right == nullptr)
        {
            if (ParentOfDeleteNode->left == deleteNode)
            {
                ParentOfDeleteNode->left = deleteNode->left;
            }
            else
            {
                ParentOfDeleteNode->right = deleteNode->left;
            }
            return true;
        }
        if ((deleteNode->left != nullptr) && (deleteNode->right != nullptr))
        {
            Node* temp = min(deleteNode->right);
            if (temp == deleteNode->right)
            {
                deleteNode->key = temp->key;
                deleteNode->data = temp->data;
                deleteNode->right = temp->right;
                delete temp;
            }
            else
            {
                deleteNode->data = temp->data;
                deleteNode->key = temp->key;
                del(temp->key);
            }
            return true;
        }
    };

    std::string find(const int key) {
        Node* node = root;
        if (node == nullptr)
            return " ";
        while (node->key != key)
        {
            if (key > node->key)
            {
                if (node->right == nullptr) return " ";
                else node = node->right;
            }
            else if (key < node->key)
            {
                if (node->left == nullptr) return " ";
                else node = node->left;
            }
        }
        return node->data;
    };
};

int main() 
{
    std::cout << "The end." << std::endl;
}
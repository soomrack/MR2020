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
    Node(int key, std :: string data){
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
    Node* findParentWhileAdding  (Node * root, int key) {
        if (root->key <= key) {
            if (root->right == nullptr)
                return root;
            return findParentWhileAdding(root->right, key);
        }
        if (root->key > key) {
            if (root->left == nullptr)
                return root;
            return findParentWhileAdding(root->left, key);
        }
        return nullptr;
    }
    Node* findParentWhileDeliting(Node* root, int key){
        if (root->right->key == key) return root;
        if (root->left->key == key) return root;
        if (root->key<=key) return findParentWhileDeliting(root->right,key);
        return findParentWhileDeliting(root->left,key);
    };
    Node* min(Node* root)
    {
        if (root->left == nullptr)
            return root;
        else
            return min(root->left);
    }
public:
    bool add(const int key, std:: string data) {
        Node* child = new Node (key,data);
        if (lookForNode(root,key)!= nullptr)
            return false;
        if (root == nullptr){
            root = child;
            return true;
        }
        Node* parent = findParentWhileAdding(root, key);
        if (key <= parent->key)
            parent->left = child;
        else
            parent->right = child;
        return true;
    };  // false if key already exists
    bool del(const int key){
        Node* deletedNode = lookForNode(root,key);
        Node* parentOfDeletedNode = findParentWhileDeliting(root, key);
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
        Node* node = root;
        if (node == nullptr)
            return "2";
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
    };  // return '' if no key
public:
    Tree(){
        root = nullptr;
    };
};



int main() {
    Tree testTree;
    testTree.add(33, "3");
    testTree.add(31,"5");
    testTree.add(150,"/");
    testTree.add(6,"2");
    testTree.add(33, "<3");
    std::cout<<testTree.find(33)<<std::endl;
    std::cout<<testTree.find(0)<<std::endl;
    std::cout<<testTree.find(8)<<std::endl;
    std::cout<<testTree.find(6)<<std::endl;
    testTree.del(150);
    std::cout<<testTree.find(150)<<std::endl;
    std::cout<<testTree.find(31)<<std::endl;
    std::cout << "The end." << std::endl;
}

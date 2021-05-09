#include <iostream>
#include <string>

std::string NO_KEY = "no_key";

class Node {
public:
    int key;
    unsigned short height;
    std::string data;   
public:
    Node *left;
    Node *right;
public:
    Node(const int key, const std::string data, unsigned short height);
};

Node::Node(const int key, const std::string data, unsigned short height){
    this->key = key;
    this->data = data;
    this->height = height;
    this->left = nullptr;
    this->right = nullptr;
}

class Tree { // avl tree
private:
    Node* small_turn_left(Node* cur_root); 
    Node* small_turn_right(Node* cur_root);
    Node* big_turn_left(Node* cur_root);
    Node* big_turn_right(Node* cur_root);
    Node* balance(Node* cur_root);
    void update_height(Node* root);     // recalculates height value of the subtree
    unsigned short height(Node * root); // get current height of subtree
    int8_t bfactor(Node * root);        // calculates bfactor of subtree as difference between left and right subtree heights
                                        // if value is positive, right subtree is deeper
    Node* find_node(Node* root, const int key);
    Node* find_replace_node(Node* root);
    Node* find_parent(Node* root, const int key);
public:
    Node* root;
    bool del(Node* root, const int key);
    Node* add(Node* root, const int key, const std::string data);  
public:
    Tree(){ root = nullptr; };
    ~Tree(){ while(root != nullptr){ del(root, root->key); } }
};


int8_t Tree::bfactor(Node * root) {
    int8_t hright = root -> right ? height(root -> right) : 0;
    int8_t hleft = root -> left ? height(root -> left) : 0;
    return hright - hleft;
}

unsigned short Tree::height(Node * root) {
    return root ? root -> height : 0;
}

void Tree::update_height(Node* root){
    unsigned short hleft = height(root -> left);
    unsigned short hright = height(root -> right);
    root -> height = (hleft > hright ? hleft : hright) + 1;
}

Node* Tree::small_turn_left(Node* cur_root){
    Node* new_root = cur_root -> right;
    cur_root -> right = new_root -> left;
    new_root -> left = cur_root;
    update_height(cur_root);
    update_height(new_root);
    return new_root;
}

Node* Tree::small_turn_right(Node* cur_root){
    Node* new_root = cur_root -> left;
    cur_root -> left = new_root -> right;
    new_root -> right = cur_root;
    update_height(cur_root);
    update_height(new_root);
    return new_root;
}

Node* Tree::big_turn_left(Node* cur_root){
    Node* right_subtree = cur_root -> right;
    Node* new_root = right_subtree -> left;
    right_subtree -> left = new_root -> right;
    cur_root -> right = new_root -> left;
    new_root -> left = cur_root;
    new_root -> right = right_subtree;
    update_height(right_subtree);
    update_height(cur_root);
    update_height(new_root);
    return new_root;
}

Node* Tree::big_turn_right(Node* cur_root){
    Node* left_subtree = cur_root -> left;
    Node* new_root = left_subtree -> right;
    left_subtree -> right = new_root -> left;
    cur_root -> left = new_root -> right;
    new_root -> left = left_subtree;
    new_root -> right = cur_root;
    update_height(left_subtree);
    update_height(cur_root);
    update_height(new_root);
    return new_root;
}

Node* Tree::balance(Node* root){
    update_height(root);
    if (bfactor(root) == 2){
        if (bfactor(root -> right) > 0){
            return small_turn_left(root);
        }
        else{
            return big_turn_left(root);
        }
    }
    if (bfactor(root) == -2){
        if (bfactor(root -> left) < 0){
            return small_turn_right(root);
        }
        else{
            return big_turn_right(root);
        }
    }
    return root;
}

Node* Tree::add(Node* root, const int key, const std::string data){
    if (!root) {
        Node * root = new Node(key, data, 1);
        return root;
    }
    if (key < root -> key)
        root -> left = add(root -> left, key, data);
    else 
        root -> right = add(root -> right, key, data);
    return balance(root);
}

Node* Tree::find_replace_node(Node* root){
    if (bfactor(root) > 0){ 
        Node* replace_node = root -> right;
        while (replace_node -> left){
            replace_node = replace_node -> left;
        }
        return replace_node;
    }

    Node* replace_node = root -> left;
    while (replace_node -> right){
        replace_node = replace_node -> right;
    }
    return replace_node;
    

}

Node* Tree::find_parent(Node* root, const int key){
    if (root -> key == key){
        return root;
    }
    if (((root -> left) && (root -> left -> key == key)) || ((root -> right) && (root -> right -> key == key))){
        return root;
    }
    if (key > root -> key){
        return find_parent(root -> right, key);
    }
    return find_parent(root -> left, key);
}

bool Tree::del(Node* root, const int key){
    bool status = false;
    if (root == nullptr){
        return false;
    }
    if (root -> key == key){ 
        // if node to delete is found
        Node* parent = find_parent(this->root, key);
        if (!(root -> left) && !(root -> right)){ 
            // if it has no children (is leaf)
            if (root != this->root){ 
                // if it is not root of current tree
                if (parent -> left == root)
                    parent -> left = nullptr;
                else
                    parent -> right = nullptr;
            }
            else
                root = nullptr;
        }
        else{ 
            // if it has at least one child we sholud find node, which is going to replace node to delete
            // then we should delete reaplace node and finale replace node to delete with replace node
            Node* replace_node = find_replace_node(root);
            if (!del(root, replace_node -> key)){
                return false;
            }
            
            replace_node -> left = root -> left;
            replace_node -> right = root -> right;
            if (parent != root){
                if (parent -> left == root)
                    parent -> left = replace_node;
                else
                    parent -> right = replace_node;
            }
            else{
                root = replace_node;
            }
        }
    }
    
    else if (key > root -> key){
        status = del(root -> right, key);
    }
    else {
        status = del(root -> left, key);
    }
    if (!status){ return false; }
    balance(root);
    return true; // balance tree, while going up the recursion
}


int main()
{
    Tree tree;
    
    //Потестим
    tree.root = tree.add(tree.root, 12, "HelloWorld!");
    tree.add(tree.root, 1, "str");
    tree.add(tree.root, 2, "str");
    tree.add(tree.root, 3, "str");
    tree.add(tree.root, 5, "str");
    tree.add(tree.root, 6, "str");
    tree.add(tree.root, 7, "str");
    tree.add(tree.root, 30, "str");
    tree.add(tree.root, 31, "str");
    std::cout << tree.del(tree.root, 10);

    while (1);

    return 0;
}

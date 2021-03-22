#include <iostream>

using namespace std;

const int t=2;

class BNode {
public:
    int keys[2*t-1]{};
    BNode *children[2*t+1]{};
    BNode *parent{};
    int keys_count;       //количество ключей
    int child_count{};    //количество сыновей
    bool leaf;
    explicit BNode(int key);
};

BNode::BNode(int key) {
    this->keys[0] = key;
    for (int i = 1; i < (2 * t - 1); i++)
        this->keys[i] = 0;
    for (auto & i : this->children)
        i = nullptr;
    this->keys_count = 1;
    this->leaf = true;
}

class BTree {
private:
    BNode *root;
    void insert_in_node(int key, BNode *node);
    void sort(BNode *node);
    bool searchKey(int key, BNode *node);
    void delete_node(BNode *node);

public:
    BTree();
    ~BTree();
    void insert(int key);
    bool search(int key);
};

BTree::BTree()  { root = nullptr; }

BTree::~BTree() { if (root != nullptr) delete_node(root); }

//Функция для деконструктора
void BTree::delete_node(BNode *node) {
    if (node != nullptr) {
        for (int i = 0; i <= (2*t-1); i++) {
            if (node->children[i] != nullptr)
                delete_node(node->children[i]);
            else {
                delete(node);
                break;
            }
        }
    }
}

void BTree::insert_in_node(int key, BNode *node) {
    node->keys[node->keys_count] = key;
    node->keys_count = node->keys_count + 1;
    sort(node);
}

void BTree::sort(BNode *node) {
    int m;
    for (int i=0; i<(2*t-1); i++){
        for (int j=i+1; j<=(2*t-1); j++){
            if ((node->keys[i]!=0) && (node->keys[j]!=0)){
                if ((node->keys[i]) > (node->keys[j])){
                    m=node->keys[i];
                    node->keys[i]=node->keys[j];
                    node->keys[j]=m;
                }
            } else break;
        }
    }
}

bool BTree::search(int key){
    return searchKey(key, this->root);
}

bool BTree::searchKey(int key, BNode *node){
    if (node!=nullptr){
        if (!node->leaf){
            int i;
            for (i=0; i<=(2*t-1); i++){
                if (node->keys[i]!=0) {
                    if(key==node->keys[i]) return true;
                    if ((key<node->keys[i])){
                        return searchKey(key, node->children[i]);
                    }
                } else break;
            }
            return searchKey(key, node->children[i]);
        } else {
            for(int j=0; j<=(2*t-1); j++)
                if (key==node->keys[j]) return true;
            return false;
        }
    } else return false;
}
int main() {
    BTree tree = BTree();

    tree.insert(5);
    tree.search(5);
    return 0;
}

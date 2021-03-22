#include <iostream>

using namespace std;

const int t = 2;
struct Node
{
    bool leaf;
    int keys[2 * t];
    Node *child[2 * t + 1];
    Node *parent;
    int count_keys;
    int count_Child;
};
class Tree
{
private:
    Node *root;
    void add_to_node(int key, Node *node);
    void sort(Node *node);
    void restruct(Node *node);
    void delete_node(Node *node);
    bool search_key(int key, Node *node);

public:
    Tree();
    ~Tree();
    void add(int key);
    bool search(int key);
};
Tree::Tree() { root=nullptr; }

Tree::~Tree(){ if(root!=nullptr) delete_node(root); }

void Tree::delete_node(Node *node)
{
    if (node != nullptr)
        for (int i = 0; i <= (2 * t - 1); i++)
        {
            if (node->child[i] != nullptr)
                delete_node(node->child[i]);
            else
            {
                delete(node);
                break;
            }
        }
}
void Tree::add_to_node(int key, Node *node)
{
    node->keys[node->count_keys] = key;
    node->count_keys = node->count_keys + 1;
    sort(node);
}
void Tree::sort(Node *node)
{
    int m ;
    for (int i = 0; i < (2*t-1); i++)
        for (int j = i + 1; j <= (2*t-1); j++)
        {
            if ((node->keys[i] != 0) && (node->keys[j] != 0))
            {
                if ((node->keys[i]) > (node->keys[j]))
                {
                    m = node->keys[i];
                    node->keys[i] = node->keys[j];
                    node->keys[j] = m;
                }
            }
            else
                break;
        }
}
void Tree::add(int key){
    if (root==nullptr) {
        Node *newRoot = new Node;
        newRoot->keys[0]=key;
        for(int j=1; j<=(2*t-1); j++) newRoot->keys[j]=0;
        for (int i=0; i<=(2*t); i++) newRoot->child[i]=nullptr;
        newRoot->count_keys=1;
        newRoot->count_Child=0;
        newRoot->leaf=true;
        newRoot->parent=nullptr;
        root=newRoot;
    } else {
        Node *ptr=root;
        while (ptr->leaf==false){
            for (int i=0; i<=(2*t-1); i++){
                if (ptr->keys[i]!=0) {
                    if (key<ptr->keys[i]) {
                        ptr=ptr->child[i];
                        break;
                    }
                    if ((ptr->keys[i+1]==0)&&(key>ptr->keys[i])) {
                        ptr=ptr->child[i+1];
                        break;
                    }
                } else break;
            }
        }
        add_to_node(key, ptr);

        while (ptr->count_keys==2*t){
            if (ptr==root){
                restruct(ptr);
                break;
            } else {
                restruct(ptr);
                ptr=ptr->parent;
            }
        }
    }
}
void Tree::restruct(Node *node){
    if (node->count_keys<(2*t-1)) return;

    //первый сын
    Node *child1 = new Node;
    int j;
    for (j=0; j<=t-2; j++) child1->keys[j]=node->keys[j];
    for (j=t-1; j<=(2*t-1); j++) child1->keys[j]=0;
    child1->count_keys=t-1;
    if(node->count_Child!=0){
        for (int i=0; i<=(t-1); i++){
            child1->child[i]=node->child[i];
            child1->child[i]->parent=child1;
        }
        for (int i=t; i<=(2*t); i++) child1->child[i]=nullptr;
        child1->leaf=false;
        child1->count_Child=t-1;
    } else {
        child1->leaf=true;
        child1->count_Child=0;
        for (int i=0; i<=(2*t); i++) child1->child[i]=nullptr;
    }

    //второй сын
    Node *child2 = new Node;
    for (int j=0; j<=(t-1); j++) child2->keys[j]=node->keys[j+t];
    for (j=t; j<=(2*t-1); j++) child2->keys[j]=0;
    child2->count_keys=t;
    if(node->count_Child!=0) {
        for (int i=0; i<=(t); i++){
            child2->child[i]=node->child[i+t];
            child2->child[i]->parent=child2;
        }
        for (int i=t+1; i<=(2*t); i++) child2->child[i]=nullptr;
        child2->leaf=false;
        child2->count_Child=t;
    } else {
        child2->leaf=true;
        child2->count_Child=0;
        for (int i=0; i<=(2*t); i++)
            child2->child[i]=nullptr;
    }

    //родитель
    if (node->parent==nullptr){
        node->keys[0]=node->keys[t-1];
        for(int j=1; j<=(2*t-1); j++)
            node->keys[j]=0;
        node->child[0]=child1;
        node->child[1]=child2;
        for(int i=2; i<=(2*t); i++)
            node->child[i]=nullptr;
        node->parent=nullptr;
        node->leaf=false;
        node->count_keys=1;
        node->count_Child=2;
        child1->parent=node;
        child2->parent=node;
    } else {
        add_to_node(node->keys[t-1], node->parent);
        for (int i=0; i<=(2*t); i++){
            if (node->parent->child[i]==node) node->parent->child[i]=nullptr;
        }
        for (int i=0; i<=(2*t); i++){
            if (node->parent->child[i]==nullptr) {
                for (int j=(2*t); j>(i+1); j--) node->parent->child[j]=node->parent->child[j-1];
                node->parent->child[i+1]=child2;
                node->parent->child[i]=child1;
                break;
            }
        }
        child1->parent=node->parent;
        child2->parent=node->parent;
        node->parent->leaf=false;
        delete node;
    }
}


bool Tree::search(int key){
    return search_key(key, this->root);
}
bool Tree::search_key(int key, Node *node){
    if (node!=nullptr){
        if (node->leaf==false){
            int i;
            for (i=0; i<=(2*t-1); i++){
                if (node->keys[i]!=0) {
                    if(key==node->keys[i]) return true;
                    if ((key<node->keys[i])){
                        return search_key(key, node->child[i]);
                        break;
                    }
                } else break;
            }
            return search_key(key, node->child[i]);
        } else {
            for(int j=0; j<=(2*t-1); j++)
                if (key==node->keys[j]) return true;
            return false;
        }
    } else return false;
}

int main()
{
    return 0;
}
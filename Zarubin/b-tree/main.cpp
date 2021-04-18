#include <iostream>
using namespace std;

const int t=2;
struct BNode {
    int keys[2*t];
    BNode *children[2*t+1];
    BNode *parent;
    int count; //количество ключей
    int countSons; //количество сыновей
    bool leaf;
};

class Tree {
private:
    BNode *root;
    int x;
    void insert_to_node(int key, BNode *node);
    void sort(BNode *node);
    void restruct(BNode *node);
    void deletenode(BNode *node);
    bool searchKey(int key, BNode *node);
    void remove(int key, BNode *node);
    void removeFromNode(int key, BNode *node);
    void removeLeaf(int key, BNode *node);
    void lconnect(BNode *node, BNode *othernode);
    void rconnect(BNode *node, BNode *othernode);
    void repair(BNode *node);

public:
    Tree(int x);
    ~Tree();
    void insert(int key);
    bool search(int key);
    void remove(int key);
};

Tree::Tree(int x)
{
    this->root = nullptr;
    this->x = x;
}

Tree::~Tree(){ if(root!=nullptr) deletenode(root); }

void Tree::deletenode(BNode *node){
    if (node!=nullptr){
        for (int i=0; i<=(2*t-1); i++){
            if (node->children[i]!=nullptr) deletenode(node->children[i]);
            else {
                delete(node);
                break;
            }
        }
    }
}

void Tree::insert_to_node(int key, BNode *node){
    node->keys[node->count]=key;
    node->count=node->count+1;
    sort(node);
}

void Tree::sort(BNode *node) {
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

void Tree::insert(int key){
    if (root==nullptr) {
        BNode *newRoot = new BNode;
        newRoot->keys[0]=key;
        for(int j=1; j<=(2*t-1); j++) newRoot->keys[j]=0;
        for (int i=0; i<=(2*t); i++) newRoot->children[i]=nullptr;
        newRoot->count=1;
        newRoot->countSons=0;
        newRoot->leaf=true;
        newRoot->parent=nullptr;
        root=newRoot;
    } else {
        BNode *ptr=root;
        while (ptr->leaf==false){ //выбор ребенка до тех пор, пока узел не будет являться листом
            for (int i=0; i<=(2*t-1); i++){ //перебираем все ключи
                if (ptr->keys[i]!=0) {
                    if (key<ptr->keys[i]) {
                        ptr=ptr->children[i];
                        break;
                    }
                    if ((ptr->keys[i+1]==0)&&(key>ptr->keys[i])) {
                        ptr=ptr->children[i+1]; //перенаправляем к самому последнему ребенку, если цикл не "сломался"
                        break;
                    }
                } else break;
            }
        }
        insert_to_node(key, ptr);

        while (ptr->count==2*t){
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

void Tree::restruct(BNode *node){
    if (node->count<(2*t-1)) return;

    //первый сын
    BNode *child1 = new BNode;
    int j;
    for (j=0; j<=t-2; j++) child1->keys[j]=node->keys[j];
    for (j=t-1; j<=(2*t-1); j++) child1->keys[j]=0;
    child1->count=t-1; //количество ключей в узле
    if(node->countSons!=0){
        for (int i=0; i<=(t-1); i++){
            child1->children[i]=node->children[i];
            child1->children[i]->parent=child1;
        }
        for (int i=t; i<=(2*t); i++) child1->children[i]=nullptr;
        child1->leaf=false;
        child1->countSons=t-1; //количество сыновей
    } else {
        child1->leaf=true;
        child1->countSons=0;
        for (int i=0; i<=(2*t); i++) child1->children[i]=nullptr;
    }

    //второй сын
    BNode *child2 = new BNode;
    for (int j=0; j<=(t-1); j++) child2->keys[j]=node->keys[j+t];
    for (j=t; j<=(2*t-1); j++) child2->keys[j]=0;
    child2->count=t; //количество ключей в узле
    if(node->countSons!=0) {
        for (int i=0; i<=(t); i++){
            child2->children[i]=node->children[i+t];
            child2->children[i]->parent=child2;
        }
        for (int i=t+1; i<=(2*t); i++) child2->children[i]=nullptr;
        child2->leaf=false;
        child2->countSons=t; //количество сыновей
    } else {
        child2->leaf=true;
        child2->countSons=0;
        for (int i=0; i<=(2*t); i++) child2->children[i]=nullptr;
    }

    //родитель
    if (node->parent==nullptr){ //если родителя нет, то это корень
        node->keys[0]=node->keys[t-1];
        for(int j=1; j<=(2*t-1); j++) node->keys[j]=0;
        node->children[0]=child1;
        node->children[1]=child2;
        for(int i=2; i<=(2*t); i++) node->children[i]=nullptr;
        node->parent=nullptr;
        node->leaf=false;
        node->count=1;
        node->countSons=2;
        child1->parent=node;
        child2->parent=node;
    } else {
        insert_to_node(node->keys[t-1], node->parent);
        for (int i=0; i<=(2*t); i++){
            if (node->parent->children[i]==node) node->parent->children[i]=nullptr;
        }
        for (int i=0; i<=(2*t); i++){
            if (node->parent->children[i]==nullptr) {
                for (int j=(2*t); j>(i+1); j--) node->parent->children[j]=node->parent->children[j-1];
                node->parent->children[i+1]=child2;
                node->parent->children[i]=child1;
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
    return searchKey(key, this->root);
}

bool Tree::searchKey(int key, BNode *node){
    if (node!=nullptr){
        if (node->leaf==false){
            int i;
            for (i=0; i<=(2*t-1); i++){
                if (node->keys[i]!=0) {
                    if(key==node->keys[i]) return true;
                    if ((key<node->keys[i])){
                        return searchKey(key, node->children[i]);
                        break;
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

void Tree::removeFromNode(int key, BNode *node){
    for (int i=0; i<node->count; i++){
        if (node->keys[i]==key){
            for (int j=i; j<node->count; j++) {
                node->keys[j]=node->keys[j+1];
                node->children[j]=node->children[j+1];
            }
            node->keys[node->count-1]=0;
            node->children[node->count-1]=node->children[node->count];
            node->children[node->count]=nullptr;
            break;
        }
    }
    node->count--;
}

void Tree::lconnect(BNode *node, BNode *othernode){
    if (node==nullptr) return;
    for (int i=0; i<=(othernode->count-1); i++){
        node->keys[node->count]=othernode->keys[i];
        node->children[node->count]=othernode->children[i];
        node->count=node->count+1;
    }
    node->children[node->count]=othernode->children[othernode->count];
    for (int j=0; j<=node->count; j++){
        if (node->children[j]==nullptr) break;
        node->children[j]->parent=node;
    }
    delete othernode;
}

void Tree::rconnect(BNode *node, BNode *othernode){
    if (node==nullptr) return;
    for (int i=0; i<=(othernode->count-1); i++){
        node->keys[node->count]=othernode->keys[i];
        node->children[node->count+1]=othernode->children[i+1];
        node->count=node->count+1;
    }
    for (int j=0; j<=node->count; j++){
        if (node->children[j]==nullptr) break;
        node->children[j]->parent=node;
    }
    delete othernode;
}

void Tree::repair(BNode *node){
    if ((node==root)&&(node->count==0)){
        if (root->children[0]!=nullptr){
            root->children[0]->parent=nullptr;
            root=root->children[0];
        } else {
            delete root;
        }
        return;
    }
    BNode *ptr=node;
    int k1;
    int k2;
    int positionSon;
    BNode *parent=ptr->parent;
    for (int j=0; j<=parent->count; j++){
        if (parent->children[j]==ptr){
            positionSon=j; //позиция узла по отношению к родителю
            break;
        }
    }
    //если ptr-первый ребенок (самый левый)
    if (positionSon==0){
        insert_to_node(parent->keys[positionSon], ptr);
        lconnect(ptr, parent->children[positionSon+1]);
        parent->children[positionSon+1]=ptr;
        parent->children[positionSon]=nullptr;
        removeFromNode(parent->keys[positionSon], parent);
        if(ptr->count==2*t){
            while (ptr->count==2*t){
                if (ptr==root){
                    restruct(ptr);
                    break;
                } else {
                    restruct(ptr);
                    ptr=ptr->parent;
                }
            }
        } else
        if (parent->count<=(t-2)) repair(parent);
    } else {
        //если ptr-последний ребенок (самый правый)
        if (positionSon==parent->count){
            insert_to_node(parent->keys[positionSon-1], parent->children[positionSon-1]);
            lconnect(parent->children[positionSon-1], ptr);
            parent->children[positionSon]=parent->children[positionSon-1];
            parent->children[positionSon-1]=nullptr;
            removeFromNode(parent->keys[positionSon-1], parent);
            BNode *temp=parent->children[positionSon];
            if(ptr->count==2*t){
                while (temp->count==2*t){
                    if (temp==root){
                        restruct(temp);
                        break;
                    } else {
                        restruct(temp);
                        temp=temp->parent;
                    }
                }
            } else
            if (parent->count<=(t-2)) repair(parent);
        } else { //если ptr имеет братьев справа и слева
            insert_to_node(parent->keys[positionSon], ptr);
            lconnect(ptr, parent->children[positionSon+1]);
            parent->children[positionSon+1]=ptr;
            parent->children[positionSon]=nullptr;
            removeFromNode(parent->keys[positionSon], parent);
            if(ptr->count==2*t){
                while (ptr->count==2*t){
                    if (ptr==root){
                        restruct(ptr);
                        break;
                    } else {
                        restruct(ptr);
                        ptr=ptr->parent;
                    }
                }
            } else
            if (parent->count<=(t-2)) repair(parent);
        }
    }
}

void Tree::remove(int key){
    BNode *ptr=this->root;
    int position;
    int positionSon;
    int i;
    if (searchKey(key, ptr)==false) {
        return;
    } else {
        //ищем узел, в котором находится ключ для удаления
        for (i=0; i<=ptr->count-1; i++){
            if (ptr->keys[i]!=0) {
                if(key==ptr->keys[i]) {
                    position=i;
                    break;
                } else {
                    if ((key<ptr->keys[i])){
                        ptr=ptr->children[i];
                        positionSon=i;
                        i=-1;
                    } else {
                        if (i==(ptr->count-1)) {
                            ptr=ptr->children[i+1];
                            positionSon=i+1;
                            i=-1;
                        }
                    }
                }
            } else break;
        }
    }
    if (ptr->leaf==true) {
        if (ptr->count>(t-1)) removeFromNode(key,ptr);
        else removeLeaf(key, ptr);
    } else remove(key, ptr);
}

int main() {
    Tree tree = Tree(1);
    tree.insert(95);
    tree.insert(55);
    tree.insert(89);
    tree.insert(60);
    tree.insert(78);
    tree.insert(15);

    int key = 78;
    if (tree.search(key))
        cout<<key<<" is found"<<endl;
    else
        cout<<key<<" is not Found"<<endl;

    tree.remove(15);

    key = 15;
    if (tree.search(key))
        cout<<key<<" is found"<<endl;
    else
        cout<<key<<" is not Found"<<endl;


    return 0;
}
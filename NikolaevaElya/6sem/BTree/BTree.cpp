#include <iostream> 
using namespace std; 
  
class BTreeNode { 
    int *keys;  
    int maxDegree;      
    BTreeNode **child;
    int keyNumber;      
    bool leaf;
public: 
    BTreeNode(int degree, bool leaf1);
    void insertNonFull(int k);
    void splitChild(int i, BTreeNode *node); 
    void traverse(); 
    BTreeNode *search(int k);
friend class BTree; 
}; 

class BTree { 
    BTreeNode *root; 
    int maxDegree;  
public:  
    void traverse();
    BTreeNode* search(int k); 
    void insert(int k); 
public:    
    BTree(int _t);
};   

BTreeNode::BTreeNode(int degree, bool leaf1) { 
    maxDegree = degree; 
    leaf = leaf1; 
    keys = new int[2 * maxDegree - 1]; 
    child = new BTreeNode *[2 * maxDegree];
    keyNumber = 0; 
} 

void BTreeNode::insertNonFull(int k) { 
    int i = keyNumber-1; 
    if (leaf == true) { 
        while (i >= 0 && keys[i] > k) { 
            keys[i + 1] = keys[i]; 
            i--; 
        } 
        keys[i + 1] = k; 
        keyNumber = keyNumber + 1; 
    } else { 
        while (i >= 0 && keys[i] > k) { 
            i--; 
        }
        if (child[i + 1]->keyNumber == 2 * maxDegree - 1) { 
            splitChild(i + 1, child[i + 1]); 
            if (keys[i + 1] < k) {
                i++; 
            }
        } 
        child[i + 1]->insertNonFull(k); 
    } 
} 
  
void BTreeNode::splitChild(int i, BTreeNode *node) { 
    BTreeNode *newNode = new BTreeNode(node->maxDegree, node->leaf); 
    newNode->keyNumber = maxDegree - 1; 
    for (int j = 0; j < maxDegree - 1; j++) {
        newNode->keys[j] = node->keys[j + maxDegree]; 
    }
    if (node->leaf == false) { 
        for (int j = 0; j < maxDegree; j++) {
            newNode->child[j] = node->child[j + maxDegree]; 
        }
    } 
    node->keyNumber = maxDegree - 1; 
    for (int j = keyNumber; j >= i + 1; j--); 
    child[j + 1] = child[j]; 
    child[i + 1] = newNode; 
    for (int j = keyNumber - 1; j >= i; j--) {
        keys[j + 1] = keys[j]; 
    }
    keys[i] = node->keys[maxDegree - 1];
    keyNumber = keyNumber + 1; 
} 
  
void BTreeNode::traverse() { 
    int i = 0;
    for (; i < keyNumber; i++) {  
        if (leaf == false) {
            child[i]->traverse(); 
        }
        cout << " " << keys[i]; 
    } 
    if (leaf == false) {
        child[i]->traverse(); 
    }
} 
   
BTreeNode *BTreeNode::search(int k) { 
    int i = 0; 
    while (i < keyNumber && k > keys[i]) {
        i++; 
    }
    if (keys[i] == k) {
        return this; 
    }
    if (leaf == true) {
        return NULL; 
    }
    return child[i]->search(k); 
} 
    
void BTree::traverse() {
    if (root != nullptr) {
        root->traverse();
    }
}

BTreeNode* BTree::search(int k) {
    if(root == nullptr) {
        return NULL;
    } else {
        return root->search(k);
    }   
}

void BTree::insert(int k) { 
    if (root == nullptr) { 
        root = new BTreeNode(maxDegree, true); 
        root->keys[0] = k; 
        root->keyNumber = 1;  
    } 
    else { 
        if (root->keyNumber == 2 * maxDegree - 1) { 
            BTreeNode *newRoot = new BTreeNode(maxDegree, false); 
            newRoot->child[0] = root;  
            newRoot->splitChild(0, root); 
            int i = 0; 
            if(newRoot->keys[0] < k) {
                i++; 
            }
            newRoot->child[i]->insertNonFull(k); 
            root = newRoot; 
        } else { 
            root->insertNonFull(k); 
        }
    } 
} 

BTree:: BTree(int degree) {
    root = nullptr;  
    maxDegree = degree;
}

int main() { 
    BTree Test(4);
    Test.insert(67); 
    Test.insert(13); 
    Test.insert(9); 
    Test.insert(22); 
    Test.insert(99); 
    Test.traverse(); 
    for (int k = 13; k > 11; k--) { 
        if(Test.search(k) != NULL) {
            cout << "\nExists";
        } else {
            cout << "\nNot exists";
        }
    }
    return 0; 
} 
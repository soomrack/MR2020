#include <iostream> 
using namespace std; 
  
class BTreeNode { 
    int *keys;  
    int maxDegree;      
    BTreeNode **child; // An array of child pointers 
    int keyNumber;      
    bool leaf; // Is true when node is leaf. Otherwise false 
public: 
    BTreeNode(int degree, bool leaf1);
    void insertNonFull(int k); //Inserts a new key. Node must be non-full when this function is called 
    void splitChild(int i, BTreeNode *node); 
    void traverse(); 
    BTreeNode *search(int k);   // returns NULL if there is no k
    int findGEKey(int k); //returns an index of the first key which is greater or equal to k
    int getParent(int i); //returns the last key of the leaf
    int getChild(int i); //returns the first key of the leaf
    void merge(int i); 
    void removeFromLeaf(int i);
    void removeFromNonLeaf(int i);
    void remove(int k);

friend class BTree; 
}; 

class BTree { 
    BTreeNode *root; 
    int maxDegree;  
public:  
    void traverse();
    BTreeNode* search(int k); 
    void insert(int k); 
    void remove(int k);
public:    
    BTree(int _t);
};   

BTreeNode::BTreeNode(int degree, bool leaf1) { 
    maxDegree = degree; 
    leaf = leaf1; 
  
    // Allocate memory for maximum number of possible keys and child pointers 
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

        // See if the found child is full 
        if (child[i + 1]->keyNumber == 2 * maxDegree - 1) { 
            // If the child is full, then split it 
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
  
    // Since this node is going to have a new child, create space of new child 
    for (int j = keyNumber; j >= i + 1; j--) 
        child[j + 1] = child[j]; 
  
    // Link the new child to this node 
    child[i + 1] = newNode; 
  
    // A key of node will move to this node. Find the location of new key and move all greater keys one space ahead 
    for (int j = keyNumber - 1; j >= i; j--) {
        keys[j + 1] = keys[j]; 
    }
  
    // Copy the middle key of node to this node 
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

int BTreeNode::findGEKey(int k) {
    int i = 0;

    while((i < keyNumber) && (keys[i] < k)) {
        ++i;
    } 
    return i;  
}

int BTreeNode::getParent(int i) {
    BTreeNode *currentNode = child[i];

    while(!currentNode->leaf) {
        currentNode = currentNode->child[currentNode->keyNumber];
    }
    return currentNode->keys[currentNode->keyNumber - 1];
}

int BTreeNode::getChild(int i) {
    BTreeNode *currentNode = child[i + i];

    while(!currentNode->leaf) {
        currentNode = currentNode->child[0];
    }
    return currentNode->keys[0];
}

void BTreeNode::merge(int i) {
    BTreeNode *c = child[i];
    BTreeNode *sibling = child[i + 1];

    c->keys[maxDegree - 1] = keys[i];
    for (int k = 0; k < sibling->keyNumber; ++k) {
        c->keys[keyNumber + k] = sibling->keys[k];
    }

    if(!c->leaf) {
        for (int k = 0; k <= sibling->keyNumber; ++k) {
            c->keys[keyNumber + k] = sibling->keys[k];
        }
    }
    
    for (int k = i + 1; k < keyNumber; ++k) {
        keys[k - 1] = keys[k];
    }
    
    for (int k = i + 2; k <= keyNumber; ++k) {
        child[k - 1] = child[k];
    }

    //To update the key count of child
    c->keyNumber += sibling->keyNumber + 1;
    keyNumber--;

    delete(sibling);
    return;
}

void BTreeNode::removeFromLeaf(int i) {
    for (int k = i + 1; k < keyNumber; ++k) {
        keys[k - 1] = keys[k];
    }

    keyNumber--;
    return;
}

void BTreeNode::removeFromNonLeaf(int i) {
    int k = keys[i];

    if(child[i]->keyNumber >= maxDegree) {
        int parent = getParent(i);
        keys[i] = parent;
        child[i]->remove(parent);
    } else if(child[i + 1]->keyNumber >= maxDegree) {
        int c = getChild(i);
        keys[i] = c;
        child[i + 1]->remove(c);
    }  else {
        merge(i);
        child[i]->remove(k);
    }
    
    return;
}

void BTreeNode::remove(int k) {
    int i = BTreeNode::findGEKey(k);
  
    if ((i < keyNumber) && (keys[i] == k)) {
        if (leaf) {
            removeFromLeaf(i);
        } else {
            removeFromNonLeaf(i);
        }
    } else {
        // If this node is a leaf node, then the key is not present in tree
        if (leaf) {
            cout << "The key "<< k <<" does not exist in the tree\n";
            return;
        }
  
        // The key to be removed is present in the sub-tree rooted with this node
        bool flag = false;
        if(i == keyNumber) {
            flag = true;
        }

        if (flag && (i > keyNumber)){
            child[i - 1]->remove(k);
        } else {
            child[i]->remove(k);
        }
    }
    return;
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
    BTree Test(3);
    Test.insert(32); 
    Test.insert(12); 
    Test.insert(1); 
    Test.insert(16); 
    Test.insert(352); 
    Test.insert(11); 
    Test.insert(7); 
    Test.insert(17); 
  
    Test.traverse(); 
  
    for (int k = 16; k > 14; k--) { 
        if(Test.search(k) != NULL) {
            cout << "\nPresent";
        } else {
            cout << "\nNot Present";
        }
    }

    return 0; 
} 
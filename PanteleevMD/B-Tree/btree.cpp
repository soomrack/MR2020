#include <iostream>
#include <string>

#define DEBUG True

#define STR_ERR ""
#define t 3         // minimum degee

class Node {
public:
    bool is_leaf;
    int num_of_keys;            // currently stored
    int keys[2*t-1];            // keys stored in nondecreasing order
    std::string data[2*t-1];
    Node* children[2*t];

public:
    Node();
    Node(int keys, bool is_leaf);
    Node(int keys, bool is_leaf, std::string data);
    void remove(int key);
    ~Node();
private:
    void remove_from_leaf(int index);
    void remove_from_nonleaf(int index);
    void borrowFromNext(int index);
    void borrowFromPrev(int index);
    void fill(int index);
    void merge(int index);
    int get_max(int index);
    int get_min(int idx);
};


class BTree {
private:
    Node* root;

    void delete_node(Node* node_to_del);
    Node* find_node(Node* search_start, const int key);
    Node* find_node(const int key);
    void split_child(Node* target, int child_gen);
    void insert_nonfull(Node* target, const int key, std::string data);
    std::string data_search(Node* target, const int key);
    Node* node_search(Node* target, const int key);
    int get_max(Node* node, int index);
// fields for Debug Visualizer VSCode addon
#ifdef DEBUG
    std::string json_viz;
    std::string nodes;
    std::string edges;
    void visualize(Node* node, int par_id);
#endif

public:
    void add(const int key, std::string data);  
    bool delete_by_key(const int key);  
    std::string find_by_key(const int key);  
public:
    BTree();
    ~BTree();
};

Node::Node() {
    for (int b = 0; b<2*t; b++)
        this->children[b] = nullptr;
    //this->keys[2*t+1] = {0};

}

Node::Node(int keys, bool is_leaf) {
    this->num_of_keys = keys;
    this->is_leaf = is_leaf;
    for (int b = 0; b<2*t; b++)
        this->children[b] = nullptr;
}
/*
Node::Node(int keys, bool is_leaf) {
    this->num_of_keys = keys;
    this->is_leaf = is_leaf;
    for (int b = 0; b<2*t; b++)
        this->children[b] = nullptr;
}
*/
Node::~Node() {
    // for delete children
}
// gets the maximum pre-index key from predecessor
int Node::get_max(int index)
{
    Node* current = this->children[index];
    while (!current->is_leaf)
        current = current->children[current->num_of_keys]; //takes the maximum index child until a leaf reached
    return current->keys[current->num_of_keys-1];
}
// find the minimum index (left-most) from successor
int Node::get_min(int idx)
{
    Node* current = this->children[idx+1];
    while (!current->is_leaf)
        current = current->children[0];
  
    // Return the first key of the leaf
    return current->keys[0];
}

void Node::remove_from_leaf(int index)
{
    // Move all the keys after the index-th pos one place backward
    for (int i=index+1; i<num_of_keys; ++i)
        keys[i-1] = keys[i];
    num_of_keys--;
}

void Node::remove_from_nonleaf(int index)
{
    int k = keys[index];
  
    if (children[index]->num_of_keys >= t)
    {
        // find the predecessor 'pred' in the subtree 
        int pred = get_max(index);
        keys[index] = pred;
        children[index]->remove(pred);
    }
    // If idx+1 child has at least t keys, find the successor 'succ' in the subtree    
    else if (children[index+1]->num_of_keys >= t)
    {
        int succ = get_min(index);
        keys[index] = succ;                         // Replace k by succ
        children[index+1]->remove(succ);            // Recursively delete succ in C[idx+1]
    }
    // both index and index+1 children have less that t keys
    // into C[idx]
    // Now C[idx] contains 2t-1 keys
    // Free C[idx+1] and recursively delete k from C[idx]
    else
    {
        merge(index);
        children[index]->remove(k);
    }
    return;
}

// A function to merge C[idx] with C[idx+1]
// C[idx+1] is freed after merging
void Node::merge(int index)
{
    Node *child = children[index];
    Node *sibling = children[index+1];
  
    // Pulling a key from the current node and inserting it into (t-1)th
    // position of C[idx]
    child->keys[t-1] = keys[index];
  
    // Copying the keys from C[idx+1] to C[idx] at the end
    for (int i=0; i<sibling->num_of_keys; ++i)
        child->keys[i+t] = sibling->keys[i];
  
    // Copying the child pointers from C[idx+1] to C[idx]
    if (!child->is_leaf)
    {
        for(int i=0; i<=sibling->num_of_keys; ++i)
            child->children[i+t] = sibling->children[i];
    }
  
    // Moving all keys after idx in the current node one step before -
    // to fill the gap created by moving keys[idx] to C[idx]
    for (int i=index+1; i<num_of_keys; ++i)
        keys[i-1] = keys[i];
  
    // Moving the child pointers after (idx+1) in the current node one
    // step before
    for (int i=index+2; i<=num_of_keys; ++i)
        children[i-1] = children[i];
  
    // Updating the key count of child and the current node
    child->num_of_keys += sibling->num_of_keys+1;
    num_of_keys--;
  
    // Freeing the memory occupied by sibling
    delete(sibling);
    return;
}
  

void Node::borrowFromPrev(int index)
{
  
    Node *child=children[index];
    Node *sibling=children[index-1];
  
    // The last key from C[idx-1] goes up to the parent and key[idx-1]
    // from parent is inserted as the first key in C[idx]. Thus, the  loses
    // sibling one key and child gains one key
  
    // Moving all key in C[idx] one step ahead
    for (int i=child->num_of_keys-1; i>=0; --i)
        child->keys[i+1] = child->keys[i];
  
    // If C[idx] is not a leaf, move all its child pointers one step ahead
    if (!child->is_leaf)
    {
        for(int i=child->num_of_keys; i>=0; --i)
            child->children[i+1] = child->children[i];
    }
  
    // Setting child's first key equal to keys[idx-1] from the current node
    child->keys[0] = keys[index-1];
  
    // Moving sibling's last child as C[idx]'s first child
    if(!child->is_leaf)
        child->children[0] = sibling->children[sibling->num_of_keys];
  
    // Moving the key from the sibling to the parent
    // This reduces the number of keys in the sibling
    keys[index-1] = sibling->keys[sibling->num_of_keys-1];
  
    child->num_of_keys += 1;
    sibling->num_of_keys -= 1;
  
    return;
}
  
// A function to borrow a key from the C[idx+1] and place
// it in C[idx]
void Node::borrowFromNext(int index)
{
  
    Node *child=children[index];
    Node *sibling=children[index+1];
  
    // keys[idx] is inserted as the last key in C[idx]
    child->keys[(child->num_of_keys)] = keys[index];
  
    // Sibling's first child is inserted as the last child
    // into C[idx]
    if (!(child->is_leaf))
        child->children[(child->num_of_keys)+1] = sibling->children[0];
  
    //The first key from sibling is inserted into keys[idx]
    keys[index] = sibling->keys[0];
  
    // Moving all keys in sibling one step behind
    for (int i=1; i<sibling->num_of_keys; ++i)
        sibling->keys[i-1] = sibling->keys[i];
  
    // Moving the child pointers one step behind
    if (!sibling->is_leaf)
    {
        for(int i=1; i<=sibling->num_of_keys; ++i)
            sibling->children[i-1] = sibling->children[i];
    }
  
    // Increasing and decreasing the key count of C[idx] and C[idx+1]
    // respectively
    child->num_of_keys += 1;
    sibling->num_of_keys -= 1;
  
    return;
}

// A function to fill child C[idx] which has less than t-1 keys
void Node::fill(int index)
{
  
    // If the previous child(C[idx-1]) has more than t-1 keys, borrow a key
    // from that child
    if (index!=0 && children[index-1]->num_of_keys>=t)
        borrowFromPrev(index);
  
    // If the next child(C[idx+1]) has more than t-1 keys, borrow a key
    // from that child
    else if (index!=num_of_keys && children[index+1]->num_of_keys>=t)
        borrowFromNext(index);
  
    // Merge C[idx] with its sibling
    // If C[idx] is the last child, merge it with with its previous sibling
    // Otherwise merge it with its next sibling
    else
    {
        if (index != num_of_keys)
            merge(index);
        else
            merge(index-1);
    }
    return;
}


void Node::remove(int key)
{
    int index = 0;
    // getting the index of the first key >= k
    while (index < num_of_keys && key > keys[index])
        index++;
  
    // The key to be removed is present in this node
    if (index <= num_of_keys && key == keys[index])
    {
        if (is_leaf)
            remove_from_leaf(index);
        else
            remove_from_nonleaf(index);
    }
    else
    {
        // If this node is a leaf node, then the key is not present in tree
        if (is_leaf)
        {
            return;
        }
  
        // The key to be removed is present in the sub-tree rooted with this node
        // The flag indicates whether the key is present in the sub-tree rooted
        // with the last child of this node
        bool flag = ( (index==num_of_keys)? true : false );
  
        // If the child where the key is supposed to exist has less that t keys,
        // we fill that child
        if (children[index]->num_of_keys < t)
            fill(index);
  
        // If the last child has been merged, it must have merged with the previous
        // child and so we recurse on the (idx-1)th child. Else, we recurse on the
        // (idx)th child which now has atleast t keys
        if (flag && index > num_of_keys)
            children[index-1]->remove(key);
        else
            children[index]->remove(key);
    }
    return;
}

BTree::BTree() {
    this->root = new Node(0, true);
}

BTree::~BTree() {
    delete root;
}

std::string BTree::data_search(Node* target, const int key)
{
    int index = 0;
    while (index < target->num_of_keys && key > target->keys[index])
        index++;
    //index--;
    if (index <= target->num_of_keys && key == target->keys[index])
        return target->data[index];                            
    else if (target->is_leaf)
        return STR_ERR;
    return data_search(target->children[index], key);
}

Node* BTree::node_search(Node* target, const int key)
{
    int index = 1;
    while (index <= target->num_of_keys && key > target->keys[index])
        index++;
    if (index <= target->num_of_keys && key == target->keys[index])
        return target;                            
    return node_search(target->children[index], key);
}

std::string BTree::find_by_key(const int key)
{
    return data_search(this->root, key);
}

void BTree::split_child(Node* target, int child_i)               // target is the node being split
{   
    Node* child = target->children[child_i];                    // target's child_i'th child
    Node* new_node = new Node(t-1, child->is_leaf);
    for (int j = 0; j < t-1; j++) {                      
        new_node->keys[j] = child->keys[j+t];
        new_node->data[j] = child->data[j+t];
    }
    if (child->is_leaf == false)
        for (int c = 0; c < t; c++)                     
            new_node->children[c] = child->children[c+t];       // new_node takes t largest children (w t-1 keys) from y
    child->num_of_keys = t-1;                                   // adjust the key count (wrong will be rewritten)
    for (int j = target->num_of_keys; j > child_i + 1; j--)
        target->children[j+1] = target->children[j];
    target->children[child_i+1] = new_node;                     // new_node becomes a new child just after 'child'
                        
    for (int j = target->num_of_keys; j > child_i; j--) {       // move the median key up to separate new_node and child
        target->keys[j+1] = target->keys[j];
        target->data[j+1] = target->data[j];
    }
    target->keys[child_i] = child->keys[t-1];
    target->data[child_i] = child->data[t-1];
    target->num_of_keys++;     

#if DEBUG == True
    visualize(this->root, 0);     
#endif                           
}

// inserts key into node x (assumed nonfull)
void BTree::insert_nonfull(Node* target, const int key, std::string data)
{
    int index = target->num_of_keys-1;      //
    if (target->is_leaf) {                                      // target is a leaf 
        while (index >= 0 && key < target->keys[index])
        {
            target->keys[index+1] = target->keys[index];
            target->data[index+1] = target->data[index];
            index--;
        }
        target->keys[index+1] = key;                            // so we insert key into it
        target->data[index+1] = data;
        target->num_of_keys++;
    }
    else {                                                      // target is not a leaf
        while (index >= 0 && key < target->keys[index])         // determine the child to which recursion descends
            index--;
        index++;
        if (target->children[index]->num_of_keys == 2*t-1) {    // determine wheteher this child would be full
            split_child(target, index);                         // yes => split into two nonfull children 
            if (key > target->keys[index])                      // decide where to descend next after the split
                index++;
        }
        insert_nonfull(target->children[index], key, data);           // no => recursevely go for the right node
    }

#if DEBUG == True
    visualize(this->root, 0);     
#endif 
}

void BTree::add(const int key, std::string data)
{
    if (this->root == nullptr)
    {
        this->root = new Node(0, true);
    }


    Node* cur_root = this->root;
    if (cur_root->num_of_keys == 2*t-1)                          // node is full
    {
        this->root = new Node(0, false);
        this->root->children[0] = cur_root;
        split_child(this->root, 0);                             // => need split to increase height
        insert_nonfull(this->root, key, data);                        // now can insert 
    }
    else insert_nonfull(cur_root, key, data);       
}

bool BTree::delete_by_key(const int key)
{
    if (this->root == nullptr) {
        return false;     // the tree is empty
    }
    this->root->remove(key);

    if (this->root->num_of_keys == 0)
    {
        Node *temporary = this->root;
        if (this->root->is_leaf)
            this->root = nullptr;
        else 
            this->root = this->root->children[0];
        delete temporary;
    }

#if DEBUG == True
    visualize(this->root, 0);     
#endif 


    return true;
}

int main()
{
    BTree test_tree;

    bool dbg = false;
    test_tree.add(15, "data15");
    test_tree.add(19, "data19");
    dbg = test_tree.delete_by_key(19);
    dbg = test_tree.delete_by_key(15);
    test_tree.add(21, "data21");
    test_tree.add(20, "data20");
    test_tree.add(22, "data22"); 
    test_tree.add(25, "data25"); 
    test_tree.add(30, "data30"); 
    test_tree.add(27, "data27"); 
    test_tree.add(37, "data37"); 
    test_tree.add(2, "data2"); 
    std::string outpt = test_tree.find_by_key(25);
    dbg = test_tree.delete_by_key(25);
    dbg = test_tree.delete_by_key(22);
    test_tree.add(34, "data34");
    test_tree.add(5, "data5"); 
    test_tree.add(1, "data1"); 
    test_tree.add(9, "data9"); 
    test_tree.add(77, "data77");
    dbg = test_tree.delete_by_key(21);
    //cout<<'wow';
    return 0;
}







// generates JSON string out of the tree to provide graphviz visualization 
#if DEBUG == True
    void BTree::visualize(Node* node, int par_id)
    {   
        // -exec set print elements 0        <- to debug console

        if (node == nullptr)
            return;

        int iter = node->num_of_keys;
        if (iter != 0) {
            int id = node->keys[0];
            std::string label = "";
            for (int i = 0; i < iter; i++)
                label += std::to_string(node->keys[i]) + " ";
            this->nodes += "{\"id\":\"" + std::to_string(id) + "\", \"label\": \"" + label + "\"}, ";
            this->edges += "{\"from\":\"" + std::to_string(par_id) + "\",\"to\":\"" + std::to_string(id) + "\"}, ";
            for (int i = 0; i<=iter; i++)
                if (node->children[i] != nullptr)
                    visualize(node->children[i], id);
        }
        if (node == this->root)
        {
            std::string nd_lst = this->nodes;
            std::string edg_lst = this->edges;
                        
            nd_lst = nd_lst.substr(0, nd_lst.length()-2);
            edg_lst = edg_lst.substr(0, edg_lst.length()-2);
            this->json_viz = "{\"kind\":{\"graph\":true}, "
            "\"nodes\":[" + nd_lst + "],"
            "\"edges\":[" + edg_lst + "]}";
            this->nodes.clear();
            this->edges.clear();
            //this->json_viz.clear();
        }
    }
#endif
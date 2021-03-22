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
    ~Node();
};


class BTree {
private:
    Node* root;

    void delete_node(Node* node_to_del);
    Node* find_node(Node* search_start, const int key);
    Node* find_node(const int key);
    void split_child(Node* target, int child_gen);
    void insert_nonfull(Node* target, const int key, std::string data);
    std::string tree_search(Node* target, const int key);
// fields for Debug Visualizer VSCode addon
#ifdef DEBUG
    std::string json_viz;
    std::string nodes;
    std::string edges;
    void visualize(Node* node, int par_id);
#endif

public:
    void add(const int key, std::string data);  
    void del(const int key);  
    std::string find_key(const int key);  
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

BTree::BTree() {
    this->root = new Node(0, true);
}

BTree::~BTree() {
    delete root;
}

std::string BTree::tree_search(Node* target, const int key)
{
    int index = 1;
    Node* root = this->root;
    while (index <= root->num_of_keys && key > root->keys[index])
        index++;
    if (index <= root->num_of_keys && key == root->keys[index])
        return target->data[index];                            
    else if (target->is_leaf)
        return STR_ERR;
    return tree_search(target->children[index], key);
}

std::string BTree::find_key(const int key)
{
    return tree_search(this->root, key);
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


int main()
{
    BTree test_tree;

    test_tree.add(15, "data15");
    test_tree.add(19, "data19");
    test_tree.add(21, "data21");
    test_tree.add(20, "data20");
    test_tree.add(22, "data22"); 
    test_tree.add(25, "data25"); 
    test_tree.add(30, "data30"); 
    test_tree.add(27, "data27"); 
    test_tree.add(37, "data37"); 
    test_tree.add(2, "data2"); 
    std::string outpt = test_tree.find_key(25);
    test_tree.add(34, "data34");
    test_tree.add(5, "data5"); 
    test_tree.add(1, "data1"); 
    test_tree.add(9, "data9"); 
    test_tree.add(77, "data77");
    //test_tree.del(25);
    //cout<<'wow';
    return 0;
}



// generates JSON string out of the tree to generate graphviz visualization 
#if DEBUG == True
    void BTree::visualize(Node* node, int par_id)
    {   
        // -exec set print elements 0        <- to debug console

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
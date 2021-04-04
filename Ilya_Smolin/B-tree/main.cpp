#include <iostream>
using namespace std;

const int POINTERS_COUNT = 4;
const int EMPTY_CODE =  INT_MAX;


class Node {
private:
    bool Node_Full (); //true if node is full
    bool Node_Leaf (); //true if node is a leaf
    /* An utility function to split the *child of this Node
     * Note that *child must be full when this function is called*/
    void Split_Child (int i, Node *Child);
    /*An utility function to insert a new key in the subtree rooted with this node
     * Node must be non-full when this function is called*/
    void Insert_Non_Full (const int key, string data);
    int Count_Keys();
public:
    int Keys [POINTERS_COUNT - 1]{}; //array of keys
    string Data [POINTERS_COUNT - 1]; //array of data
    Node *Pointers [POINTERS_COUNT]{}; //array of pointers
public:
    Node();
    ~Node();
    friend class BTree;
};


class BTree {
private:
    Node *root;
    string Find_In_Subtree (Node *current_node, int key);
public:
    void Insert(const int key, string data);
    bool Delete(const int key);  // false if no key
    string Find(const int key);  // return '' if no key
public:
    BTree() { root = nullptr; };
    ~BTree() { delete root; };

    friend class Node;
};

bool Node::Node_Full()
{
    if ( Keys[POINTERS_COUNT - 2] == EMPTY_CODE )
        return false;
    return true;
}

bool Node::Node_Leaf()
{
    if ( Pointers[0] == nullptr )
        return true;
    return false;
}

string BTree::Find_In_Subtree(Node *current_node, int key)
{
    if (current_node == nullptr)
        return "fault";
    int index = 0;
    while (index <= POINTERS_COUNT - 2 && current_node -> Keys [index] <= key)
        index++;

    if (current_node -> Keys[index-1] == key)
        return current_node -> Data[index-1];
    if (current_node -> Node_Leaf())
        return "not_found";
    return Find_In_Subtree(current_node->Pointers[index], key);
}


string BTree::Find(const int key)
{
    return Find_In_Subtree(root, key);
}

void BTree::Insert(const int key, string data)
{
    // If tree is empty
    if (root == nullptr)
    {
        root = new Node();
        root -> Keys[0] = key;
        root -> Data [0] = data;
    }

    if (root -> Node_Full()) //Root is Full
    {
        //Allocate memory for new root
        Node *New_Root = new Node();

        //Make old root as child of new root
        New_Root -> Pointers[0] = root;

        //Split the old root and move 1 key to the new root
        New_Root -> Split_Child(0, root);

        /*New root has two children now. Decide which of the
         * two children is going to have new key*/
        if (New_Root -> Keys[0] < key)
            New_Root -> Pointers[1] -> Insert_Non_Full (key, data);
        else
            New_Root -> Pointers[0] -> Insert_Non_Full (key, data);

        //Change root
        root = New_Root;
    }
    else //If root is not full
        root -> Insert_Non_Full (key, data);
}



/* An utility function to split the *child of this Node
* Note that *child must be full when this function is called*/

void Node::Split_Child(int i, Node *Child)
{
    //Create new node which is going to store keys of Parent
    Node *Right = new Node();

    //Cut and paste POINTER_COUNT - 3 Keys
    for (int j = 0; j < POINTERS_COUNT - 3; ++j)
    {
        Right -> Keys[j] = Child -> Keys[j+(POINTERS_COUNT-2)];
        Right -> Data[j] = Child -> Data[j+(POINTERS_COUNT-2)];
        Child -> Keys[j+(POINTERS_COUNT-2)] = EMPTY_CODE;
        Child -> Data[j+(POINTERS_COUNT-2)] = "";
    }

    //Cut and paste last POINTER_COUNT - 2 Children
    for (int j = 0;  j < POINTERS_COUNT - 2; j++)
    {
        Right -> Pointers[j] = Child -> Pointers[j+(POINTERS_COUNT-2)];
        Child -> Pointers[j+(POINTERS_COUNT-2)] = nullptr;
    }

    //Create a space for a new child
    for (int j = Count_Keys(); j >= i+1; j--)
        Pointers[j+1] = Pointers[j];

    //Link the new child to this node
    Pointers [i+1] = Right;

    //Key and data of child will move to this node, so find the location of the new key
    //and move all greater key one space ahead
    for (int j = Count_Keys()-1; j >= i; j--)
    {
        Keys[j+1] = Keys[j];
        Data[j+1] = Data[j];
    }


    //Cut and paste the middle key and data of child to this node
    Keys[i] = Child -> Keys[POINTERS_COUNT-3];
    Child -> Keys[POINTERS_COUNT-3] = EMPTY_CODE;
    Data[i] = Child -> Data[POINTERS_COUNT-3];
    Child -> Data[POINTERS_COUNT-3] = "";
}

Node::Node()
{
    for (int i = 0; i <= (POINTERS_COUNT - 2); i++) {
        Keys[i] = EMPTY_CODE;
        Data[i] = "";
        Pointers[i] = nullptr;
    }
    Pointers[POINTERS_COUNT - 1] = nullptr;
}

Node::~Node()
{
    delete Pointers [POINTERS_COUNT - 1];
}

int Node::Count_Keys()
{
    int count = 0;
    for (int i = 0; i <= (POINTERS_COUNT - 2); i++) {
        if (Keys[i] != EMPTY_CODE)
            count++;
    }
    return count;
}

void Node::Insert_Non_Full(const int key, string data)
{
    //Initialize index as index fo the rightmost element
    int i = Count_Keys()-1;

    if (Node_Leaf()) //If this is a leaf node
    {
        /*This loop does two things
         * a) Finds the location of the new key to be inserted
         * b) Moves all grater keys to one place ahead*/
        while (i >= 0 && Keys[i] > key)
        {
            Keys[i + 1] = Keys[i];
            Data[i + 1] = Data[i];
            i--;
        }

        //Insert new key and data at found location
        Keys[i + 1] = key;
        Data[i + 1] = data;
    }
    else
    {
        //Find which child is gonna have the new key
        while (i >= 0 && Keys[i] > key)
            i--;

        // See if the found child is full
        if (Pointers[i+1] -> Node_Full())
        {
            Split_Child(i+1, Pointers[i+1]);

            /*After split the middle key of Pointers[i] goes up and
             * Pointers[i] is split by two. See which of them is going to have the new key*/
            if (Keys[i+1] < key)
                i++;
        }
        Pointers[i+1] -> Insert_Non_Full(key,data);
    }
}

int main()
{
    BTree mytree;
    mytree.Insert(30,"30");
    mytree.Insert(10,"10");
    mytree.Insert(20,"20");
    mytree.Insert(1,"1");
    mytree.Insert(2,"2");
    mytree.Insert(3,"3");
    mytree.Insert(4,"4");
    mytree.Insert(5,"5");
    mytree.Insert(6,"6");

    cout<<mytree.Find(30)<<endl;
    cout<<mytree.Find(10)<<endl;
    cout<<mytree.Find(20)<<endl;
    cout<<mytree.Find(1)<<endl;
    cout<<mytree.Find(2)<<endl;
    cout<<mytree.Find(3)<<endl;
    cout<<mytree.Find(4)<<endl;
    cout<<mytree.Find(5)<<endl;
    cout<<mytree.Find(6)<<endl;


    return 0;
}

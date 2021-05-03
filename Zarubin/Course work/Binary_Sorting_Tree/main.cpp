#include <algorithm>
#include <vector>
#include <iostream>
#include <memory>
#include <functional>

using namespace std;

struct BinaryTreeNode
{
    shared_ptr<BinaryTreeNode> left, right;
    int key;
};

class BinaryTree
{
public:

    void insert(int key);
    typedef function<void(int key)> Visitor;
    void visit(const Visitor& visitor);

private:

    void visit_recursive(const shared_ptr<BinaryTreeNode> cur_node, const Visitor visitor);
    shared_ptr<BinaryTreeNode> node_recursive;
    shared_ptr<BinaryTreeNode> m_root;
    void insert_recursive(const shared_ptr<BinaryTreeNode> cur_node, const shared_ptr<BinaryTreeNode> node_to_insert);

};

// cur_node и node_to_insert не могут быть nullptr
void BinaryTree::insert_recursive(const shared_ptr<BinaryTreeNode> cur_node, const shared_ptr<BinaryTreeNode> node_to_insert)
{
    if(node_to_insert->key < cur_node->key)
    {
        if(cur_node->left == nullptr)
        {
            cur_node->left = node_to_insert;
            return;
        }
        node_recursive = cur_node->left;
    }
    else
    {
        if(cur_node->right == nullptr)
        {
            cur_node->right = node_to_insert;
            return;
        }
        node_recursive = cur_node->right;
    }
    insert_recursive(node_recursive, node_to_insert);
}

void BinaryTree::insert(int key)
{
    shared_ptr<BinaryTreeNode> node_to_insert(new BinaryTreeNode);
    node_to_insert->key = key;

    if(m_root == nullptr)
    {
        m_root = node_to_insert;
        return;
    }

    insert_recursive(m_root, node_to_insert);
}

// узлы посещаем в порядке: левое поддерево -> текущий элемент -> правое поддерево
// cur_node не может быть nullptr
void BinaryTree::visit_recursive(const shared_ptr<BinaryTreeNode> cur_node, const Visitor visitor)
{
    if(cur_node->left != nullptr)
        visit_recursive(cur_node->left, visitor);

    visitor(cur_node->key);

    if(cur_node->right != nullptr)
        visit_recursive(cur_node->right, visitor);
}

void BinaryTree::visit(const Visitor& visitor)
{
    if(m_root == nullptr)
        return;
    visit_recursive(m_root, visitor);
}

int main()
{
    BinaryTree tree;
    vector<int> data_to_sort = {0, -1, 2, -3, 4, -5, 6, -7, 8, -9};
    for(int value : data_to_sort)
    {
        tree.insert(value);
    }
    tree.visit([](int visited_key)
               {
                   cout<<visited_key<<" ";
               });
    cout<<endl;

    return 0;
}
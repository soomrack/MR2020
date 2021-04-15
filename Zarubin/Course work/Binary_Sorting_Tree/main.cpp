#include <cassert>
#include <algorithm>
#include <vector>
#include <iostream>
#include <memory>
#include <functional>

using namespace std;

// класс, представляющий бинарное дерево
class BinaryTree
{
protected:
    // узел бинарного дерева
    struct BinaryTreeNode
    {
        shared_ptr<BinaryTreeNode> left, right; // левое и правое поддерево
        int key; // ключ
    };

    shared_ptr<BinaryTreeNode> m_root; // корень дерева

protected:
    // рекурсивная процедура вставки ключа
    // cur_node - текущий узел дерева, с которым сравнивается вставляемый узел
    // node_to_insert - вставляемый узел
    void insert_recursive(const shared_ptr<BinaryTreeNode>& cur_node, const shared_ptr<BinaryTreeNode>& node_to_insert)
    {
        assert(cur_node != nullptr);
        // сравнение
        bool insertIsLess = node_to_insert->key < cur_node->key;
        if(insertIsLess)
        {
            // вставка в левое поддерево
            if(cur_node->left == nullptr)
                cur_node->left = node_to_insert;
            else
                insert_recursive(cur_node->left, node_to_insert);
        }
        else
        {
            // вставка в правое поддерево
            if(cur_node->right == nullptr)
                cur_node->right = node_to_insert;
            else
                insert_recursive(cur_node->right, node_to_insert);
        }
    }

public:
    void insert(int key)
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

public:
    typedef function<void(int key)> Visitor;

protected:
    // рекурсивная процедура обхода дерева
    // cur_node - посещаемый в данный момент узел
    void visit_recursive(const shared_ptr<BinaryTreeNode>& cur_node, const Visitor& visitor)
    {
        assert(cur_node != nullptr);

        // сначала посещаем левое поддерево
        if(cur_node->left != nullptr)
            visit_recursive(cur_node->left, visitor);

        // посещаем текущий элемент
        visitor(cur_node->key);

        // посещаем правое поддерево
        if(cur_node->right != nullptr)
            visit_recursive(cur_node->right, visitor);
    }

public:
    void visit(const Visitor& visitor)
    {
        if(m_root == nullptr)
            return;
        visit_recursive(m_root, visitor);
    }
};

int main()
{
    BinaryTree tree;
    // добавление элементов в дерево
    vector<int> data_to_sort = {0, -1, 2, -3, 4, -5, 6, -7, 8, -9};
    for(int value : data_to_sort)
    {
        tree.insert(value);
    }
    // обход дерева
    tree.visit([](int visited_key)
               {
                   cout<<visited_key<<" ";
               });
    cout<<endl;

    return 0;
}
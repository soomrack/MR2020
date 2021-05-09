#include <iostream>
#include <ctime>

struct node // структура для представления узлов дерева
{
    int key; //текущий ключ
    unsigned short height; //высота поддерева с корнем в текущем узле
    node * left; //указатель на левое дерево
    node * right; //указатель на правое дерево

};
class tree {

    public:
    node * root;
    node * turnright(node * p);
    node * turnleft(node * q);
    node * insert(node * p, int k);
    node * balance(node * p);
    tree() {
        root = new node;
        root -> left = 0;
        root -> right = 0;
        root -> key = 0;
        root -> height = 1;
    };
    private:
    unsigned short height(node * p);
    int8_t bfactor(node * p);
    void realheight(node * p);
};

unsigned short tree::height(node * p) {
    return p ? p -> height : 0;
}

int8_t tree::bfactor(node * p) {
    return (int8_t)(height(p -> right) - height(p -> left));
}

void tree::realheight(node * p) {
    unsigned short hleft = height(p -> left);
    unsigned short hright = height(p -> right);
    p -> height = (hleft > hright ? hleft : hright) + 1;
}

node * tree::turnright(node * p) // правый поворот вокруг p
{
    node * q = p -> left;
    p -> left = q -> right;
    q -> right = p;
    realheight(p);
    realheight(q);
    return q;
}

node * tree::turnleft(node * q) // левый поворот вокруг q
{
    node * p = q -> right;
    q -> right = p -> left;
    p -> left = q;
    realheight(q);
    realheight(p);
    return p;
}

node * tree::balance(node * p) // балансировка узла p
{
    realheight(p);
    if (bfactor(p) == 2) {
        if (bfactor(p -> right) < 0)
            p -> right = turnright(p -> right);
        return turnleft(p);
    }
    if (bfactor(p) == -2) {
        if (bfactor(p -> left) > 0)
            p -> left = turnleft(p -> left);
        return turnright(p);
    }
    return p; // балансировка не нужна
}

node * tree::insert(node * p, int k) // вставка ключа k в дерево с корнем p
{
    if (!p) {
        node * A = new node;
        A -> height = 1;
        A -> key = k;
        A -> left = 0;
        A -> right = 0;
        return A;
    }
    if (k < p -> key)
        p -> left = insert(p -> left, k);
    else
        p -> right = insert(p -> right, k);
    return balance(p);
}


int main() {

    using namespace std;
    tree A;

    A.root = A.insert(A.root, 100);
    A.root = A.insert(A.root, 1);
    A.root = A.insert(A.root, 2);
    A.root = A.insert(A.root, 3);
    A.root = A.insert(A.root, 102);
    A.root = A.insert(A.root, 103);
    A.root = A.insert(A.root, 104);
    A.root = A.insert(A.root, 7);
    A.root = A.insert(A.root, 4);
    A.root = A.insert(A.root, 108);
    A.root = A.insert(A.root, 112);
    A.root = A.insert(A.root, 109);

    return 0;
}
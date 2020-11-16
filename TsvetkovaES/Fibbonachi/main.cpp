//#include <iostream>
#include <stdio.h>
//#include <d2d1helper.h>

//using namespace std;
struct Node { // тип данных "узел". У него есть:
    int key; // ключ-значение
    Node* left; // левая палка (указатель на ещё один "узел")
    Node* right; // правая палка
};

class Tree {
private:
    Node* root; //Указатель на корень дерева.
public:
    Tree() {
        root = NULL;
    };
    void Print_tree (Node*, int); // передаём в функцию значение (указателя)
    void Declare_tree (int, Node**); //передаём в функцию указатель (на указатель)
    void Define_tree (Node**,int *); //передаём в функцию указатель (на указатель)
    Node** Get_rooot() {return &root;};
    Node* Get_root() {return root;};
};

// поиск узла в дереве по ключу key
Node* Search_node(Tree Tree, int key) {
    Node* answer=Tree.Get_root(); // начинаем поиск с корневого узла
    while(answer!=NULL||key!=answer->key) { // пока не дойдём до конца дерева или
        if(key<answer->key) {               // не найдём узел с заданым ключом
            answer=answer->left;
        } else {
            answer=answer->right;
        }
    }
    printf("\n%d",answer->key);
    return answer;
}
// узел с минимальным и максимальным ключом в дереве
Node* Search_min(Tree Tree) {
    Node* answer=Tree.Get_root(); // начинаем поиск с корневого узла
    while(answer->left!=NULL) { // это просто "самый левый" узел
        answer=answer->left;
    }
    printf("\n%d",answer->key);
    return answer;
}
Node* Search_max(Tree Tree) {
    Node** answer=Tree.Get_rooot(); // начинаем поиск с корневого узла
    while((*answer)->right!=NULL) { // это просто "самый правый" узел
        (*answer)=(*answer)->right;
    }
    printf("\n%d",(*answer)->key);
    return (*answer);
}

// Построение дерева Фибоначчи порядка k с незаполненными полями "key"
void Tree::Declare_tree (int k, Node** node) { // в аргумент передаём указатель на корень
    if (k==0) {                                // (а корень указывает на своё значение)
        (*node) = NULL; // конец ветки
    }
    else if ( k==1 ) {
        (*node) = new (Node); // выделяем память под последний узел
        (*node)->left = (*node)->right = NULL; // без выходящих палок из него
    } else {
        (*node) = new (Node); // корень
        Declare_tree (k-1,&((*node)->left)); // создаём ветку слева от корня
        Declare_tree (k-2,&((*node)->right)); // создаём ветку справа от корня
    }
}

// Заполнение полей "key" узлов созданного заранее дерева
void Tree::Define_tree (Node** node, int* key) { // начинаем с корня, key=1 в начале
    if ((*node)!=NULL) {
        Define_tree (&((*node)->left),key); // идём в самый левый край (минимальный ключ)
        (*node)->key = (*key); // дошли до min - даём ему минимальное значение
        (*key)++;
        Define_tree (&((*node)->right),key); // рекурсия идёт снизу вверх по дереву, пока не наткнётся
    } // на "развилку" (где есть правая палка), дальше пойдёт в самый правый конец
}
void Tree::Print_tree (Node* node, int h) {
    int i=0;
    if  (node!=NULL) {
        Print_tree (node->right,h+1); // уходим в самое права
        for (i=1;i<=h;i++) {
            printf("     ");
        }
        printf("%d\n",node->key);
        Print_tree (node->left,h+1);
    }
}

int main() {
    Tree my_tree;
    int h=5; // высота дерева
    int i=1; // первый ключ дерева
    my_tree.Declare_tree(h,my_tree.Get_rooot());
    my_tree.Define_tree(my_tree.Get_rooot(),&i);
    my_tree.Print_tree(my_tree.Get_root(),0);
    Search_max(my_tree);
    Search_min(my_tree);
    return 0;
}

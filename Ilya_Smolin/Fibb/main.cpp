#include <iostream>
#include <stdio.h>

/*Пока успел реализовать функции балансировки и работы с АВЛ деревом, и примерныйвид функции Фиббоначи,
 * осталось дописать функции, возвращающие, амксимальный подсчитанный элемент в стеке, а также, которая
 возвращает значение числа Фиббоначи по ключу*/

struct node // структура для представления узлов дерева
{
    int key;
    int value;
    unsigned char height;
    node* left;
    node* right;
    node(int k, int val) { key = k; left = right = 0; height = 1; value = val; }
};

unsigned char height(node* p)
{
    return p?p->height:0;
}

int bfactor(node* p)
{
    return height(p->right)-height(p->left);
}

void fixheight(node* p)
{
    unsigned char hl = height(p->left);
    unsigned char hr = height(p->right);
    p->height = (hl>hr?hl:hr)+1;
}

node* rotateright(node* p) // правый поворот вокруг p
{
    node* q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}

node* rotateleft(node* q) // левый поворот вокруг q
{
    node* p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}

node* balance(node* p) // балансировка узла p
{
    fixheight(p);
    if( bfactor(p)==2 )
    {
        if( bfactor(p->right) < 0 )
            p->right = rotateright(p->right);
        return rotateleft(p);
    }
    if( bfactor(p)==-2 )
    {
        if( bfactor(p->left) > 0  )
            p->left = rotateleft(p->left);
        return rotateright(p);
    }
    return p; // балансировка не нужна
}

node* insert(node* p, int k, int val) // вставка ключа k в дерево с корнем p
{
    if( !p ) return new node(k,val);
    if( k<p->key )
        p->left = insert(p->left,k,val);
    else
        p->right = insert(p->right,k,val);
    return balance(p);
}

node* findmin(node* p) // поиск узла с минимальным ключом в дереве p
{
    return p->left?findmin(p->left):p;
}

node* removemin(node* p) // удаление узла с минимальным ключом из дерева p
{
    if( p->left==nullptr )
        return p->right;
    p->left = removemin(p->left);
    return balance(p);
}

node* remove(node* p, int k) // удаление ключа k из дерева p
{
    if( !p ) return 0;
    if( k < p->key )
        p->left = remove(p->left,k);
    else if( k > p->key )
        p->right = remove(p->right,k);
    else //  k == p->key
    {
        node* q = p->left;
        node* r = p->right;
        delete p;
        if( !r ) return q;
        node* min = findmin(r);
        min->right = removemin(r);
        min->left = q;
        return balance(min);
    }
    return balance(p);
}
//Поиск максимального числа в АВЛ дереве:
int maxsearch (node* p) // удаление ключа k из дерева p
{

};
//Поиск числа по ключу и возврат его value
int valuefromkey (node* p,int key)
{

}
struct node *Cashe = nullptr; //Глобальный Кэш
//Реализация Фиббоначи с Кэшем в виде АВЛ дерева
int fibb (int n){
    if (n == 1 || n == 0)
        return 1;
    else if (maxsearch(Cashe)>=n)
    {
        return valuefromkey(Cashe,n);
    } else
    {
     int answer = fibb(n-1) + fibb(n-2);
     insert(Cashe,n,answer);
        return answer;
    }
}
int main() {
    insert(Cashe,2,2);
    int N;
    printf("N=");
    scanf("%d", &N);
    printf("%d ", fibb(N));
    return 0;
}
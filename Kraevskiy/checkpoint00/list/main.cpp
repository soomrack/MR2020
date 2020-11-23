#include <iostream>
using namespace std;

class List {
public:
    List();
    ~List();
    int list_size;
    void Pop_first();           //удаление первого элемента в списке
    int Get_size()              // получить количество елементов в списке
    {
        return list_size;
    }
    int get_value(int index);               //получение значение списка
    void set_value(int index, int value);   //вставка значение
    void del_value(int index);              //удаление элемента

private:
    class Node
    {
    public:
        Node *next;                             //указатель на следующий узел
        int value;
        //конструктор для узла
        Node(int value, Node *next = nullptr)   //параметр по умолчанию для добавления в конец списка
        {
            this->value = value;
            this->next = next;
        }
    };
    Node *root;                                 //указатель на первый элемент списка
};

List::List()
{
    list_size = 0;
    root = nullptr;
}

List::~List()
{
    while (list_size)   // пока size не станет равным нулю
    {
        Pop_first();
    }
}

void List::Pop_first()
{
    Node *temp = root;  //временный узел, для хранения адреса первого элемента
    root = root->next;  //адресс следующиего элемента за головой (второй элемент)
    delete temp;        //удаление первого узла
    list_size--;
}

void List::del_value(int index)
{
    Node *prev = this->root;                    //адрес предыдущего элемент
    if (index == 0)                             //если удаляем первый элемент
    {
        Pop_first();
    } else
    {
        for (int i = 0; i < index - 1; i++)     //ищем предыдущий
        {
            prev = prev->next;
        }
        Node *del = prev->next;                 //адрес удаляемого элемента
        prev->next = del->next;                 //новый адрес предыдущего
        delete del;
        list_size--;
    }
}

void List::set_value(int index, int value)
{
    if (index == 0)                         //если добавляем первый элемент
    {
        root = new Node(value, root);
    } else
    {
        Node *prev = this->root;            //адрес предыдущего элемент
        for (int i = 0; i < index - 1; i++) //ищем предыдущий
        {
            prev = prev->next;              //указатель на элемент, до добавляемого
        }
        if (prev->next == nullptr)          //если добавляем в конец списка
        {
            Node *newNode = new Node (value);
            prev->next = newNode;
        } else
        {
            Node *newNode = new Node (value, prev->next);   //вставляем элемент с адресом на следующий
            prev->next = newNode;                           //присваиваем предыдущему адресс добавленного
        }
    }
    list_size++;
}

int List::get_value(int index)
{
    int counter = 0;                //счетчик для индекса элемента по списку
    Node *current = this->root;     //временный указатель на начало списка
    while (current != nullptr)      //цикл до конца списка
    {
        if (counter == index)
        {
            return current->value;  //возвращаем данные из текущего узла
        }
        current = current->next;    //временный адресс ссылается на следующий элемент
        counter++;
    }
}

int main() {
    List lst;
    lst.set_value(0,1);
    lst.set_value(1,7);
    lst.set_value(2,555);
    lst.set_value(0,11111);
    lst.set_value(2,2222);

    for (int i = 0; i < lst.Get_size(); i++)
    {
        cout << lst.get_value(i) << endl;
    }

    cout << endl << "del_value 2" << endl << endl;
    lst.del_value(2);

    for (int i = 0; i < lst.Get_size(); i++)
    {
        cout << lst.get_value(i) << endl;
    }
    
    cout << endl << "The end." << endl;
}
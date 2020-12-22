#include <iostream> 

class List;

class nod {
public:
    int value;
    nod *next;
public:
    nod(int value);
    nod(int value, nod *next);
};


class iter {
private:
    nod *current;
    nod *prev;
    List *head;
public:
    iter next();
    int get_value();
    void set_value(const int value);
public:
    void insert(const int value);
    void del();
public:
    iter();
    iter (List &head);
};


class List {
private:
    friend class iter;
    nod *root;
public:
    iter begin();
public:
    List();
    ~List();
};

nod :: nod(int value){
    this->value = value;
    next = nullptr;
}

nod ::nod(int value, nod *next) {
    this-> value = value;
    this-> next = next;
}

iter :: iter(){
    current = head->root;
}

iter :: iter (List &rooot){
    head = &rooot;
    current = head->root;
    prev = nullptr;
}

iter List :: begin(){
    iter remake(*this);
    return (*this);
}

List ::List() {
    root = nullptr;
}

List :: ~List() {
    iter toDelete;
    while (root != nullptr)
        toDelete.del();
}

void iter::insert (const int value){
    current = new nod(value, current);
    head->root = current;
}

void iter::del() {
    if (current != nullptr && prev != nullptr)
    {
        prev->next = current->next;
        delete current;
        current = prev->next;
        return;
    }
    if (prev == nullptr && current != nullptr)
    {
        head->root = current->next;
        delete current;
        current = head->root;
        return;
    }
}

int iter  :: get_value() {
    return current->value;
}

void iter ::set_value(const int value) {
    current->value = value;
}

iter  ::next() {
    if (current != nullptr){
        prev = current;
        current = current->next;
    }
    return *this;
}


int main() {
    List list;
    iter iterator = list.begin();
    iteriterator.insert(1);
    iterator.insert(2);
    std::cout << iterator.get_value() << '\n';
    iterator.del();
    std::cout << iterator.get_value() << '\n';
    iterator.set_value(25);
    std::cout << iterator.get_value() << '\n';
    std::cout << " Finished " << std::endl;
}

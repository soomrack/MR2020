#include "List.h"

int main() {
    // заполнение списка
    List December_list;
    December_list.push_back(14);
    December_list.push_back(15);
    December_list.push_back(16);
    December_list.push_back(17);
    December_list.push_back(18);
    December_list.Print_list();
    printf("\n");
    
    // изменение содержимого списка с помощью итератора
    Iterator date = December_list.begin();
    date.del();
    date.next();
    date.next();
    date.next();
    date.insert(19);
    December_list.Print_list();
    date.next();
    printf("%d - the last element.\n", date.get_data());
    date.set_data(20);
    printf("%d - updated last element.\n", date.get_data());
    
    std::cout << "The end." << std::endl;
}

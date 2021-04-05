#include <iostream>
#include "B_tree.h"

int main() {
    B_Tree Marple_tree(3);
    Marple_tree.insert(1);
    Marple_tree.insert(3);
    Marple_tree.insert(7);
    Marple_tree.insert(10);
    Marple_tree.insert(11);
    Marple_tree.insert(13);
    Marple_tree.Print();
    std::cout << std::endl;
    Marple_tree.insert(14);
    Marple_tree.insert(15);
    Marple_tree.insert(18);
    Marple_tree.insert(16);
    Marple_tree.insert(19);
    Marple_tree.insert(24);
    Marple_tree.insert(25);
    Marple_tree.insert(26);
    Marple_tree.insert(21);
    Marple_tree.Print();
    std::cout << std::endl;
    Marple_tree.insert(4);
    Marple_tree.insert(5);
    Marple_tree.insert(20);
    Marple_tree.insert(22);
    Marple_tree.insert(2);
    Marple_tree.insert(17);
    Marple_tree.insert(12);
    Marple_tree.insert(6);
    Marple_tree.Print();
    std::cout << std::endl;
    
    return 0;
}

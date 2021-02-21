#include "My_header.h"

int main() {
    Tree maple_tree;
    maple_tree.add(6,"meow");
    maple_tree.add(8,"woof");
    maple_tree.add(9,"9");
    maple_tree.add(7,"7");
    maple_tree.add(4,"4");
    maple_tree.Print_tree(maple_tree.get_root());
    std::cout<<std::endl;
    
    maple_tree.add(5,"5");
    maple_tree.add(3,"3");
    maple_tree.add(2,"2");
    maple_tree.add(1,"1");
    maple_tree.add(10,"10");
    maple_tree.Print_tree(maple_tree.get_root());
    
    maple_tree.del(8);
    printf("\n\n");
    maple_tree.Print_tree(maple_tree.get_root(),0);
    printf("\n\n");
    maple_tree.del(4);
    maple_tree.Print_tree(maple_tree.get_root(),0);
    
    std::cout << termcolor::reset;
    printf("Minimum element in tree - %d\n",maple_tree.search_min(maple_tree.get_root())->key);
    printf("Element with key = 6 is '%s'. \n",maple_tree.find(6).c_str());
    std::cout << "Success." << std::endl;
    return 0;
}

#include <typeinfo>
#include <iostream>

void f(int (&x)[5]){

    int a = x[2];

}

int main(){

    int c[] = {1, 2, 3, 4, 5};
    f(c);
    
    return 0;
}
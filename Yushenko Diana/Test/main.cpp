#include <iostream>


int main() {
    int res;
    std::cout << "Hi there! It's time to know: What kind of pizza you are?\nLet's start!" << std::endl;
    std::cout <<"1.Do you like to dress up nicely?\n1)NO\n2)Clothes are the meaning of my life\n3)I only wear what I need\n";
    int a = 0;
    std::cin >> a;
    if (a == 1)
        res = 1;
    else if (a == 2)
        res = 2;
    else
        res = 3;

    std::cout <<"2.What kind of pizza do you like?\n1)Pepperoni\n2)Margarita\n3)4 cheese\n";
    int b = 0;
    std::cin >> b;
    if (b == 1)
        res += 1;
    else if (b == 2)
        res += 2;
    else
        res += 3;

    std::cout <<"3.How many languages do you know?\n1)Chto eto?\n2)1 and more\n3)How much do you need?\n";
    int c = 0;
    std::cin >> c;
    if (c == 1)
        res += 1;
    else if (c == 2)
        res += 2;
    else
        res += 3;

    std::cout << "4.Do you like to cook?\n1)Food delivery number: 880055...\n2)I'll cook an omelet for you\n3)I'm a restaurant chef\n";
    int d = 0;
    std::cin >> d;
    if (d == 1)
        res += 1;
    else if (d == 2)
        res += 2;
    else
        res += 3;

    std::cout <<"5.What is your favorite color?\n1)Black\n2)Green\n3)White\n";
    int e = 0;
    std::cin >> e;
    if (e == 1)
        res += 1;
    else if (e == 2)
        res += 2;
    else
        res += 3;

    std::cout <<"6.Do you like to ride a bike?\n1)Sport is life!!\n2)I broke my leg and therefore am afraid of bike\n3)I'll ride you on my bike\n";
    int f = 0;
    std::cin >> f;
    if (f == 1)
        res += 1;
    else if (f == 2)
        res += 2;
    else
        res += 3;

    if (res <= 6)
        std::cout <<"Wow!! You are a sicilian pizza";
    else if (6 <= res and res < 12)
        std::cout <<"Wow! You are a pizza calzone";
    else
    std::cout <<"Wow! You are a Neapolitan pizza";

    return 0;
}

#include <iostream>
#include <string>
using namespace std;

int Result = 0;

void showQuestion (string question){
    cout << question;
}

void check_if1 (){
    char answer;
      cin >> answer;
    while (answer != 'a' && answer != 'b' && answer != 'c' && answer != 'd') {
        cout << "Enter a, b, c or d.\n";
        cin >> answer;
    }
    if (answer == 'c') {
        cout << "Congratulations! You are right.\n\n\n";
        Result++;
    }
    else {
        cout << "You made a mistake.\n\n\n";
    }
}

void check_if2 (){
    char answer;
     cin >> answer;
    while (answer != 'a' && answer != 'b') {
        cout << "Enter a, or b.\n";
        cin >> answer;
    }
    if (answer == 'a') {
        cout << "Congratulations! You are right.\n\n\n";
        Result++;
    }
    else {
        cout << "You made a mistake.\n\n\n";
    }
}

int main()
{
    showQuestion("How many bones does a person have?\n\na.86\nb.314\nc.206\nd.106\n");
    check_if1 ();

    showQuestion("Is a killer whale a mammal?\n\na.Yes\nb.No\n");
    check_if2 (); 

    cout << "Your result: " << Result;

    return 0;
}

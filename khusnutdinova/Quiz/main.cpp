#include <iostream>
using namespace std;
int k=0;

int main () {
    string B="B";
    string A="A";
    string C="C";
   cout << "1. Calculate 45+187" << endl;
    cout << "A.230 B.232 C.227"<< endl;
    string answer1;
   cin>>answer1;
   if (answer1 == B)
   k++;

    cout << "2. What is the value of y if 3*y=45+6*y" << endl;
    cout << "A.5 B.7 C.9"<< endl;
    string answer2;
    cin>>answer2;
    if (answer2 == A)
        k++;

    cout << "3. Find 15% of 60" << endl;
    cout << "A.9 B.3 C.15"<< endl;
    string answer3;
    cin>>answer3;
    if (answer3 == A)
        k++;

    cout << "4. A cuboid measures 7 cm by 12 cm by 3 cm. What is the volume?" << endl;
    cout << "A.243 B.232 C.252"<< endl;
    string answer4;
    cin>>answer4;
    if (answer4 == C)
        k++;

    cout << "5. Calculate 3^5" << endl;
    cout << "A.249 B.243 C.247"<< endl;
    string answer5;
    cin>>answer5;
    if (answer5 == B)
        k++;

       cout << "Right:"<<k<<::endl;
    return 0;
}
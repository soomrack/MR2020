#include <iostream>
#include "Quiz.h"
//using namespace std;



/*
int Quiz(string Question, string A, string B, string C, string D, string Right){
    cout   << Question << "\n\n"
                << "A. " << A << "\n"
                << "B. " << B << "\n"
                << "C. " << C << "\n"
                << "D. " << D << "\n\n";
    string Answer;
    cin >> Answer;
//    cout << Answer;
    while (Answer != "A" && Answer != "B" && Answer != "C" && Answer != "D"){
        cout << "Use only \"A\", \"B\", \"C\", and \"D\" \n";
        cin >> Answer;
    }

    if (Answer == Right) {
        cout << "You`re Right!\n";
        return 1;
    }
        else {
        cout << "unfortunately, it`s wrong\n";
        return 0;
        }
}
*/

int main() {


    Quiz_Init();
//    extern Question Quiz[5];
//    struct Question *ptrQuiz = &Quiz[4];
//   Quiz_Struct(&Quiz[2]);
    while (1) {

        Start_Quiz();

        if (!One_More_Time()){
            return 0;
        }
    }
    return 0;
}

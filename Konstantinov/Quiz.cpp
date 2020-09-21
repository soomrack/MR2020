//
// Created by Alex on 19.09.2020.
//

#include "Quiz.h"
#define ARRAY_SIZE(array) (sizeof(array)/sizeof(array[0]))

using namespace std;
Question Again;
Question Quiz[5];

uint8_t Quiz_Struct(struct Question *Quest){
    cout   << Quest->Text << "\n\n"
           << "A. " << Quest->Answer_A << "\n"
           << "B. " << Quest->Answer_B << "\n";
    if (Quest->Answer_C != "None"){
        cout   << "C. " << Quest->Answer_C << "\n";
        if (Quest->Answer_D != "None")
            cout   << "D. " << Quest->Answer_D << "\n";
    }
    cout << endl;

    string Answer;
    cin >> Answer;

    while(Quest->Answer_D == "None" && Answer != "A" && Answer != "B" && Answer != "C"){
        cout << R"(Use only "A", "B", and "C")" << "\n\n";
        cin >> Answer;
    }
    while (Quest->Answer_C == "None" && Answer != "A" && Answer != "B"){
        cout << R"(Use only "A" or "B")" << "\n\n";
        cin >> Answer;
    }
    while (Answer != "A" && Answer != "B" && Answer != "C" && Answer != "D"){
        cout << R"(Use only "A", "B", "C", and "D")" << "\n\n";
        cin >> Answer;
    }



    if (Answer == Quest->Right_Letter) {
        cout << "You`re Right!\n\n";
        return 1;
    }
    else {
        cout << "Unfortunately, it`s wrong\n\n";
        return 0;
    }
}
bool One_More_Time(){

    cout   << Again.Text << "\n\n"
           << "A. " << Again.Answer_A << "\n"
           << "B. " << Again.Answer_B << "\n\n";

    string Answer;
    cin >> Answer;
    while (Answer != "A" && Answer != "B" && Answer != "C" && Answer != "D"){
        cout << R"(Use only "A" or "B")" << "\n\n";
        cin >> Answer;
    }

    if (Answer == Again.Right_Letter) {
        cout << "It`s absolutely the right decision!\n\n";
        return true;
    }
    else {
        cout << "Well, see you next time. Good luck!\n\n";
        return false;
    }
}

void Start_Quiz(){
    uint8_t Score = 0;
    for (uint8_t i = 0; i < ARRAY_SIZE(Quiz); i++) {
        if (i == 0)
            cout << "First question:\n";
        else
            cout << "Next question:\n";
        Score += Quiz_Struct(&Quiz[i]);
    }
    cout << "\n" << "Your score: " << to_string(Score) << " point(s). Thank you for a good game!\n";

}

void Quiz_Init(){
    cout << "Hello, World! Thanks for the joining our game. Hope, you`ll have a good time. Good luck!\n";


    Quiz[0] = Set_Question("1. How many planets in the Solar System?", "5", "12", "9", "8", "D");

    Quiz[1] = Set_Question("2. sizeof(uint64_t variable) = ...", "64", "12", "8", "4", "C");

    Quiz[2] = Set_Question(R"(3. Is "array_Name[2]" equal to "2[array_Name]"?)", "Yes", "No", "A");

    Quiz[3] = Set_Question(R"(4. Should you used "std::" before "cin" or "cout"?)", "Yes, I should", "No,  that's not necessary.", "Not always", "C");


    Quiz[4] = Set_Question(R"(5. What you`ll see in the console after command "std::cout << "Hello, World!\\nHello, World!""?)",
                           "Hello, World!\nHello, World!",
                           "Hello, World!\\\nHello, World!",
                           R"(Hello, World!\\nHello, World!)",
                           "Something different", "C");

    Again = Set_Question("Would you like to play again?", "Yeah, sure!", "Thanks, not now.", "A");

}

Question Set_Question(string Text, string A, string B, string C, string D, string Right_Letter){
    Question Temp;
    Temp.Text = move(Text);  //std::move(...);
    Temp.Answer_A = move(A);
    Temp.Answer_B = move(B);
    Temp.Answer_C = move(C);
    Temp.Answer_D = move(D);
    Temp.Right_Letter = move(Right_Letter);

    return Temp;

}

Question Set_Question(string Text, string A, string B, string C, string Right_Letter){
    Question Temp;
    Temp.Text = move(Text);  //std::move(...);
    Temp.Answer_A = move(A);
    Temp.Answer_B = move(B);
    Temp.Answer_C = move(C);
    Temp.Answer_D = "None";
    Temp.Right_Letter = move(Right_Letter);

    return Temp;

}

Question Set_Question(string Text, string A, string B, string Right_Letter){
    Question Temp;
    Temp.Text = move(Text);
    Temp.Answer_A = move(A);
    Temp.Answer_B = move(B);
    Temp.Answer_C = "None";
    Temp.Answer_D = "None";
    Temp.Right_Letter = move(Right_Letter);

    return Temp;

}

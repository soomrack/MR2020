//
// Created by Alex on 19.09.2020.
//


#ifndef FIRST_PROJECT_QUIZ_H
#define FIRST_PROJECT_QUIZ_H
#include <iostream>
struct Question{
    std::string Text;
    std::string Answer_A;
    std::string Answer_B;
    std::string Answer_C;
    std::string Answer_D;
    std::string Right_Letter;
};


uint8_t Quiz_Struct(struct Question *Quest);
bool One_More_Time();
void Start_Quiz();
void Quiz_Init();
Question Set_Question(std::string Text, std::string A, std::string B, std::string C, std::string D, std::string Right_Letter);
Question Set_Question(std::string Text, std::string A, std::string B, std::string C, std::string Right_Letter);
Question Set_Question(std::string Text, std::string A, std::string B, std::string Right_Letter);


#endif //FIRST_PROJECT_QUIZ_H

#include <iostream>
#include <bits/stdc++.h> 
using namespace std; 

char *questionBase[2][4] = {"What year is it now?", "1) 2020", "2) 2002", "1", "What is the closest star to Earth?", "1) Moon", "2) Sun", "2"};
int rightAnswers = 0;

int askingQuestion(int questionNumber) {
    int answer;

    cout << questionBase[questionNumber][0] << '\n' << questionBase[questionNumber][1] << '\t' << '\t' << questionBase[questionNumber][2] << '\n';
    cout << "Your answer is ";
    cin >> answer;
    if (stoi(questionBase[questionNumber][3]) == answer) {
        cout << "Congratulations! You are right." << '\n';
        rightAnswers++;
    }
    return 0;
}

int main() {
    for (int i = 0; i < sizeof(questionBase) / sizeof(questionBase[0]); i++) {
        askingQuestion(i);
    }
    cout << "You gave " << rightAnswers << " right answers.";
    return 0;
}

#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>
#include <cstdlib>

using namespace std;

int main(int argc, char const *argv[])
{

    // create Q&A and local veriables

    vector<string> questions = {
        "Linux vs Win?",
        "How many planets are there in the solar system?v",
        "Root of 144:",
        "ROS?",
        "What's the best editor?",
        "Who Poisoned Navalny?",
        "What is pi? (3 significant digits)",
    };
    vector<string> answer = {
        "linux",
        "8",
        "12",
        "yes",
        "vscode",
        "putin (my friend sasha putin)",
        "3.14",
    };
    string fname;
    string sname;
    int score = 0;

    // input player's data

    cout << "Enter your first name: " << endl;
    cin >> fname;
    cout << "\nEnter your second name: " << endl;
    cin >> sname;
    


    // Start game
    
    cout << "Answer few questions (all answer is lowercase and safe in russia):" << endl;
    for (int i = 0; i < 7; i++){
        string ans;
        cout << questions[i] << endl;
        getline(cin, ans);
        if (ans == answer[i]){
            score++;
            cout << "Ok" << endl;
        }
        else {
            cout << "No" << endl;
        }

    }

    // Score

    cout << "You gave " << score << " correct answers" << endl;




    return 0;
}


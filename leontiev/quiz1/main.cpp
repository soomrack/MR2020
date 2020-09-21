#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>
#include <cstdlib>

using namespace std;

int main(int argc, char const *argv[])
{
    vector<string> questions = {
            "What is the best processor on the market now?",
            "What is the most modern type of DRAM?",
            "What is faster: HDD or SSD",
            "Hotel?",
            "Anime?",
    };
    vector<string> answer = {
            "Ryzen 5 3600",
            "DDR4",
            "SSD",
            "Trivago",
            "Yes",
    };
    string fname;
    string sname;
    int score = 0;

    cout << "Enter your first name: " << endl;
    getline(cin, fname);
    cout << "Enter your second name: " << endl;
    getline(cin, sname);

    cout << "Answer few questions:" << endl;
    for (int i = 0; i < 5; i++){
        string ans;
        cout << questions[i] << endl;
        getline(cin, ans);
        if (ans == answer[i]){
            score++;
            cout << "Yes" << endl;
        }
        else {
            cout << "No" << endl;
        }

    }

    cout << "You gave " << score << " correct answers" << endl;

    return 0;
}
#include <iostream>
using namespace std;

int main() {
    int answer = 0;
    int result = 0;

    cout << "You have to answer 7 question. Use numbers to answer.\n\n";

    cout << "Question 1: (2+2):2+2 = ?\n" << "Your answer:";
    cin >> answer;
    if (answer == 4){
        result++;
    }

    cout << "\nQuestion 2: (81)^(1/4) > 3 ?\n" << "If your answer is 'yes', write 1, else write 0.\n" <<"Your answer:";
    cin >> answer;
    if (answer == 0){
        result++;
    }

    cout << "\nQuestion 3: (64)^(1/3) = ?\n" <<"Your answer:";
    cin >> answer;
    if (answer == 4){
        result++;
    }

    cout << "\nQuestion 4: What is x in an equation 12 = x + 16?\n" <<"Your answer:";
    cin >> answer;
    if (answer == -4){
        result++;
    }

    cout << "\nQuestion 5: Remainder of the division 24/13?\n" <<"Your answer:";
    cin >> answer;
    if (answer == 11){
        result++;
    }

    cout << "\nQuestion 6: Find the smaller of the roots of the equation x^2-4x-5.\n" <<"Your answer:";
    cin >> answer;
    if (answer == -1){
        result++;
    }

    cout << "\nQuestion 7: How many mistakes do you think you've made?\n" <<"Your answer:";
    cin >> answer;
    if (answer == 6-result){
        result++;
    }

    cout << "\nYour result: " << result << "/7";
    return 0;
}

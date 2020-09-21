#include <iostream>

using namespace std;

int main() {
	//вектор ответов
	int otvet[7];
	for (int i = 0; i < 7; i++) {
		if (i % 2 == 0) {
			otvet[i] = 1;
		}
		else {
			otvet[i] = 2;
		}
	}

	int j = 0, ans[7];
	//тест
	cout << "Hello World!"<<endl;
	cout << "This test created to exemine your knowlege about safety" << endl;
	cout << " and safety measures of performing operations with bank card." << endl;
	cout << "Please, answer the following questions by choosing the right answer." << endl;

	//1
	cout << endl << "Number one." << endl << "Your are in the store and operation with your card has failed. The cashier" << endl;
	cout << " told you, that he knows how to solve this problem, he did it many times before." << endl;
	cout << "You should just tell him your pin-code. Will you do it?" << endl;
	cout << "1. No" << endl << "2. Yes" << endl;
	cin >> ans[0];
	//2
	cout << "Number two." << endl << "Could your mother use your card to buy products in the store, " << endl;
	cout << "if you have the same surnames?" << endl;
	cout << "1. Yes" << endl << "2. No" << endl;
	cin >> ans[1];
	//3
	cout << "Number tree." << endl << "Do you have to sign on the back of the card?" << endl;
	cout << "1. No" << endl << "2. Yes" << endl;
	cin >> ans[2];
	//4
	cout << "Number four." << endl << "Is it possible to set a weekly limit on the amount of " << endl;
	cout << "transactions on credit card?" << endl;
	cout << "1. Yes" << endl << "2. No" << endl;
	cin >> ans[3];
	//5
	cout << "Number five." << endl << "Is it polite to ask strangers to move away until you have finished " << endl;
	cout << "performing operations with your Bank card and ATM?" << endl;
	cout << "1. Yes" << endl << "2. No" << endl;
	cin >> ans[4];
	//6
	cout << "Number six." << endl << "Can you provide your passport or sign on the checks at the cashier's request?" << endl;
	cout << "1. No" << endl << "2. Yes" << endl;
	cin >> ans[5];
	//7
	cout << "Number seven." << endl << "You received a call from a Bank employee who asks you to " << endl;
	cout << "tell them your entire card number and expiration date for " << endl;
	cout << "confirmation operations (safety measures)." << endl;
	cout << "Will you do it?" << endl;
	cout << "1. No" << endl << "2. Yes" << endl;
	cin >> ans[6];

	//проверка
	for (int i = 0; i < 7; i++) {
		if (otvet[i] == ans[i]) {
			j++;
		}
	}

	//ответ
	cout << "Your score is " << j << "/7.";
	return 0;
}
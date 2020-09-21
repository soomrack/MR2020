#include <iostream>
using namespace std;
char otv;
int n;
int main() {
	cout << "Quiz Adjectives\n";
	cout << "1) Oval\n";
	cout << "A)Kruglyi  B)Ostorozhnyi  C)Pryamoy D)Ovalnyi\n";
	cout << "Vvedite svoy otvet\n";
	cin  >> otv;
	if (otv == 'D') {
		cout << "Verno\n";
		n++;
	}
	else {
		cout << "Oshibka\n";

	}
	cout << "2) Fast\n";
	cout << "A)Slozhnyi  B)Medlennyi  C)Bistryi D)Lyogkyi\n";
	cout << "Vvedite svoy otvet\n";
	cin >> otv;
	if (otv == 'C') {
		cout << "Verno\n";
		n++;
	}
	else {
		cout << "Oshibka\n";
	}
	cout << "3) Difficult\n";
	cout << "A)Myagkyi  B)Slozhnyi  C)Lyogkyi D)Skuchnyi\n";
	cout << "Vvedite svoy otvet\n";
	cin >> otv;
	if (otv == 'B') {
		cout << "Verno\n";
		n++;
	}
	else {
		cout << "Oshibka\n";
	}
	cout << "4) Soft\n";
	cout << "A)Skuchnyi  B)Medlennyi  C)Bistryi D)Myagkyi\n";
	cout << "Vvedite svoy otvet\n";
	cin >> otv;
	if (otv == 'D') {
		cout << "Verno\n";
		n++;
	}
	else {
		cout << "Oshibka\n";
	}
	cout << "5) Unique\n";
	cout << "A)Udivitelnyi  B)Skuchnyi  C)Bistryi D)Unikalnyi\n";
	cout << "Vvedite svoy otvet\n";
	cin >> otv;
	if (otv == 'D') {
		cout << "Verno\n";
		n++;
	}
	else {
		cout << "Oshibka\n";
	}
	cout << "6) Slow\n";
	cout << "A)Vyagkyi  B)Medlennyi  C)Bistryi D)Nezhnyi\n";
	cout << "Vvedite svoy otvet\n";
	cin >> otv;
	if (otv == 'B') {
		cout << "Verno\n";
		n++;
	}
	else {
		cout << "Oshibka\n";
	}
	cout << "Kolichestvo vernyh otvetov ";
	cout <<  n;
}
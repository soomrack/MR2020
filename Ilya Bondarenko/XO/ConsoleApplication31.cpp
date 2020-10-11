#include <iostream>
using namespace std;
char table[3][3], table1[3][3];
int i = 0;
int j = 0;
int l = 0;
int a, b, v, c, d, e, q, z;
char X;

int p1()
{
	if ((table[2][0] == 'O' && table[1][1] == 'O' && table[0][2] == 'O')

		|| (table[0][0] == 'O' && table[1][1] == 'O' && table[2][2] == 'O')
		|| (table[0][0] == 'O' && table[0][1] == 'O' && table[0][2] == 'O')
		|| (table[0][2] == 'O' && table[1][2] == 'O' && table[2][2] == 'O')
		|| (table[2][0] == 'O' && table[2][1] == 'O' && table[2][2] == 'O')
		|| (table[0][0] == 'O' && table[1][0] == 'O' && table[2][0] == 'O'))
	{

		cout << " Вы проиграли! "; exit(1);
	}

	else if ((table[2][0] == 'X' && table[1][1] == 'X' && table[0][2] == 'X')

		|| (table[0][0] == 'X' && table[1][1] == 'X' && table[2][2] == 'X')
		|| (table[0][0] == 'X' && table[0][1] == 'X' && table[0][2] == 'X')
		|| (table[0][2] == 'X' && table[1][2] == 'X' && table[2][2] == 'X')
		|| (table[2][0] == 'X' && table[2][1] == 'X' && table[2][2] == 'X')
		|| (table[0][0] == 'X' && table[1][0] == 'X' && table[2][0] == 'X'))
	{

		cout << " Вы выиграли! "; exit(1);


	}
}
int at() {
	if (table[0][0] == '1') { table[0][0] = 'O'; }
	else if (table[0][1] == '2') { table[0][1] = 'O'; }
	else if (table[0][2] == '3') { table[0][2] = 'O'; }
	else if (table[1][0] == '4') { table[1][0] = 'O'; }
	else if (table[1][1] == '5') { table[1][1] = 'O'; }
	else if (table[1][2] == '6') { table[1][2] = 'O'; }
	else if (table[2][0] == '7') { table[2][0] = 'O'; }
	else if (table[2][1] == '8') { table[2][1] = 'O'; }
	else if (table[2][2] == '9') { table[2][2] = 'O'; }
	z = 1;
	return 0;
}
int vivod() {

	i = 0; j = 0; while (i < 3) {
		j = 0; while (j < 3) { cout << "|" << table[i][j]; j = j + 1; }
		cout << "|" << endl; i = i + 1; ;
	}
	return 0;
}
void instruction() {
	cout << "Крестики нолики" << endl;
	cout << "Побеждает тот, кто составит выйграшную комбинацию" << endl;
	cout << "Вид поля:\n\n";
	int i = 0; int j = 0;
	while (i < 3) {
		j = 0;
		while (j < 3) { cout << "|" << table[i][j]; j = j + 1; }
		cout << "|" << endl; i = i + 1;
	}cout << "Конец";
}
int proverka()
{
	if (table[0][0] == 'X' && table[0][2] == 'X' && table[0][1] != 'O' && table[0][1] != 'X') { table[0][1] = 'O'; q = 1; }
	else if (table[2][0] == 'X' && table[2][2] == 'X' && table[2][1] != 'O' && table[2][1] != 'X') { table[2][1] = 'O'; q = 1; }
	else if (table[0][2] == 'X' && table[2][2] == 'X' && table[1][2] != 'O' && table[1][2] != 'X') { table[1][2] = 'O'; q = 1; }

	else if (table[0][0] == 'X' && table[2][0] == 'X' && table[1][0] != 'O' && table[1][0] != 'X') { table[1][0] = 'O'; q = 1; }
	else if (table[0][1] == 'X' && table[0][2] == 'X' && table[0][0] != 'O' && table[0][0] != 'X') { table[0][0] = 'O'; q = 1; }
	else if (table[0][0] == 'X' && table[0][1] == 'X' && table[0][2] != 'O' && table[0][2] != 'X') { table[0][2] = 'O'; q = 1; }

	else if (table[0][2] == 'X' && table[1][2] == 'X' && table[2][2] != 'O' && table[2][2] != 'X') { table[2][2] = 'O'; q = 1; }
	else if (table[2][2] == 'X' && table[1][2] == 'X' && table[0][2] != 'O' && table[0][2] != 'X') { table[0][2] = 'O'; q = 1; }
	else if (table[0][0] == 'X' && table[1][0] == 'X' && table[2][0] != 'O' && table[2][0] != 'X') { table[2][0] = 'O'; q = 1; }

	else if (table[2][0] == 'X' && table[1][0] == 'X' && table[0][0] != 'O' && table[0][0] != 'X') { table[0][0] = 'O'; q = 1; }
	else if (table[2][0] == 'X' && table[2][1] == 'X' && table[2][2] != 'O' && table[2][2] != 'X') { table[2][2] = 'O'; q = 1; }
	else if (table[2][2] == 'X' && table[2][1] == 'X' && table[2][0] != 'O' && table[2][0] != 'X') { table[2][0] = 'O'; q = 1; }



	else if (table[0][0] == 'X' && table[1][1] == 'X' && table[2][2] != 'O' && table[2][2] != 'X') { table[2][2] = 'O'; q = 1; }
	else if (table[2][0] == 'X' && table[1][1] == 'X' && table[0][2] != 'O' && table[0][2] != 'X') { table[0][2] = 'O'; q = 1; }
	else if (table[0][2] == 'X' && table[1][1] == 'X' && table[2][0] != 'O' && table[2][0] != 'X') { table[2][0] = 'O'; q = 1; }
	else if (table[2][2] == 'X' && table[1][1] == 'X' && table[0][0] != 'O' && table[0][0] != 'X') { table[0][0] = 'O'; q = 1; }

	else if (table[2][1] == 'X' && table[1][1] == 'X' && table[0][1] != 'O' && table[0][1] != 'X') { table[0][1] = 'O'; q = 1; }
	else if (table[1][2] == 'X' && table[1][1] == 'X' && table[1][0] != 'O' && table[1][0] != 'X') { table[1][0] = 'O'; q = 1; }

	else if (table[1][0] == 'X' && table[1][1] == 'X' && table[1][2] != 'O' && table[1][2] != 'X') { table[1][2] = 'O'; q = 1; }
	else if (table[0][1] == 'X' && table[1][1] == 'X' && table[2][1] != 'O' && table[2][1] != 'X') { table[2][1] = 'O'; q = 1; }
	

	return 0;
}
int ugol() {

	if (table[0][0] == '1') { table[0][0] = 'O'; }
	else if (table[0][2] == '3') { table[0][2] = 'O'; }
	else if (table[2][0] == '7') { table[2][0] = 'O'; }
	else if (table[2][2] == '9') { table[2][2] = 'O'; }
	else at();
	return 0;
}
int kuda(int a1) {
	q = 0;
	z = 0;

	proverka();
	if (q == 0)
	{
		if ((a1 == 1) && (table[0][0] == table[2][2]) || (a1 == 1) && (table[0][0] == table[2][1])) {
			ugol(); q = 1;
		}
		else if ((a1 == 1) && (table[0][0] == table[1][2]) || (a1 == 3) && (table[0][2] == table[2][0])) {
			ugol(); q = 1;
		}
		else if ((a1 == 3) && (table[0][2] == table[1][0]) || (a1 == 3) && (table[0][2] == table[2][1])) {
			ugol(); q = 1;
		}
		else if ((a1 == 7) && (table[2][0] == table[0][2]) || (a1 == 7) && (table[2][0] == table[0][1])) {
			ugol(); q = 1;
		}

		else if ((a1 == 7) && (table[2][0] == table[1][2]) || (a1 == 9) && (table[2][2] == table[1][0])) {
			ugol(); q = 1;
		}

		else if ((a1 == 9) && (table[2][2] == table[0][1]) || (a1 == 9) && (table[2][2] == table[0][0])) {
			ugol(); q = 1;
		}



		return q;
	}
}
int zapolnenie() {
	vivod();
	cout << "Введите номер 2-й ячейки: "; cin >> b;

	if ((b == a)||(a < 1) || (a > 9)) {
		cout << "Ошибка, вводите значения, отличные от предыдущих в интервале 1-9: ";
		cin >> b;
		if ((b == a) || (a < 1) || (a > 9)) {
			cout << "Ошибка, До свидания:"; exit(1);
		}
	}

	if (b == 1) { table[0][0] = 'X'; } if (b == 2) { table[0][1] = 'X'; } if (b == 3) { table[0][2] = 'X'; }
	if (b == 4) { table[1][0] = 'X'; } if (b == 5) { table[1][1] = 'X'; } if (b == 6) { table[1][2] = 'X'; }
	if (b == 7) { table[2][0] = 'X'; } if (b == 8) { table[2][1] = 'X'; } if (b == 9) { table[2][2] = 'X'; }
	kuda(a);
	if (q == 0) { at(); }
	vivod();
	cout << "Введите номер 3-й ячейки: "; cin >> c;

	if ((b == c) || (c == a) || (a < 1) || (a > 9)) {
		cout << "Ошибка, вводите значения, отличные от предыдущих в интервале 1-9: ";
		cin >> b;
		if ((b == c) || (c == a) || (a < 1) || (a > 9)) {
			cout << "Ошибка, До свидания:"; exit(1);
		}
	}

	if (c == 1) { table[0][0] = 'X'; } if (c == 2) { table[0][1] = 'X'; } if (c == 3) { table[0][2] = 'X'; }
	if (c == 4) { table[1][0] = 'X'; } if (c == 5) { table[1][1] = 'X'; } if (c == 6) { table[1][2] = 'X'; }
	if (c == 7) { table[2][0] = 'X'; } if (c == 8) { table[2][1] = 'X'; } if (c == 9) { table[2][2] = 'X'; }

	kuda(a);
	if (q == 0) { at(); }
	vivod();
	p1();

	cout << "Введите номер 4-й ячейки: ";
	cin >> d;

	if ((b == d) || (d == c) || (d == a) || (a < 1) || (a > 9)) {
		cout << "Ошибка, вводите значения, отличные от предыдущих в интервале 1-9: ";
		cin >> b;
		if ((b == d) || (d == c) || (d == a) || (a < 1) || (a > 9)) {
			cout << "Ошибка, До свидания:"; exit(1);
		}
	}

	if (d == 1) { table[0][0] = 'X'; } if (d == 2) { table[0][1] = 'X'; } if (d == 3) { table[0][2] = 'X'; }
	if (d == 4) { table[1][0] = 'X'; } if (d == 5) { table[1][1] = 'X'; } if (d == 6) { table[1][2] = 'X'; }
	if (d == 7) { table[2][0] = 'X'; } if (d == 8) { table[2][1] = 'X'; } if (d == 9) { table[2][2] = 'X'; }

	kuda(a);

	if (q == 0) { at(); }
	vivod();
	p1();



	cout << "Введите номер 5-й ячейки: ";
	cin >> e;

	if ((b == e) || (d == e) || (e == c) || (e == a) || (a < 1) || (a > 9)) {
		cout << "Ошибка, вводите значения, отличные от предыдущих в интервале 1-9: ";
		cin >> b;
		if ((b == e) || (d == e) || (e == c) || (e == a) || (a < 1) || (a > 9)) {
			cout << "Ошибка, До свидания:"; exit(1);
		}
	}

	if (e == 1) { table[0][0] = 'X'; } if (e == 2) { table[0][1] = 'X'; } if (e == 3) { table[0][2] = 'X'; }
	if (e == 4) { table[1][0] = 'X'; } if (e == 5) { table[1][1] = 'X'; } if (e == 6) { table[1][2] = 'X'; }
	if (e == 7) { table[2][0] = 'X'; } if (e == 8) { table[2][1] = 'X'; } if (e == 9) { table[2][2] = 'X'; }

	kuda(a);
	if (q == 0) { at(); }
	vivod();
	p1();

	cout << "Повезет в другой раз!"; exit(1);
	return 0;

}
void vvod(int a1) {
	q = 0;
	if (a1 == 1) { table[0][0] = 'X'; } if (a1 == 2) { table[0][1] = 'X'; } if (a1 == 3) { table[0][2] = 'X'; }
	if (a1 == 4) { table[1][0] = 'X'; } if (a1 == 5) { table[1][1] = 'X'; } if (a1 == 6) { table[1][2] = 'X'; }
	if (a1 == 7) { table[2][0] = 'X'; } if (a1 == 8) { table[2][1] = 'X'; } if (a1 == 9) { table[2][2] = 'X'; }

	if (a1 == 1 || a1 == 3 || a1 == 7 || a1 == 9)//угловый положения
	{
		table[1][1] = 'O';
		zapolnenie();
	}
	else if (a1 == 2 || a1 == 4 || a1 == 6 || a1 == 8) {

		table[1][1] = 'O';

		zapolnenie();

		/*cout << "Введите номер 2-й ячейки: ";
		cin >> b;
		if (b == a1) {
			cout << "Ошибка, вводите значения, отличные от предыдущих"; _Exit;
		}

		if (b == 1) { table[0][0] = 'X'; } if (b == 2) { table[0][1] = 'X'; } if (b == 3) { table[0][2] = 'X'; }
		if (b == 4) { table[1][0] = 'X'; } if (b == 5) { table[1][1] = 'X'; } if (b == 6) { table[1][2] = 'X'; }
		if (b == 7) { table[2][0] = 'X'; } if (b == 8) { table[2][1] = 'X'; } if (b == 9) { table[2][2] = 'X'; }
		vivod();
		*/

	}
	else { table[0][0] = 'O'; zapolnenie(); }
}
int main() {

	setlocale(LC_ALL, "Russian");
	table[0][0] = 49; table[0][1] = 50; table[0][2] = 51; table[1][0] = 52;
	table[1][1] = 53; table[1][2] = 54; table[2][0] = 55; table[2][1] = 56; table[2][2] = 57;
	instruction();
	cout << "Введите номер ячейки: ";
	cin >> a;
	if ((a<0)||(a>9)){
		cout << "Ошибка, вводите значение, в интервале 1-9: ";
		cin >> a;
		if ((a < 1) || (a > 9)) {
			cout << "Ошибка, До свидания:"; exit(1);
		}
	}
	vvod(a);




}
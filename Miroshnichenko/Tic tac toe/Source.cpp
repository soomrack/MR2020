#include<iostream>
using namespace std;
int cell;
char ar[9] = {'-','-','-','-','-','-','-','-','-'};
void cross() {
	cout << "Enter number of the cell if numbers of cells is\n";
	cout << "1	2	3\n";
	cout << "4	5	6\n";
	cout << "7	8	9\n\n";
	cin >> cell;
	ar[cell-1] = 'x';
	if ((ar[0] == 'x' && ar[1] == 'x' && ar[2] == 'x')
		|| (ar[3] == 'x' && ar[4] == 'x' && ar[5] == 'x')
		|| (ar[6] == 'x' && ar[7] == 'x' && ar[8] == 'x')
		|| (ar[0] == 'x' && ar[3] == 'x' && ar[6] == 'x')
		|| (ar[1] == 'x' && ar[4] == 'x' && ar[7] == 'x')
		|| (ar[2] == 'x' && ar[5] == 'x' && ar[8] == 'x')
		|| (ar[0] == 'x' && ar[4] == 'x' && ar[8] == 'x')
		|| (ar[2] == 'x' && ar[4] == 'x' && ar[6] == 'x'))
	{
		cout << "Congratulations! You won this game!\n";
		cout << ar[0] << "	" << ar[1] << "	" << ar[2] << "\n";
		cout << ar[3] << "	" << ar[4] << "	" << ar[5] << "\n";
		cout << ar[6] << "	" << ar[7] << "	" << ar[8] << "\n\n";
		exit(0);
	}
}
void field() {
	cout << "Wow! You are so close. I believe you win my program\n";
	cout << ar[0] << "	" << ar[1] << "	" << ar[2] << "\n";
	cout << ar[3] << "	" << ar[4] << "	" << ar[5] << "\n";
	cout << ar[6] << "	" << ar[7] << "	" << ar[8] << "\n\n";
}
void firststep() {
	switch(cell){
	case 5: ar[2] = '0'; break;
	default: ar[4] = '0';
	}
}
void secondstep() {
	bool enough = 0;
	if (enough == 0) {
		for (int i = 0; i < 9; i += 3) {
			if ((ar[i] == '0') && (ar[i + 1] == '0') && (ar[i + 2] != 'x')) { ar[i + 2] = '0'; enough = 1; break; }
			if ((ar[i] != 'x') && (ar[i + 1] == '0') && (ar[i + 2] == '0')) { ar[i] = '0'; enough = 1; break; }
			if ((ar[i] == '0') && (ar[i + 1] != 'x') && (ar[i + 2] == '0')) { ar[i + 1] = '0'; enough = 1; break; }
		}
	}
	if (enough == 0) {
		for (int i = 0; i < 3; i++) {
			if ((ar[i] == '0') && (ar[i + 3] == '0') && (ar[i + 6] != 'x')) { ar[i + 6] = '0'; enough = 1; break; }
			if ((ar[i] != 'x') && (ar[i + 3] == '0') && (ar[i + 6] == '0')) { ar[i] = '0'; enough = 1; break; }
			if ((ar[i] == '0') && (ar[i + 3] != 'x') && (ar[i + 6] == '0')) { ar[i + 3] = '0'; enough = 1; break; }
		}
	}
	if ((ar[0] == '0') && (ar[4] == '0') && (ar[8] != 'x') && (enough == 0)) { ar[8] = '0'; enough = 1; }
	if ((ar[0] != 'x') && (ar[4] == '0') && (ar[8] == '0') && (enough == 0)) { ar[0] = '0'; enough = 1; }
	if ((ar[0] == '0') && (ar[4] != 'x') && (ar[8] == '0') && (enough == 0)) { ar[4] = '0'; enough = 1; }
	if ((ar[2] == '0') && (ar[4] == '0') && (ar[6] != 'x') && (enough == 0)) { ar[6] = '0'; enough = 1; }
	if ((ar[2] != 'x') && (ar[4] == '0') && (ar[6] == '0') && (enough == 0)) { ar[2] = '0'; enough = 1; }
	if ((ar[2] == '0') && (ar[4] != 'x') && (ar[6] == '0') && (enough == 0)) { ar[4] = '0'; enough = 1; }
	if (enough == 0) {
		for (int i = 0; i < 9; i += 3) {
			if ((ar[i] == 'x') && (ar[i + 1] == 'x') && (ar[i + 2] != '0')) { ar[i + 2] = '0'; enough = 1; break; }
			if ((ar[i] != '0') && (ar[i + 1] == 'x') && (ar[i + 2] == 'x')) { ar[i] = '0'; enough = 1; break; }
			if ((ar[i] == 'x') && (ar[i + 1] != '0') && (ar[i + 2] == 'x')) { ar[i + 1] = '0'; enough = 1; break; }
		}
	}
	if (enough == 0) {
		for (int i = 0; i < 3; i++) {
			if ((ar[i] == 'x') && (ar[i + 3] == 'x') && (ar[i + 6] != '0')) { ar[i + 6] = '0'; enough = 1; break; }
			if ((ar[i] != '0') && (ar[i + 3] == 'x') && (ar[i + 6] == 'x')) { ar[i] = '0'; enough = 1; break; }
			if ((ar[i] == 'x') && (ar[i + 3] != '0') && (ar[i + 6] == 'x')) { ar[i + 3] = '0'; enough = 1; break; }
		}
	}
	if ((ar[0] == 'x') && (ar[4] == 'x') && (ar[8] != '0') && (enough == 0)) { ar[8] = '0'; enough = 1; }
	if ((ar[0] != '0') && (ar[4] == 'x') && (ar[8] == 'x') && (enough == 0)) { ar[0] = '0'; enough = 1; }
	if ((ar[0] == 'x') && (ar[4] != '0') && (ar[8] == 'x') && (enough == 0)) { ar[4] = '0'; enough = 1; }
	if ((ar[2] == 'x') && (ar[4] == 'x') && (ar[6] != '0') && (enough == 0)) { ar[6] = '0'; enough = 1; }
	if ((ar[2] != '0') && (ar[4] == 'x') && (ar[6] == 'x') && (enough == 0)) { ar[2] = '0'; enough = 1; }
	if ((ar[2] == 'x') && (ar[4] != '0') && (ar[6] == 'x') && (enough == 0)) { ar[4] = '0'; enough = 1; }
	if ((ar[0] == '-') && (ar[1] == '-') && (ar[2] == '-') && (ar[3] == '-') && (ar[4] == '0') && (ar[5] == 'x')
		&& (ar[6] == '-') && (ar[7] == 'x') && (ar[8] == '-')) {
		ar[8] = '0'; enough = 1;
	}
		for (int j = 0; j < 9; j++) {
			if ((enough == 0) && (ar[j] != 'x') && (ar[j] != '0')) {ar[j]='0';break;}
		}
		if ((ar[0] == '0' && ar[1] == '0' && ar[2] == '0')
			|| (ar[3] == '0' && ar[4] == '0' && ar[5] == '0')
			|| (ar[6] == '0' && ar[7] == '0' && ar[8] == '0')
			|| (ar[0] == '0' && ar[3] == '0' && ar[6] == '0')
			|| (ar[1] == '0' && ar[4] == '0' && ar[7] == '0')
			|| (ar[2] == '0' && ar[5] == '0' && ar[8] == '0')
			|| (ar[0] == '0' && ar[4] == '0' && ar[8] == '0')
			|| (ar[2] == '0' && ar[4] == '0' && ar[6] == '0'))
		{
			cout << "Oops, You have just lost!\n";
			cout << ar[0] << "	" << ar[1] << "	" << ar[2] << "\n";
			cout << ar[3] << "	" << ar[4] << "	" << ar[5] << "\n";
			cout << ar[6] << "	" << ar[7] << "	" << ar[8] << "\n\n";
			exit(0);
		}
}
int main() {
	cross();
	firststep();
	field();
	for (int i = 0; i < 3; i++) {
		cross();
		secondstep();
		field();
	}
	cross();
	field();
	cout << "There is no winner! Try again\n";
	return 0;
}
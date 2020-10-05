#include <iostream>
#include <string>



char board[9] = { '-','-', '-','-','-','-','-','-','-' };
char var[9];

void robot() {
	int ii = 0;
		for (int i = 0; i < 9; i++) {
			if (board[i] == '-') {
				var[ii] = i;
				ii++;
			}
		}
		int variant = rand() % ii;
	int robo = var[variant]; 
	board[robo] = 'X';
	std::cout << '\n' << "Computer:" << robo+1 << '\n';

}


bool check() {
	bool check = ((board[0] == board[3]) && (board[3] == board[6]) && ((board[0] == 'X') || (board[0] == 'O'))) ||
				((board[1] == board[4]) && (board[4] == board[7]) && ((board[1] == 'X') || (board[1] == 'O'))) ||
				((board[2] == board[5]) && (board[5] == board[8]) && ((board[2] == 'X') || (board[2] == 'O'))) ||
				((board[0] == board[1]) && (board[1] == board[2]) && ((board[0] == 'X') || (board[0] == 'O'))) ||
				((board[3] == board[4]) && (board[4] == board[5]) && ((board[3] == 'X') || (board[3] == 'O'))) ||
				((board[6] == board[7]) && (board[7] == board[8]) && ((board[6] == 'X') || (board[6] == 'O'))) ||
				((board[6] == board[4]) && (board[4] == board[2]) && ((board[6] == 'X') || (board[6] == 'O'))) ||
				((board[0] == board[4]) && (board[4] == board[8]) && ((board[0] == 'X') || (board[0] == 'O')));
	return check;
}   // Проверка трех совпадений


void print_board(){
	std::cout << "Move options: " << std::endl <<
		" -7-|-8-|-9-" << std::endl <<
		" -4-|-5-|-6-" << std::endl <<
		" -1-|-2-|-3-" << std::endl <<
		"\n";
	std::cout << "Game board: " << std::endl <<
		" -" << board[6] << "-|-" << board[7] << "-|-" << board[8] << "-" << std::endl <<
		" -" << board[3] << "-|-" << board[4] << "-|-" << board[5] << "-" << std::endl <<
		" -" << board[0] << "-|-" << board[1] << "-|-" << board[2] << "-" << std::endl <<
		"\n";
}  // напечатать доску 


int pain() {
	print_board();
	int move;
	std::cin >> move;
	while (move > 9 || move < 1 || board[move-1] != '-') {
		std::cout << "\n  Please enter a legal move (1-9):";
		std::cin >> move;
	}
	return move;
} //Ввод данных пользователем


int main(){
	std::string play;
	again:
	for (int i = 0; !check(); i++) {
		if (i % 2 == 0) {            //Всегда первым ходит игрок
				int move = pain();
				board[move - 1] = 'O';
		}
		else {
				robot();             //Компьютер ходит после
		}
	}
	print_board();
	std::cout << "    Play? \n No     Yes \n";
		std::cin >> play;
		if (play == "Yes") {
			system("cls");
			for (int x = 0; x < 9; x++) {
				board[x] = '-';
			}
			goto again;
		}
	return 0;
}


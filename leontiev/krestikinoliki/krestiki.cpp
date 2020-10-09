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
	std::cout << '\n' << "Computer:" << robo + 1 << '\n';
}

bool check() {
	bool check = ((board[0] == board[1]) && (board[1] == board[2]) && ((board[0] == 'X') || (board[0] == 'O'))) ||
		((board[3] == board[4]) && (board[4] == board[5]) && ((board[3] == 'X') || (board[3] == 'O'))) ||
		((board[6] == board[7]) && (board[7] == board[8]) && ((board[6] == 'X') || (board[2] == 'O'))) ||
		((board[0] == board[3]) && (board[3] == board[6]) && ((board[0] == 'X') || (board[0] == 'O'))) ||
		((board[1] == board[4]) && (board[4] == board[7]) && ((board[1] == 'X') || (board[1] == 'O'))) ||
		((board[2] == board[5]) && (board[5] == board[8]) && ((board[2] == 'X') || (board[2] == 'O'))) ||
		((board[0] == board[4]) && (board[4] == board[8]) && ((board[0] == 'X') || (board[0] == 'O'))) ||
		((board[2] == board[4]) && (board[4] == board[6]) && ((board[2] == 'X') || (board[2] == 'O')))||
		((board[0]!='-') && (board[1] != '-') && (board[2] != '-') && (board[3] != '-') && (board[4] != '-') && (board[5] != '-') && (board[6] != '-') && (board[7] != '-') && (board[8] != '-'));
	return check;
} 

void print_board() {
	std::cout << "Move options: " << std::endl <<
		" -1-|-2-|-3-" << std::endl <<
		" -4-|-5-|-6-" << std::endl <<
		" -7-|-8-|-9-" << std::endl <<
		"\n";
	std::cout << "Game board: " << std::endl <<
		" -" << board[0] << "-|-" << board[1] << "-|-" << board[2] << "-" << std::endl <<
		" -" << board[3] << "-|-" << board[4] << "-|-" << board[5] << "-" << std::endl <<
		" -" << board[6] << "-|-" << board[7] << "-|-" << board[8] << "-" << std::endl <<
		"\n";
}

int user() {
	print_board();
	int move;
	std::cin >> move;
	while (move > 9 || move < 1 || board[move - 1] != '-') {
		std::cout << "\n  Please, select a legal cell (1-9):";
		std::cin >> move;
	}
	return move;
}

int main() {
	std::string play;
	for (int i = 0; !check(); i++) {
		if (i % 2 == 0) {    
			int move = user();
			board[move - 1] = '0';
		}
		else {
			robot();           
		}
	}
	print_board();
	if (((board[0] == board[3]) && (board[3] == board[6]) && (board[0] == '0')) ||
		((board[1] == board[4]) && (board[4] == board[7]) && (board[1] == '0')) ||
		((board[2] == board[5]) && (board[5] == board[8]) && (board[2] == '0')) ||
		((board[0] == board[1]) && (board[1] == board[2]) && (board[0] == '0')) ||
		((board[3] == board[4]) && (board[4] == board[5]) && (board[3] == '0')) ||
		((board[6] == board[7]) && (board[7] == board[8]) && (board[6] == '0')) ||
		((board[6] == board[4]) && (board[4] == board[2]) && (board[6] == '0')) ||
		((board[0] == board[4]) && (board[4] == board[8]) && (board[0] == '0'))) std::cout << "You win!";
	else if (((board[0] == board[3]) && (board[3] == board[6]) && (board[0] == 'X')) ||
		((board[1] == board[4]) && (board[4] == board[7]) && (board[1] == 'X')) ||
		((board[2] == board[5]) && (board[5] == board[8]) && (board[2] == 'X')) ||
		((board[0] == board[1]) && (board[1] == board[2]) && (board[0] == 'X')) ||
		((board[3] == board[4]) && (board[4] == board[5]) && (board[3] == 'X')) ||
		((board[6] == board[7]) && (board[7] == board[8]) && (board[6] == 'X')) ||
		((board[6] == board[4]) && (board[4] == board[2]) && (board[6] == 'X')) ||
		((board[0] == board[4]) && (board[4] == board[8]) && (board[0] == 'X'))) std::cout << "You lose.";
	else std::cout << "Draw.";
	return 0;
}


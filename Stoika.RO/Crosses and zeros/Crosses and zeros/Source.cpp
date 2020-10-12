#include<iostream>
#include<ctime>
using namespace std;

const int ROW = 3;
const int COL = 3;
int arr[ROW][COL] ={};
int Turn = 0;
int& TurnRef = Turn;

void DisplayPole()
{
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)
		{
			switch (arr[i][j])
			{
			case 1:
				cout << "x\t";
				break;
			case -1:
				cout << 0 << '\t';;
				break;
			case 0:
				cout << "-\t";
				break;
			default:
				break;
			}
		}
		cout << "\n\n";
	}
}

void PlayerTurn()
{
	cout << "Выберите место куда поставить крестик\n" 
		<< "1\t2\t3\n4\t5\t6\n7\t8\t9\n\n";
	int a;
	cin >> a;
	cout << '\n';
	switch (a)
	{
	case 1:
		arr[0][0] = 1;
		break;
	case 2:
		arr[0][1] = 1;
		break;
	case 3:
		arr[0][2] = 1;
		break;
	case 4:
		arr[1][0] = 1;
		break;
	case 5:
		arr[1][1] = 1;
		break;
	case 6:
		arr[1][2] = 1;
		break;
	case 7:
		arr[2][0] = 1;
		break;
	case 8:
		arr[2][1] = 1;
		break;
	case 9:
		arr[2][2] = 1;
		break;
	default:
		break;
	}
	DisplayPole();
}

int ConditionWinRow()
{
	int Sum;
	for (int i = 0; i < ROW; i++)
	{
		Sum = 0;
		for (int j = 0; j < COL; j++)
		{
			Sum += arr[i][j];
		}
		if ((Sum == -2) || (Sum == 2))
			return i;
	}
	return -1;
}

void TurnWinRow(int a)
{
	if (a == -1)
		return;
	for (int i = 0; i < COL; i++)
	{
		if (arr[a][i] == 0)
		{
			arr[a][i] = -1;
			TurnRef = 1;
		}
	}
}

int ConditionWinCol()
{
	int Sum;
	for (int i = 0; i < COL; i++)
	{
		Sum = 0;
		for (int j = 0; j < ROW; j++)
		{
			Sum += arr[j][i];
		}
		if ((Sum == -2) || (Sum == 2))
			return i;
	}
	return -1;
}

void TurnWinCol(int a)
{
	if (a == -1)
		return;
	for (int i = 0; i < ROW; i++)
	{
		if (arr[i][a] == 0)
		{ 
			arr[i][a] = -1;
			TurnRef = 1;
		}
	}
}

int ConditionWinDiagonal()
{
	int Sum = 0;
	for (int i = 0; i < ROW; i++)
	{
		Sum += arr[i][i];
	}
	if ((Sum == -2)||(Sum == 2))
		return 1;
	Sum = 0;
	for (int i = 2,j=0; i >= 0; i--,j++)
	{
		Sum += arr[i][j];
	}
	if ((Sum == -2) || (Sum == 2))
		return 2;
	return 0;
}

void TurnWinDiagonal(int a)
{
	switch (a)
	{
	case 1:
		for (int i = 0; i < ROW; i++)
		{
			if (arr[i][i] == 0)
			{
				arr[i][i] = -1;
				TurnRef = 1;
			}
		}
		break;
	case 2:
		for (int i = 2, j = 0; i >= 0; i--, j++)
		{
			if (arr[i][j] == 0)
			{
				arr[i][j] = -1;
				TurnRef = 1;
			}
		}
		break;
	default:
		break;
	}
}

void ConditionalWin1()
{
	if (arr[1][1] == 1)
	{
		arr[0][0] = -1;
		TurnRef = 1;
	}
}

void ConditionalWin2()
{
	if ((arr[0][1] == 1) || (arr[1][0] == 1))
	{
		arr[0][0] = -1;
		TurnRef = 1;
	}
	if ((arr[2][1] == 1) || (arr[1][2] == 1))
	{
		arr[2][2] = -1;
		TurnRef = 1;
	}
}

void ComputerTurn()
{
	cout << "Ходит компьютер\n";
	int i, j;
	if (TurnRef==0)
	{
		TurnWinRow(ConditionWinRow());
		if (TurnRef == 0)
		{
			TurnWinCol(ConditionWinCol());
			if (TurnRef == 0)
			{
				TurnWinDiagonal(ConditionWinDiagonal());
				if (TurnRef == 0)
				{
					do
					{
						i = rand() % 3;
						j = rand() % 3;
					} while ((arr[i][j] == -1) || (arr[i][j] == 1));
					arr[i][j] = -1;
				}
			}
		}
	}
	TurnRef = 0;
	DisplayPole();
}

void main()
{
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));
	DisplayPole();
	for (int i = 0; i < 4; i++)
	{
		PlayerTurn();
		if (i == 0)
		{
			ConditionalWin1();
			ConditionalWin2();
		}
			
		ComputerTurn();
	}
	PlayerTurn();
}
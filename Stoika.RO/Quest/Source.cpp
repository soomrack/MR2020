#include<iostream>
using namespace std;

int main()
{
	int otvet[5];
	otvet[0] = 1;
	otvet[1] = 2;
	otvet[2] = 1;
	otvet[3] = 2;
	otvet[4] = 1;
	int j = 0, ans[5];
	//����
		setlocale(LC_ALL, "Rus");
		//1
		cout << "���� ������������ ��������\n";
		cout << "1) 7 �������� 1812 �.\n";
		cout << "2) 18 ���� 1815 �. \n";
		cin >> ans[0];
		//2
		cout << "���� �������� ����\n";
		cout << "1) 24 ���� 962 �.\n";
		cout << "2) 31 ��� 988 �.\n";
		cin >> ans[1];
		//3
		cout << "������ ����������� �����\n";
		cout << "1) 19 �������� 1861 �.\n";
		cout << "2) 17 ������� 1879 �.\n";
		cin >> ans[2];
		//4
		cout << "������ ������ ������� �����\n";
		cout << "1) 22 ���� 1941 �.\n";
		cout << "2) 1 �������� 1939 �.\n";
		cin >> ans[3];
		//5
		cout << "������ ����\n";
		cout << "1) 19 ������� 1993 �.\n";
		cout << "2) 26 ������� 1991 �.\n";
		cin >> ans[4];

		for (int i = 0; i < 5; i++) {
			if (otvet[i] == ans[i]) {
				j++;
			}
		}
		cout << "���������� �������\t" << j << "\n";
		return 0;
}
#include <iostream>
#include <cmath>
using namespace std;

//������� ������� - ����������, c������ �������� �� ������� (��������� ��������, �.�., ��� �������), ������ (�����) ���� ������� (���������� t_mor)
double Ipoteka(double Sum, double x, double y, double p_mor) {
	double Sum_Mortgage = Sum - y; //�������� �������������� �����
 	Sum_Mortgage = (Sum_Mortgage * p_mor) / (1 - (1 / (1 + p_mor ))); //������� ����� ������� �� �������
	double t_mor = Sum_Mortgage / x ; //���� ������� ��� �������� � � �����
	return Sum_Mortgage;
}
//������� - ������ � ���������� � ������� �����, ���������� ��� �������.
double Ipoteka_Dep(double Sum, double x, double y, double &t_mor, double t_dep, double z_dep, double p_mor) {
	double sum_mor_last = Ipoteka(Sum, x,y, p_mor) -x* floor(t_mor); //��������� �������
	t_mor = ceil(t_mor);
	int tt_mor = (int)t_mor;
	double remainder_mor = x - sum_mor_last; //������� ��� ������� � ���� ������� ����� ���������� ������ �� �������
	double Sum_dep_mor;
		if (tt_mor < (t_dep * 12)) {
			Sum_dep_mor = remainder_mor + x * (tt_mor % 12); //� �� ����� ���� ��� ����� ������� ������� �� ����� 
			Sum_dep_mor = Sum_dep_mor * pow((z_dep + 1), (t_dep - (tt_mor/12))); //�������� ��������� � ����� ����
			for (int i = 1; i <= (t_dep - (tt_mor / 12)); i++) { //� ������ ���������� ����
				Sum_dep_mor = Sum_dep_mor + x * 12 * pow((z_dep + 1), i);
			}
		}
		Sum_dep_mor = Sum_dep_mor + x * (tt_mor % 12);
		return Sum_dep_mor;
}
//������� - ���������� ��������� �������� ��-�� ��������
double Inflation(double Sum, double r_inflation, double t_dep) {
	double Sum_inflation = Sum * pow((r_inflation + 1), t_dep);
	return Sum_inflation;
}
//������� - ������� ����� �� ��������
double Deposite(double y, double x, double z_dep, double t_dep) {
	double Sum_dep = y * pow((z_dep + 1), t_dep);
	for (int i = 1; i < t_dep; i++) {
		Sum_dep += x * 12 * pow((z_dep + 1), i);
	}
	return Sum_dep;
}

int main() {
	setlocale(LC_ALL, "Rus");
	//������� ������ (�������� �������������, �� ��������� ������ - ��� ������� ����)
	double x = 50000;         //����� � ����� - � ������/���
	double y = 1000000;       //��������� ������� - � ���
	double t_dep = 10;        //���� - T ���
	double Sum = 2100000;     //���� �������� - Sum ���
	double z_dep = 0.04;      //������� - Z %/���
	double v_mor = 1000000;   //�������: �������������� ����� - V ���. ��� �������� - ��������� � ������ ������������.
	double p_mor = 0.2;        //�������: ������� - P %/���
	double r_inflation = 0.03; //���� ��������� �������� - R %/���
	double VI=0, VD=0;        //������ �� ������� � �� �������� ��������������
	double t_mor = Ipoteka(Sum, x, y, p_mor) / x;        //���� ������� �������, �������

	VD = Deposite(y, x, z_dep, t_dep)-y-x*t_dep*12;
	VI = Inflation(Sum, r_inflation, t_dep) - y - Ipoteka(Sum, x, y, p_mor) + Ipoteka_Dep(Sum, x,y, t_mor, t_dep, z_dep, p_mor) - x * (t_dep - Ipoteka(Sum, x, y, p_mor) / x);
	cout << VD << " " << VI;
	return 0;
}
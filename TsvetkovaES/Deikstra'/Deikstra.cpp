#include <iostream>
#include "MyHeader.h" 

using namespace std;

void Make_matrix(int n, vector<vector<pair<int, int>>>& a) {
	// ������� ������ ����, ������������� ��������� �� ������ �� ������
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int wt;
			cout << "������� ���������� �� ������� " << i + 1 << " �� ������� " << j + 1 << endl;
			if (i == 0 && j == 0) {
				cout << "���� ������������� �����, ������������ ��� ������� ���, ������� 0.\n";
			}
			cin >> wt;
			if (wt != 0) {
				a[i].push_back(make_pair(j, wt));
			}
		}
	}
}

void Deikstra(int n, vector<vector<pair<int, int>>> a, int start, vector<int>& dist) {
	set<pair<int, int> > unused; /* ����� ������� ������������ ������� �������������� (����: wt - j),
									����� �� ������ ������ ��� ����������� ����������*/
	unused.insert(make_pair(0, start)); // ������ ���� 

	while (!unused.empty()) {
		int i = unused.begin()->second; // �������, �� ���. ���������� ���������� �� start
		unused.erase(unused.begin()); // �������, �.�. �� � ��������
		for (auto edge : a[i]) { // ��������� ��� ������� j, ��������� �� ��
			int j = edge.first;
			int wt = edge.second;
			if (dist[i] + wt < dist[j]) { // ���� ����� ����� ����������� ���������� �� start � j
				unused.erase(make_pair(dist[j], j));
				dist[j] = dist[i] + wt; // �� ������� ���
				unused.insert(make_pair(dist[j], j));
			}
		}
	}
}


int main() {
	setlocale(LC_ALL, "Russian");
	int n = 0;
	cout << "������� ���������� ������:\n n = ..";
	cin >> n;
	int start;
	cout << "������� ����� ����� ����� ���������\n start = .. ";
	cin >> start; start--;

	vector<vector<pair<int, int>>> Weights(n); /*�� ������ ������� ���� ������ ��� ��������
										   ���� "j - wt". j - �������, wt - ���������� �� ��.*/
	vector<int> dist(n, 10000); // ����������� ���������� �� start-���� �� i-�� �������. ������� - �� ���������� ������
	dist[start] = 0; // �����, �������, ���������� ����� start � ����� start :)

	Make_matrix(n, Weights); /// ������� �����. 
	Deikstra(n, Weights, start, dist);
	for (int i = 0; i < n; i++) {
		cout << i + 1 << " " << dist[i] << endl;
	}
	return 0;
}

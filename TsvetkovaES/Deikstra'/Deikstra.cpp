#include <iostream>
#include "MyHeader.h" 

using namespace std;

void Make_matrix(int n, vector<vector<pair<int, int>>>& a) {
	// заносим только рЄбра, действительно выход€щие из каждой из вершин
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int wt;
			cout << "¬ведите рассто€ние от вершины " << i + 1 << " до вершины " << j + 1 << endl;
			if (i == 0 && j == 0) {
				cout << "≈сли единственного ребра, соедин€ющего эти вершины нет, введите 0.\n";
			}
			cin >> wt;
			if (wt != 0) {
				a[i].push_back(make_pair(j, wt));
			}
		}
	}
}

void Deikstra(int n, vector<vector<pair<int, int>>> a, int start, vector<int>& dist) {
	set<pair<int, int> > unused; /* будем хранить непосещЄнные вершины отсортированно (пара: wt - j),
									чтобы не искать каждый раз минимальное рассто€ние*/
	unused.insert(make_pair(0, start)); // перва€ пара 

	while (!unused.empty()) {
		int i = unused.begin()->second; // вершина, до кот. кратчайшее рассто€ние из start
		unused.erase(unused.begin()); // удал€ем, т.к. мы еЄ посетили
		for (auto edge : a[i]) { // провер€ем все вершины j, выход€щие из неЄ
			int j = edge.first;
			int wt = edge.second;
			if (dist[i] + wt < dist[j]) { // если нашли новое минимальное рассто€ние из start в j
				unused.erase(make_pair(dist[j], j));
				dist[j] = dist[i] + wt; // то заносим его
				unused.insert(make_pair(dist[j], j));
			}
		}
	}
}


int main() {
	setlocale(LC_ALL, "Russian");
	int n = 0;
	cout << "¬ведите количество вершин:\n n = ..";
	cin >> n;
	int start;
	cout << "¬ведите кака€ точка будет стартовой\n start = .. ";
	cin >> start; start--;

	vector<vector<pair<int, int>>> Weights(n); /*Ќа каждую вершину есть вектор пар значений
										   типа "j - wt". j - вершина, wt - рассто€ние до неЄ.*/
	vector<int> dist(n, 10000); // ћинимальное рассто€ние от start-овой до i-ой вершины. —начала - всЄ бесконечно далеко
	dist[start] = 0; // кроме, конечно, рассто€ни€ между start и самим start :)

	Make_matrix(n, Weights); /// ћатрица св€зи. 
	Deikstra(n, Weights, start, dist);
	for (int i = 0; i < n; i++) {
		cout << i + 1 << " " << dist[i] << endl;
	}
	return 0;
}

#include <iostream>


using namespace std;

int make_sells (int N, int X_st, int Y_st, int X_fin, int Y_fin) {
    int Cell[N][N];
    cout << "Enter 1 or 0:";
    for(int i = 0; i <= N; i++) {
        for (int j = 0; j <= N; j++) {
            cin >> Cell[i][j];
        }
    }
    int Move_gor = 0;
    int Move_vert = 0;
    Move_gor = X_fin - X_st;
    Move_vert = Y_fin - Y_st;
}

int main() {
    cout << "Enter map size (cell): " << endl;
    int map_size = 0;
    cin >> map_size;
    cout << "Enter start coordinates: " << endl;
    int X_start = 0;
    int Y_start = 0;
    cin >> X_start;
    cin >> Y_start;
    cout << "Enter finish coordinates: " << endl;
    int X_finish = 0;
    int Y_finish = 0;
    cin >> X_finish;
    cin >> Y_finish;
    return 0;
}

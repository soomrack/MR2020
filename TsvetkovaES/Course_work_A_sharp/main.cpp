/*
 * Программа реализует поиск оптимального пути из точки srs до dest на поле grid[][]. 0 - препятсивие, 1 - путь.
 * На выходе - печатает последовательность координат точек для отпимального пути.
 * Анализ постоен на оценке параметра F. Точки отсортированы в set <pPair> openList по параметру F.
 * Все возможные пути при движении от srs в dest и соотв. им параметры F представлены в cells_grid[ROW][COL];
 * Финальный путь отслеживается по координатам parent_i и parent_j, двигаясь от точки dest.
*/

#include <iostream>
#include <cmath>
#include <set>
#define ROW 9
#define COL 10
#define FLT_MAX 50000.0f
using namespace std;

//******* Types *******//
typedef pair<int, int> coordinates;
typedef pair<double, coordinates> pPair;
class cell {
private:
    int parent_i, parent_j;
    double f, g, h;
public:
    cell() { // default - max path, "wrong" parents
        f = FLT_MAX;
        g = FLT_MAX;
        h = FLT_MAX;
        parent_i = -1;
        parent_j = -1;
    }
    void set_fgh(double f_,double g_,double h_) {
        this->f = f_;
        this->g = g_;
        this->h = h_;
    }
    void set_parents(int parent_i_, int parent_j_) {
        this->parent_i = parent_i_;
        this->parent_j = parent_j_;
    }
    double get_g() {
        return g;
    }
    double get_f() {
        return f;
    }
    int get_parent_i() {
        return parent_i;
    }
    int get_parent_j() {
        return parent_j;
    }
};

//******* Utility  functions to check correctness *******//
bool is_valid(int row, int col) {
    return (row >= 0) && (row < ROW) && (col >= 0)
           && (col < COL);
}
bool is_unblocked(int grid[][COL], int row, int col) {
    if (grid[row][col] == 1) return (true);
    else return (false);
}

//******* Utility  functions *******//
bool is_destination(int row, int col, coordinates dest) {
    if (row == dest.first && col == dest.second)
        return (true);
    else
        return (false);
}
double calculate_H(int row, int col, coordinates dest) {
    auto H = (float)sqrt(
            (row - dest.first) * (row - dest.first)
            + (col - dest.second) * (col - dest.second));
    return H;
}
void trace_path(cell cellDetails[][COL], coordinates dest) {
    printf("\nThe Path is ");
    int row = dest.first;
    int col = dest.second;
    int temp_row = 0;
    int temp_col = 0;
    coordinates p;
    
    while (!(cellDetails[row][col].get_parent_i() == row
             && cellDetails[row][col].get_parent_j() == col)) {
        p = make_pair(row, col);
        printf("(%d,%d) <- ", p.first + 1, p.second + 1);
        temp_row = cellDetails[row][col].get_parent_i();
        temp_col = cellDetails[row][col].get_parent_j();
        row = temp_row;
        col = temp_col;
    }
    p = make_pair(row, col);
    printf("(%d,%d)", p.first + 1, p.second + 1);
}

//******* Search algorithm *******//
void aStarSearch(int grid[][COL], coordinates src, coordinates dest) {
    // Check some stuff
    if (!is_valid(src.first, src.second)) {
        printf("Source is invalid\n");
        return;
    }
    if (!is_valid(dest.first, dest.second)) {
        printf("Destination is invalid\n");
        return;
    }
    if (!is_unblocked(grid, src.first, src.second)
        || !is_unblocked(grid, dest.first, dest.second)) {
        printf("Source or the destination is blocked\n");
        return;
    }
    if (is_destination(src.first, src.second, dest)) {
        printf("We are already at the destination\n");
        return;
    }
    
    // Create a closed list for cells we already checked
    bool closed_list[ROW][COL] = {false};
    // Create an set having information as <f, <x, y>>, where f = g + h,
    set <pPair> open_list;
    // Details for all cells: f,g,h of each cell, coordinates of their parents
    cell cells_grid[ROW][COL];
    
    int x, y;
    // Initialising the parameters of the starting node
    x = src.first, y = src.second;
    cells_grid[x][y].set_fgh(0.0, 0.0, 0.0);
    cells_grid[x][y].set_parents(x, y);
    // Put the starting cell on the open list
    open_list.insert(make_pair(0.0, make_pair(x, y)));
    
    while (!open_list.empty()) {
        // take vertex - the smallest F-value
        pPair cur_point = *open_list.begin();
        open_list.erase(open_list.begin());
        x = cur_point.second.first;
        y = cur_point.second.second;
        closed_list[x][y] = true;
        
        // check 8 Successors of vertex: {-1,-1},{-1,0},{-1,1},{1,-1},{1,0},{1,1},{0,-1},{0,1}
        double gNew = 0.0;
        double hNew = 0.0;
        double fNew = 0.0;
        double step = 0.0;
        
        for(int x_step = -1; x_step <= 1; x_step++) {
            for(int y_step = -1; y_step <= 1; y_step++) {
                // 1. Check some stuff
                if(x_step == 0 && y_step == 0) {
                    continue; // the current position
                }
                if(closed_list[x + x_step][y + y_step]) {
                    continue; // already in the closed_list
                }
                if(!is_valid(x + x_step, y + y_step) || !is_unblocked(grid, x + x_step, y + y_step)) {
                    continue; // not valid or blocked position
                }
                if (is_destination(x + x_step, y + y_step, dest)) {
                    cells_grid[x + x_step][y + y_step].set_parents(x, y);
                    printf("The destination cell is found\n");
                    trace_path(cells_grid, dest);
                    return;
                }
                // 2. Check the F - value
                if(abs(x_step) == abs(y_step)) {
                    step = 1.414; // diagonal
                } else step = 1.0; // straight
                gNew = cells_grid[x][y].get_g() + step;
                hNew = calculate_H(x + x_step, y + y_step, dest);
                fNew = gNew + hNew;
                // If it isn’t on the open list : add.
                // if it is on the open list already : evaluate the F-parameter.
                if (cells_grid[x + x_step][y + y_step].get_f() == FLT_MAX
                    || cells_grid[x + x_step][y + y_step].get_f() > fNew) {
                    open_list.insert(make_pair(fNew, make_pair(x + x_step, y + y_step)));
                    // Update the details of this cell
                    cells_grid[x + x_step][y + y_step].set_fgh(fNew, gNew, hNew);
                    cells_grid[x + x_step][y + y_step].set_parents(x, y);
                }
            }
        }
    }
    printf("Failed to find the Destination Cell\n");
}

int main() {
    int grid[ROW][COL] = {
        { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
        { 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
        { 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
        { 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
        { 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
        { 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
        { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
        { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
        { 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 }
    };
    coordinates src = make_pair(8, 0);
    coordinates dest = make_pair(0, 0);
    aStarSearch(grid, src, dest);
    return 0;
}

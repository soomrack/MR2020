#include<iostream>
#include<windows.h>
using namespace std;

const unsigned int rows = 8;
const unsigned int cols = 8;
bool treasure_map[rows][cols] = {
  {1,0,0,0,0,1,1,1},
  {0,0,0,0,0,1,0,1},
  {1,1,0,0,0,0,0,0},
  {1,0,1,0,0,1,0,1},
  {1,0,0,1,0,1,1,0},
  {1,0,0,1,0,0,0,1},
  {0,0,0,1,0,0,0,1},
  {0,0,1,0,0,0,0,1},
};

unsigned int newmap[rows][cols];
unsigned int solution_map[rows][cols];
unsigned int mark_col = 6;
unsigned int mark_row = 1;
unsigned int start_col = 0;
unsigned int start_row = 7;
unsigned int steps_count = 0;

void print_treasure_map() {
  cout << "This is the map\n";
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (i == mark_row && j == mark_col) {
        cout << "X"; continue;
      }
      cout << treasure_map[i][j];
    }
    cout << endl;
  }
  cout << endl;
}

void voidmapfill(unsigned int voidmap[rows][cols]) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      voidmap[i][j] = 0;
    }
  }
}

void print_map(unsigned int map[rows][cols]) {
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      cout << map[i][j];
    }
    cout << endl;
  }
  cout << endl;
}

void minimum_steps() {
  newmap[start_row][start_col] = 1;
  for (int g = 2; g < (rows * cols - (cols - 1) * (rows / 2)); g++) {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        if (newmap[i][j] == g - 1) {
          if (i < rows - 1 && treasure_map[i + 1][j] == 0 && newmap[i + 1][j] == 0) {
            newmap[i + 1][j] = g; 
          }
          if (j < cols - 1 && treasure_map[i][j + 1] == 0 && newmap[i][j + 1] == 0) {
            newmap[i][j + 1] = g; 
          }
          if (i > 0 && treasure_map[i - 1][j] == 0 && newmap[i - 1][j] == 0) {
            newmap[i - 1][j] = g; 
          }
          if (j > 0 && treasure_map[i][j - 1] == 0 && newmap[i][j - 1] == 0) {
            newmap[i][j - 1] = g; 
          }
          if (i < rows - 1 && j < cols - 1 && treasure_map[i + 1][j + 1] == 0 && newmap[i + 1][j + 1] == 0) {
            newmap[i + 1][j + 1] = g; 
          }
          if (i < rows - 1 && j>0 && treasure_map[i + 1][j - 1] == 0 && newmap[i + 1][j - 1] == 0) {
            newmap[i + 1][j - 1] = g; 
          }
          if (i > 0 && j < cols - 1 && treasure_map[i - 1][j + 1] == 0 && newmap[i - 1][j + 1] == 0) {
            newmap[i - 1][j + 1] = g; 
          }
          if (i > 0 && j > 0 && treasure_map[i - 1][j - 1] == 0 && newmap[i - 1][j - 1] == 0) {
            newmap[i - 1][j - 1] = g; 
          }
        }
      }
    }
    print_map(newmap);
    Sleep(1000);
    if (newmap[mark_row][mark_col] != 0) {
      steps_count = g;
      cout << "you need " << steps_count - 1 << " steps to reach treasure\n";
      break;
    }
  }
  if (newmap[mark_row][mark_col] == 0) {
    cout << "you can't reach treasure :(";
    exit(0);
  }
}

bool nearby_cell_check(unsigned int map[rows][cols], unsigned int i, unsigned int j, int number_in_cell)
{
  bool check = 0;
  if (i < rows - 1 ) {
    check = check || map[i + 1][j] == number_in_cell;
  }
  if (j < cols - 1) {
    check = check || map[i][j + 1] == number_in_cell; 
  }
  if (i > 0) {
    check = check || map[i - 1][j] == number_in_cell; 
  }
  if (j > 0) {
    check = check || map[i][j - 1] == number_in_cell; 
  }
  if (i < rows - 1 && j < cols - 1) {
    check = check || map[i + 1][j + 1] == number_in_cell; 
  }
  if (i < rows - 1 && j>0) {
    check = check || map[i + 1][j - 1] == number_in_cell; 
  }
  if (i > 0 && j < cols - 1) {
    check = check || map[i - 1][j + 1] == number_in_cell; 
  }
  if (i > 0 && j > 0) {
    check = check || map[i - 1][j - 1] == number_in_cell; 
  }
  return check;
}

void collect_steps_back() {
  solution_map[mark_row][mark_col] = steps_count;
  bool stop = 0;
  for (int f = steps_count-1; f != 0; f--) {
    stop = 0;
    for (int i = 0; stop == 0 && i < rows; i++) {
      for (int j = 0; stop == 0 && j < cols; j++) {
        if (newmap[i][j] == f && nearby_cell_check(solution_map, i, j, f+1)) {
          solution_map[i][j] = f;
          stop = 1;
        }
      }
    }
  }
}

int main() {
  print_treasure_map();
  voidmapfill(newmap);
  minimum_steps();
  collect_steps_back();
  cout << "This is our way to become rich! MUHAHAH\n";
  print_map(solution_map);
  system("PAUSE");
  return 0;
}

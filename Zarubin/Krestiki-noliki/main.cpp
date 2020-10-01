#include <iostream>
#include <cmath>

using namespace std;

int main()
{
    setlocale(0,"");


    char cells[9] = {'-','-','-','-','-','-','-','-','-',};
    int cells_number[9]={1,2,3,4,5,6,7,8,9};

    int cell;
    int cell1;

    cout << "------------" << "\n" << endl;
    cout << "Coordinate of cell:" << endl;
    cout << "-" << 1 << "-" << '|' << "-" << 2 << "-" << '|' << "-" << 3 << "-" << " |" << endl;
    cout << "-" << 4 << "-" << '|' << "-" << 5 << "-" << '|' << "-" << 6 << "-" << " |" <<  endl;
    cout << "-" << 7 << "-" << '|' << "-" << 8 << "-" << '|' << "-" << 9 << "-" << " |" << "\n" << endl;


    cout << "Game field (--- empty):" << endl;
    cout << "-" << cells[0] << "-" << '|' << "-" << cells[1] << "-" << '|' << "-" << cells[2] << "-" << " |" <<  endl;
    cout << "-" << cells[3] << "-" << '|' << "-" << cells[4] << "-" << '|' << "-" << cells[5] << "-" << " |" <<  endl;
    cout << "-" << cells[6] << "-" << '|' << "-" << cells[7] << "-" << '|' << "-" << cells[8] << "-" << " |" <<  "\n" << endl;

    cout << "------------\n" << endl;



    for(int o = 0; o <= 9; ++o){
        cout << "Enter the number of the cell for  X: ";
        cin >> cell;
        cells[cell-1] = 'x';
        cells_number[cell-1]=0;

        cout << "-" << cells[0] << "-" << '|' << "-" << cells[1] << "-" << '|' << "-" << cells[2] << "-" << " |" <<  endl;
        cout << "-" << cells[3] << "-" << '|' << "-" << cells[4] << "-" << '|' << "-" << cells[5] << "-" << " |" <<  endl;
        cout << "-" << cells[6] << "-" << '|' << "-" << cells[7] << "-" << '|' << "-" << cells[8] << "-" << " |" <<  "\n" << endl;

        if((cells[0] == 'x') && (cells[1] == 'x') && (cells[2] == 'x' )){
            cout << "You win! X" << endl;
            break;
        }
        if((cells[3] == 'x') && (cells[4] == 'x') && (cells[5] == 'x' )){
            cout << "You win! X" << endl;
            break;
        }
        if((cells[6] == 'x') && (cells[7] == 'x') && (cells[8] == 'x' )){
            cout << "You win! X" << endl;
            break;
        }
        if((cells[0] == 'x') && (cells[3] == 'x') && (cells[6] == 'x' )){
            cout << "You win! X" << endl;
            break;
        }
        if((cells[1] == 'x') && (cells[4] == 'x') && (cells[7] == 'x' )){
            cout << "You win! X" << endl;
            break;
        }
        if((cells[2] == 'x') && (cells[5] == 'x') && (cells[8] == 'x' )){
            cout << "You win! X" << endl;
            break;
        }
        if((cells[0] == 'x') && (cells[4] == 'x') && (cells[8] == 'x' )){
            cout << "You win! X" << endl;
            break;
        }
        if((cells[2] == 'x') && (cells[4] == 'x') && (cells[6] == 'x' )){
            cout << "You win! X" << endl;
            break;
        }


        int i=1;
        cell1 = rand() %9 +1;
        while(cells_number[cell1-1]==0) {
            if (i == 1) {cell1 = 0;}
            cell1 += 1;
            i+=1;
        }
        cells[cell1-1] = 'O';
        cells_number[cell1-1]=0;
cout << cell1 << endl;
        cout << "-" << cells[0] << "-" << '|' << "-" << cells[1] << "-" << '|' << "-" << cells[2] << "-" << " |" <<  endl;
        cout << "-" << cells[3] << "-" << '|' << "-" << cells[4] << "-" << '|' << "-" << cells[5] << "-" << " |" <<  endl;
        cout << "-" << cells[6] << "-" << '|' << "-" << cells[7] << "-" << '|' << "-" << cells[8] << "-" << " |" <<  "\n" << endl;

        if((cells[0] == 'O') && (cells[1] == 'O') && (cells[2] == 'O' )){
            cout << "You lose! O" << endl;
            break;
        }
        if((cells[3] == 'O') && (cells[4] == 'O') && (cells[5] == 'O' )){
            cout << "You lose! O" << endl;
            break;
        }
        if((cells[6] == 'O') && (cells[7] == 'O') && (cells[8] == 'O' )){
            cout << "You lose! O" << endl;
            break;
        }
        if((cells[0] == 'O') && (cells[3] == 'O') && (cells[6] == 'O' )){
            cout << "You lose! O" << endl;
            break;
        }
        if((cells[1] == 'O') && (cells[4] == 'O') && (cells[7] == 'O' )){
            cout << "You lose! O" << endl;
            break;
        }
        if((cells[2] == 'O') && (cells[5] == 'O') && (cells[8] == 'O' )){
            cout << "You lose! O" << endl;
            break;
        }
        if((cells[0] == 'O') && (cells[4] == 'O') && (cells[8] == 'O' )){
            cout << "You lose! O" << endl;
            break;
        }
        if((cells[2] == 'O') && (cells[4] == 'O') && (cells[6] == 'O' )){
            cout << "You lose! O" << endl;
            break;
        }

    }






    system("pause");
    return 0;


}
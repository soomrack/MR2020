#include <string>
#include <iostream>
#include <vector>
#include <cmath>

///////////// by Panteleev MD aka Qu0Z \\\\\\\\\\\\

using namespace std;

struct CRUTCH       //makeshift touple
{
    int score;
    int move;
};
class gameState     //class to handle the hame
{
    public:
        vector <vector <int>> game;
        int currentPlayer = 1;          //-1: "o"-AI   1: "x"-Human
        int winner = 0;

        void reset()
        {
            game = { {0, 0, 0},
                     {0, 0, 0}, 
                     {0, 0, 0} };
            currentPlayer = 1;
            winner = 0;
        }
        
        void display()      //prints staff
        {
            cout << "State of the game:" << '\n';
            for (int a = 0; a < 3; a++) 
            {

                for (int b = 0; b < 3; b++)
                {
                    if (game[a][b] == -1) 
                    {cout << " o ";}
                    else if (game[a][b] == 1)
                    {cout << " x ";}
                    else {cout << " . ";}
                }
                
                cout << '\n';
            }
        }

        void begin()        //welcome message 
        {
            reset();
            cout << "Let the game begin! " << '\n';
            cout << "Use numbers to pick spot where to put your 'x'" << '\n';

            cout << " 1  2  3 " << '\n'
                 << " 4  5  6 " << '\n'
                 << " 7  8  9 " << '\n';
        }

        void makeTurn(int turn, int player)     //self-explainatory. No checks included
        {
            game[(turn-1)/3][(turn-1)%3] = 1*player;
        }


        bool hasWinner()        //checks if there is winner already
        {
            bool flag = false;
            for (int a = 0; a < 3; a++) 
            {
                int row = 0;
                for (int b = 0; b < 3; b++)
                {
                    row += game[a][b];          //checking rows
                }
                
                if (abs(row) == 3) {flag = true; winner = copysign(1, row); break;} 
            }
            for (int a = 0; a < 3; a++) 
            {
                int column = 0;
                for (int b = 0; b < 3; b++)
                {
                    column += game[b][a];           //checking columns
                }
                
                if (abs(column) == 3) {flag = true; winner = copysign(1, column); break;} 
            }
            int diagL = 0;
            for (int a = 0; a < 3; a++) 
            {
                diagL += game[a][a];              
                
            }if (abs(diagL) == 3) {flag = true; winner = copysign(1, diagL);} 
            int diagR = 0;
            for (int a = 0; a < 3; a++) 
            {
                diagR += game[a][2-a];              
                
            }if (abs(diagR) == 3) {flag = true; winner = copysign(1, diagR);} 

            return flag;
        }

        bool isFull()       //checks if all the cells are filled
        {
            bool flag = false;
            int counter = 0;

            for (int a = 0; a < 3; a++) 
            {
                for (int b = 0; b < 3; b++)
                {
                    counter += abs(game[a][b]);    //checking everything
                }
            }
            if (counter == 9) flag = true;

            return flag;

        }

};

bool checkUser(gameState board, int turn)       //checking availability of the cell
{
    bool flag = false;

    if (turn <= 0 || turn >= 10)
        {cout << "Wrong coordinate" << '\n'; flag = false;}
    else if (abs(board.game[(turn-1)/3][(turn-1)%3]) == 1) 
    {
        flag = false;   
        cout << "Oops seems like this spot is already taken" << '\n';
    }
    else { flag = true; }  

    return flag;

}

bool checkAI(gameState board, int turn)     //Just like *checkUser* but no indication
{
    bool flag = true;

    if (turn <= 0 || turn >= 10) { flag = false; }
    else if (abs(board.game[(turn-1)/3][(turn-1)%3]) == 1) 
    {
        flag = false;   
    } 

    return flag;
}

CRUTCH AIturn(gameState curState, int player)       //MiniMax 
{
    CRUTCH touple;
    touple.move = -1;
    touple.score = -2;      //-infinity but bigger

    if (curState.hasWinner()) {
        touple.score = player * curState.winner; return touple; }
    else {
        for (int i = 1; i < 10; i++)
        {
            if (checkAI(curState, i))
            {
                gameState newState = curState;      //not to touch curState
                newState.makeTurn(i, player);       
                int tempScore = -AIturn(newState, -1*player).score;
                if (tempScore > touple.score)       //update best(worst) score
                {
                    touple.score = tempScore;
                    touple.move = i;
                }
            }

        }
    }
    if (touple.move == -1) {touple.score=0;} //no new turns
    return touple;
}

void nextTurn(gameState curState, int player)    //recursive turn handling
{   
    if (curState.hasWinner()) {cout << "Happy victory to me! "; exit;}
    else if (curState.isFull()) {cout << "Tie! "; exit;}
    else if (player == 1) {    
        int turn;
        //bool shit = false;
        do
        {
            curState.display();
            cin >> turn;
            //shit = ;
        } while (!checkUser(curState, turn));         //check fed cell

        curState.makeTurn(turn, 1);
        //curState.currentPlayer *= -1;
        nextTurn(curState, -1);
    }
    else {          //player == -1
        int decision;
        decision = AIturn(curState, player).move;
        curState.makeTurn(decision, -1);
        //curState.currentPlayer *= -1;
        nextTurn(curState, 1);
    }
}


int main()
{
    gameState Game;
    Game.begin();

    nextTurn(Game, 1); //first turn, actially. '1' for Human to start
    
    cout << "I didn't even bother to write a winning line for you, meatbag.";
    return 0;
}

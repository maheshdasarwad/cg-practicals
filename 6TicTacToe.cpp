/*
Write a c++ program to implement the game Tic Tac Toe. Apply the concept of polymorphism.;
*/
#include <iostream>
#include <vector>
using namespace std;

class TicTacToe {
protected:
    char spaces[9] = {' ',' ',' ',' ',' ',' ',' ',' ',' '};
    char player1 = 'X' , player2 = 'O';

public:
    virtual void drawBoard() {
        int j = 0;
        cout << "\n ___________ ";
        for (int i = 0; i < 3; i++) {
            cout << "\n|";
            for (int k = 0; k < 3; k++) {
                cout << "_" << spaces[j] << "_|";
                j++;
            }
        }
        cout << endl;
    }

    virtual void playerMove() {
        int num;
        char curplayer = player1;
        for (int i = 0; i < 9; i++) {
            cout << "\nEnter a spot to place(0-8): ";
            cin >> num;
            if (num < 0 || num > 8 || spaces[num] != ' ') {
                cout << "Invalid move. Try again." << endl;
                i--;
                continue;
            }
            spaces[num] = curplayer;
            drawBoard();

            if (checkWinner(curplayer)) {
                if(curplayer == player1) cout<<"\nPlayer 1(X) wins!"<<endl;
                else cout<<"\nPlayer 2(O) wins!"<<endl;
                return;
            }
            else if (isDraw()) {
                cout << "\nThe game is a draw!" << endl;
                return;
            }

            if(curplayer == player1) curplayer = player2;
            else curplayer = player1;
        }
    }

    virtual bool checkWinner(char curplayer) {
        // Rows
        for (int i = 0; i < 3; i++) {
            if (spaces[i * 3] == curplayer && spaces[i * 3 + 1] == curplayer && spaces[i * 3 + 2] == curplayer) {
                return true;
            }
        }
        // Columns
        for (int i = 0; i < 3; i++) {
            if (spaces[i] == curplayer && spaces[i + 3] == curplayer && spaces[i + 6] == curplayer) {
                return true;
            }
        }
        // Diagonals
        if ((spaces[0] == curplayer && spaces[4] == curplayer && spaces[8] == curplayer) ||
            (spaces[2] == curplayer && spaces[4] == curplayer && spaces[6] == curplayer)) {
            return true;
        }
        return false;
    }

    virtual bool isDraw() {
        for (int i = 0; i < 9; i++) {
            if (spaces[i] == ' ') {
                return false;
            }
        }
        return true;
    }
};

class AdvancedTicTacToe : public TicTacToe {
public:
    void drawBoard() override {
        cout << "\nCurrent Board:";
        TicTacToe::drawBoard();
    }
    void playerMove() override {
        cout << "\nAdvanced Tic Tac Toe Game Starting!" << endl;
        TicTacToe::playerMove();
    }
};

int main() {
    AdvancedTicTacToe game;
    game.drawBoard();
    game.playerMove();
    return 0;
}

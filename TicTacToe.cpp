#include <bits/stdc++.h>
using namespace std;

void printBoard(const vector <string> &board){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            cout << " " << board[i][j];
            if(j < 2) cout << " |";
        }
        cout << endl;
        if(i < 2) cout << "---+---+---" << endl;
    }
    cout << endl;
    return;
}

bool full(const vector <string> &board){
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(board[i][j] == '.') return false;
        }
    }
    return true;
}


bool winX(const vector <string> &board){
    for(int i = 0; i < 3; i++){
        if(board[i][0] == 'X' && board[i][1] == 'X' && board[i][2] == 'X') return true;
        if(board[0][i] == 'X' && board[1][i] == 'X' && board[2][i] == 'X') return true;
    }
    if(board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == 'X') return true;
    if(board[0][2] == 'X' && board[1][1] == 'X' && board[2][0] == 'X') return true;
    return false;
}

bool winO(const vector <string> &board){
    for(int i = 0; i < 3; i++){
        if(board[i][0] == 'O' && board[i][1] == 'O' && board[i][2] == 'O') return true;
        if(board[0][i] == 'O' && board[1][i] == 'O' && board[2][i] == 'O') return true;
    }
    if(board[0][0] == 'O' && board[1][1] == 'O' && board[2][2] == 'O') return true;
    if(board[0][2] == 'O' && board[1][1] == 'O' && board[2][0] == 'O') return true;
    return false;
}

int value(const vector <string> &board){
    if(winX(board)) return 1;
    if(winO(board)) return -1;
    return 0;
}

int terminal(const vector <string> &board){
    if(winX(board)) return 1;
    if(winO(board)) return -1;
    if(full(board)) return 0;
    return 2;
}

int minimax(vector <string> &board, bool X){
    if(winX(board)) return 1;
    if(winO(board)) return -1;
    if(full(board)) return 0;

    if(X){
        int best = -2;
        for(int x = 0; x < 9; x++){
            int i = x/3, j = x%3;
            if(board[i][j] == '.'){
                board[i][j] = 'X';
                best = max(best, minimax(board, false));
                board[i][j] = '.';
            }
        }
        return best;
    }
    else{
        int best = 2;
        for(int x = 0; x < 9; x++){
            int i = x/3, j = x%3;
            if(board[i][j] == '.'){
                board[i][j] = 'O';
                best = min(best, minimax(board, true));
                board[i][j] = '.';
            }
        }
        return best;
    }
}

void computerMove(vector <string> &board, bool* X){
    int r = -1, c = -1;
    int bestValue = -2;
    for(int x = 0; x < 9; x++){
        int i = x/3, j = x%3;
        if(board[i][j] == '.'){
            board[i][j] = 'X';
            int moveValue = minimax(board, false);
            board[i][j] = '.';
            if(moveValue > bestValue){
                bestValue = moveValue;
                r = i;
                c = j;
            }
        }
    }
    board[r][c] = 'X';
    *X = false;
    printBoard(board);
    return;
}

void playerMove(vector <string> &board, bool* X){
    int r = -1, c = -1;
    cin >> r >> c;
    board[r][c] = 'O';
    *X = true;
    printBoard(board);
    return;
}

int main(){
    vector <string> board(3, string(3, '.'));
    bool X = true;
    while(true){
        if(winX(board)){
            cout << "Computer wins!\n" << endl;
            break;
        }
        if(winO(board)){
            cout << "Player wins!\n" << endl;
            break;
        }
        if(full(board)){
            cout << "It's a draw!\n" << endl;
            break;
        }
        if(X) computerMove(board, &X);
        else playerMove(board, &X);
    }
    return 0;
}
#include <bits/stdc++.h>
using namespace std;

vector <string> board(4, string(5, '.'));
vector <int> used(5, 0);
bool R = true;

bool full(){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 5; j++){
            if(board[i][j] == '.') return false;
        }
    }
    return true;
}

bool winR(){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 2; j++){
            if(board[i][j] == 'R' && board[i][j+1] == 'R' && board[i][j+2] == 'R' && board[i][j+3] == 'R') return true;
        }
    }
    for(int j = 0; j < 5; j++){
        for(int i = 0; i < 1; i++){
            if(board[i][j] == 'R' && board[i+1][j] == 'R' && board[i+2][j] == 'R' && board[i+3][j] == 'R') return true;
        }
    }
    for(int i = 0; i < 1; i++){
        for(int j = 0; j < 2; j++){
            if(board[i][j] == 'R' && board[i+1][j+1] == 'R' && board[i+2][j+2] == 'R' && board[i+3][j+3] == 'R') return true;
        }
    }
    for(int i = 3; i > 2; i--){
        for(int j = 0; j < 2; j++){
            if(board[i][j] == 'R' && board[i-1][j+1] == 'R' && board[i-2][j+2] == 'R' && board[i-3][j+3] == 'R') return true;
        }
    }
    return false;
}

bool winY(){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 2; j++){
            if(board[i][j] == 'Y' && board[i][j+1] == 'Y' && board[i][j+2] == 'Y' && board[i][j+3] == 'Y') return true;
        }
    }
    for(int j = 0; j < 5; j++){
        for(int i = 0; i < 1; i++){
            if(board[i][j] == 'Y' && board[i+1][j] == 'Y' && board[i+2][j] == 'Y' && board[i+3][j] == 'Y') return true;
        }
    }
    for(int i = 0; i < 1; i++){
        for(int j = 0; j < 2; j++){
            if(board[i][j] == 'Y' && board[i+1][j+1] == 'Y' && board[i+2][j+2] == 'Y' && board[i+3][j+3] == 'Y') return true;
        }
    }
    for(int i = 3; i > 2; i--){
        for(int j = 0; j < 2; j++){
            if(board[i][j] == 'Y' && board[i-1][j+1] == 'Y' && board[i-2][j+2] == 'Y' && board[i-3][j+3] == 'Y') return true;
        }
    }
    return false;
}

void printBoard(){
    for(int i = 3; i >= 0; i--){
        for(int j = 0; j < 5; j++){
            cout << " " << board[i][j];
            if(j < 4) cout << " |";
        }
        cout << endl;
    }
}

int minimax(){
    if(winR()) return 1;
    if(winY()) return -1;
    if(full()) return 0;

    if(R){
        int best = -2;
        for(int c = 0; c < 5; c++){
            if(used[c] < 4){
                board[used[c]][c] = 'R';
                used[c]++;
                R = false;
                best = max(best, minimax());
                R = true;
                used[c]--;
                board[used[c]][c] = '.';
            }
        }
        return best;
    }
    else{
        int best = 2;
        for(int c = 0; c < 5; c++){
            if(used[c] < 4){
                board[used[c]][c] = 'Y';
                R = true;
                best = min(best, minimax());
                R = false;
                board[used[c]][c] = '.';
            }
        }
        return best;
    }
}

void computerMove(){
    int r, c;
    int bestValue = -2;
    for(int i = 0; i < 5; i++){
        if(used[i] < 4){
            board[used[i]][i] = 'R';
            int moveValue = minimax();
            board[used[i]][i] = '.';
            if(moveValue > bestValue){
                r = used[i];
                c = i;
                bestValue = moveValue;
            } 
        }
    }
    board[r][c] = 'R';
    R = false;
    printBoard();
    return;
}

void playerMove(){
    int r, c;
    cin >> c;
    c--;
    r = used[c];
    board[r][c] = 'Y';
    printBoard();
    used[c]++;
    R = true;
}

int main(){
    while(true){
        if(winR()){
            cout << "Red wins!" << endl;
            break;
        }
        if(winY()){
            cout << "Yellow wins!" << endl;
            break;
        }
        if(full()){
            cout << "It's a draw!" << endl;
            break;
        }
        if(R) computerMove();
        else playerMove();
    }
}
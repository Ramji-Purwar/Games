#include <bits/stdc++.h>
using namespace std;

char grid[3][3];
bool X = true;

void printGrid(){
    for(int r = 0; r < 3; r++){
        for(int c = 0; c < 3; c++){
            cout << ' ' << grid[r][c];
            if(c < 2) cout << " |";
        }
        cout << endl;
        if(r < 2) cout << "---+---+---\n";
    }
    cout << endl;
    return;
}

bool isFull(){
    for(int r = 0; r < 3; r++){
        for(int c = 0; c < 3; c++){
            if(grid[r][c] == '.')
                return false;
        }
    }
    return true;
}

bool win(char player){
    for(int r = 0; r < 3; r++){
        if(grid[r][0] == player && grid[r][1] == player && grid[r][2] == player)
            return true;
    }
    for(int c = 0; c < 3; c++){
        if(grid[0][c] == player && grid[1][c] == player && grid[2][c] == player)
            return true;
    }
    if(grid[0][0] == player && grid[1][1] == player && grid[2][2] == player)
        return true;
    if(grid[0][2] == player && grid[1][1] == player && grid[2][0] == player)
        return true;
    return false;
}

int func(int a, int b){
    if(win('X')) return 1;
    if(win('O')) return -1;
    if(isFull()) return 0;

    int alfa = a, beta = b;
    int score;

    if(X){
        score = -2;
        for(int x = 0; x < 9; x++){
            int r = x/3 , c = x%3;  
            if(grid[r][c] == '.'){
                grid[r][c] = 'X';
                X = false;
                int move = func(alfa, beta);
                score = max(score, move);
                alfa = max(alfa, score);
                grid[r][c] = '.';
                X = true;
                if(alfa >= beta) break;
            }
        }
    }
    else{
        score = 2;
        for(int x = 0; x < 9; x++){
            int r = x/3 , c = x%3;
            if(grid[r][c] == '.'){
                grid[r][c] = 'O';
                X = true;
                int move = func(alfa, beta);
                score = min(score, move);
                beta = min(beta, score);
                grid[r][c] = '.';
                X = false;
                if(alfa >= beta) break;
            }
        }
    }
    return score;
}

void computerMove(){
    int R = -1, C = -1;
    int best_score = -2;
    for(int x = 0; x < 9; x++){
        int r = x/3 , c = x%3;
        if(grid[r][c] == '.'){
            grid[r][c] = 'X';
            X = false;
            int move_score = func(-2, 2);
            if(move_score > best_score){
                best_score = move_score;
                R = r;
                C = c;
            }
            grid[r][c] = '.';
            X = true;
        }
    }
    grid[R][C] = 'X';
    X = false;
    printGrid();
}

void userMove(){
    int r, c;
    cin >> r >> c;
    grid[r][c] = 'O';
    X = true;
    printGrid();
}

int main(){
    for(int r = 0; r < 3; r++){
        for(int c = 0; c < 3; c++) grid[r][c] = '.';
    }
    printGrid();
    while(true){
        if(win('X')){
            cout << "Computer Wins\n";
            break;
        }
        if(win('O')){
            cout << "User Wins\n";
            break;
        }
        if(isFull()){
            cout << "Draw\n";
            break;
        }
        if(X) computerMove();
        else userMove();
    }
}
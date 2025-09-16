#include <bits/stdc++.h>
using namespace std;

char grid[4][5];
int used[5];
bool Y = false;

void printGrid(){
    for(int r = 3; r >= 0; r--){
        for(int c = 0; c < 5; c++){
            cout << ' ' << grid[r][c];
            if(c < 4) cout << " |";
            else cout << " \n";
        }
    }
    cout << endl;
}

bool isFull(){
    for(int &el : used){
        if(el < 4) return false; 
    }
    return true;
}

bool win(char X){
    for(int r = 0; r < 4; r++){
        if(grid[r][1] == X && grid[r][2] == X && grid[r][3] == X && (grid[r][0] == X || grid[r][4] == X)) 
            return true; 
    }

    for(int c = 0; c < 5; c++){
        if(grid[0][c] == X && grid[1][c] == X && grid[2][c] == X && grid[3][c] == X)
            return true;
    }

    if(grid[0][0] == X && grid[1][1] == X && grid[2][2] == X && grid[3][3] == X) return true;
    if(grid[0][1] == X && grid[1][2] == X && grid[2][3] == X && grid[3][4] == X) return true;

    if(grid[0][3] == X && grid[1][2] == X && grid[2][1] == X && grid[3][0] == X) return true;
    if(grid[0][4] == X && grid[1][3] == X && grid[2][2] == X && grid[3][1] == X) return true;

    return false;
}

int func(int a, int b){
    if(win('Y')) return 1;
    if(win('R')) return -1;
    if(isFull()) return 0;

    int alfa = a, beta = b;
    int score = Y ? -2 : 2;
    for(int c = 0; c < 5; c++){
        int r = used[c];
        if(r < 4){
            grid[r][c] = Y ? 'Y' : 'R'; used[c]++; Y = !Y;
            int move = func(alfa, beta);
            score = Y ? min(score, move) : max(score, move);
            if(Y) beta = min(beta, score);
            else alfa = max(alfa, score);
            grid[r][c] = '.'; used[c]--; Y = !Y;
            if(alfa >= beta) break;
        }
    }

    return score;
}

void computerMove(){
    int R = -1, C = -1;
    int bestScore = -2;
    for(int c = 0; c < 5; c++){
        int r = used[c];
        if(r < 4){
            grid[r][c] = 'Y'; used[c]++; Y = false;
            int moveScore = func(-2, 2);
            if(moveScore > bestScore){
                bestScore = moveScore;
                C = c;
                R = r;
            }
            grid[r][c] = '.'; used[c]--; Y = true;
        }
    }
    grid[R][C] = 'Y'; used[C]++; Y = false;
    printGrid();
}

void userMove(){
    int c; cin >> c;
    if(used[c] == 4 || c < 0 || c > 4) userMove();
    int r = used[c];
    grid[r][c] = 'R'; used[c]++; Y = true;
    printGrid();
}

int main(){
    for(int c = 0; c < 5; c++){
        used[c] = 0;
        for(int r = 0; r < 4; r++){
            grid[r][c] = '.';
        }
    }
    printGrid();
    while(true){
        if(win('Y')){
            cout << "Computer Wins\n";
            break;
        }
        if(win('R')){
            cout << "User Wins\n";
            break;
        }
        if(isFull()){
            cout << "Draw\n";
            break;
        }
        if(Y) computerMove();
        else userMove();
    }
}
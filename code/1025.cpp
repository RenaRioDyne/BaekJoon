#include <stdio.h>
#include <cmath>
#include <algorithm>

const int MAX_N = 9;

int matrix[MAX_N][MAX_N];

int N, M;

bool checkBoundary(int x, int y){
    return (x < N && x >= 0 && y < M && y >= 0);
}

bool checkSquare(int squareCandidate){
    int root = static_cast<int>(std::sqrt(squareCandidate));
    return root * root == squareCandidate;
}

// x, y : start square 
// xDir, yDir : direction
int getMaxSquare(int x, int y, int xDir, int yDir){
    int max = -1;
    int squareCandidate = 0;
    while(checkBoundary(x, y)){
        squareCandidate = squareCandidate * 10 + matrix[x][y];
        if(checkSquare(squareCandidate)){
            max = squareCandidate;
        }
        x += xDir;
        y += yDir;
    }

    return max;
}

int main(){
    scanf("%d %d", &N, &M);
    char digit;
    for(int n = 0; n < N; n++){
        for(int m = 0; m < M; m++){
            scanf(" %c", &digit);
            matrix[n][m] = digit - '0';
        }
    }

    int best = -1;
    int cur;

    for(int n = 0; n < N; n++){
        for(int m = 0; m < M; m++){
            for(int nDir = -N+1; nDir < N; nDir++){
                for(int mDir = -M+1; mDir < M; mDir++){
                    if(nDir == 0 && mDir == 0){
                        if(checkSquare(matrix[n][m])) cur = matrix[n][m];
                        else cur = -1;
                    }else{
                        cur = getMaxSquare(n, m, nDir, mDir);
                    }
                    //printf("%d %d %d %d %d\n", n, m, nDir, mDir, cur);
                    if(cur > best) std::swap(cur, best);
                    
                }
            }
        }
    }

    printf("%d", best);
}

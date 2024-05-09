#include <stdio.h>
#include <algorithm>

const int HARD_UPPER = 1000;
const int MAX_N = 12;
const int MAX_K = 10;

enum Color{
    WHITE,
    RED,
    BLUE,
};

class Piece;

class BoardElement{ // serves as head of linked list
public:
    int x;
    int y;
    int N;
    Color c;
    Piece* top;
};

BoardElement myBoard[MAX_N][MAX_N];

class Piece{
public:
    Piece* below;
    Piece* above;
    BoardElement* location;
    int vertical;
    int horizontal;
    int id;
    
    int move(){
        Piece* lowest = this;
        while(lowest->below != NULL){
            lowest = lowest->below;
        }
        location = lowest->location;
        
        bool changedDirection = false;
        int newX = location->x + vertical;
        int newY = location->y + horizontal;
        if(newX == location->N || newX < 0){
            vertical = -vertical;
            newX += 2 * vertical;
            changedDirection = true;
        }
        if(newY == location->N || newY < 0){
            horizontal = -horizontal;
            newY += 2 * horizontal;
            changedDirection = true;
        }

        BoardElement* newLocation = &myBoard[newX][newY];
        if(newLocation->c == BLUE){
            if(!changedDirection){
                vertical = -vertical;
                horizontal = -horizontal;
                newX += 2 * vertical;
                newY += 2 * horizontal;
            }else return 0;
            
            if(newX == location->N || newX < 0
            || newY == location->N || newY < 0
            || myBoard[newX][newY].c == BLUE){
                return 0;
            }
            newLocation = &myBoard[newX][newY];
        }
        printf("color %d loc %d %d\n", id,
        newLocation->c, newLocation->x, newLocation->y);
        printf("horiz %d vert %d \n", horizontal, vertical);

        
        Piece* prevTop = location->top;
        location->top = below;
        if(below != NULL) below->above = NULL;

        if(newLocation->c == RED){
            lowest = this;
            while(lowest->above != NULL){
                std::swap(lowest->above, lowest->below);
                lowest = lowest->below;
            }
            std::swap(lowest->above, lowest->below);
            lowest->location = newLocation;

            if(newLocation->top != NULL){
                newLocation->top->above = lowest;
                lowest->below = newLocation->top;
            }
            newLocation->top = this;
        }else{
            if(newLocation->top != NULL){
                newLocation->top->above = this;
                below = newLocation->top;
            }
            newLocation->top = prevTop;
        }

        printf("id %d location %d %d\n", id, newLocation->x,newLocation->y);

        int stack = 1;
        lowest = newLocation->top;
        while(lowest->below != NULL){
            lowest = lowest->below;
            stack++;
        }
        return stack;
    }
};

Piece myPieces[MAX_K];

void setup(int N, int K){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            int color;
            scanf("%d", &color);
            if(color == 0) myBoard[i][j].c = WHITE;
            if(color == 1) myBoard[i][j].c = RED;
            if(color == 2) myBoard[i][j].c = BLUE;
            myBoard[i][j].x = i;
            myBoard[i][j].y = j;
            myBoard[i][j].N = N;
        }
    }

    int x, y, d;
    for(int i=0; i<K; i++){
        scanf("%d %d %d", &x, &y, &d);
        x--;
        y--;
        myPieces[i].location = &myBoard[x][y];
        myPieces[i].location->top = &myPieces[i];
        myPieces[i].below = myPieces[i].above = NULL;
        myPieces[i].id = i;
        if(d == 1){
            myPieces[i].vertical = 0;
            myPieces[i].horizontal = 1;
        }
        if(d == 2){
            myPieces[i].vertical = 0;
            myPieces[i].horizontal =-1;
        }
        if(d == 3){
            myPieces[i].vertical = -1;
            myPieces[i].horizontal = 0;
        }
        if(d == 4){
            myPieces[i].vertical = 1;
            myPieces[i].horizontal = 0;
        }
    }
}

int main(){
    int N, K;
    scanf("%d %d", &N, &K);

    setup(N, K);

    for(int i=1; i<= HARD_UPPER; i++){
        for(int j=0; j<K; j++){
            if(myPieces[j].move() == N){
                printf("%d\n", i);
                return 0;
            }
        }
    }
    printf("-1\n");
}
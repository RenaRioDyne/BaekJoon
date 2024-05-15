#include <stdio.h>
#include <vector>

const int maxSide = 1255;

char playground[maxSide][maxSide];

bool boundaryCheck(int side, int row, int col){
    return row <= side && col <= side && row > 0 && col > 0;
}

enum Rotation{
    CLOCKWISE,
    COUNTERCLOCKWISE,
};

enum Direction{
    UP,
    RIGHT,
    DOWN,
    LEFT,
};

Direction next(Direction d, Rotation r){
    switch(r){
        case CLOCKWISE: 
            switch(d){
                case UP:
                    return RIGHT;
                case RIGHT:
                    return DOWN;
                case DOWN:
                    return LEFT;
                case LEFT:
                    return UP;
                default:
                    printf("error in next function");
            }
        case COUNTERCLOCKWISE:
            switch(d){
                case UP:
                    return LEFT;
                case RIGHT:
                    return UP;
                case DOWN:
                    return RIGHT;
                case LEFT:
                    return DOWN;
                default:
                    printf("error in next function");
            }
        default:
            printf("error in next function");
            return UP;
    }
}

void printType(Direction d, Rotation r){
    switch(r){
        case CLOCKWISE:
            switch(d){
                case UP:
                    printf("UL");
                    return;
                case RIGHT:
                    printf("RU");
                    return;
                case DOWN:
                    printf("DR");
                    return;
                case LEFT:
                    printf("LD");
                    return;
                default:
                    printf("error in printType function");
                    return;
            }
        case COUNTERCLOCKWISE:
            switch(d){
                case UP:
                    printf("UR");
                    return;
                case RIGHT:
                    printf("RD");
                    return;
                case DOWN:
                    printf("DL");
                    return;
                case LEFT:
                    printf("LU");
                    return;
                default:
                    printf("error in printType function");
                    return;
            }
        default:
            printf("error in printType function");
            return;
    }
}

struct Coords{
    int row;
    int col;
    Direction d;
    Rotation r;
};

int main(){
    int N;
    std::vector<Coords> center;
    Coords cur;

    scanf("%d", &N);
    for(int row = 1; row <= N; row++){
        for(int col = 1; col <= N; col++){
            scanf(" %c", &playground[row][col]);
        }
    }

    // find centers
    for(int row = N-2; row >= 3; row--){
        for(int col = N-2; col >= 3; col--){
            if(playground[row][col] == '#'){
                if(playground[row+1][col] == '#'){
                    if(playground[row-1][col] == '.' &&
                       playground[row][col+1] == '.' &&
                       playground[row][col-1] == '.' &&
                       (!boundaryCheck(N, row+3, col) || playground[row+3][col] == '.')){
                        cur.d = DOWN;
                        if(playground[row+2][col+1] == '#') cur.r = COUNTERCLOCKWISE;
                        else cur.r = CLOCKWISE;
                    } else continue;
                } else if (playground[row-1][col] == '#'){
                    if(playground[row][col+1] == '.' &&
                       playground[row][col-1] == '.' &&
                       (!boundaryCheck(N, row-3, col) || playground[row-3][col] == '.')){
                        cur.d = UP;
                        if(playground[row-2][col-1] == '#') cur.r = COUNTERCLOCKWISE;
                        else cur.r = CLOCKWISE;
                    } else continue;
                } else if (playground[row][col+1] == '#'){
                    if(playground[row][col-1] == '.' &&
                       (!boundaryCheck(N, row, col+3) || playground[row][col+3] == '.')){
                        cur.d = RIGHT;
                        if(playground[row-1][col+2] == '#') cur.r = COUNTERCLOCKWISE;
                        else cur.r = CLOCKWISE;
                    } else continue;
                } else if (playground[row][col-1] == '#'){
                    if(!boundaryCheck(N, row, col-3) || playground[row][col-3] == '.'){
                        cur.d = LEFT;
                        if(playground[row+1][col-2] == '#') cur.r = COUNTERCLOCKWISE;
                        else cur.r = CLOCKWISE;
                    } else continue;
                } else continue;
                
                cur.row = row;
                cur.col = col;

                center.push_back(cur);
            }
        }
    }

    printf("%lu\n", center.size());

    // find sizes
    for(; center.size() > 0; center.pop_back()){
        cur = center.back();
        int length = 3;
        bool flag = false;

        printf("%d %d ", cur.row, cur.col);

        while(true){
            switch(cur.d){
                case UP:
                    cur.row -= (length-2);
                    break;
                case RIGHT:
                    cur.col += (length-2);
                    break;
                case DOWN:
                    cur.row += (length-2);
                    break;
                case LEFT:
                    cur.col -= (length-2);
                    break;
                default:
                    printf("bug in while-true loop");
                    break;
            }
            if(boundaryCheck(N, cur.row, cur.col) && playground[cur.row][cur.col] == '#'){
                switch(cur.d){
                    case UP:
                        cur.row -= 1;
                        break;
                    case RIGHT:
                        cur.col += 1;
                        break;
                    case DOWN:
                        cur.row += 1;
                        break;
                    case LEFT:
                        cur.col -= 1;
                        break;
                    default:
                        printf("bug in while-true loop");
                        break;
                }
                cur.d = next(cur.d, cur.r);
                if(flag){
                    flag = false;
                    length += 2;
                } else flag = true;
            } else {
                printf("%d ", length-2);
                break;
            }
        }
        printType(cur.d, cur.r);
        
        printf("\n");
    }
}
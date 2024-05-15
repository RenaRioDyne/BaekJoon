#include <stdio.h>
#include <algorithm>

const int MAX_N = 55;

struct MapItem {
    int massSum;
    int speedSum;
    int numFireBalls;
    bool odd, even;
};

MapItem grid[MAX_N][MAX_N];

const MapItem BLANK = {0, 0, 0, false, false};

void clear_grid(){
    for(int i = 0; i < MAX_N; i++){
        for(int j = 0; j < MAX_N; j++){
            grid[i][j] = BLANK;
        }
    }
}

struct FireBall {
    int row, col;
    int mass;
    int speed;
    int direction;
};

FireBall buffer[MAX_N * MAX_N * 10];

void move(FireBall* fireball, int N){
    int x, y;
    if(fireball->direction == 1 || fireball->direction == 2 || fireball->direction == 3){
        x = 1;
    }else if(fireball->direction == 5 || fireball->direction == 6 || fireball->direction == 7){
        x = -1;
    }else{
        x = 0;
    }

    if(fireball->direction == 3 || fireball->direction == 4 || fireball->direction == 5){
        y = 1;
    }else if(fireball->direction == 7 || fireball->direction == 0 || fireball->direction == 1){
        y = -1;
    }else{
        y = 0;
    }

    fireball->col += x * fireball->speed;
    fireball->row += y * fireball->speed;

    fireball->col = (fireball->col + N * 250) % N;
    fireball->row = (fireball->row + N * 250) % N;

    grid[fireball->row][fireball->col].numFireBalls++;
    grid[fireball->row][fireball->col].massSum += fireball->mass;
    grid[fireball->row][fireball->col].speedSum += fireball->speed;
    if(fireball->direction % 2 == 0){
        grid[fireball->row][fireball->col].even = true;
    }else grid[fireball->row][fireball->col].odd = true;
}

int main(){
    int N, M, K;
    scanf("%d %d %d", &N, &M, &K);

    FireBall* cur_buffer = buffer;
    FireBall* prev_buffer = buffer + MAX_N * MAX_N * 5;

    for(int i = 0; i < M; i++){
        scanf("%d %d %d %d %d",
            &cur_buffer[i].row,
            &cur_buffer[i].col,
            &cur_buffer[i].mass,
            &cur_buffer[i].speed,
            &cur_buffer[i].direction);
        cur_buffer[i].row--;
        cur_buffer[i].col--;
    }

    int cur_items = M;
    int prev_items = 0;

    FireBall palette = {0, 0, 0, 0, 0};

    for(int moves = 0; moves < K; moves++){
        clear_grid();
        std::swap(cur_buffer, prev_buffer);
        prev_items = cur_items;
        cur_items = 0;
        
        for(int items = 0; items < prev_items; items++){
            move(prev_buffer + items, N);
        }

        for(int items = 0; items < prev_items; items++){
            MapItem* coord = &grid[prev_buffer[items].row][prev_buffer[items].col];
            if(coord->massSum != prev_buffer[items].mass){
                // 2+ fireballs at this coord
                if(coord->odd || coord->even){
                    // first time checking this coord
                    palette.mass = coord->massSum / 5;
                    if(palette.mass == 0) continue;

                    palette.row = prev_buffer[items].row;
                    palette.col = prev_buffer[items].col;
                    palette.speed = coord->speedSum / coord->numFireBalls;

                    if(coord->odd && coord->even){
                        palette.direction = 1;
                    }else palette.direction = 0;

                    for(int dir = 0; dir < 4; dir++){
                        cur_buffer[cur_items] = palette;
                        cur_items++;
                        palette.direction += 2;
                    }

                    // prevents entering this condition again
                    coord->odd = false;
                    coord->even = false;
                }
            }else{
                // 1 fireball at this coord
                cur_buffer[cur_items] = prev_buffer[items];
                cur_items++;
            }
        }
    }

    int mass_sum = 0;
    for(int items = 0; items < cur_items; items++){
        // printf("%d %d %d %d %d\n", cur_buffer[items].row + 1, cur_buffer[items].col + 1, cur_buffer[items].mass, cur_buffer[items].speed, cur_buffer[items].direction);
        mass_sum += cur_buffer[items].mass;
    }

    printf("%d", mass_sum);
}
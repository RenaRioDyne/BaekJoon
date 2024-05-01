#include <stdio.h>
#include <algorithm>

const int MAX_MN = 10;
int classroom[MAX_MN];

const int MAX_ROW_TYPES = 1024; // 2^MAX_MN
int best[MAX_ROW_TYPES * 2]; // buffers

const int IMPOSSIBLE_VAL = -10;

void clear_buffers(){
    for(int i=0; i<MAX_ROW_TYPES * 2; i++){
        best[i] = 0;
    }
}

int count_seats(int row){
    int seats = 0;
    while(row != 0){
        if(row & 1) seats++;
        row = row >> 1;
    }
    return seats;
}

bool is_valid_row(int row, int rownum){
    return ((row & (row << 1)) == 0) && ((row & classroom[rownum]) == 0);
}

bool are_compatible(int prev_row, int cur_row){
    return ((cur_row << 1 | cur_row >> 1) & prev_row) == 0;
}

void test(){
    int N, M;
    scanf("%d %d", &N, &M);

    for(int n=0; n<N; n++){
        int row = 0;
        char seat;
        for(int m=0; m<M; m++){
            row = row << 1;

            scanf(" %c", &seat);
            if(seat == 'x'){
                row |= 1;
            }
        }

        classroom[n] = row;
    }

    int* best_prev = best;
    int* best_cur = best + MAX_ROW_TYPES;
    clear_buffers();

    for(int rownum = 0; rownum < N; rownum++){
        std::swap(best_prev, best_cur);
        for(int cur_combination = 0; cur_combination < (1 << M); cur_combination++){
            if(is_valid_row(cur_combination, rownum)){
                if(rownum != 0){
                    for(int prev_combination = 0; prev_combination < (1 << M); prev_combination++){
                        if(are_compatible(prev_combination, cur_combination)){
                            best_cur[cur_combination] = std::max(best_cur[cur_combination], best_prev[prev_combination]);
                        }
                    }
                }
                best_cur[cur_combination] += count_seats(cur_combination);
            } else best_cur[cur_combination] = IMPOSSIBLE_VAL;
        }
    }

    int ans = 0;
    for(int combination = 0; combination < (1 << M); combination++){
        ans = std::max(ans, best_cur[combination]);
    }

    printf("%d\n", ans);
}

int main(){
    int C;
    scanf("%d", &C);

    for(int cases=0; cases<C; cases++){
        test();
    }
}
#include <stdio.h>

const int MAX_NUM = 100005;

int vals[MAX_NUM];

int main(){
    int N;
    int cur;

    for(int i=0; i<MAX_NUM; i++){
        vals[i] = 0;
    }

    scanf("%d", &N);

    for(int n=0; n<N; n++){
        scanf("%d", &cur);
        vals[cur]++;
    }

    
}
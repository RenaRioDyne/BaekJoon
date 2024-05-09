#include <stdio.h>

const int MAX_NUM = 100005;

int vals[MAX_NUM];
int toLeft[MAX_NUM];
int toRight[MAX_NUM];

bool startAt(int start, int min, int max){
    bool flag = true;
    toRight[min-1] = 0;
    toLeft[min] = 0;

    for(int i=min; i<=max; i++){
        int inEdge = vals[i] - toRight[i-1];
        if(i == start) inEdge--;
        if(inEdge < 0) {
            if(inEdge == -1 && flag){
                flag = false;
                inEdge = 0;
                toRight[i-1]--;
            }
            else return false;
        }

        toLeft[i+1] = inEdge;

        toRight[i] = vals[i] - toLeft[i];
        if(toRight[i] < 0) return false;
    }

    return toLeft[max+1] == 0;
}

void printCards(int cur, int N){

    for(int i=0; i<N; i++){
        printf("%d ",cur);
        if(toLeft[cur] > 0){
            toLeft[cur]--;
            cur--;
        }else{
            toRight[cur]--;
            cur++;
        }
    }
}

int main(){
    int N;
    int cur;

    for(int i=0; i<MAX_NUM; i++){
        vals[i] = 0;
    }

    scanf("%d", &N);

    int min = MAX_NUM;
    int max = -1;

    for(int n=0; n<N; n++){
        scanf("%d", &cur);
        vals[cur]++;
        if(cur < min) min = cur;
        if(cur > max) max = cur;
    }
    
    if(startAt(min, min, max)){
        printCards(min, N);
    }else if(min+1 <= max && startAt(min+1, min, max)){
        printCards(min+1, N);
    }else printf("-1\n");
    return 0;
}
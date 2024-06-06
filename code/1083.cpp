#include <stdio.h>
#include <algorithm>

const int MAX_NUM_VALUES = 55;
int input[MAX_NUM_VALUES];

int cost(int* arr, int length){
    int max = arr[0];
    int maxIdx = 0;
    for(int i=1; i<length; i++){
        if(max < arr[i]) {
            max = arr[i];
            maxIdx = i;
        }
    }
    for(int i=maxIdx-1; i>=0; i--){
        std::swap(arr[i+1], arr[i]);
    }
    return maxIdx;
}

int main(){
    int N, S;
    scanf("%d", &N);
    for(int i=0; i<N; i++){
        scanf("%d", input+i);
    }
    scanf("%d", &S);

    for(int i=0; i<N; i++){
        int budget = std::min(N - i, S + 1);
        if(budget <= 0) break;
        int c = cost(input + i, budget);
        S -= c;
    }

    for(int i=0; i<N; i++){
        printf("%d ", input[i]);
    }
    printf("\n");
}
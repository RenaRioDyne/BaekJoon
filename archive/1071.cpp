#include <stdio.h>
#include <algorithm>

const int MAX_VALUE = 1001;
int input[MAX_VALUE];

int main(){
    for(int i=0; i<MAX_VALUE; i++){
        input[i] = 0;
    }

    int N;
    scanf("%d", &N);

    int cur;
    int min = MAX_VALUE;
    int max = -1;
    int diffVal = 0;
    for(int i=0; i<N; i++){
        scanf("%d", &cur);
        if(input[cur] == 0) diffVal++;
        input[cur]++;
        if(min > cur) min = cur;
        if(max < cur) max = cur;
    }

    if(diffVal == 2 && min + 1 == max){
        for(int i=0; i<input[max]; i++){
            printf("%d ", max);
        }
        for(int i=0; i<input[min]; i++){
            printf("%d ", min);
        }
        printf("\n");
        return 0;
    }

    cur = min;
    int skipped = -1;
    while(cur < MAX_VALUE){
        for(int i=0; i<input[cur];){
            printf("%d ", cur);
            input[cur]--;
            if(skipped >= 0 && skipped != max - 1) break;
        }
        if(skipped >= 0){
            cur = skipped;
            skipped = -1;
        }
        else{
            if(cur != max && input[cur + 1] > 0) skipped = cur + 1;
            cur += 2;
            while(cur < max && input[cur] == 0) cur++;
            if(cur + 1 == max && skipped < 0){
                skipped = cur;
                cur++;
            }
        }
    }
}
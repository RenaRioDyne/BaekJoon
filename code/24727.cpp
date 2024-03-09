#include <stdio.h>

int injiyoong[105][105];

void printInjiyoong(int N){
    for(int i=0; i<N*N; i++){
        printf("%d", injiyoong[i/N][i%N]);
        if(i%N == N-1) printf("\n");
    }
}

int main(){
    int N, C, E;
    
    scanf("%d", &N);
    scanf("%d %d", &C, &E);

    if(N*N < C + E){
        printf("-1\n");
        return 0;
    }

    int margin = N * N - C - E;
    if(margin >= N){
        for(int i=0; i<N*N; i++){
            if(i < C){
                injiyoong[i/N][i%N] = 1;
            }else if(i < N * N - E){
                injiyoong[i/N][i%N] = 0;
            }else{
                injiyoong[i/N][i%N] = 2;
            }
        }
    }else{
        int max = (C < E ? E : C);
        int min = (C < E ? C : E);

        if((N - margin) * (N + margin) + min > max){
            printf("-1\n");
            return 0;
        }

        int maxCollege = 1;
        int minCollege = 2;

        if(max == E){
            maxCollege = 2;
            minCollege = 1;
        }

        for(int i=0; i<N*N; i++){
            injiyoong[i/N][i%N] = maxCollege;
        }

        int painted = 0;
        int barricade = 0;
        for(int i=0; i < margin; i++){
            int j;
            for(j=0; j < margin - 1 - i; j++){
                if(painted >= min) break;
                if(injiyoong[i][j] == 0) barricade--;
                injiyoong[i][j] = minCollege;
                painted++;
                injiyoong[i+1][j] = 0;
                barricade++;
            }
            if(injiyoong[i][j] != 0 && barricade < margin){
                injiyoong[i][j] = 0;
                barricade++;
            }
        }
    }
    printf("1\n");
    printInjiyoong(N);
    return 0;
}
#include <stdio.h>

const int MAX_ROLL = 12;
const int MAX_BOWLS = 100;

struct FishBowl {
    int numFish;
    FishBowl* rollAdjacent[4];
    int numRollAdjacent;
    FishBowl* sandAdjacent[4];
    int numSandAdjacent;
    int diff;
    int id;
};

FishBowl fishBowls[MAX_BOWLS * 2];
FishBowl* rollFishBowls[MAX_ROLL][MAX_ROLL];
FishBowl* sandFishBowls[MAX_BOWLS / 4][4];

void printStatus(int numFishBowls){
    for(int i=0; i<numFishBowls; i++){
        printf("%d %d %d %d\n",
        fishBowls[i].id,
        fishBowls[i].numRollAdjacent,
        fishBowls[i].numSandAdjacent,
        fishBowls[i].numFish);
    }
    /*
    for(int i=0; i<MAX_ROLL; i++){
        for(int j=0; j<MAX_ROLL; j++){
            if(rollFishBowls[i][j] != NULL){
                printf("%d %d %d %d %d %d\n", i, j,
                rollFishBowls[i][j]->id,
                rollFishBowls[i][j]->numRollAdjacent,
                rollFishBowls[i][j]->numSandAdjacent,
                rollFishBowls[i][j]->numFish);
            }
        }
    }
    */
    printf("end of status check\n");
}

void replenish(int numFishBowls){
    int min = 11111;
    for(int i=0; i<numFishBowls; i++){
        if(min > fishBowls[i].numFish) min = fishBowls[i].numFish;
    }

    for(int i=0; i<numFishBowls; i++){
        if(fishBowls[i].numFish == min) fishBowls[i].numFish++;
    }
}

void reorderFromRoll(int numFishBowls){
    int N, M;
    for(N=1; N<MAX_ROLL; N++){
        if(numFishBowls < (N+1) * (N+1)) break;
    }
    M = N;
    if(numFishBowls >= N * (N+1)) M++;

    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            if(rollFishBowls[i+1][j+1] == NULL){
                printf("bad output in reorderFromRoll()\n");
            }

            fishBowls[i*M+j+MAX_BOWLS].numFish = rollFishBowls[i+1][j+1]->numFish;
        }
    }

    for(int i=0; i<N*M; i++){
        fishBowls[i].numFish = fishBowls[i+MAX_BOWLS].numFish;
    }
}

void reorderFromSandwich(int N){ // N is the length of the sandwich
    for(int i=0; i<N; i++){
        for(int j=0; j<4; j++){
            fishBowls[i*4+j+MAX_BOWLS].numFish = sandFishBowls[i][j]->numFish;
        }
    }

    for(int i=0; i<N*4; i++){
        fishBowls[i].numFish = fishBowls[i+MAX_BOWLS].numFish;
    }
}

void makeRoll(int numFishBowls){
    int N, M;
    for(N=1; N<MAX_ROLL; N++){
        if(numFishBowls < (N+1) * (N+1)) break;
    }
    M = N;
    if(numFishBowls >= N * (N+1)) M++;

    for(int n=0; n<MAX_ROLL; n++){
        for(int m=0; m<MAX_ROLL; m++){
            rollFishBowls[n][m] = NULL;
        }
    }

    FishBowl temp;
    FishBowl* tempptr = &temp;

    for(int i=0; i<N+2; i++){
        for(int j=0; j<M+2; j++){
            if(i>0 && j>0 && i < N+1 && j < M+1){
                rollFishBowls[i][j] = tempptr;
            } 
        }
    }

    for(int i=0; i<numFishBowls; i++){
        fishBowls[i].numRollAdjacent = 0;
    }

    int n = N;
    int m = 1;

    int ndiff = -1;
    int mdiff = 0;

    for(int cur = N * M - 1; cur >= 0; cur--){
        if(rollFishBowls[n][m] != tempptr){
            // wrong way; counterclockwise turn
            n -= ndiff;
            m -= mdiff;
            if(ndiff == -1){
                mdiff = 1;
                ndiff = 0;
            }else if(ndiff == 1){
                mdiff = -1;
                ndiff = 0;
            }else if(mdiff == -1){
                ndiff = -1;
                mdiff = 0;
            }else if(mdiff == 1){
                ndiff = 1;
                mdiff = 0;
            }
            n += ndiff;
            m += mdiff;
        }
        rollFishBowls[n][m] = fishBowls + cur;
        n += ndiff;
        m += mdiff;
    }

    for(int n = 1; n <= N; n++){
        for(int m = 1; m <= M; m++){
            if(n != N){
                rollFishBowls[n][m]->rollAdjacent[rollFishBowls[n][m]->numRollAdjacent] = rollFishBowls[n+1][m];
                rollFishBowls[n][m]->numRollAdjacent++;
            }
            if(n != 1){
                rollFishBowls[n][m]->rollAdjacent[rollFishBowls[n][m]->numRollAdjacent] = rollFishBowls[n-1][m];
                rollFishBowls[n][m]->numRollAdjacent++;
            }
            if(m != M){
                rollFishBowls[n][m]->rollAdjacent[rollFishBowls[n][m]->numRollAdjacent] = rollFishBowls[n][m+1];
                rollFishBowls[n][m]->numRollAdjacent++;
            }
            if(m != 1){
                rollFishBowls[n][m]->rollAdjacent[rollFishBowls[n][m]->numRollAdjacent] = rollFishBowls[n][m-1];
                rollFishBowls[n][m]->numRollAdjacent++;
            }
        }
    }

    for(int cur = N * M; cur < numFishBowls; cur++){
        fishBowls[cur].rollAdjacent[fishBowls[cur].numRollAdjacent] = fishBowls + cur - 1;
        fishBowls[cur].numRollAdjacent++;
        
        fishBowls[cur-1].rollAdjacent[fishBowls[cur-1].numRollAdjacent] = fishBowls + cur;
        fishBowls[cur-1].numRollAdjacent++;
    }
}

void makeSand(int numFishBowls){
    int cur = 0;
    for(int i=numFishBowls / 4 - 1; i >= 0; i--){
        sandFishBowls[i][1] = fishBowls + cur;
        cur++;
    }
    for(int i=0; i<numFishBowls / 4; i++){
        sandFishBowls[i][2] = fishBowls + cur;
        cur++;
    }
    for(int i=numFishBowls / 4 - 1; i >= 0; i--){
        sandFishBowls[i][3] = fishBowls + cur;
        cur++;
    }
    for(int i=0; i<numFishBowls / 4; i++){
        sandFishBowls[i][0] = fishBowls + cur;
        cur++;
    }
    
    for(int i=0; i<numFishBowls; i++){
        fishBowls[i].numSandAdjacent = 0;
    }

    for(int i=0; i<numFishBowls / 4; i++){
        for(int j=0; j<4; j++){
            if(j != 0){
                sandFishBowls[i][j]->sandAdjacent[sandFishBowls[i][j]->numSandAdjacent] = sandFishBowls[i][j-1];
                sandFishBowls[i][j]->numSandAdjacent++;
            }
            if(j != 3){
                sandFishBowls[i][j]->sandAdjacent[sandFishBowls[i][j]->numSandAdjacent] = sandFishBowls[i][j+1];
                sandFishBowls[i][j]->numSandAdjacent++;
            }
            if(i != 0){
                sandFishBowls[i][j]->sandAdjacent[sandFishBowls[i][j]->numSandAdjacent] = sandFishBowls[i-1][j];
                sandFishBowls[i][j]->numSandAdjacent++;
            }
            if(i != numFishBowls / 4 - 1){
                sandFishBowls[i][j]->sandAdjacent[sandFishBowls[i][j]->numSandAdjacent] = sandFishBowls[i+1][j];
                sandFishBowls[i][j]->numSandAdjacent++;
            }
        }
    }
}

void propagate(int numFishBowls, bool forRoll){
    for(int i=0; i<numFishBowls; i++){
        fishBowls[i].diff = 0;
    }

    for(int i=0; i<numFishBowls; i++){
        if(forRoll){
            for(int j=0; j<fishBowls[i].numRollAdjacent; j++){
                int diff = fishBowls[i].numFish - fishBowls[i].rollAdjacent[j]->numFish;
                fishBowls[i].diff -= diff / 5;
                fishBowls[i].rollAdjacent[j]->diff += diff / 5;
            }
        }else{
            for(int j=0; j<fishBowls[i].numSandAdjacent; j++){
                int diff = fishBowls[i].numFish - fishBowls[i].sandAdjacent[j]->numFish;
                fishBowls[i].diff -= diff / 5;
                fishBowls[i].sandAdjacent[j]->diff += diff / 5;
                /*
                printf("%d from %d(%d) to %d(%d):\n", diff/5,
                fishBowls[i].id, fishBowls[i].numFish,
                fishBowls[i].sandAdjacent[j]->id,
                fishBowls[i].sandAdjacent[j]->numFish);
                */
            }
        }
    }

    for(int i=0; i<numFishBowls; i++){
        fishBowls[i].numFish += fishBowls[i].diff / 2;
    }
}

int difference(int numFishBowls){
    int min = 11111;
    int max = -1;
    for(int i=0; i<numFishBowls; i++){
        if(fishBowls[i].numFish < min) min = fishBowls[i].numFish;
        if(fishBowls[i].numFish > max) max = fishBowls[i].numFish;
    }

    return max - min;
}

int main(){
    int N, K;

    scanf("%d %d", &N, &K);
    for(int n=0; n<N; n++){
        scanf("%d", &fishBowls[n].numFish);
        fishBowls[n].id = n;
    }

    makeRoll(N);

    makeSand(N);

    int numIters = 0;

    while(difference(N) > K){
        replenish(N);
        //printStatus(N);
        propagate(N,true);
        reorderFromRoll(N);
        //printf("middle of iteration #%d\n", numIters);
        //printStatus(N);
        propagate(N,false);
        reorderFromSandwich(N/4);
        numIters++;
        //printf("iteration #%d done\n",numIters);
        //printStatus(N);
    }

    printf("%d", numIters);
}

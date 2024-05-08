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
};

FishBowl fishBowls[MAX_BOWLS * 2];
FishBowl* rollFishBowls[MAX_ROLL][MAX_ROLL];
FishBowl* sandFishBowls[MAX_BOWLS / 4][4];

void reorderFromRoll(int N, int M){ // N, M is the length of each side of the roll
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            if(rollFishBowls[i+1][j+1] != NULL){
                printf("bad output in reorderFromRoll()");
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

void makeRoll(int N){ // N is the number of fishbowls

}

void makeSand(int N){ // N is the number of fishbowls

}

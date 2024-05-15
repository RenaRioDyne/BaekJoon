#include <stdio.h>
#include <algorithm>

struct Cartesian{
    int x;
    int y;
    int opt;
    int clockwiseIdx;
    int counterClockwiseIdx;
};

class MaxSegTree{
public:
    int* segTree;
    int size;

    MaxSegTree(int size){
        int shift = 0;
        while(size > 0){
            shift++;
            size = size/2;
        }
        this->size = 1 << shift;
        segTree = new int[2 * this->size]{};
    }

    ~MaxSegTree(){
        delete [] segTree;
    }

    void incrementValue(int index, int value){
        if(value < segTree[index + size]) printf("Not incrementing in incrementValue() function!");
        int cur = index + size;
        while(cur > 0 && value > segTree[cur]){
            segTree[cur] = value;
            cur = cur / 2;
        }
    }

    int returnUpperMax(int from){
        if(from == 0) return segTree[1];
        int cur = from + size;
        int max = segTree[cur];
        while(cur > 1){
            if(cur % 2 == 0 && max < segTree[cur + 1]) max = segTree[cur + 1];
            cur = cur / 2;
        }
        return max;
    }
    
    int returnLowerMax(int to){
        if(to == size) return segTree[1];
        int cur = to + size - 1;
        int max = segTree[cur];
        while(cur > 1){
            if(cur % 2 == 1 && max < segTree[cur - 1]) max = segTree[cur - 1];
            cur = cur / 2;
        }
        return max;
    }

    void printAll(){
        for(int i=0; i<2 * size; i++){
            printf("%d ", segTree[i]);
        }
        printf("\n");
    }
};

Cartesian coordinates[500000];
Cartesian* counterClockwise[500000];
Cartesian* clockwise[500000];
Cartesian* sortByY[500000];

int main(){
    int N, Q;
    scanf("%d", &N);
    scanf("%d", &Q);
    int start;

    for(int n=0; n<N; n++){
        scanf("%d %d", &coordinates[n].x, &coordinates[n].y);
        coordinates[n].opt = -1;
        sortByY[n] = clockwise[n] = counterClockwise[n] = coordinates + n;
    }

    std::sort(clockwise, clockwise + N, [](Cartesian* a, Cartesian* b)
                                        {
                                            if((a->y + a->x) == (b->y + b->x)){
                                                return a->y < b->y;
                                            }
                                            else return (a->y + a->x) > (b->y + b->x);
                                        });

    std::sort(counterClockwise, counterClockwise + N, [](Cartesian* a, Cartesian* b)
                                                        {
                                                            if((a->y - a->x) == (b->y - b->x)){
                                                                return a->y < b->y;
                                                            }
                                                            else return (a->y - a->x) > (b->y - b->x);
                                                        });

    std::sort(sortByY, sortByY + N, [](Cartesian* a, Cartesian* b)
                                    {
                                        return a->y < b->y;
                                    });

    for(int n=0; n<N; n++){
        counterClockwise[n]->counterClockwiseIdx = n;
        clockwise[n]->clockwiseIdx = n;
    }

    MaxSegTree counterClockwiseSegTree(N);
    MaxSegTree clockwiseSegTree(N);

    for(int n=0; n<N; n++){
        int max1 = counterClockwiseSegTree.returnLowerMax(sortByY[n]->counterClockwiseIdx);
        int max2 = clockwiseSegTree.returnLowerMax(sortByY[n]->clockwiseIdx);
        if(max1 < max2) max1 = max2;
        sortByY[n]->opt = max1 + 1;
        
/*
        printf("-----------------\n");
        printf("item coords: (%d, %d)\n", sortByY[n]->x, sortByY[n]->y);
        printf("item opt: %d\n", sortByY[n]->opt);
        printf("item clockwise order: %d\n", sortByY[n]->clockwiseIdx);
        printf("item counterclockwise order: %d\n", sortByY[n]->counterClockwiseIdx);
*/
        
        counterClockwiseSegTree.incrementValue(sortByY[n]->counterClockwiseIdx, max1 + 1);
        clockwiseSegTree.incrementValue(sortByY[n]->clockwiseIdx, max1 + 1);
    }

/*
    // for debugging
    printf("-----------------\n");
    printf("optimal values: ");
    for(int i=0; i<N; i++){
        printf("%d ", coordinates[i].opt);
    }
    printf("\ncounterclockwise segtree: ");
    counterClockwiseSegTree.printAll();
    printf("clockwise segtree: ");
    clockwiseSegTree.printAll();
    printf("-----------------\n");
*/

    for(int q=0; q<Q; q++){
        scanf("%d", &start);
        printf("%d\n", coordinates[start - 1].opt);
    }
}
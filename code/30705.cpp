#include <stdio.h>

const int MAX_BUILDINGS = 500005;

struct interval{
    int min;
    int max;
};

class UnionFind{
public:
    interval buildings[MAX_BUILDINGS];

    UnionFind(){
        for(int i=0; i<MAX_BUILDINGS; i++){
            buildings[i].min = buildings[i].max = i;
        }
    }

    int findMin(int query){
        int cur = query;
        // find root
        while(buildings[cur].min != cur){
            cur = buildings[cur].min;
        }

        // path compression
        int temp;
        while(query != cur){
            temp = buildings[query].min;
            buildings[query].min = cur;
            query = temp;
        }

        return cur;
    }

    int intervalUnion(int min, int max){
        int i = min;
        int root = findMin(i);
        int newParasol = 0;

        while(i <= max){
            int newRoot = findMin(i);
            if(root != newRoot){
                buildings[newRoot].min = root;
                buildings[root].max = buildings[newRoot].max;
                newParasol++;
            }

            i = buildings[root].max;

            i++;
        }

        return newParasol;
    }
};

UnionFind buildings;

int main(){
    int N, M;
    int A, B;
    int discount = 0;
    int prepare = 0;

    scanf("%d %d", &N, &M);
    for(int m=0; m<M; m++){
        discount++; // you have one parasol each day

        scanf("%d %d", &A, &B);
        int diff = buildings.intervalUnion(A, B); // # more parasols you need today

        if(discount >= diff){
            discount -= diff;
        }else{
            diff -= discount;
            discount = 0;
            prepare += diff;
        }
    }

    printf("%d\n", prepare);
}
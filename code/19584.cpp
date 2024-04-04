#include <stdio.h>
#include <algorithm>

const int numCoords = 200005;

struct Coords{
    int y;
    int index;
};

Coords coords[numCoords];
int order[numCoords];
long long diff[numCoords];

int main(){
    int N, M;

    int trash;

    scanf("%d %d",&N, &M);
    for(int i=0; i<N; i++){
        scanf("%d %d", &trash, &((coords+i)->y));
        coords[i].index = i+1;
        diff[i] = 0;
    }

    std::sort(coords, coords + N, [](const Coords &a, const Coords &b){ return a.y < b.y; });

    int prev = 1000000001;
    int prevOrder = -1;
    for(int i=0; i<N; i++){
        if(coords[i].y == prev) order[coords[i].index] = prevOrder;
        else{
            order[coords[i].index] = i;
            prev = coords[i].y;
            prevOrder = i;
        }
    }

    int u, v, c;

    for(int i=0; i<M; i++){
        scanf("%d %d %d", &u, &v, &c);
        if(order[u] > order[v]) std::swap(u, v);
        diff[order[u]] += c;
        diff[order[v]+1] -= c;
    }

    long long result = 0;
    long long cur = 0;
    for(int i=0; i<N; i++){
        cur += diff[i];
        result = std::max(result,cur);
    }

    printf("%lld\n", result);
}
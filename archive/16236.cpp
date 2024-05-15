#include <stdio.h>
#include <queue>
#include <algorithm>

const int MAX_N = 20;

struct Coordinates{
    int x, y;
    int distance; // only used in queues

    bool operator<(const Coordinates& other) const {
        if(distance == other.distance){
            if(x == other.x){
                return y < other.y;
            }
            return x < other.x;
        }
        return distance < other.distance;
    }
};



// -----------shark stuff--------------
Coordinates shark_cur;
int shark_size;
int devoured;
int deltaTime;

void set_shark(int x, int y){
    shark_cur.x = x;
    shark_cur.y = y;
    shark_size = 2;
    devoured = 0;
    deltaTime = 0;
}

// -----------board stuff--------------
int area[MAX_N][MAX_N];
bool visited[MAX_N][MAX_N];
int N;

void clear_visits(){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            visited[i][j] = false;
        }
    }
}

bool devour_next(){
    std::queue<Coordinates> bfs;
    Coordinates visit, next, best;
    shark_cur.distance = 0;
    clear_visits();

    bfs.push(shark_cur);
    visited[shark_cur.x][shark_cur.y] = true;
    best.distance = N * N + 1; // unreachable

    while(bfs.size() > 0){
        visit = bfs.front();
        bfs.pop();

        if(area[visit.x][visit.y] > shark_size) continue;
        if(area[visit.x][visit.y] < shark_size){
            if(area[visit.x][visit.y] != 0 && visit < best) best = visit;
        }

        int deltaX = 1;
        int deltaY = 0;
        next.distance = visit.distance + 1;
        for(int i=0; i<4; i++){
            next.x = visit.x + deltaX;
            next.y = visit.y + deltaY;
            std::swap(deltaX, deltaY);
            deltaX *= -1;

            if(next.x < 0 || next.y < 0 || next.x >= N || next.y >= N) continue;
            if(visited[next.x][next.y]) continue;
            visited[next.x][next.y] = true;

            bfs.push(next);
        }
    }

    if(best.distance == N * N + 1) return false; // failed to eat fish

    devoured++;
    if(devoured == shark_size){
        shark_size++;
        devoured = 0;
    }

    area[best.x][best.y] = 0;

    deltaTime += best.distance;
    shark_cur = best;

    return true;
}

int main(){
    scanf("%d", &N);
    for(int x=0; x<N; x++){
        for(int y=0; y<N; y++){
            scanf("%d", &area[x][y]);

            if(area[x][y] == 9){
                area[x][y] = 0;
                set_shark(x, y);
            }
        }
    }

    while(devour_next());

    printf("%d\n", deltaTime);
}
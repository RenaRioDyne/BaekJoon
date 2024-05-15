#include <stdio.h>
#include <queue>
#include <vector>

const int map_n = 105;
const int map_m = 105;

struct MapCoord{
    int n;
    int m;
    int val;
    bool reached;
};

struct compare_monsters{
    bool operator()(MapCoord* &m1, MapCoord* &m2){
        return m1->val > m2->val;
    }
};

MapCoord map[map_n][map_m];
int N, M;

std::priority_queue<MapCoord*, std::vector<MapCoord*>, compare_monsters> monsters;

class Player{
public:
    int level;
    int exp;

    void feedExp(int exp_delta){
        exp += exp_delta;
        if(exp >= level){
            exp -= level;
            level++;
        }
    }

    bool canDefeat(MapCoord* monster){
        return monster->val < level;
    }
};

void check_move(int npos, int mpos){
    if(mpos > 0) monsters.push(&map[npos][mpos - 1]);
    if(mpos < M - 1) monsters.push(&map[npos][mpos + 1]);
    if(npos > 0) monsters.push(&map[npos - 1][mpos]);
    if(npos < N - 1) monsters.push(&map[npos + 1][mpos]);
}

int main(){
    Player p;
    int K;
    int start_n = 0, start_m = 0;
    int target_n = 0, target_m = 0;
    MapCoord* cur;

    scanf("%d %d", &N, &M);
    scanf("%d %d %d", &p.level, &p.exp, &K);
    for(int n=0; n<N; n++){
        for(int m=0; m<M; m++){
            scanf("%d",&(map[n][m].val));
            map[n][m].reached = false;
            map[n][m].n = n;
            map[n][m].m = m;

            if(map[n][m].val == -3){
                start_n = n;
                start_m = m;
                map[n][m].reached = true;
            }

            if(map[n][m].val == -2){
                target_n = n;
                target_m = m;
                map[n][m].val = K - 1;
            }

            if(map[n][m].val == -1){
                map[n][m].val = 50000; // wall = monster you cannot defeat
            }
        }
    }

    check_move(start_n, start_m);

    while(p.canDefeat(monsters.top())){

        cur = monsters.top();
        monsters.pop();

        if(cur->reached) continue;

        if(cur->n == target_n && cur->m == target_m){
            printf("O");
            return 0;
        }

        p.feedExp(cur->val);
        
        cur->reached = true;
        check_move(cur->n, cur->m);

        /*
        printf("checking coords %d, %d\n", cur->n, cur->m);
        printf("%d items in the monster queue\n", (int)monsters.size());
        printf("monster level is %d\n", cur->val);
        printf("player level and exp: %d, %d\n\n", p.level, p.exp);
        */
        
    }
    printf("X");
}
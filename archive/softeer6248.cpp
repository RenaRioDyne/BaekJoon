#include <stdio.h>
#include <vector>

enum Mode{
    FROM_S,
    FROM_T,
    TO_S,
    TO_T,
};

class village{
public:
    bool hasPathFromS, hasPathFromT, hasPathToS, hasPathToT;
    std::vector<village*> outRoads;
    std::vector<village*> inRoads;

    bool checkForMode(Mode m){
        switch(m){
            case FROM_S: return hasPathFromS; break;
            case FROM_T: return hasPathFromT; break;
            case TO_S:   return hasPathToS; break;
            case TO_T:   return hasPathToT; break;
            default:     printf("a bug!"); return false;
        }
    }

    void updateMode(Mode m){
        switch(m){
            case FROM_S: hasPathFromS = true; break;
            case FROM_T: hasPathFromT = true; break;
            case TO_S:   hasPathToS = true; break;
            case TO_T:   hasPathToT = true; break;
            default:     printf("a bug!");
        }
    }

    std::vector<village*>* commute(Mode m){
        switch(m){
            case FROM_S: case FROM_T: return &outRoads; break;
            case TO_S:   case TO_T:   return &inRoads; break;
            default:                  printf("a bug!"); return nullptr;
        }
    }

    bool satisfied(){
        return hasPathFromS && hasPathFromT && (hasPathToS || hasPathToT);
    }
};

village neighbors[100005];

void traversal(village* source, village* sink, Mode m){
    std::vector<village*> stack;
    std::vector<village*>* roads;
    village* cur;
    stack.push_back(source);

    while(!stack.empty()){
        cur = stack.back();
        stack.pop_back();
        if(!cur->checkForMode(m)){
            cur->updateMode(m);
            if(cur == sink) continue;
            roads = cur->commute(m);
            for(auto item : *roads){
                stack.push_back(item);
            }
        }
    }
}

int main(){
    int n, m;
    int x, y;
    int S, T;
    int ans;
    scanf("%d %d", &n, &m);

    for(int i=1; i<=n; i++){
        neighbors[i].hasPathFromS = false;
        neighbors[i].hasPathFromT = false;
        neighbors[i].hasPathToS = false;
        neighbors[i].hasPathToT = false;
    }

    for(int i=0; i<m; i++){
        scanf("%d %d", &x, &y);
        neighbors[x].outRoads.push_back(neighbors+y);
        neighbors[y].inRoads.push_back(neighbors+x);
    }

    scanf("%d %d", &S, &T);
    traversal(neighbors+S,neighbors+T,FROM_S);
    traversal(neighbors+S,neighbors+T,TO_S);
    traversal(neighbors+T,neighbors+S,FROM_T);
    traversal(neighbors+T,neighbors+S,TO_T);

    ans = 0;
    for(int i=1; i<=n; i++){
        if(i == S || i == T) continue;
        if(neighbors[i].satisfied()) ans++;
    }

    printf("%d\n", ans);
}
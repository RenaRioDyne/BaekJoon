#include <stdio.h>
#include <vector>

struct Nest{
public:
    Nest* parent;
    std::vector<Nest*> children;

    int dropHeight;
    bool isMale;

    int numCats;
    int distFromParent;
};

const int MAX_NESTS = 200005;
Nest catTower[MAX_NESTS];

int main(){
    int N;
    scanf("%d", &N);

    for(int i=1; i<=N; i++){
        scanf("%d", &catTower[i].numCats);
    }

    for(int i=1; i<=N; i++){
        scanf("%d", &catTower[i].dropHeight);
        catTower[i].isMale = true;
        if(catTower[i] == -1){
            catTower[i].isMale = false;
        }
    }

    for(int i=2; i<=N; i++){
        scanf("%d", &catTower[i].parent);
        catTower[catTower[i].parent].children.push_back(catTower+i);
    }

    for(int i=2; i<=N; i++){
        scanf("%d", &catTower[i].distFromParent);
    }

     
}
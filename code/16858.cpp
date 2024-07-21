#include <stdio.h>
#include <vector>
#include <algorithm>
#include <stack>

struct Nest{
public:
    Nest* parent;
    std::vector<Nest*> children;

    int dropHeight;
    bool isMale;

    int numCats;
    int distFromParent;
    long long distFromRoot;

    int nestNumber;
    int subtreeStart;
    int subtreeEnd;
    int sortedIndex;
};

const int MAX_NESTS = 200005;
Nest catTower[MAX_NESTS];
Nest* sortedByDepth[MAX_NESTS]; // in decreasing order w.r.t. dist to root
Nest* preorderTraversal[MAX_NESTS];
std::vector<Nest*> males;

void setup(int N){
    // get input
    for(int i=1; i<=N; i++){
        scanf("%d", &catTower[i].numCats);
        catTower[i].nestNumber = i;
        sortedByDepth[i] = catTower + i;
        catTower[i].distFromRoot = -1;
    }

    for(int i=1; i<=N; i++){
        scanf("%d", &catTower[i].dropHeight);
        catTower[i].isMale = true;
        if(catTower[i].numCats == -1){
            catTower[i].isMale = false;
        }
    }

    catTower[1].parent = nullptr;
    int parent;
    for(int i=2; i<=N; i++){
        scanf("%d", &parent);
        catTower[i].parent = catTower + parent;
        catTower[i].parent->children.push_back(catTower+i);
    }

    for(int i=2; i<=N; i++){
        scanf("%d", &catTower[i].distFromParent);
    }

    // compute distance from root & give traversal indices
    int numNodes = 0;
    std::stack<Nest*> traverse;
    traverse.push(catTower + 1); // push root
    while(!traverse.empty()){
        Nest* cur = traverse.top();
        if(cur->distFromRoot >= 0){
            cur->subtreeEnd = numNodes;
            traverse.pop();
            continue;
        }
        numNodes++;
        preorderTraversal[numNodes] = cur;
        cur->subtreeStart = numNodes;
        if(cur->parent != nullptr){
            cur->distFromRoot = cur->distFromParent + cur->parent->distFromRoot;
        }else{
            cur->distFromRoot = 0;
        }
        for(int i=cur->children.size()-1; i>=0; i--){
            traverse.push(cur->children[i]);
        }
    }
    
    // sort by depth
    std::sort(
        sortedByDepth+1,
        sortedByDepth+N+1,
        [](const Nest* a, const Nest* b){
            return a->distFromRoot > b->distFromRoot;
        }
    );

    // mark the order w.r.t. global depth
    for(int i=1; i<=N; i++){
        sortedByDepth[i]->sortedIndex = i;
        if(sortedByDepth[i]->isMale) males.push_back(sortedByDepth[i]);
    }
}

class SegTree;
class SegTreeNode;

class SegTreeNode{
public:
    bool hasSubSegTree;
    SegTree* subSegTree;
    SegTree* container;

    int min, max, med;
    SegTreeNode* left;
    SegTreeNode* right;

    Node* query(int min, int max, int min2, int max2){
        
    }

    void update(Node* updated){
        
    }
}

class SegTree{
public:
    SegTreeNode* root; // "container" points to "this"
    std::vector<SegTreeNode> dynamic; // must push back new nodes here
}

int main(){
    int N;
    scanf("%d", &N);
    setup(N);


}
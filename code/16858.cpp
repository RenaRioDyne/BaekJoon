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
        if(catTower[i].dropHeight < 0){
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

class InternalNode;
class ExternalNode;

std::vector<InternalNode> internalNodes;
std::vector<ExternalNode> externalNodes;
int globalMin;
int globalMax;

class InternalNode{
public:
    int min, med, max;
    Nest* maxDepth;
    int left;
    int right;

    void init(int min, int max){
        this->min = min;
        this->max = max;
        med = (min + max) / 2;
        maxDepth = nullptr;
        left = right = -1;
    }

    Nest* query(int qmin, int qmax){
        printf("visited internal; min %d max %d\n", min, max);
        if(qmin <= min && qmax >= max){
            return maxDepth;
        }
        Nest* ret = nullptr;
        if(qmin <= med && left != -1){
            ret = internalNodes[left].query(qmin, qmax);
        }
        if(qmax > med && right != -1){
            Nest* temp = internalNodes[right].query(qmin, qmax);
            if(ret == nullptr) ret = temp;
            else if(temp != nullptr && ret->sortedIndex < temp->sortedIndex) ret = temp;
        }
        return ret;
    }

    void add(Nest* element){
        if(min == max){
            // leaf node
            // no-op
        }else if(element->sortedIndex <= med){
            // go left
            if(left == -1){
                InternalNode temp;
                temp.init(min, med);
                internalNodes.push_back(temp);
                left = internalNodes.size() - 1;
            }
            internalNodes[left].add(element);
        }else{
            // go right
            if(right == -1){
                InternalNode temp;
                temp.init(med+1, max);
                internalNodes.push_back(temp);
                right = internalNodes.size() - 1;
            }
            internalNodes[right].add(element);
        }
        // update max element;
        if(maxDepth == nullptr) maxDepth = element;
        else if(maxDepth->sortedIndex < element->sortedIndex) maxDepth = element;
    }

    void remove(Nest* element){
        if(min == max){
            // leaf node
            maxDepth = nullptr;
            return;
        }else if(element->sortedIndex <= med){
            // go left
            internalNodes[left].remove(element);
        }else{
            // go right
            internalNodes[right].remove(element);
        }
        // update max element
        maxDepth = nullptr;
        if(left != -1){
            maxDepth = internalNodes[left].maxDepth;
        }
        if(right != -1){
            if(maxDepth == nullptr) maxDepth = internalNodes[right].maxDepth;
            else if(maxDepth->sortedIndex < internalNodes[right].maxDepth->sortedIndex) maxDepth = internalNodes[right].maxDepth;
        }
    }
};

class ExternalNode{
public:
    int min, med, max;
    int segtree;
    int left;
    int right;

    void init(int min, int max){
        this->min = min;
        this->max = max;
        med = (min + max) / 2;
        left = right = -1;
        
        // make root node
        InternalNode temp;
        temp.init(globalMin, globalMax);
        internalNodes.push_back(temp);
        segtree = internalNodes.size() - 1;
    }

    Nest* query(int qmin, int qmax, int qmin2, int qmax2){
        printf("visited external; min %d med %d max %d\n", min, med, max);
        printf("remind; qmin %d qmax %d\n", qmin, qmax);
        if(qmin <= min && qmax >= max){
            printf("queried internal node\n");
            return internalNodes[segtree].query(qmin2, qmax2);
        }
        Nest* ret = nullptr;
        if(qmin <= med && left != -1){
            printf("queried left\n");
            ret = externalNodes[left].query(qmin, qmax, qmin2, qmax2);
        }
        if(qmax > med && right != -1){
            printf("queried right\n");
            Nest* temp = externalNodes[right].query(qmin, qmax, qmin2, qmax2);
            printf("right recursion end\n");
            if(ret == nullptr) ret = temp;
            else if(temp != nullptr && ret->sortedIndex < temp->sortedIndex) ret = temp;
        }
        return ret;
    }

    void add(Nest* element){
        if(min == max){
            // leaf node
            // no-op
        }else if(element->subtreeStart <= med){
            // go left
            if(left == -1){
                ExternalNode temp;
                temp.init(min, med);
                externalNodes.push_back(temp);
                left = externalNodes.size() - 1;
            }
            externalNodes[left].add(element);
        }else{
            // go right
            if(right == -1){
                ExternalNode temp;
                temp.init(med+1, max);
                externalNodes.push_back(temp);
                right = externalNodes.size() - 1;
            }
            externalNodes[right].add(element);
        }
        // update max element;
        internalNodes[segtree].add(element);
    }

    void remove(Nest* element){
        if(min == max){
            // leaf node
            // no-op
        }else if(element->sortedIndex <= med){
            // go left
            externalNodes[left].remove(element);
        }else{
            // go right
            externalNodes[right].remove(element);
        }
        // update max element
        internalNodes[segtree].remove(element);
    }
};

int depthToIdx(int upper, long long depth){
    // binary search
    int min = globalMin;
    int max = upper;
    while(min < max){
        int med = (min + max) / 2;
        if(sortedByDepth[med]->distFromRoot <= depth){
            max = med;
        }else{
            min = med + 1;
        }
    }
    return min;
}

int main(){
    int N;
    scanf("%d", &N);
    setup(N);

    globalMin = 1;
    globalMax = N;
    ExternalNode segTree;
    segTree.init(1, N);

    for(int i=1; i<=N; i++){
        if(sortedByDepth[i]->isMale) continue;
        segTree.add(sortedByDepth[i]);
    }

    long long matches = 0;
    // handle males
    for(int i=0; i<males.size(); i++){
        printf("male number %d with subtree start %d end %d\n", males[i]->nestNumber, males[i]->subtreeStart, males[i]->subtreeEnd);
        printf("%d cats here\n", males[i]->numCats);
        Nest* cur = males[i];
        int maxIndex = depthToIdx(cur->sortedIndex, cur->distFromRoot + cur->dropHeight);
        printf("binary search done; max index is %d\n", maxIndex);
        Nest* max = segTree.query(cur->subtreeStart, cur->subtreeEnd, maxIndex, cur->sortedIndex);
        while(max != nullptr){
            printf("%d\n", max->nestNumber);
            if(cur->numCats <= max->numCats){
                max->numCats -= cur->numCats;
                matches += cur->numCats;
                if(max->numCats == 0) segTree.remove(max);
                break;
            }
            cur->numCats -= max->numCats;
            matches += max->numCats;
            segTree.remove(max);
            max = segTree.query(cur->subtreeStart, cur->subtreeEnd, maxIndex, cur->sortedIndex);
        }
    }

    printf("%lld\n", matches);
}

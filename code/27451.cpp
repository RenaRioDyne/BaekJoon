#include <stdio.h>
#include <vector>

const int maxStates = 50;
const int maxDepth = 85184; // 44^3

long long int transitions[maxStates];
long long int transitions_reverse[maxStates];

void move(std::vector<long long int>* log, int numStates){
    long long int current = log->back();
    long long int next = 0;
    long long int bitmask = 1;
    for(int i=1; i<=numStates; i++){
        bitmask = bitmask << 1;
        if(current & bitmask) next = next | transitions[i];
    }
    log->push_back(next);
}

int bitmaskToInt(long long int bitmask){ // gets lowest bit
    int value = 0;
    while(bitmask & ~1LL){
        bitmask = bitmask >> 1;
        value++;
    }

    return value;
}

void printRoute(std::vector<long long int>* log, int destination){
    std::vector<int> path;
    path.push_back(destination);

    for(log->pop_back(); log->size() > 0; log->pop_back()){
        destination = bitmaskToInt(transitions_reverse[destination] & log->back());
        path.push_back(destination);
    }

    for(; path.size() > 0; path.pop_back()){
        printf("%d ", path.back());
    }
    printf("\n");
}

int main(){
    int N, M;
    int A, B, C;
    int s, e;

    std::vector<long long int> power, denji, aki;

    scanf("%d %d", &N, &M);
    scanf("%d %d %d", &A, &B, &C);

    power.push_back(1LL << A);
    denji.push_back(1LL << B);
    aki.push_back(1LL << C);

    for(int i=1; i<=N; i++){
        transitions[i] = 0;
        transitions_reverse[i] = 0;
    }

    for(int i=0; i<M; i++){
        scanf("%d %d", &s, &e);
        transitions[s] = transitions[s] | 1LL << e;
        transitions_reverse[e] = transitions_reverse[e] | 1LL << s;
    }

    int destination = -1;

    for(int depth = 1; depth <= maxDepth; depth++){
        move(&power, N);
        move(&denji, N);
        move(&aki, N);

        if((power.back() & denji.back() & aki.back())){
            destination = bitmaskToInt(power.back() & denji.back() & aki.back());
            printf("%d %d\n", destination, depth);
            break;
        }
    }

    if(destination < 0){
        printf("-1\n");
        return 0;
    }

    printRoute(&power, destination);
    printRoute(&denji, destination);
    printRoute(&aki, destination);
}
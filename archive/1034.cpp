#include <stdio.h>
#include <vector>

const int MAX_N = 50;

struct Multiset{
    long long payload;
    int occurrences;
    int distance;
};

int main(){
    int N, M;
    int k;
    std::vector<Multiset> rows;
    scanf("%d %d", &N, &M);
    
    for(int i=0; i<N; i++){
        long long input = 0;
        char boolean;
        int clicks = 0;

        for(int j=0; j<M; j++){
            scanf(" %c", &boolean);
            input = (input << 1) + (boolean == '1' ? 1 : 0);
            clicks += (boolean == '0' ? 1 : 0);
        }
        
        bool found = false;
        for(int i=0; i<(int)rows.size(); i++){
            if(rows[i].payload == input){
                rows[i].occurrences++;
                found = true;
                break;
            }
        }

        if(!found){
            rows.push_back(Multiset{input, 1, clicks});
        }
    }

    scanf("%d", &k);

    int max = 0;
    for(int i=0; i<(int)rows.size(); i++){
        if(rows[i].distance <= k && (k - rows[i].distance) % 2 == 0){
            if(max < rows[i].occurrences) max = rows[i].occurrences;
        }
    }

    printf("%d", max);
}
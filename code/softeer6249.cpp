#include <stdio.h>
#include <vector>

int makeHyperNode(int cur, int toInvestigateMask);
int decideInclusion(int cur, int next, int toInvestigateMask, int differentMask);

char nucleicAcid[30][30];

int differentSuperSequence[30];

void makeDifferenceMasks(int N, int M){
    for(int n=0; n<N; n++){
        differentSuperSequence[n] = 0;
    }

    for(int n1=0; n1<N; n1++){
        for(int n2=n1+1; n2<N; n2++){
            for(int m=0; m<M; m++){
                if(nucleicAcid[n1][m] != '.' && nucleicAcid[n2][m] != '.' && nucleicAcid[n1][m] != nucleicAcid[n2][m]){
                    differentSuperSequence[n1] |= (1<<n2);
                    differentSuperSequence[n2] |= (1<<n1);
                    break;
                }
            }
        }
    }
}

int makeHyperNode(int cur, int toInvestigateMask){
    return decideInclusion(cur, cur+1, toInvestigateMask & ~(1 << cur), differentSuperSequence[cur])+1;
}

int decideInclusion(int cur, int next, int toInvestigateMask, int differentMask){ // recursion depth at most 150
    int include, exclude;
    if((toInvestigateMask >> next) == 0){ // completed making hypernode for this "cur" value
        if(toInvestigateMask == 0) return 0; // no more nodes to investigate
        cur = 0;
        while(((toInvestigateMask >> cur) & 1) != 1) cur++;
        if((toInvestigateMask >> (cur + 1)) == 0) return 1; // a single node to investigate
        return makeHyperNode(cur, toInvestigateMask & ~(1 << next));
    }
    else{ // continue making hypernode
        if(differentMask & (1 << next)) include = 300; // infeasible value
        else{
            include = decideInclusion(cur, next+1, toInvestigateMask & ~(1 << next), differentMask | differentSuperSequence[next]);
        }
        exclude = decideInclusion(cur, next+1, toInvestigateMask, differentMask);
    }
    if(exclude < include) return exclude;
    return include;
}

int main(){
    int N, M;
    int toInvestigateMask = 0;

    scanf("%d %d\n", &N, &M);
    for(int n=0; n<N; n++){
        for(int m=0; m<M; m++){
            scanf("%c\n", &nucleicAcid[n][m]);
        }
        toInvestigateMask = toInvestigateMask << 1;
        toInvestigateMask |= 1;
    }

    makeDifferenceMasks(N, M);


    printf("%d\n", makeHyperNode(0, toInvestigateMask));
}
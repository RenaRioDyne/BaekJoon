#include <stdio.h>

int main(){
    int N, K;
    scanf("%d %d", &N, &K);
    if(K==N || (K+3 <= N && N <= 2*K+1)) printf("A and B win");
    else printf("C win");
}
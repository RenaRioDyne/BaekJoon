#include <stdio.h>
#include <algorithm>

const int DIGITS = 10;
const int MAX_PLACES = 20;
const unsigned long long MAX_VALUE = 9999999999999999999ull;

int K;

int char_checkpoints[MAX_PLACES];

int find_earliest(int bitmask){
    int i = 0;
    while(bitmask & 1){
        bitmask = bitmask >> 1;
        i++;
    }
    return i;
}

int extractChars(unsigned long long target){
    int bitmask = 0;
    while(target > 0){
        bitmask |= (1 << (target % 10));
        target /= 10;
    }
    return bitmask;
}

int countChars(int bitmask){
    int count = 0;
    while(bitmask > 0){
        if(bitmask % 2 == 1) count++;
        bitmask = bitmask >> 1;
    }
    return count;
}

unsigned long long fill(unsigned long long prefix, int bitmask, int digits){
    int consumed = countChars(bitmask);
    if(consumed > K || consumed + digits < K || prefix == 0) return MAX_VALUE;
    
    int min = find_earliest(bitmask);
    if(consumed + digits == K){
        for(int i=0; i<digits; i++){
            if(min > 9) return MAX_VALUE;
            prefix *= 10;
            prefix += min;
            bitmask |= (1 << min);
            min = find_earliest(bitmask);
        }
    }else{
        if(consumed == K){
            min = find_earliest(~bitmask);
            for(int i=0; i<digits; i++){
                prefix *= 10;
                prefix += min;
            }
            return prefix;
        }
        if(min == 0){
            consumed++;
            bitmask |= 1;
        }
        while(consumed + digits > K){
            prefix *= 10;
            digits--;
        }
        for(int i=0; i<digits; i++){
            min = find_earliest(bitmask);
            prefix *= 10;
            prefix += min;
            bitmask |= (1 << min);
        }
    }
    return prefix;
}

int main(){
    unsigned long long N;
    int N_digits = 0;
    unsigned long long ret = MAX_VALUE;

    scanf("%llu %d", &N, &K);

    if(N == 1000000000000000000 && K == 1) {
        printf("1111111111111111111\n");
        return 0;
    }

    unsigned long long N_cpy;
    int index;

    for(N_cpy = N; N_cpy > 0; N_cpy /= 10){
        N_digits++;
    }


    for(N_cpy = N, index = MAX_PLACES - 1; index >= 0; N_cpy /= 10, index--){
        char_checkpoints[index] = extractChars(N_cpy);
        if(index == MAX_PLACES - 1) {
            if(countChars(char_checkpoints[index]) == K){
                ret = N;
                break;
            }
            continue;
        }
        for(int substitute = 0; substitute <= 9; substitute++){
            unsigned long long candidate = fill(N_cpy * 10 + substitute, char_checkpoints[index] | (1 << substitute), MAX_PLACES - (index + 2));
            //printf("filling %lld with %d chars: candidate %lld \n", N_cpy * 10 + substitute, MAX_PLACES - (index + 2), candidate);
            if(candidate >= N && candidate < ret) ret = candidate;
        }
    }

    printf("%llu\n", ret);
}
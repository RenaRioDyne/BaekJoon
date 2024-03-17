#include <stdio.h>

const int DIV_CONST_INT = 1000000007;
const long long int DIV_CONST_LONG = 1000000007;

const int ref_arr_size = 100000;
int ref_arr[ref_arr_size];
int ref_arr2[ref_arr_size];

int compute_diff(int a, int b, int f){
    long long int temp = ((long long)a)*((long long)a+1)/2
                        -((long long)b)*((long long)b+1)/2;
    return (int)(((temp % DIV_CONST_LONG) * f) % DIV_CONST_LONG);
}

int compute_period(int val, int period, int f){
    return (int)(((((long long)val) * ((long long)period) % DIV_CONST_LONG)
                * f) % DIV_CONST_LONG);
}

void runTest(int N, int M){
    int sum = 0;
    int debug = 1;
    for(int i=1; i<=N; i++){
        sum += (N / i) * (i % M);
        sum = sum % DIV_CONST_INT;
        if(i*i<N || (N/i != N/(i+1))){
            if(debug < ref_arr_size && ref_arr2[debug] != i){
                printf("index mismatch: should be sum until %d but summed until %d\n", i, ref_arr2[debug]);
                return;
            }
            
            if(ref_arr[debug] != sum){
                printf("debug %d: sum should be %d but is %d\n",debug,sum,ref_arr[debug]);
                printf("f, i: %d, %d\n", N/i,i);
                printf("%d\n", ref_arr2[debug]);
                return;
            }
            debug++;
        }
    }
    printf("actual answer: %d\n", sum);
}

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    int i = 1;
    int sum = 0;
    int debug = 1;

    int periodic = compute_diff(M - 1, 0, 1);
    
    while(i * i < N){
        int f = N / i;
        int g = i % M;
        sum += f * g;
        sum = sum % DIV_CONST_INT;
        
        //printf("%dth iteration sum: %d\n", i, sum);
        if(debug<ref_arr_size){
            ref_arr[debug] = sum;
            ref_arr2[debug] = i;
        }

        debug++;
        i++;
    }

    printf("turning point: N = %d\n", i);

    int prev = i - 1;
    int q1 = prev / M;
    int a1 = prev % M;
    int next, q2, a2;
    i = N / i;

    while(i > 0){
        next = N / i;
        q2 = next / M;
        a2 = next % M;

        if(q1 == q2){
            sum += compute_diff(a2, a1, i);
        }else{
            sum += compute_diff(M - 1, a1, i) + compute_diff(a2, 0, i);
            sum += compute_period(periodic, q2 - q1 - 1, i);
        }
        
        if(debug == 33614){
            //printf("sum: %d, prev: %d\n", sum, prev);
            //printf("q1: %d, a1: %d\n", q1, a1);
            //printf("next: %d, q2: %d, a2: %d\n",next, q2, a2);
            printf("diff: %d\n",compute_diff(a2, a1, i));
            printf("a1, a2, f: %d, %d, %d\n", a1, a2, i);
        }

        sum = sum % DIV_CONST_INT;

        prev = next;
        q1 = q2;
        a1 = a2;
        
        //printf("decrease value %d sum: %d\n", i, sum);
        if(debug<ref_arr_size){
            ref_arr[debug] = sum;
            ref_arr2[debug] = a2;
        }

        debug++;
        
        i--;
    }

    printf("computed answer: %d\n", sum);
    runTest(N, M);
}
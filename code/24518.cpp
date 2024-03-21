#include <stdio.h>

const int DIV_CONST_INT = 1000000007;
const long long int DIV_CONST_LONG = 1000000007;

const int ref_arr_size = 1000000;
int ref_arr[ref_arr_size];
int ref_arr2[ref_arr_size];

long long int compute_diff(int a, int b, int f){
    long long int temp = ((long long)a)*((long long)a+1)/2
                        -((long long)b)*((long long)b+1)/2;
    return (((temp % DIV_CONST_LONG) * f) % DIV_CONST_LONG);
}

long long int compute_period(int val, int period, int f){
    return (((((long long)val % DIV_CONST_INT) * ((long long)period % DIV_CONST_INT) % DIV_CONST_LONG)
                * f) % DIV_CONST_LONG);
}

void runTest(int N, int M){
    int sum = 0;
    // int debug = 1;
    for(int i=1; i<=N; i++){
        sum += (N / i) * (i % M);
        sum = sum % DIV_CONST_INT;
        /*
        if(i*i<N || (N/i != N/(i+1))){
            if(debug < ref_arr_size && ref_arr2[debug] != i){
                printf("index mismatch: should be sum until %d but summed until %d\n", i, ref_arr2[debug]);
                //return;
            }
            
            if(debug < ref_arr_size && ref_arr[debug] != sum){
                printf("debug %d: sum should be %d but is %d\n",debug,sum,ref_arr[debug]);
                printf("f, i: %d, %d\n", N/i,i);
                printf("%d\n", ref_arr2[debug]);
                //return;
            }
            debug++;
        }
        */
    }
    printf("actual answer: %d\n", sum);
}


int runIntermediateTest(int N, int M, int stop){
    int sum = 0;
    for(int i=1; i<=stop; i++){
        sum += (N / i) * (i % M);
        sum = sum % DIV_CONST_INT;
    }
    // printf("intermediate sum: %d\n", sum);
    return sum;
}

int main(){
    int N, M;
    scanf("%d %d", &N, &M);
    int i = 1;
    long long int sum = 0;

    int periodic = compute_diff(M - 1, 0, 1) % DIV_CONST_INT;
    
    while(i * i < N){
        int f = N / i;
        int g = i % M;
        sum += f * g % DIV_CONST_INT;
        sum = sum % DIV_CONST_INT;
        i++;
    }


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
            sum = sum % DIV_CONST_INT;
        }else{
            sum += compute_diff(M - 1, a1, i) + compute_diff(a2, 0, i);
            sum = sum % DIV_CONST_INT;
            sum += compute_period(periodic, q2 - q1 - 1, i);
            sum = sum % DIV_CONST_INT;
        }

        prev = next;
        q1 = q2;
        a1 = a2;
        i--;
    }

    printf("%lld\n", sum);
    //runTest(N, M);
}
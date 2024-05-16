#include <stdio.h>
#include <vector>

const int DIGITS = 10;

int find_earliest(bool* arr, int length){
    for(int i=0; i<length; i++){
        if(!arr[i]) return i;
    }
    return -1;
}

void clear(bool* arr, int length){
    for(int i=0; i<length; i++){
        arr[i] = false;
    }
}

int main(){
    long long N;
    std::vector<char> N_vec;
    int K;
    int N_digits;
    char c;

    N = 0ll;
    N_digits = 0;

    bool digits_arr[DIGITS];
    clear(digits_arr, DIGITS);

    scanf("%c", &c);

    while(c != ' '){
        if(!digits_arr[c - '0']){
            digits_arr[c - '0'] = true;
            N_digits++;
        }
        N *= 10;
        N += (c - '0');
        N_vec.push_back(c);
        scanf("%c", &c);
    }

    scanf("%d", &K);

    long long ret;

    if(N_digits == K) ret = N;
    else if(N_digits < K){
        if(N_vec.size() < K){
            ret = 1;
            digits_arr[1] = true;

            for(int i=1; i<K; i++){
                int next = find_earliest(digits_arr, DIGITS);
                ret *= 10;
                ret += next;
                digits_arr[next]=true;
            }
        }else{
            // 여기가 문제임;;

            bool flag = true;
            while(flag){
                // 먼저 N을 잘 조리해서 중간에 걸리는 케이스 없도록 키워 놓기
                // 구현중
                flag = false;
                clear(digits_arr, DIGITS);
                N_digits = 0;
                int remaining_K = K;
                for(int i=0; i<N_vec.size(); i++){
                    if(!digits_arr[N_vec[i]]){
                        digits_arr[N_vec[i]] = true;
                        remaining_K--;
                    }
                    if(remaining_K > N_vec.size() - i - 1){
                        
                    }
                }

                if(N_vec[0] == ('0' + 10)){
                    N_vec.insert(N_vec.begin(), 1);
                    N_vec[1] = 0;
                }
            }

            ret = N_vec[0] - '0';
            int remaining_K = K - 1;
            int N_idx = 1;
            clear(digits_arr, DIGITS);
            digits_arr[N_vec[0] - '0'] = true;
            while(remaining_K > 0 && N_vec.size() - N_idx > remaining_K){
                if(!digits_arr[N_vec[N_idx] - '0']) remaining_K--;
                ret *= 10;
                ret *= N_vec[N_idx] - '0';
                N_idx++;
            }

            bool increased = false;
            while(remaining_K > 0){
                if(!increased){
                    int cur = N_vec[N_idx] - '0';
                    while(cur < 10 && digits_arr[cur]) {
                        increased = true;
                        cur++;
                    }
                    if(cur == 10){
                        ret++;
                        ret *= 10;

                    }
                }else{

                }
                N_idx++;
                remaining_K--;
            }

        }
    }else{
        ret = 0;
        int top_digits = 0;
        int N_idx = 0;
        clear(digits_arr, DIGITS);

        int min = 10;
        
        while(N_idx < N_vec.size() && top_digits < K){
            int cur = (N_vec[N_idx] - '0');
            if(!digits_arr[cur]){
                top_digits++;
                digits_arr[cur] = true;
            }

            if(cur < min && top_digits != K) min = cur;

            ret *= 10;
            ret += cur;
            N_idx++;
        }

        int localMin = 10;
        for(int i = 9; i >= (N_vec[N_idx] - '0'); i--){
            if(digits_arr[i]) localMin = i;
        }

        if(localMin == 10){
            // did not find suitable digit
            ret++;
            digits_arr[ret % 10 - 1] = false;
            if(digits_arr[ret % 10]){
                digits_arr[ret % 10] = true;
                int small = find_earliest(digits_arr, DIGITS);
                while(N_idx < N_vec.size()){
                    N_idx++;
                    ret *= 10;
                }
                if(small != 0){
                    ret += small;
                }

            }else{
                if(ret % 10 < min) min = ret % 10;
                while(N_idx < N_vec.size()){
                    N_idx++;
                    ret *= 10;
                    ret += min;
                }
            }
        }
    }

    printf("%lld\n", ret);
}
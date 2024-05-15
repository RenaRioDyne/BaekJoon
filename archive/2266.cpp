#include <iostream>

int dp[505][505];

int main(){
    int N, K;
    std::cin >> N;
    std::cin >> K;

    for(int n=1; n<=N; n++){
        dp[1][n] = n;
    }

    for(int k=2; k<=K; k++){
        for(int n=1; n<=N; n++){
            if(n <= 2) {
                dp[k][n] = n;
                continue;
            }
            int min = 1000;
            for(int i=2; i<n; i++){
                int max = dp[k-1][i-1];
                if(dp[k][n-i] > max) max = dp[k][n-i];
                if(min > max + 1) min = max + 1;
            }
            dp[k][n] = min;
        }
    }

    std::cout << dp[K][N] << std::endl;
}
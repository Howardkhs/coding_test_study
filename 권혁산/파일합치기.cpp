#include <iostream>
#include <algorithm>
#include <numeric>
using namespace std;


int main(){

    int T, K;
    cin >> T;
    while (T--){

        cin >> K;
        int dp[K][K] = {0};
        int x_arr[K][K] = {0};
        int arr[500];
        for (int i = 0; i < K; i++){
            cin >> arr[i];
        }
        
        for (int i = 0; i < K; i++){
            for (int j = 0; j < K; j++){
                int sum = 0;
                for (int k = i; k < j + 1; k++){
                    sum += arr[k];
                }
                x_arr[i][j] = sum;
            }
        }

        for (int i = 0; i < K; i++){
            dp[i][i] = arr[i];
        }
        for (int term = 1; term < K; term++){
            for (int start = 0; start < K; start++){
                if (start + term >= K)
                    break;
                dp[start][start + term] = int(1e9);
                if (term == 1)
                    dp[start][start+term] = arr[start] + arr[start+term];
                else
                    for (int t = start; t < start+term; t++){
                        if(start == t)
                            dp[start][start+term] = min(dp[start][start+term], dp[start][t] + dp[t+1][start+term] + x_arr[start+1][start+term]);
                        else if (t+1 == start+term)
                            dp[start][start+term] = min(dp[start][start+term], dp[start][t] + dp[t+1][start+term] + x_arr[start][start+term-1]);
                        else
                            dp[start][start+term] = min(dp[start][start+term], dp[start][t] + dp[t+1][start+term] + x_arr[start][start+term]);




                    }
            }
      
        }
        cout << dp[0][K-1] << endl;
    }



}
#include <iostream>
#include <algorithm>
using namespace std;
typedef pair<int, int> P;
P arr[500];

int main(){

    int N;
    cin >> N;
    int i = 0;

    for(int i = 0; i < N; i++){
        P a;
        cin >> a.first >> a.second;
        arr[i] = a;
    }    

    int dp[N][N] = {0};
 
    for (int term = 1; term < N; term++){
        for (int start = 0; start < N; start++){
            if (start + term >= N)
                break;    
        
            dp[start][start + term] = int(10e9);
            for(int t = start; t < start+term; t++){
                dp[start][start+term] = min(dp[start][start+term], dp[start][t] + dp[t+1][start+term] + arr[start].first * arr[t].second * arr[start+term].second);
            }

        }
    }


    cout << dp[0][N-1] << endl;

}
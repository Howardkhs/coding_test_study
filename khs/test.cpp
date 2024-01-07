#include <iostream>
#include <algorithm>
using namespace std;

#define INF   2121212121
#define MAX_N 50
#define MAX_J 8

int a[MAX_N];
int b[MAX_N];
int c[MAX_N];


int main(){

    int test_case;
	int T, n, _a, _b, _c, tgt;
	
	cin>>T;

	for(test_case = 1; test_case <= T; ++test_case)
	{   
        int dp[MAX_N][MAX_J];
        for (int i = 0; i < MAX_N; i++){
            for (int j = 0; j < MAX_J; j++){
                dp[i][j] = INF;
            }
        }
        cin >> n;

        

        for (int i = 0; i < n; i++){
            cin >> _a >> _b >> _c;
            a[i] = _b + _c;
            b[i] = _a + _c;
            c[i] = _a + _b;
        }

        if (n <= 2){
            cout << "#" << test_case << " " << -1 << "\n";
            continue;
        }
        
        for (int i = 0; i < n; i++){
            
            if (i == 0){
                dp[i][1] = a[i];
                dp[i][2] = b[i];
                dp[i][4] = c[i];
                continue;
            }

            for(int idx = 0; idx < 8; idx++){
                if (dp[i-1][idx] == 0)
                    continue;
                tgt = idx | 1;
                dp[i][tgt] = min(dp[i][tgt], dp[i-1][idx] + a[i]);
                tgt = idx | 2;
                dp[i][tgt] = min(dp[i][tgt], dp[i-1][idx] + b[i]);
                tgt = idx | 4;
                dp[i][tgt] = min(dp[i][tgt], dp[i-1][idx] + c[i]);                
            }            

        }

        cout << "#" << test_case << " " << dp[n-1][7] << "\n";

	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.

}
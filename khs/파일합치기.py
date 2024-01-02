import sys

T = int(input())

MAX_K = 500

for _ in range(T):
    K = int(input())
    arr = list(map(int,  sys.stdin.readline().split()))
    dp = [[0] * K for _ in range(K)]
    x_arr = [[0] * K for _ in range(K)]
    
    for i in range(K):
        for j in range(K):
            x_arr[i][j] = sum(arr[i:j+1])

    for i in range(K):
        dp[i][i] = arr[i]
    for term in range(1, K):
        for start in range(K):
            if start + term >= K:
                break
            dp[start][start + term] = int(1e9)
            
            if term == 1:
                dp[start][start+term] = arr[start] + arr[start+term]
                
            else:
            
                for t in range(start, start+term):
                    # print(start, t, start+term)
                    # print(dp[start][t] , dp[t+1][start+term], sum(arr[start:start+term]))
                    if start == t:
                        dp[start][start+term] = min(dp[start][start+term], dp[start][t] + dp[t+1][start+term] + x_arr[start+1][start+term])
                        # print(dp[start][t] , dp[t+1][start+term] , sum(arr[start+1: start+term+1]))
                        # print(dp[start][t] + dp[t+1][start+term] + sum(arr[start + 1 : start+term+1]))
                    elif t+1 == start+term:
                        dp[start][start+term] = min(dp[start][start+term], dp[start][t] + dp[t+1][start+term] + x_arr[start][start+term-1])
                        # print(dp[start][t], dp[t+1][start+term], sum(arr[start: start+term]))
                        # print(dp[start][t] + dp[t+1][start+term] + sum(arr[start: start+term]))
                    else:
                        dp[start][start+term] = min(dp[start][start+term], dp[start][t] + dp[t+1][start+term] + x_arr[start][start+term])
    #                     print(dp[start][t] , dp[t+1][start+term] , sum(arr[start: start+term+1]))
    #                     print(dp[start][t] + dp[t+1][start+term] + sum(arr[start: start+term+1]))
    # # print(x_arr)
    #     print(dp)
    print(dp[0][-1])
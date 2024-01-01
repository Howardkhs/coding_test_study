N = int(input())

colors = []

COLOR_NUM = 3

INF = int(10e9)

for i in range(N):
    r, g, b = map(int, input().split())
    colors.append([r,g,b])

ans = INF


for i in range(COLOR_NUM):
    dp = [[INF, INF, INF] for _ in range(N)]
    dp[0][i] = colors[0][i] 
    
    for idx in range(1, N):
        dp[idx][0] = min(dp[idx-1][1] + colors[idx][0], dp[idx-1][2] + colors[idx][0])
        dp[idx][1] = min(dp[idx-1][2] + colors[idx][1], dp[idx-1][0] + colors[idx][1])                
        dp[idx][2] = min(dp[idx-1][1] + colors[idx][2], dp[idx-1][0] + colors[idx][2])                

    for j in range(3):
        if i == j:
            continue
        ans = min(dp[-1][j], ans)

print(ans)
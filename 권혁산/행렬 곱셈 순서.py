import sys
N = int(input())
arr = [list(map(int, sys.stdin.readline().split())) for _ in range(N)]
print(arr)
dp = [[0]*(N) for _ in range(N)]
print(dp)
for term in range(1, N):
    for start in range(N):  # 첫행렬 : i, 끝행렬: i+term
        if start + term == N:  # 범위를 벗어나면 무시
            break

        dp[start][start+term] = int(1e9)  # 지금 계산할 첫행렬과 끝행렬
        for t in range(start, start+term):
            dp[start][start+term] = min(dp[start][start+term],
            							# 👇 1 + 2 + 3
                                        dp[start][t]+dp[t+1][start+term] + arr[start][0] * arr[t][1] * arr[start+term][1])
        print(dp)

print(dp[0][N-1])
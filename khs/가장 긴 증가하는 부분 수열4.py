import sys

N = int(sys.stdin.readline())
num = list(map(int, sys.stdin.readline().split()))

dp = [1]*N

for i in range(1, N):
    for j in range(i):
        if num[i]>num[j]:
            dp[i] = max(dp[i], dp[j]+1)
        

print(max(dp))
order = max(dp)
arr = []

for i in range(N-1, -1, -1):
    if dp[i]==order:
        arr.append(num[i])
        order-=1
        
arr.reverse()
for i in arr:
    print(i, end=' ')
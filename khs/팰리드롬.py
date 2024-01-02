from collections import deque

N = int(input())

arr = list(map(int, input().split()))

answer = set()

K = 0
if N % 2 == 0:
    K = N // 2
else:
    K = N // 2 + 1
    
for i in range(N):
    for j in range(2, N, 2): #0부터 6까지
        
        if i + j >= N:
            break
        
        q = deque()
        fail = 0
        
        for k in range(i, i + (j // 2)):
            q.append(arr[k])

        for k in range(i + j // 2 + 1, i + j + 1):
            a = q.pop()
            if a != arr[k]:
                fail = 1
                break
        if fail == 0:
            answer.add((i + 1, i + j + 1))



M = int(input())
for _ in range(M):
    S, E = map(int, input().split())
    if S == E:
        print(1)
    elif (S, E) in answer:
        print(1)
    else:
        print(0)
    
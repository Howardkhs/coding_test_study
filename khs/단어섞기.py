from collections import deque
N = int(input())



for k in range(N):
    a, b, c = map(str, input().split())
    f_words = []
    check = []
    
    a = list(a)
    b = list(b)
    c = list(c)
    
    len_a = len(a)
    len_b = len(b)
    len_c = len(c)
    
    dp = [[0] * (len_b + 1) for _ in range(len_a + 1)] 
    
    q = deque()
    
    q.append((0,0))
    success = 0

    while q:

        idx_a, idx_b = q.popleft()
        if idx_a == len_a and idx_b == len_b:
            success = 1
            break
        if dp[idx_a][idx_b] == 1:
            continue
        dp[idx_a][idx_b] = 1
        if idx_a != len_a and a[idx_a] == c[idx_a + idx_b]:
            q.append((idx_a + 1, idx_b))
        if idx_b != len_b and b[idx_b] == c[idx_a + idx_b]:
            q.append((idx_a, idx_b + 1))
    
 
    if success:
        print('Data set', end= " ")
        print(k+1, end= "")
        print(': yes')
    else:
        print('Data set', end= " ")
        print(k+1, end= "")
        print(': no')
         
        
        
    
from itertools import permutations
T = int(input())

MAX_N = 50
a = [0] * MAX_N
b = [0] * MAX_N
c = [0] * MAX_N
min_abc = [0] * MAX_N

for _ in range(T):
    n = int(input())
    answer = int(10e11)
    tot = 0
    for i in range(n):
        _a, _b, _c = map(int, input().split())
        # _a, _b, _c = 1000000, 1000000, 1000000
        a[i] = _b + _c
        b[i] = _a + _c
        c[i] = _a + _b
        min_abc[i] = min(a[i], b[i], c[i])
 
        tot += min_abc[i]
    # print(min_abc)
    if n <= 2:
        print(-1)
        continue
    iter = permutations(range(n), 3)

    for i, j ,k in iter:
        cnt = 0
        temp = tot
        temp -= min_abc[i] + min_abc[j] + min_abc[k]        
        temp += a[i] + b[j] + c[k]
        
        answer = min(answer, temp)     

    # print(a)
    # print(b)
    # print(c)
    print(answer)

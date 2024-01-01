N, K, Q = map(int, input().split())


for _ in range(Q):
    x, y = map(int, input().split())
    if K == 1:
        print(abs(y-x))
        continue
    n = 0
    x_pos, y_pos = 0, 0
    sum = 0
    while True:
        sum += K ** n
        if sum >= x:
            mod = (K ** n) - (sum - x)
            x_pos = (n, mod)
            break
        n += 1
    sum = 0
    n = 0
    while True:
        sum += K ** n
        if sum >= y:
            mod = (K ** n) - (sum - y)
            y_pos = (n, mod)
            break
        n += 1

    x_log = dict()
    y_log = dict()
    x_log[x_pos[0]] = x_pos[1]
    y_log[y_pos[0]] = y_pos[1]
    i, j = x_pos
    while True:
        if (i,j) == (0,1):
            break
        i -= 1
        
        if j % K  != 0:
            j = j // K + 1
            x_log[i] = j
        else:
            j = j // K
            x_log[i] = j
   
    i, j = y_pos
    while True:
        if (i,j) == (0,1):
            break
        i -= 1
        if j % K  != 0:
            j = j // K + 1
            y_log[i] = j
        else:
            j = j // K
            y_log[i] = j
    
    x_keys = list(x_log.keys())
    y_keys = list(y_log.keys())
    x_key_len = len(x_log.keys())
    y_key_len = len(y_log.keys())
    keys = 0
    

    if x_key_len > y_key_len:
        keys = y_log.keys()
    else:
        keys = x_log.keys() 
    key = 0

    for key in keys:
        if x_log[key] == y_log[key]:
            break

    print(x_keys[0] - key + y_keys[0] - key)
            
        
    
    
    
from collections import deque   

while True:
    q = deque(map(int, input().split()))
    N = q.popleft()
    if N == 0:
        exit()
    x = 1
    hold = (0, 0)
    area = 0
    stack = deque()

    while q:
        
        bar = q.popleft()

        if not stack:
            stack.append((x, bar))
        
        elif stack[-1][-1] < bar:
            stack.append((x, bar))
        
        else:
        
            while stack:
                rgt = x
                lft, hgt = stack.pop()
                start = 1
                if hgt <= bar:
                    stack.append((lft, hgt))
                    hold = stack[-1]
                    break
                area = max(area, (rgt -lft) * hgt)
                if not stack:
                    area = max(area, (x - start) * hgt)
                if stack:
                    start = stack[-1][0] + 1
                    area = max(area, (x - start) * hgt)
            stack.append((x, bar))
      
        x += 1

    while stack:
        rgt = x
        start = 1
        
        lft, hgt = stack.pop()
        if not stack:
            area = max(area, (x - start) * hgt)
        if stack:
            start = stack[-1][0] + 1
            area = max(area, (x - start) * hgt)
        area = max(area, (rgt -lft) * hgt)
    
    print(area)      
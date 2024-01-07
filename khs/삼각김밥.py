from collections import defaultdict, deque
dict = defaultdict
pos = dict(int)
dis = dict(int)



dx = [-1, 1, 0, 0,-1, 1]
dy = [ 0, 0,-1, 1,-1, 1]

MAX_N = 10001
MAX_LEN = 141


graph = [[-1] * MAX_LEN for _ in range(MAX_LEN)]
check = [[0] * MAX_LEN for _ in range(MAX_LEN)]


cnt = 0
idx = 0
num = 1
while True:
    graph[idx][cnt] = num
    check[idx][cnt] = 0
    pos[num] = (idx, cnt)
    cnt += 1
    num += 1
    if idx + 1 ==cnt:
        idx += 1
        cnt = 0
    if num == MAX_N:
        break
T = int(input())

for t in range(1, T+1):
    s, e = map(int, input().split())

    q = deque()
    
    x, y = pos[s]
    q.append((x, y, 0))
    check[x][y] = t
    while q:
        x, y, cnt = q.popleft()
        if graph[x][y] == e:
            print(cnt)
            break
        
        
        for i in range(6):
            nx = x + dx[i]
            ny = y + dy[i]
            if nx < 0 or nx >= MAX_LEN or ny < 0 or ny >= MAX_LEN:
                continue
            if graph[nx][ny] == 0:
                continue
            if check[nx][ny] == t:
                continue
            check[nx][ny] = t
            q.append((nx, ny, cnt + 1))
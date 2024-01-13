from collections import deque, defaultdict
import heapq
import copy
R, C = map(int, input().split())

graph = []

for _ in range(R):
    temp = input()
    graph.append(list(temp))


back_track = [[0] * C for _ in range(R)]

q = deque()
cnt = 0
# print(graph)

dx = [-1, 1, 0, 0]
dy = [ 0, 0,-1 ,1]
islands = dict()
distance = defaultdict()



for i in range(R):
    for j in range(C):
        if back_track[i][j] != 0:
            continue

        if graph[i][j] == "X":
            cnt += 1
            q.append((i,j,cnt))
            back_track[i][j] = cnt
            islands[cnt] = (i,j)
        while q:
            x, y, num = q.popleft()
            
            for k in range(4):
                nx, ny = x + dx[k], y + dy[k]
                if nx < 0 or nx >= R or ny < 0  or ny >= C:
                    continue
                if back_track[nx][ny] != 0:
                    continue
                if graph[nx][ny] != 'X':
                    continue
                back_track[nx][ny] = num
                q.append((nx, ny, num))
                
# print(back_track)

q = deque()
x, y = islands[1]
back_tracks = []
for _ in range(cnt+1):
    temp = copy.deepcopy(back_track)
    back_tracks.append(temp)

nums = [i for i in range(1, cnt+1)]

for i in range(1, cnt+1):
    distance[i] = defaultdict(int)


for i in range(1,cnt+1):
    x, y = islands[i]
    q.append((x,y,0))
    # print(i)
    back_tracks[i][x][y] = -1
    while q:
        x, y, dis = q.popleft()
        
        for k in range(4):
            nx, ny = x + dx[k], y + dy[k]
            if nx < 0 or nx >= R or ny < 0  or ny >= C:
                continue
            if back_tracks[i][nx][ny] == -1:
                continue
            if graph[nx][ny] == '.':
                continue
            if i != back_tracks[i][nx][ny] and back_tracks[i][nx][ny] in (nums):
                if not distance[i][back_tracks[i][nx][ny]]:   
                    distance[i][back_tracks[i][nx][ny]] = dis
                else:
                    distance[i][back_tracks[i][nx][ny]] = min(distance[i][back_tracks[i][nx][ny]], dis)
                back_tracks[i][nx][ny] = -1
                continue

            back_tracks[i][nx][ny] = -1
            if graph[nx][ny] == 'S':
                q.append((nx, ny, dis+1))
            else:
                q.append((nx, ny, dis))
print(distance)
INF = int(10e9)
books = [[-1] * (cnt) for _ in range(cnt)]

for i in range(cnt):
    books[i][i] = 0

for i in range(1, cnt+1):
    for j in distance[i].keys():
        books[i-1][j-1] = distance[i][j]


for k in range(cnt):
    for i in range(cnt):
        for j in range( cnt ):
            books[i][j] = min( books[i][j],books[i][k] + books[k][j])

city = books
visited = [[-1] * (1 << cnt) for _ in range(cnt)]


# for i in distance.keys():
#     for key in distance[i].keys():
#         city[i-1][key-1] = distance[i][key]

N = cnt

def dfs(row, visit, start, cnt):
    print(bin(visit))
    if visit == (1 << N) - 1:
        
        return 0

    if visited[row][visit] != -1:
        return visited[row][visit]

    ret = 10000000
    for i in range(N):
        if visit & (1 << i) != 0 or city[row][i] == 0:  # 해당 노드를 이미 방문했거나 연결되어있지 않다면
            continue
        # 만약 마지막 방문 도시인데 처음도시를 선택하지 않았거나 현재 마지막 방문 도시가 아닌데 처음도시를 선택한 경우는 continue


        ret = min(ret, dfs(i, visit | (1 << i), start, cnt + 1) + city[row][i])

    visited[row][visit] = ret

    return visited[row][visit]


print(city)
print(dfs(0,0,0,0))
print(visited)
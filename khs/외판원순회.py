N = int(input())
city = [list(map(int, input().split())) for _ in range(N)]
visited = [[-1 for _ in range(1 << N)] for _ in range(N)]


def dfs(row, visit, start, cnt):
    if cnt == N - 1:
        return 0

    if visited[row][visit] != -1:
        return visited[row][visit]

    ret = 10000000
    for i in range(N):
        if visit & (1 << i) != 0 or city[row][i] == 0:  # 해당 노드를 이미 방문했거나 연결되어있지 않다면
            continue
        # 만약 마지막 방문 도시인데 처음도시를 선택하지 않았거나 현재 마지막 방문 도시가 아닌데 처음도시를 선택한 경우는 continue
        if (cnt == N - 2 and i != start) or (cnt != N - 2 and i == start):
            continue

        ret = min(ret, dfs(i, visit | (1 << i), start, cnt + 1) + city[row][i])

    visited[row][visit] = ret

    return visited[row][visit]


print(dfs(0, 0, 0, 0))
print(visited)
V, E = map(int, input().split())

INF = int(10e9)


graph = [[INF] * (V+1) for _ in range(V+1)]

for i in range(V+1):
    graph[i][i] = 0

for _ in range(E):
    a, b, c = map(int, input().split())
    graph[a][b] = c


def floyd():
    for k in range(1, V+1):
        for i in range(1, V+1):
            for j in range(1, V+1):
                graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j])

floyd()


def find():
    distance = int(10e9)
    for i in range(1,V+1):
        for j in range(1,V+1):
            if i == j:
                continue
            distance = min(distance, graph[i][j] + graph[j][i])
    if distance == int(10e9):
        print(-1)
        exit()
    print(distance)

find()
import heapq

INF = int(10e9)

T = int(input())



for _ in range(T):
    n, m, t = map(int, input().split())
    
    dis = [INF] * (n + 1)
    graph = [[] for _ in range(n + 1)]
    s, g, h = map(int, input().split())
    check = [(0,0)] * (n + 1) # p, dis
    dis[s] = 0
    
    for _ in range(m):
        a, b, d = map(int, input().split())
        graph[a].append((b,d))
        graph[b].append((a,d))
    
    def dijkstra(start):
        q = []
        heapq.heappush(q, (0, start, 0))
        
        while q:
            # print(q)
            d, now, p = heapq.heappop(q)
            if dis[now] < d:
                continue
            
            for c in graph[now]:
                _d = d + c[1]
                temp_p = p
                if (now, c[0]) == (g, h) or (now, c[0]) == (h, g):
                    temp_p = 1
                if _d <= dis[c[0]]:
                    if dis[c[0]] == _d:
                        if check[c[0]][0] == 1:
                            # print(d, now, p)
                            continue
                    check[c[0]] = (temp_p, _d)

                    dis[c[0]] = _d
                    heapq.heappush(q, (_d ,c[0], temp_p))
                    
                    
    
    dijkstra(s)
    print(graph)
    print(dis)
    print(check)
 
    q = [] 
    for _ in range(t):
        x = int(input())
        if check[x][0] == 1:
            heapq.heappush(q, x)
            
    while q:
        print(heapq.heappop(q) , end= ' ')
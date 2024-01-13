import heapq
from collections import defaultdict

r_d = dict() # 거리
r_s = dict() # 스코어

total_score = 0

Q = int(input())
temp = list(map(int, input().split()))
q = []

N, M, P = temp[1:4]

def below_jump(x, y, dis):
    
    dis = dis % ((N-1) * 2)
    x += dis
    if x > N:
        x = N - (x - N)
    if x < 1:
        x = 1 - (x - 1)

    return x, y

def right_jump(x, y, dis):
    
    dis = dis % ((M-1) * 2)
    y += dis
    if y > M:
        y = M - (y - M)
    if y < 1:
        y = 1 - (y - 1)

    return x, y

def upper_jump(x, y, dis):
    
    dis = dis % ((N-1) * 2)
    x -= dis
    if x < 1:
        x = 1 - (x - 1)
    if x > N:
        x = N - (x - N)
    return x, y

def left_jump(x, y, dis):
    
    dis = dis % ((M-1) * 2)
    y -= dis
    if y < 1:
        y = 1 - (y - 1)
    if y > M:
        y = M - (y - M)
    

    return x, y

        
def race(K, S):
    global total_score
    r_c = defaultdict(int) # 이번턴에 뛰었는지 체크
    
    K_q = []
    
    for _ in range(K):
        j_time, x_y, x, y, id = heapq.heappop(q)
        dis = r_d[id]
        t_q = []
        r_c[id] = 1
        nx, ny = below_jump(x, y, dis)
        heapq.heappush(t_q, (-(nx + ny), -nx, -ny)) 
        # (행 번호 + 열 번호가 큰 칸, 행 번호가 큰 칸, 열 번호가 큰 칸)
        nx, ny = upper_jump(x, y, dis)
        heapq.heappush(t_q, (-(nx + ny), -nx, -ny))
        nx, ny = left_jump(x, y, dis)
        heapq.heappush(t_q, (-(nx + ny), -nx, -ny))
        nx, ny = right_jump(x, y, dis)
        heapq.heappush(t_q, (-(nx + ny), -nx, -ny))
        
     
        nx_ny, x, y = heapq.heappop(t_q)
        x = -x
        y = -y        
        total_score += x + y
        r_s[id] -= x + y      
        heapq.heappush(q, (j_time + 1, x + y, x, y, id)) # j, x+y ,x, y
        heapq.heappush(K_q, (-(x + y), -x , -y, -id))
      
    x_y, x, y, id = heapq.heappop(K_q)
    r_s[-id] += S
    
    
        
        
    


for i in range(4, 2*P+4, 2):
    r_d[temp[i]] = temp[i + 1] # i id i+1 거리
    r_s[temp[i]] = 0
    heapq.heappush(q, (0, 2, 1, 1, temp[i]))


for _ in range(Q-1):
    order = list(map(int, input().split()))
    if order[0] == 200:
        race(order[1], order[2])
    elif order[0] == 300:
        r_d[order[1]] *= order[2]
    else:
        score = -int(10e9)
        id = 0
        for id in r_s.keys():
            score = max(score, r_s[id])
        print(score + total_score)
        exit()
            
# 전체 순회를 최대한 피하고
# pq의 순서를 제대로 사용하면서
# 기록하나가는 형식으로 풀면 되는 문제
from collections import defaultdict
import sys
sys.setrecursionlimit(1000000) # 재귀 깊이 제한 늘리기
input = sys.stdin.readline
nodes = defaultdict(int)

class Node:
    def __init__(self, num):
        self.num = num
        self.parent = self
        self.cnt = 1
    def find_parent(self):
        if self.parent != self:
            return self.parent.find_parent()
        return self
            
        

n, m = map(int, input().split())
A = Node(0)
B = Node(0)

for i in range(0, 1000001):
    t = Node(i)
    nodes[i] = t

for _ in range(m):
    order, a, b = map(int, input().split())
    
    if order == 0:
        if a == b:
            continue
        A = nodes[a]
        B = nodes[b]
        P_A = A.find_parent()
        P_B = B.find_parent()
        if P_A == P_B:

            continue
        if P_A.cnt >= P_B.cnt:
            P_B.parent = P_A
            P_A.cnt += P_B.cnt
        else:
            P_A.parent = P_B
            P_B.cnt += P_A.cnt
   
    elif order == 1:
        if a == b:
            print("YES")
            continue        
        A = nodes[a]
        B = nodes[b]
        P_A = A.find_parent()
        P_B = B.find_parent()
        if P_A == P_B:
            print("YES")
        else:
            print("NO")
        
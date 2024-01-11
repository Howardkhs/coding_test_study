N, M, K = map(int, input().split())

idx = N

DIV = 1000000007

storage = [0] * (N + N + 1) # 0 ~ N-1까진 노드 그 뒤는 개별 노드3

class Tree:
    def __init__(self, N):
        self.N = N
        self.sum = 1
        self.lft = None
        self.rgt = None
        self.idx = 0
        self.cover = (0,N-1)
    
    def make_child(self):
        global idx
        if self.N == 1:
            self.sum = (storage[idx] % DIV)
            idx += 1
            return self.sum
        else:
            if self.N % 2 == 0:
                lft = Tree(self.N//2)
                lft.cover = (self.cover[0], self.cover[0] + self.N // 2 - 1)
                self.lft = lft
                self.sum *= lft.make_child() 
                rgt = Tree(self.N//2)
                rgt.cover = (self.cover[0] + self.N // 2, self.cover[1])
                self.rgt = rgt
                self.sum *= rgt.make_child()
                self.sum %= DIV
                return self.sum
            else:
                lft = Tree(self.N//2 + 1)
                lft.cover = (self.cover[0], self.cover[0] + self.N // 2)
                self.lft = lft
                self.sum *= lft.make_child()
                rgt = Tree(self.N//2)
                rgt.cover = (self.cover[0] + self.N // 2 + 1, self.cover[1])
                self.rgt = rgt
                self.sum *= rgt.make_child()
                self.sum %= DIV
                return self.sum
    
    def print_cover(self):
        print(self.cover)
        if self.lft:
            self.lft.print_cover()
        if self.rgt:
            self.rgt.print_cover()
    
    def print_child(self):
        print(self.sum)
        if self.lft:
            self.lft.print_child()
        if self.rgt:
            self.rgt.print_child()
    
    def change_child(self, order, c):
        if self.cover[0] == order and self.cover[1] == order:
            self.sum = c % DIV
            return self.sum

        elif self.lft.cover[0] <= order <= self.lft.cover[1]:
            lft_sum = self.lft.change_child(order, c)
            self.sum = (lft_sum * self.rgt.sum) % DIV
            return self.sum
        else:
            rgt_sum = self.rgt.change_child(order, c)
            self.sum = (rgt_sum * self.lft.sum) % DIV
            return self.sum
    
    def print_multi(self, b, c):
        answer = 1
        if self.cover == (b,c):
            return self.sum
        elif self.lft.cover[0] <= b <= c <= self.lft.cover[1]:
            temp = self.lft.print_multi(b, c)
            answer = (answer * temp) % DIV
            return answer
        elif self.rgt.cover[0] <= b <= c <= self.rgt.cover[1]:
            temp = self.rgt.print_multi(b, c)
            answer = (answer * temp) % DIV
            return answer
        else:
            temp_1 = self.lft.print_multi(b, self.lft.cover[1])
            temp_2 = self.rgt.print_multi(self.rgt.cover[0], c)
            answer = (temp_1 * temp_2) % DIV
            return answer
        
        
        

tree = Tree(N)

for i in range(N):
    num = int(input())
    storage[i + N]  = num
tree.make_child()
# tree.print_child()

for _ in range(M+K):
    a,b,c = map(int, input().split())
    if a == 1:
        tree.change_child(b-1, c)
        # tree.print_child()
        # tree.print_cover()
    elif a == 2:
        answer = tree.print_multi(b-1, c-1)
        print(answer)
        
        
    

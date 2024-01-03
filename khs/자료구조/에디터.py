string = str(input())

M = int(input())

class String:
    def __init__(self, alpha="0"):
        self.alpha = alpha
        self.lft = None
        self.rgt = None
    
    def add_right(self, alpha):
        self.rgt = String(alpha)
        self.rgt.lft = self
        return self.rgt


string = list(string)

cursor = String()
start = cursor

for c in string:
    cursor = cursor.add_right(c)
# print(cursor.alpha)
# print(start.alpha)
# while True:
#     start = start.rgt
#     print(start.alpha, end="")
    
#     if start.rgt == None:
#         break
# print()
# while True:
    
#     print(cursor.alpha, end="")
#     cursor = cursor.lft
#     if cursor.lft == None:
#         break
for _ in range(M):
    order = list(map(str , input().split()))
    if order[0] == 'L':
        if cursor.lft != None: # none 대체
            cursor = cursor.lft
 
    if order[0] == 'D':
        if cursor.rgt != None:
            cursor = cursor.rgt

    if order[0] == 'B':
        if cursor.alpha != "0":
            temp = cursor
     
            cursor.lft.rgt = cursor.rgt
            if cursor.rgt:
                cursor.rgt.lft = cursor.lft
            cursor = cursor.lft
            temp.lft = None
            temp.rgt = None         
        
    if order[0] == 'P':
        c = String(order[1])
        if cursor.rgt == None:
            c.lft = cursor
            cursor.rgt = c
            cursor = c 
            continue
        else:
            c.rgt = cursor.rgt
            c.lft = cursor
            c.lft.rgt = c
            c.rgt.lft = c
            cursor = c
        
while True:
    start = start.rgt
    print(start.alpha, end="")
    
    if start.rgt == None:
        break
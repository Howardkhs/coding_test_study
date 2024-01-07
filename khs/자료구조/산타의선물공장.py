from collections import defaultdict
dict = defaultdict
import sys
input = sys.stdin.readline

q = int(input())

n, m  = 0,0 
belts = [1] * 11
box_container = dict(int)
belt_num = dict(int)
heads = [0] * 11
tails = [0] * 11

class Box:
    def __init__(self, id, w):
        self.id = id
        self.w = w
        self.prv = None
        self.nxt = None



def set_factory(order):
    global n, m
    n, m = order[0], order[1]
    
    belt_number = 1
    while True:
        if belt_number == m + 1:
            break
        for i in range(n//m):
            id, w = order[n//m * (belt_number - 1) + 2+i], order[n//m * (belt_number - 1)+n+2+i]
            b = Box(id, w)
            if heads[belt_number] == 0 and tails[belt_number] == 0:
                heads[belt_number] = b
                tails[belt_number] = b
                belt_num[id] = belt_number
                box_container[id] = b

            elif tails[belt_number]:
                belt_num[id] = belt_number
                tail = tails[belt_number]
                tail.nxt = b
                b.prv = tail
                tails[belt_number] = b
                box_container[id] = b
        belt_number += 1
                

def box_drop(w_max):
    tot_w = 0

    for i in range(1,m+1):
        box = heads[i]

        if box == -1 or box == 0: # 0이면 빈벨트 -1 이면 고장
            continue
        if box.w <= w_max:
            if heads[i] == tails[i]:
                heads[i] = 0
                tails[i] = 0
                belt_num[box.id] = -1
                tot_w += box.w
                box_container[box.id] = -1
            else:
                heads[i] = box.nxt
                box.nxt.prv = None
                box.nxt = None
                belt_num[box.id] = -1
                tot_w += box.w
                box_container[box.id] = -1
        else:
            if heads[i] == tails[i]:
                continue
            heads[i] = box.nxt
            box.nxt.prv = None
            box.nxt = None
            tail = tails[i]
            tail.nxt = box
            box.prv = tail
            tails[i] = box
        
    print(tot_w)

def remove_box(r_id):
    if box_container[r_id] == -1 or box_container[r_id] == 0:
        print(-1)
        return
    belt_number = belt_num[r_id]
    box = box_container[r_id]
    
    if heads[belt_number] == tails[belt_number]:
        heads[belt_number] = 0
        tails[belt_number] = 0
        belt_num[box.id] = -1
        box_container[box.id] = -1
    
    elif heads[belt_number] == box:
        heads[belt_number] = box.nxt
        box.nxt.prv = None
        box.nxt = None
        belt_num[box.id] = -1
        box_container[box.id] = -1
    elif tails[belt_number] == box:
        tails[belt_number] = box.prv
        box.prv.nxt= None
        box.prv = None
        belt_num[box.id] = -1
        box_container[box.id] = -1
    else:
        box.nxt.prv = box.prv
        box.prv.nxt = box.nxt
        box.nxt = None
        box.prv = None
        belt_num[box.id] = -1
        box_container[box.id] = -1
    
    print(r_id)
    
def check_box(f_id):
    if box_container[f_id] == -1 or box_container[f_id] == 0:
        print(-1)
        return
    belt_number = belt_num[f_id]
    box = box_container[f_id]
    
    if heads[belt_number] == tails[belt_number]:
        print(belt_number)
        return
    elif heads[belt_number] == box:
        print(belt_number)
        return
    else:
        tail = tails[belt_number]
        head = heads[belt_number]
        heads[belt_number] = box
        tails[belt_number] = box.prv
        box.prv.nxt = None
        box.prv =  None
        head.prv = tail
        tail.nxt = head
        print(belt_number)
        return

def broken_belt(b_num):
    if belts[b_num] == -1:
        print(-1)
        return
    
    start = b_num
    while True:
        b_num += 1

        if b_num == m + 1:
            b_num = 1
        if belts[b_num] == 1:
            belts[start] = -1
            if heads[start] == 0:
                print(start)
                return
            
            box = heads[start]
            while box != None:
                belt_num[box.id] = b_num
                box = box.nxt
            head = heads[start]
            tail = tails[start]
            head.prv = tails[b_num]
            tails[b_num].nxt = head
            tails[b_num] = tail
            
            heads[start] = 0
            tails[start] = 0
            print(start)
            return
            
               
    


for _ in range(q):
    order = list(map(int, input().split()))
    if order[0] == 100:
        set_factory(order[1:])
    elif order[0] == 200:
        box_drop(order[1])
    elif order[0] == 300:
        remove_box(order[1])
    elif order[0] == 400:
        check_box(order[1])
    elif order[0] == 500:
        broken_belt(order[1])

    
    # for i in range(1,m+1):
    #     print("belt number : ", end='')
    #     print(i)
    #     if belts[i] == -1:
    #         print("belt broken")
    #         continue
    #     box = heads[i]
    #     while box != None:
    #         print(box.id, box.w)
    #         box = box.nxt
    
    
    # for i in range(1,m+1):
    #     print("Head, tail : ", end='')
    #     print(i)
    #     if belts[i] == -1:
    #         print("belt broken")
    #         continue
    #     head = heads[i]
    #     tail = tails[i]
    #     print(head.id, head.w)
    #     print(tail.id, tail.w)
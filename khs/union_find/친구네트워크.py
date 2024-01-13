from collections import defaultdict
import sys
dict = defaultdict
input = sys.stdin.readline
T = int(input())

for _ in range(T):
    net = dict(set)    
    F = int(input())
    set_nums = 1
    idx_dict = dict(int)
    
    for _ in range(F):
        name_1, name_2 = map(str, input().split())
        if set_nums == 1:
            net[set_nums].add(name_1)
            net[set_nums].add(name_2)
            idx_dict[name_1] = set_nums
            idx_dict[name_2] = set_nums
            set_nums += 1
            print(2)
            continue
        
        idx_1 = idx_dict[name_1]
        idx_2 = idx_dict[name_2]

        if idx_1 == 0 and idx_2 == 0:
            net[set_nums].add(name_1)
            net[set_nums].add(name_2)
            idx_dict[name_1] = set_nums
            idx_dict[name_2] = set_nums
            set_nums += 1
            print(2)
        elif idx_1 == idx_2:
            continue

        elif idx_1 and idx_2:

            net[idx_1].update(net[idx_2])    
            net[idx_2] = net[idx_1]     
            print(len(net[idx_1]))
            
        else:
            if idx_2:
                net[idx_2].add(name_1)
                idx_dict[name_1] = idx_2
                print(len(net[idx_2]))
            else:
                net[idx_1].add(name_2)
                idx_dict[name_2] = idx_1
                print(len(net[idx_1]))
    
        print(net)
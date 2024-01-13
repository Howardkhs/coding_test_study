N, M = 3, 5

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

print(below_jump(1,1,5))
print(upper_jump(1,1,5))
print(left_jump(1,1,5))
print(right_jump(1,1,5))
import sys
sys.stdin = open('sample_input.txt', 'r')
Testcases = int(input())

def check(arr, temp_arr):
    index = 0
    for _ in range(len(arr)):
        if arr[_] == 1:
            temp_arr[index] -= 1
            if temp_arr[index] == 0:
                index += 1
                if index == len(data):
                    break
        elif arr[_] == 0:
            if temp_arr[index] != 0:
                temp_arr[index] = data[index]
    for _ in temp_arr:
        if _ != 0:
            return False # center를 키운다.
    else:
        return True # center를 줄인다.

def inserting(s, g):
    center = (s + g) // 2
    if visited[center] == 0:
        check_arr = [0 for _ in range(len(Flash))]
        temp_data = [0 for _ in range(len(data))]
        for _ in range(len(data)):
            temp_data[_] = data[_]
        for _ in range(len(Flash)):
            if Flash[_] <= center:
                check_arr[_] = 1

        if check(check_arr, temp_data) == False:
            if s >= g:
                return
            else:
                inserting(center + 1, g)
        else:
            visited[center] = 1
            inserting(s, center - 1)


for testcase in range(1, Testcases + 1):
    N, K = list(map(int,input().split()))
    Flash = list(map(int,input().split()))
    data = list(map(int,input().split()))

    visited = [0 for _ in range(200001)] # 이미 방문한 값은 다시 방문할 필요가 없으니 만들었습니다.

    inserting(min(Flash), max(Flash)) # 최소 값과 최댓 값 사이에 있을 정답을 찾아봅시다.

    for _ in range(len(visited)):
        if visited[_] == 1:
            print('#{} {}'.format(testcase, _))
            break
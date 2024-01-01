#include <iostream>
#include <cstdio>
#include <queue>
#include <algorithm>
#include <functional>
 
#define MAX_N 100002
 
using namespace std;
 
priority_queue<int, vector<int>, less<int>> max_heap;
priority_queue<int, vector<int>, greater<int>> min_heap;
int arr[MAX_N];
 
/*
중간 값 구하기 알고리즘
1. 최대 힙의 크기는 최소 힙의 크기와 같거나, 하나 더 크다.
2. 최대 힙의 최대 원소는 최소 합의 최소 원소보다 작거나 같다.
이때 알고리즘에 맞지 않다면 최대 힙, 최소 힙의 가장 위의 값을 swap해준다.
*/
 
int main()
{
    int n, val;
    scanf("%d", &n);
 
    while (n--)
    {
        scanf("%d", &val);
 
        // By 1
        if (max_heap.empty())
            max_heap.push(val);
 
        else if (max_heap.size() == min_heap.size())
            max_heap.push(val);
 
        else
            min_heap.push(val);
 
        // By 2
        if (!max_heap.empty() && !min_heap.empty() && !(max_heap.top() <= min_heap.top()))
        {
            int a = max_heap.top();
            int b = min_heap.top();
 
            max_heap.pop();
            min_heap.pop();
 
            max_heap.push(b);
            min_heap.push(a);
        }
 
 
        printf("%d\n", max_heap.top());
    }
 
    return 0;
}
 
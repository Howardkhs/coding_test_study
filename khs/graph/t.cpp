#include<iostream>
#include <queue>
#include <vector>
#include <algorithm>
using namespace std;

struct pairs{
    int dis;
    int b; //before
};

typedef pair<int, int> P; // 노드, 거리

bool compare(pairs a, pairs b){
    return a.dis >= b.dis;
}

int T, N, M, a, b, c;

int main(int argc, char** argv)
{   
    ios::sync_with_stdio(false);
	cin.tie(); cout.tie();
	int test_case;
	
    pairs arr[3];
    arr[0] = {2, 4};
    arr[1] = {3, 5};
    arr[2] = {4, 2};

    sort(arr, arr + 3, compare);

    cout << arr[0].dis << " " << arr[1].dis << " " << arr[2].dis << " " << endl;
	
}
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
vector<int> a;
int N, K; // K 버틸수있는무게
int W, V;
int arr[100001] = {0};
int v[100001] = {0};
int max_v;

typedef pair <int, int> P;
queue <P> pq;

int main(){

    
    cin >> N >> K;
    for (int cnt = 0; cnt < N; cnt++){
        cin >> W >> V;
        P now = {W, -V};
        pq.push(now);
    }


    while (!pq.empty()){
        P now = pq.front();
        W = now.first;
        V = -now.second;
        pq.pop();
        for (int i = K; i > W-1; i--){
            arr[i] = max(arr[i], arr[i - W] + V);
        }
    }
    // cout << "after gravity\n";

    // for (int i = 0; i < 13; i++){
  
    //     cout << arr[i] << " ";

    // }
    cout << arr[K];
}
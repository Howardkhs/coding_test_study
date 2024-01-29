#include <queue>
#include <unordered_map>
#include <iostream>

using namespace std;

typedef pair<int, int> P; // 목적지, ost

unordered_map<int,vector<P>> Scitys; // 허브에서 출발할대 구하는 용도
unordered_map<int,vector<P>> Ecitys; // 다시 돌아올때 구하는 용도
// vector<P> citys;
struct pairs{
    int dis;
    int now;
};

struct compare{
    bool operator()(pairs &a, pairs &b){
        if (a.dis != b.dis)
            return a.dis >= b.dis;
        return a.now >= b.now;
    }
};


int init(int N, int sCity[], int eCity[], int mCost[]) {
    Scitys.clear();
    for (int i = 0; i < N; i++){
        int start = sCity[i];
        int end = eCity[i];
        int cost = mCost[i];
        Scitys[start].push_back({end, cost});
        Ecitys[end].push_back({start, cost});
    }
	return distance(Scitys.begin(), Scitys.end());
}

void add(int sCity, int eCity, int mCost) {

    int start = sCity;
    int end = eCity;
    int cost = mCost;
    Scitys[start].push_back({end, cost});
    Ecitys[end].push_back({start, cost});
    
	return;
}

int cost(int mHub) {
    unordered_map<int, int> visited;
    unordered_map<int, int> visited2;
    unordered_map<int, int> StartX;
    unordered_map<int, int> EndX;

    
    pairs a = {0, mHub};  // dis now
    priority_queue<pairs, vector<pairs>, compare> pq;
    pq.push(a);

    while (!pq.empty()){
        a = pq.top();
        pq.pop();
        int dis = a.dis;
        int now = a.now;
        if (visited[now] == 1)
            continue;
        visited[now] = 1;
        StartX[now] = dis;
        for (auto p = Scitys[now].begin() ; p != Scitys[now].end(); p++){
            int ndis = dis + p->second;
            int nnow = p->first;
            if (visited[nnow] == 1)
                continue;
            pq.push({ndis, nnow});
        }     
    }
    a = {0, mHub};
    pq.push(a); // dis now
    while (!pq.empty()){
        a = pq.top();
        pq.pop();
        int dis = a.dis;
        int now = a.now;
        if (visited2[now] == 1)
            continue;
        visited2[now] = 1;
        EndX[now] = dis;
        for (auto p = Ecitys[now].begin() ; p != Ecitys[now].end(); p++){
            int ndis = dis + p->second;
            int nnow = p->first;
            if (visited2[nnow] == 1)
                continue;
            pq.push({ndis, nnow});
        }     
    }

    StartX[mHub] = 0;
    EndX[mHub] = 0;
    int answer = 0;
    for (auto p = StartX.begin() ; p != StartX.end(); p++){
        answer += p->second;
    }
    for (auto p = EndX.begin() ; p != EndX.end(); p++){
        answer += p->second;
    }
    // cout << answer << endl;

	return answer;
}
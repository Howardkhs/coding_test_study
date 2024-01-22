#include<iostream>
#include <queue>
#include <vector>

using namespace std;


struct pairs{
    long long dis;
    long long now;
    long long start;
};

typedef pair<long long, long long> P; // 노드, 거리

struct compare{
    bool operator()(pairs &a, pairs &b){
        if (a.dis != b.dis)
            return a.dis >= b.dis;
        return a.now >= b.now;
    }
};



long long T, N, M, X, a, b, c;
long long answer = 0;
int main(int argc, char** argv)
{   
    ios::sync_with_stdio(false);
	cin.tie(); cout.tie();
	int test_case;


	// freopen("input.txt", "r", stdin);
	cin>>T;
	/*
	   여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
	*/
    
	for(test_case = 1; test_case <= T; ++test_case)
	{      
        cin >> N >> M >> X;
        vector<vector<P>> graph;
        vector<vector<P>> graph_2;
        for (int i = 0; i < N + 1; i++){
            vector<P> a;
            graph.push_back(a);
        }

        for (int i = 0; i < N + 1; i++){
            vector<P> a;
            graph_2.push_back(a);
        }
        priority_queue<pairs, vector<pairs>, compare> pq;

        while(M--){
            cin >> a >> b >> c;
            graph[a].push_back({b,c});
            graph_2[b].push_back({a,c});
        }
        int visited[50001] = {0,};
        int StartX[50001] = {0,};
        int EndX[50001] = {0,};
        // x번에서 출발하는 거 기록
        pairs a = {0, X, 0};
        pq.push(a); // dis now

        while(!pq.empty()){
            a = pq.top();
            pq.pop();
            long long dis = a.dis;
            long long now = a.now;
            
            if (visited[now] == 1)
                continue;
            visited[now] = 1;
            StartX[now] = dis;
            for (auto p = graph[now].begin(); p != graph[now].end(); p++){
                long long ndis = dis + p->second; // 노드 거리
                long long nnow = p->first;
                if (visited[nnow] == 1)
                    continue;
                pq.push({ndis, nnow, 0});
            }

        }
        a = {0, X, 0};
        pq.push(a); // dis now
        int visited2[50001] = {0,};
        while(!pq.empty()){
            a = pq.top();
            pq.pop();
            long long dis = a.dis;
            long long now = a.now;
            if (visited2[now] == 1)
                continue;
            visited2[now] = 1;
            EndX[now] = dis;
            for (auto p = graph_2[now].begin(); p != graph_2[now].end(); p++){
                long long ndis = dis + p->second; // 노드 거리
                long long nnow = p->first;
                if (visited2[nnow] == 1)
                    continue;
                pq.push({ndis, nnow, 0});
            }
        }

        // for(int i = 0; i < N + 1; i++){
        //     cout << StartX[i] << " ";
        // }
        // cout << endl;

        // for(int i = 0; i < N + 1; i++){
        //     cout << EndX[i] << " ";
        // }
        // cout << endl;
        int answer = 0;
        for (int i = 1; i < N + 1; i++){
            answer = max(answer, StartX[i] + EndX[i]);
        }
        cout << '#' << test_case << ' ' << answer << '\n';
      
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}

// 단일통행일 때 방향으 ㄹ반대로 하면 다시 구할 숭있다. 한곳에서 나갈때 유용
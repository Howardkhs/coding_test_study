#include<iostream>
#include <queue>
#include <vector>

using namespace std;

struct pairs{
    long long dis;
    long long b; //before
    long long now;
};

typedef pair<long long, long long> P; // 노드, 거리

struct compare{
    bool operator()(pairs &a, pairs &b){
        if (a.dis != b.dis)
            return a.dis >= b.dis;
        if (a.b != b.b)
            return a.b >= b.b;
        return a.now >= b.now;
    }
};

long long T, N, M, a, b, c;
long long answer = 0;
int main(int argc, char** argv)
{   
    ios::sync_with_stdio(false);
	cin.tie(); cout.tie();
	int test_case;


	freopen("input.txt", "r", stdin);
	cin>>T;
	/*
	   여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
	*/
    
	for(test_case = 1; test_case <= T; ++test_case)
	{      
        cin >> N >> M;
        answer = 0;
        
        vector<vector<P>> graph;
        for (int i = 0; i < N + 1; i++){
            vector<P> a;
            graph.push_back(a);
        }
        priority_queue<pairs, vector<pairs>, compare> pq;
        
        while(M--){
            cin >> a >> b >> c;
            graph[a].push_back({b,c});
            graph[b].push_back({a,c});
        }
        int visited[200001] = {0,};

        pairs a = {0,0,1};
        pq.push(a); // dis b now

        while(!pq.empty()){
            a = pq.top();
            pq.pop();
            long long dis = a.dis;
            long long b = a.b;
            long long now = a.now;

            if (visited[now] == 1)
                continue;
            answer += b;
            visited[now] = 1;
            for (auto p = graph[now].begin(); p != graph[now].end(); p++){
                long long ndis = dis + p->second; // 노드 거리
                long long nb = p->second;
                long long nnow = p->first;
                if (visited[nnow] == 1)
                    continue;
                pq.push({ndis, nb, nnow});
            }
        }
        cout << '#' << test_case << ' ' << answer << '\n';


	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
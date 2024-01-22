#include<iostream>
#include <queue>
#include <vector>

using namespace std;

struct pairs{
    int dis;
    int b; //before
    int now;
};

typedef pair<int, int> P; // 노드, 거리

struct compare{
    bool operator()(pairs &a, pairs &b){
        if (a.dis != b.dis)
            return a.dis >= b.dis;
        return a.b >= b.b;
    }
};

int T, N, M, a, b, c;

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
        int answer = 0;
        vector<P> graph[200001];
        priority_queue<pairs, vector<pairs>, compare> pq;
        cin >> N >> M;
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
            int dis = a.dis;
            int b = a.b;
            int now = a.now;

            if (visited[now] == 1)
                continue;
            answer += b;
            visited[now] = 1;
            for (auto p = graph[now].begin(); p != graph[now].end(); p++){
                int ndis = dis + p->second; // 노드 거리
                int nb = p->second;
                int nnow = p->first;
                if (visited[nnow] == 1)
                    continue;
                pq.push({ndis, nb, nnow});
            }
        }
        cout<< '#' << test_case << ' ' << answer << '\n';


	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
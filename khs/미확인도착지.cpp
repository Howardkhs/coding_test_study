#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <algorithm>

using namespace std;
#define INF 10000000
#define MAX_N 2001

typedef pair <int, int> P;
typedef vector <P> V;
// typedef tuple <int, int , int> T;
int g, h;
struct T{
    int first, second, third;

};

int dis[MAX_N];
V graph[MAX_N];
P check[MAX_N];

struct Compare{
    bool operator()(const T &a, const T &b){
        if (a.first != b.first)
            return a.first > b.first;
        else if(a.second != b.second)
            return a.second > b.second;
        return a.third > b.third;
    }
};

void dijkstra(int start){
    priority_queue<T, vector<T>, Compare> pq;
    T t = {0, start, 0};
    pq.push(t);
    

    while(!pq.empty()){
        auto t = pq.top();
        int d, now, p;
        d = t.first;
        now = t.second;
        p = t.third;
        pq.pop();

        if (dis[now] < d)
            continue;

        for (auto c = graph[now].begin(); c < graph[now].end(); c++){
            int _d = d + c->second;
            int temp_p = p;

            if ((now == g && c->first == h) or (now == h && c->first == g))
                temp_p = 1;

            if (_d <= dis[c->first]){
                if (dis[c->first] == _d && check[c->first].first == 1)
                    continue;
                check[c->first] = {temp_p, _d};
                dis[c->first] = _d;
                T pq_push = {_d, c->first, temp_p};
                pq.push(pq_push);

            }
        }

    }

}


int main(){
    int T, n, m, t, s, a, b, d, x;
    cin >> T;

    while (T--){
        fill(dis, dis + MAX_N, 0);
        fill(graph, graph + MAX_N, V()); // 벡터의 경우 따로 초기화
        fill(check, check + MAX_N, P(0, 0));
        cin >> n >> m >> t;
        for  (int i = 0; i < n + 1; i++){
            dis[i] = INF;
        }
        cin >> s >> g >> h;
        for  (int i = 0; i < n + 1; i++){
            check[i] = {0,0};
        }
        dis[s] = 0;

        while (m--){
            cin >> a >> b >> d;
            graph[a].push_back({b,d});
            graph[b].push_back({a,d});
        }
        dijkstra(s);

        // for (int i = 0; i < n + 1; i++){
        //     for (auto j = graph[i].begin(); j < graph[i].end(); j++){
        //         cout << '(' << j->first << " " << j->second << ')';
        //     }
        //     cout << endl;
        // }

        // for (int i = 0; i < n + 1; i++){
        //     cout << dis[i] << " ";
        // }
        // cout << endl;

        // for (int i = 0; i < n + 1; i++){
        //     cout << '(' << check[i].first << " " << check[i].second  << ')';
        // }
        // cout << endl;






        priority_queue<int, vector<int>, greater<int>> q;
        while (t--){
            cin >> x;
            if (check[x].first == 1)
                q.push(x);
        }
        while (!q.empty()){
            cout << q.top() << " ";
            q.pop();
        }
        cout << "\n";
        
    }
}
#include <iostream>
#include <climits>
#include <queue>
#include <vector>

using namespace std;

using i2 = pair<int, int>;

int N, P, K;
vector<i2> graph[1001];

int dijkstra(int price) {
	int distance[1001] = {};
	priority_queue<i2> pq;
	distance[1] = 0;
	for (int i = 2; i <= N; i++) {
		distance[i] = INT32_MAX;
	}
	pq.push(i2(0, 1));
	while (!pq.empty()) {
		int cost = -pq.top().first;
		int node = pq.top().second;
		int newCost = 0;
		pq.pop();
		for (int i = 0; i < graph[node].size(); i++) {
			if (graph[node][i].second > 0) {
				if (graph[node][i].second > price) {
					newCost = cost + 1;
					if (newCost < distance[graph[node][i].first]) {
						distance[graph[node][i].first] = newCost;
						pq.push(i2(-newCost, graph[node][i].first));
					}
				}
				else {
					newCost = cost;
					if (newCost < distance[graph[node][i].first]) {
						distance[graph[node][i].first] = newCost;
						pq.push(i2(-newCost, graph[node][i].first));
					}
				}
			}
		}
	}
	
	return distance[N];
}

int main() {
	int s, e, v;
	cin >> N >> P >> K;
	for (int i = 0; i < P; i++) {
		cin >> s >> e >> v;
		graph[s].push_back(i2(e, v));
		graph[e].push_back(i2(s, v));
	}

	int start = 0, end = 1000000, middle = 0;
	while (true) {
		middle = (start + end) / 2;
		if (dijkstra(middle) > K) {
			if (start == end) {
				cout << -1;
				return 0;
			}
			start = middle + 1;
		}
		else {
			if (start == end) {
				cout << start;
				return 0;
			}
			end = middle;
		}

	}

	return 0;
}

/*
처음에 dfs를 사용해서 완전탐색을 했는데 예상은 했지만 시간초과를 받았다..
도저히 다른 방법이 생각 안나서 구글의 도움을 받았다.


정답을 N이라고 가정했을 때 N보다 큰 비용의 선을 K개 이하로 사용할 수 있으면
정답은 N보다 작거나 같을 것이고 그렇지 않다면 정답은 N보다 클 것이다.

이 점을 토대로 다익스트라, 이분탐색을 사용하면 해결할 수 있다.
*/
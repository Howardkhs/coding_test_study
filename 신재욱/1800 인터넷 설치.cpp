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
ó���� dfs�� ����ؼ� ����Ž���� �ߴµ� ������ ������ �ð��ʰ��� �޾Ҵ�..
������ �ٸ� ����� ���� �ȳ��� ������ ������ �޾Ҵ�.


������ N�̶�� �������� �� N���� ū ����� ���� K�� ���Ϸ� ����� �� ������
������ N���� �۰ų� ���� ���̰� �׷��� �ʴٸ� ������ N���� Ŭ ���̴�.

�� ���� ���� ���ͽ�Ʈ��, �̺�Ž���� ����ϸ� �ذ��� �� �ִ�.
*/
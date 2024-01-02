#include <iostream>
#include <queue>
#include <utility>

#define min(a, b) (((a) < (b)) ? (a) : (b))

using namespace std;

using i2 = pair<int, int>;

int N, M;

int graph[501][501];

void floyd_warshall() {
	int A, B, C;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			for (int k = 1; k <= N; k++) {
				graph[j][k] = min(graph[j][k], graph[j][i] + graph[i][k]);
			}
		}
	}

	for (int i = 0; i < M; i++) {
		cin >> A >> B >> C;
		if (graph[A][B] <= C) {
			cout << "Enjoy other party\n";
		}
		else {
			cout << "Stay here\n";
		}
	}
}

bool dijkstra(int A, int B, int C) {
	int minCost[501] = {0};
	priority_queue<i2> pq;
	for (int i = 1; i <= N; i++) {
		minCost[i] = 1000000001;
	}

	pq.push(i2(0, A));
	while (!pq.empty()) {
		int cost = -pq.top().first;
		int cur = pq.top().second;
		int newCost = 0;
		pq.pop();

		for (int i = 1; i <= N; i++) {
			if (i != cur) {
				newCost = cost + graph[cur][i];
				if (newCost < minCost[i]) {
					minCost[i] = newCost;
					if (newCost <= C) {
						if (i == B) {
							return true;
						}
						pq.push(i2(-newCost, i));
					}
				}
			}
		}
	}

	return (minCost[B] <= C);
}

int main() {
	int A, B, C;
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cin >> N >> M;
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			cin >> graph[i][j];
		}
	}


	//dijkstra
	for (int i = 0; i < M; i++) {
		cin >> A >> B >> C;

		if (graph[A][B] <= C) {
			cout << "Enjoy other party\n";
		}
		else {
			if (dijkstra(A, B, C)) {
				cout << "Enjoy other party\n";
			}
			else {
				cout << "Stay here\n";
			}
		}
	}

	//floyd-warshall
	//floyd_warshall();
	return 0;
}

/*
다익스트라, 플로이드-워셜 두 방법으로 해결할 수 있지만
플로이드-워셜이 더 빠르다.
*/
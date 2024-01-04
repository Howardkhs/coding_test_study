#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;
using i2 = pair<int, int>;

int N, M, K;
int markets[5];
bool hasMarket[10001];
vector<i2> graph[10001];
int minCost[5][10001];

void dijkstra() {
	int market;
	for (int i = 0; i < K; i++) {
		market = markets[i];
		for (int j = 1; j <= N; j++) {
			minCost[i][j] = INT32_MAX;
		}
		minCost[i][market] = 0;

		priority_queue<i2> pq;
		pq.push(i2(0, market));
		while (!pq.empty()) {
			int cost = -pq.top().first;
			int cur = pq.top().second;
			int newCost;
			pq.pop();
			for (int j = 0; j < graph[cur].size(); j++) {
				newCost = cost + graph[cur][j].second;
				if (newCost < minCost[i][graph[cur][j].first]) {
					minCost[i][graph[cur][j].first] = newCost;
					pq.push(i2(-newCost, graph[cur][j].first));
				}
			}
		}

		/*for (int j = 1; j <= N; j++) {
			cout << minCost[i][j] << ' ';
		}
		cout << '\n';*/
	}
	//cout << '\n';
}

int bruteforce() {
	int ret = INT32_MAX;
	int distance = 0;
	vector<int> permuVec;
	for (int i = 0; i < K; i++) {
		permuVec.push_back(i);
	}

	do {
		for (int i = 1; i <= N; i++) {
			if (!hasMarket[i]) {
				distance = 0;
				distance += minCost[permuVec[0]][i];
				for (int j = 0; j < K - 1; j++) {
					distance += minCost[permuVec[j]][markets[permuVec[j + 1]]];
				}
				distance += minCost[permuVec[K - 1]][i];
				ret = ret < distance ? ret : distance;
			}
		}
	} while (next_permutation(permuVec.begin(), permuVec.end()));

	return ret;
}

int main() {
	int n1, n2, l;
	cin >> N >> M >> K;
	for (int i = 0; i < K; i++) {
		cin >> markets[i];
		hasMarket[markets[i]] = true;
	}
	for (int i = 0; i < M; i++) {
		cin >> n1 >> n2 >> l;
		graph[n1].push_back(i2(n2, l));
		graph[n2].push_back(i2(n1, l));
	}
	dijkstra();
	cout << bruteforce();
	return 0;
}

/*
ó���� ���� �ϳ��ϳ� �� ���ͽ�Ʈ�� ����ؼ� �ð��ʰ��� �޾Ҵ�.
������ �ִ� ���ÿ� ���ؼ��� ���ͽ�Ʈ��� �ٸ� ���õ�� ���� �ּ� �Ÿ��� ���ϰ�
���ϵ��� �� �湮�� �� �ִ� ��� ����� ���� �ּ� �Ÿ��� ���ϸ� �ȴ�. ((N-K) * K!)
*/
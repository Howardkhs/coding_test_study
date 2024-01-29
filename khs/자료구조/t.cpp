#include <iostream>
#include <queue>

using namespace std;

int N, K, Ans;
int Nums[11];

void Input() {
	int i;
	scanf("%d", &N);
	for (i = 0; i < N; i++) {
		scanf("%d", &Nums[i]);
	}
	scanf("%d", &K);
}

void GetAns() {
	int i;
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	pq.push(make_pair(0, K));
	while (pq.top().second) {
		pair<int, int> cur = pq.top();
		pq.pop();

		pq.push(make_pair(cur.first + cur.second, 0));
		for (i = 0; i < N; i++) {
			pq.push(make_pair(cur.first + cur.second % Nums[i], cur.second / Nums[i]));
		}
	}
	Ans = pq.top().first;
}

int main() {
	int t, t_i;
	scanf("%d", &t);
	for (t_i = 1; t_i <= t; t_i++) {
		Input();
		GetAns();
		printf("#%d %d\n", t_i, Ans);
	}
	return 0;
}
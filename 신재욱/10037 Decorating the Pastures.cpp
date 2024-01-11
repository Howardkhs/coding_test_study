#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N, M;
vector<int> graph[50001];
int signs[50001];

int BFS() {
	int positive, negative, ret = 0;
	queue<int> q;
	for (int i = 1; i <= N; i++) {
		if (signs[i] == 0) {
			positive = 0;
			negative = 0;
			signs[i] = 1;
			q.push(i);
			positive++;
			while (!q.empty()) {
				int node = q.front(), sign = signs[node];
				q.pop();
				for (int j = 0; j < (int)graph[node].size(); j++) {
					if (signs[graph[node][j]] == 0) {
						signs[graph[node][j]] = -sign;
						q.push(graph[node][j]);
						if (sign > 0) {
							negative++;
						}
						else {
							positive++;
						}
					}
					else {
						if (signs[graph[node][j]] == sign) {
							return -1;
						}
					}
				}
			}
			ret += positive > negative ? positive : negative;
		}
	}
	return ret;
}

int main() {
	int A_i, B_i;
	cin >> N >> M;
	for (int i = 0; i < M; i++) {
		cin >> A_i >> B_i;
		graph[A_i].push_back(B_i);
		graph[B_i].push_back(A_i);
	}

	cout << BFS();
	return 0;
}

/*
인접한 목장끼리 다른 문자(F, J)를 사용해야될 때 J의 최대 개수를 구하는 문제다.


BFS를 사용해서 방문하지 않은 목장에 진행할 때 마다 문자를 바꿔주고,
방문한 목장의 경우 다른 문자가 사용되었는지 확인하고, 같은 문자가 사용되었다면 -1을 출력하고 종료하면 된다.
탐색을 마쳤다면 두 문자 중 많이 사용된 문자를 리턴 값에 더해주면 된다.
위를 모든 목장에 대해 반복.
*/
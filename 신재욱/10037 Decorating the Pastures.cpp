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
������ ���峢�� �ٸ� ����(F, J)�� ����ؾߵ� �� J�� �ִ� ������ ���ϴ� ������.


BFS�� ����ؼ� �湮���� ���� ���忡 ������ �� ���� ���ڸ� �ٲ��ְ�,
�湮�� ������ ��� �ٸ� ���ڰ� ���Ǿ����� Ȯ���ϰ�, ���� ���ڰ� ���Ǿ��ٸ� -1�� ����ϰ� �����ϸ� �ȴ�.
Ž���� ���ƴٸ� �� ���� �� ���� ���� ���ڸ� ���� ���� �����ָ� �ȴ�.
���� ��� ���忡 ���� �ݺ�.
*/
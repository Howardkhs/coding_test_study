#include <iostream>
#include <algorithm>
#include <utility>
#include <queue>

using namespace std;

using i2 = pair<int, int>;

int N;
i2 warmHoles[12];

int indexOfPair[12];
i2 pairs[6];

int countNum = 0;

int findFirstMeetWarmHole(i2 warmhole) {
	int x = warmhole.first, y = warmhole.second;
	int minX = 1000000001;
	int ret = -1;
	for (int i = 0; i < N; i++) {
		if ((warmHoles[i].first > x) && (warmHoles[i].second == y)) {
			if (warmHoles[i].first < minX) {
				minX = warmHoles[i].first;
				ret = i;
			}
		}
	}

	return ret;
}

bool hasCycle() {
	bool visited[12] = {};

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			visited[j] = false;
		}

		queue<int> q;
		q.push(findFirstMeetWarmHole(warmHoles[i]));
		while (!q.empty()) {
			int cur = q.front(), next;
			q.pop();
			if (cur == -1) {
				break;
			}
			
			next = (cur == pairs[indexOfPair[cur]].first
				? pairs[indexOfPair[cur]].second : pairs[indexOfPair[cur]].first);
			if (visited[next]) {
				//cout << "true" << '\n';
				return true;
			}
			else {
				visited[next] = true;
				q.push(findFirstMeetWarmHole(warmHoles[next]));
			}
		}
	}
	//cout << "false" << '\n';
	return false;
}

void getCasesOfPairs(int idx, int firstPair) {
	if (idx == (N / 2 - 1)) {
		for (int i = firstPair + 1; i < N; i++) {
			if (indexOfPair[i] == idx) {
				pairs[idx] = i2(firstPair, i);
			}
		}

		/*for (int i = 0; i < N / 2; i++) {
			cout << pairs[i].first << pairs[i].second << ' ';
		}
		cout << '\n';*/

		if (hasCycle()) {
			countNum++;
		}
		return;
	}
	int nextFirstPair = -1;
	for (int i = firstPair + 1; i < N; i++) {
		if (indexOfPair[i] > idx) {
			indexOfPair[i] = idx;
			pairs[idx] = i2(firstPair, i);
			if (nextFirstPair == -1) {
				nextFirstPair = i;
				for (int j = i + 1; j < N; j++) {
					if (indexOfPair[j] > idx) {
						indexOfPair[j] = idx + 1;
						getCasesOfPairs(idx + 1, j);
						indexOfPair[j] = N / 2 - 1;
						break;
					}
				}
			}
			else {
				indexOfPair[nextFirstPair] = idx + 1;
				getCasesOfPairs(idx + 1, nextFirstPair);
				indexOfPair[nextFirstPair] = N / 2 - 1;
			}
			indexOfPair[i] = N / 2 - 1;
		}
	}
}

int main() {
	int x, y;
	cin >> N;
	for (int i = 0; i < N; i++) {
		cin >> x >> y;
		warmHoles[i] = i2(x, y);
	}

	for (int i = 0; i < N; i++) {
		indexOfPair[i] = N / 2 - 1;
	}
	indexOfPair[0] = 0;
	getCasesOfPairs(0, 0);
	cout << countNum;
	return 0;
}

/*
������ ��Ȧ �ֵ��� ��� ��쿡 ���ؼ� ����Ŭ�� �߻��ϴ� ����� ���� ������ ����ϸ� �ȴ�.
��Ȧ ���� ��� ����� ���� Ž���� �� �ִٸ�
����Ŭ�� ã�� ���� ����� �ʰ� �ذ��� �� �ִ�.
*/
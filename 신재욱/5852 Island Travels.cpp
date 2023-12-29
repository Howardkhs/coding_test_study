#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <deque>
#include <tuple>
#include <climits>

#define min(a, b) (((a) < (b)) ? (a) : (b))

using namespace std;

using i2 = pair<int, int>;
using i3 = tuple<int, int, int>;

int xDir[4] = { 1, 0, -1, 0 };
int yDir[4] = { 0, 1, 0, -1 };

int N, R, C;
char map[50][51] = {};
vector<i2> islands[15] = {};
int graph[15][15] = {0};
int dpArr[16][32767] = { 0 };

void findIslands() {
	int num = 0;
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			if (map[i][j] == 'X') {
				queue<i2> q;
				int newX = 0, newY = 0;
				map[i][j] = num;
				islands[num].push_back(i2(i, j));
				q.push(i2(i, j));
				while (!q.empty()) {
					i2 pos = q.front();
					q.pop();
					for (int k = 0; k < 4; k++) {
						newX = pos.first + xDir[k];
						newY = pos.second + yDir[k];
						if (newX >= 0 && newX < R && newY >= 0 && newY < C) {
							if (map[newX][newY] == 'X') {
								map[newX][newY] = num;
								islands[num].push_back(i2(newX, newY));
								q.push(i2(newX, newY));
							}
						}
					}
				}
				num++;
			}
		}
	}
	N = num;
}
void getGraph() {
	bool visited[50][50] = { false };
	for (int i = 0; i < N; i++) {
		deque<i3> dq;
		for (int i = 0; i < R; i++) {
			for (int j = 0; j < C; j++) {
				visited[i][j] = false;
			}
		}
		for (int j = 0; j < (int)islands[i].size(); j++) {
			dq.push_back(i3(islands[i][j].first, islands[i][j].second, 0));
			visited[islands[i][j].first][islands[i][j].second] = true;
		}
		while (!dq.empty()) {
			int x, y, dist, newX, newY;
			tie(x, y, dist) = dq.front();
			dq.pop_front();
			for (int j = 0; j < 4; j++) {
				newX = x + xDir[j];
				newY = y + yDir[j];
				if (newX >= 0 && newX < R && newY >= 0 && newY < C) {
					if (!visited[newX][newY]) {
						visited[newX][newY] = true;
						if (map[newX][newY] == '.') {
							continue;
						}
						else if (map[newX][newY] == 'S') {
							dq.push_back(i3(newX, newY, dist + 1));
						}
						else {
							//cout << i << newX << newY << (int)map[newX][newY] << '\n';
							graph[i][map[newX][newY]] = dist;
							graph[map[newX][newY]][i] = dist;
							dq.push_front(i3(newX, newY, dist));
						}
					}
				}
			}
		}
	}
}

void processMask(int n, int prev, int mask) {
	int numOfOne = 0, power = 1;
	for (int i = 1; i <= N; i++) {
		numOfOne += ((power & mask) != 0);
		power *= 2;
	}
	//cout << numOfOne << '\n';

	if (n != numOfOne) {
		return;
	}
	//cout << mask << '\n';
	power = 1;
	for (int i = 0; i < N; i++) {
		if ((power & mask) == 0) {
			if (dpArr[prev][mask] != INT32_MAX) {
				dpArr[i][power | mask] = min(dpArr[i][power | mask], dpArr[prev][mask] + graph[prev][i]);
				//cout << dpArr[i][power | mask] << '\n';
			}
		}
		power *= 2;
	}
}


int dp() {
	int power = 1 << N;
	int ret = INT32_MAX;
	for (int i = 0; i < N; i++) {
		for (int j = 1; j < power; j++) {
			dpArr[i][j] = INT32_MAX;
		}
	}
	for (int i = 0; i < N; i++) {
		dpArr[i][1 << i] = 0;
	}

	for (int i = 1; i < N; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 1; k < power - 1; k++) {
				processMask(i, j, k);
			}
		}
	}

	for (int i = 0; i < N; i++) {
		ret = min(ret, dpArr[i][power - 1]);
	}
	return ret;
}

int main() {
	cin >> R >> C;
	for (int i = 0; i < R; i++) {
		cin >> map[i];
	}

	findIslands();
	getGraph();
	cout << dp();

	/*for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cout << graph[i][j];
		}
		cout << '\n';
	}*/
	
	return 0;
}

/*
섬들의 위치를 구하고 각각의 섬들 사이의 최단거리 그래프를 구한 후
그 그래프를 토대로 최단 거리의 해밀턴 경로를 구하면 된다.

0-1 BFS, 비트필드를 이용한dp를 공부한 후에 도전하니 더 수월했다.

최단거리 그래프를 얻을 때 0-1BFS를,
최단거리의 해밀턴 경로를 구할때 비트필드를 이용한 dp를 사용했다.
만약 N개의 섬이 있다면 N비트를 사용하고, 각 비트가 각 섬의 방문체크에 사용된다.
*/
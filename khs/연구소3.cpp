#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>
#include<limits.h>
using namespace std;

typedef pair<int, int> P;
int arr[51][51], visited[51][51];
int n, m, res = INT_MAX;
int dx[] = { 0,0,1,-1 };
int dy[] = { 1,-1,0,0 };
struct node {
	int x, y, vis;
};
vector<node>vir;
queue<P>q;

void bfs() {
	while (!q.empty()) {
		P now = q.front();
		q.pop();
		for (int i = 0; i < 4; i++) {
			int nx = now.first + dx[i];
			int ny = now.second + dy[i];
			if (nx < 0 || nx >= n || ny < 0 || ny >= n)
				continue;

			if (arr[nx][ny] != 1 && visited[nx][ny] == -1) {
				visited[nx][ny] = visited[now.first][now.second] + 1;
				q.push({ nx,ny });
			}
		}
	}
	int time = 0;
	bool flag = true;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (arr[i][j] == 0) {
				if (visited[i][j] == -1) {
					flag = false;
					break;
				}
				else
					time = max(time, visited[i][j]);
			}
		}
	}
	if (flag)
		res = min(res, time);
}

void virus(int cnt, int idx) {
	if (cnt == m) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				visited[i][j] = -1;
			}
		}

		for (int i = 0; i < vir.size(); i++) {
			if (vir[i].vis == 1) {
				q.push({ vir[i].x,vir[i].y });
				visited[vir[i].x][vir[i].y] = 0;
			}
		}
		bfs();
		return;
	}
	for (int i = idx; i < vir.size(); i++) {
		if (vir[i].vis == 1)
			continue;
		vir[i].vis = 1;
		virus(++cnt, ++idx);
		vir[i].vis = 0;
		cnt--;
	}
}

int main() {
	ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> arr[i][j];
			if (arr[i][j] == 2)
				vir.push_back({ i,j,0 });
		}
	}
	virus(0, 0);
	if (res == INT_MAX)
		cout << -1;
	else
		cout << res;
	return 0;
}
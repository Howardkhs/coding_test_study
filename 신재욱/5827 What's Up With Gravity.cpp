#include <iostream>
#include <utility>
#include <deque>
#include <tuple>
#include <climits>

#define gravityStatus_up 0
#define gravityStatus_down 1

using namespace std;

using i2 = pair<int, int>; //(x, y)
using i4 = pair<i2, i2>; // (pos, (flippedNum, gravityStatus))

int N, M;
char map[500][501];
int dp[2][500][500];
i2 captain, doctor;

i2 checkFall(int x, int y, int gravityStatus) {
	int newX = x;
	if (gravityStatus == gravityStatus_down) {
		newX++;
		while (newX < N) {
			if (i2(newX, y) == doctor) {
				return doctor;
			}
			else if (map[newX][y] == '#') {
				return i2(newX - 1, y);
			}
			newX++;
		}
		return i2(-1, -1);
	}
	else {
		newX--;
		while (newX >= 0) {
			if (i2(newX, y) == doctor) {
				return doctor;
			}
			else if (map[newX][y] == '#') {
				return i2(newX + 1, y);
			}
			newX--;
		}
		return i2(-1, -1);
	}
}

int zero_one_BFS() {
	deque<i4> d;

	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < M; k++) {
				dp[i][j][k] = INT32_MAX;
			}
		}
	}

	i2 newPos = checkFall(captain.first, captain.second, 1);
	if (newPos == i2(-1, -1)) {
		return -1;
	}

	d.push_back(i4(newPos, i2(0, 1)));
	dp[1][newPos.first][newPos.second] = 0;
	
	while (!d.empty()) {
		i4 data = d.front();
		int x = data.first.first;
		int y = data.first.second;
		int flippedNum = data.second.first;
		int gravityStatus = data.second.second;
		int newX, newY;
		d.pop_front();

		//cout << x << y << '\n';

		//left
		newX = x;
		newY = y - 1;
		if (newX >= 0 && newX < N && newY >= 0 && newY < M) {
			if (i2(newX, newY) == doctor) {
				return flippedNum;
			}
			else if (map[newX][newY] == '.') {
				newPos = checkFall(newX, newY, gravityStatus);
				if (newPos != i2(-1, -1)) {
					if (newPos == doctor) {
						return flippedNum;
					}
					if (flippedNum < dp[gravityStatus][newPos.first][newPos.second]) {
						d.push_front(i4(newPos, i2(flippedNum, gravityStatus)));
						dp[gravityStatus][newPos.first][newPos.second] = flippedNum;
					}
				}
			}
		}

		//right
		newX = x;
		newY = y + 1;
		if (newX >= 0 && newX < N && newY >= 0 && newY < M) {
			if (i2(newX, newY) == doctor) {
				return flippedNum;
			}
			else if (map[newX][newY] == '.') {
				newPos = checkFall(newX, newY, gravityStatus);
				if (newPos != i2(-1, -1)) {
					if (newPos == doctor) {
						return flippedNum;
					}
					if (flippedNum < dp[gravityStatus][newPos.first][newPos.second]) {
						d.push_front(i4(newPos, i2(flippedNum, gravityStatus)));
						dp[gravityStatus][newPos.first][newPos.second] = flippedNum;
					}
				}
			}
		}

		//flip gravity
		newPos = checkFall(x, y, 1 - gravityStatus);
		if (newPos != i2(-1, -1)) {
			if (newPos == doctor) {
				return (flippedNum + 1);
			}
			if (flippedNum + 1 < dp[1 - gravityStatus][newPos.first][newPos.second]) {
				d.push_back(i4(newPos, i2(flippedNum + 1, 1 - gravityStatus)));
				dp[1 - gravityStatus][newPos.first][newPos.second] = flippedNum + 1;
			}
		}
	}

	return -1;
}

int main() {
	cin >> N >> M;
	for (int i = 0; i < N; i++) {
		cin >> map[i];
		for (int j = 0; j < M; j++) {
			if (map[i][j] == 'C') {
				captain = i2(i, j);
				map[i][j] = '.';
			}
			else if (map[i][j] == 'D') {
				doctor = i2(i, j);
				map[i][j] = '.';
			}
		}
	}

	cout << zero_one_BFS();

	return 0;
}

/*
0-1BFS를 활용하면 쉽게 해결할 수 있다.

함정이 있는데, 처음에 입력으로 주어진 위치의 captain이
중력의 영향을 받아 떨어질 수 있다는 것이다....
때문에 중력체크 한번 하고 시작해야된다...
*/
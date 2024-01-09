#include <iostream>
#include <tuple>
#include <vector>
#include <climits>

#define min(a, b) (((a) < (b)) ? (a) : (b))

using namespace std;

using i3 = tuple<int, int, int>;

int L, N;
int xDir[4] = {1, 0, -1, 0};
int yDir[4] = {0, 1, 0, -1};
int dir = 0;
vector<i3> xLine, yLine;

int main() {
	int t_i;
	char dir_i;
	int prevX = 0, prevY = 0, curX = 0, curY = 0, distance;
	long long totalT = 0;
	cin >> L >> N;
	for (int i = 0; i < N + 1; i++) {
		if ((N - i) >= 1) {
			cin >> t_i >> dir_i;
			curX = prevX + xDir[dir] * t_i;
			curY = prevY + yDir[dir] * t_i;
		}
		else {
			curX = prevX + xDir[dir] * (INT32_MAX / 2);
			curY = prevY + yDir[dir] * (INT32_MAX / 2);
		}

		//cout << curX << curY << '\n';

		distance = INT32_MAX;
		for (i3 line : xLine) {
			int x1, x2, y;
			tie(x1, x2, y) = line;
			if (dir % 2 == 0) {
				if (y == curY) {
					if (prevX < curX) {
						if (curX == x1) {
							distance = min(distance, (curX - prevX));
						}
						else if (x1 > prevX && x1 < curX) {
							distance = min(distance, (x1 - prevX));
						}
					}
					else {
						if (curX == x2) {
							distance = min(distance, (prevX - curX));
						}
						else if (x2 > curX && x2 < prevX) {
							distance = min(distance, (prevX - x2));
						}
					}
				}
			}
			else {
				if (prevX >= x1 && prevX <= x2) {
					if (prevY < curY) {
						if (y > prevY && y <= curY) {
							distance = min(distance, (y - prevY));
						}
					}
					else {
						if (y >= curY && y < prevY) {
							distance = min(distance, (prevY - y));
						}
					}
				}
			}
		}

		for (i3 line : yLine) {
			int x, y1, y2;
			tie(x, y1, y2) = line;
			if (dir % 2 == 1) {
				if (x == curX) {
					if (prevY < curY) {
						if (curY == y1) {
							distance = min(distance, (curY - prevY));
						}
						else if (y1 > prevY && y1 < curY) {
							distance = min(distance, (y1 - prevY));
						}
					}
					else {
						if (curY == y2) {
							distance = min(distance, (prevY - curY));
						}
						else if (y2 > curY && y2 < prevY) {
							distance = min(distance, (prevY - y2));
						}
					}
				}
			}
			else {
				if (prevY >= y1 && prevY <= y2) {
					if (prevX < curX) {
						if (x > prevX && x <= curX) {
							distance = min(distance, (x - prevX));
						}
					}
					else {
						if (x >= curX && x < prevX) {
							distance = min(distance, (prevX - x));
						}
					}
				}
			}
		}

		if (distance != INT32_MAX) {
			cout << (totalT + distance);
			return 0;
		}

		if (curX < -L) {
			totalT += (prevX - (-L - 1));
			cout << totalT;
			return 0;
		}
		else if (curX > L) {
			totalT += (L + 1 - prevX);
			cout << totalT;
			return 0;
		}
		else if (curY < -L) {
			totalT += (prevY - (-L - 1));
			cout << totalT;
			return 0;
		}
		else if (curY > L) {
			totalT += (L + 1 - prevY);
			cout << totalT;
			return 0;
		}


		if (dir % 2 == 0) {
			if (prevX < curX) {
				xLine.push_back(i3(prevX, curX, curY));
			}
			else {
				xLine.push_back(i3(curX, prevX, curY));
			}
		}
		else {
			if (prevY < curY) {
				yLine.push_back(i3(curX, prevY, curY));
			}
			else {
				yLine.push_back(i3(curX, curY, prevY));
			}
		}

		if (dir_i == 'L') {
			dir += 1;
		}
		else {
			dir += 3;
		}
		dir %= 4;
		totalT += t_i;

		prevX = curX;
		prevY = curY;
	}
}

/*
단순 구현이다.
입력이 주어지지 않는다면 방향을 바꾸지 않고 죽을 때까지 이동함에 유의해야 한다.
*/
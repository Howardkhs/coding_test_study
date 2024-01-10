#include <iostream>

int N;
char cube[9][12];
char left[3][3], right[3][3], front[3][3], back[3][3], top[3][3], bottom[3][3];

void rotateClockwise(char(*ref)[3]) {
	char temp1 = ref[0][0], temp2 = ref[0][1];
	ref[0][0] = ref[2][0];
	ref[0][1] = ref[1][0];
	ref[2][0] = ref[2][2];
	ref[1][0] = ref[2][1];
	ref[2][2] = ref[0][2];
	ref[2][1] = ref[1][2];
	ref[0][2] = temp1;
	ref[1][2] = temp2;
}
void rotateCounterClockwise(char(*ref)[3]) {
	char temp1 = ref[0][0], temp2 = ref[0][1];
	ref[0][0] = ref[0][2];
	ref[0][1] = ref[1][2];
	ref[0][2] = ref[2][2];
	ref[1][2] = ref[2][1];
	ref[2][2] = ref[2][0];
	ref[2][1] = ref[1][0];
	ref[2][0] = temp1;
	ref[1][0] = temp2;
}

void rotateLeft(bool clockwise) {
	char temp1 = front[0][0], temp2 = front[1][0], temp3 = front[2][0];
	if (clockwise) {
		rotateClockwise(left);
		front[0][0] = top[0][0];
		front[1][0] = top[1][0];
		front[2][0] = top[2][0];
		top[0][0] = back[2][2];
		top[1][0] = back[1][2];
		top[2][0] = back[0][2];
		back[2][2] = bottom[0][0];
		back[1][2] = bottom[1][0];
		back[0][2] = bottom[2][0];
		bottom[0][0] = temp1;
		bottom[1][0] = temp2;
		bottom[2][0] = temp3;
	}
	else {
		rotateCounterClockwise(left);
		front[0][0] = bottom[0][0];
		front[1][0] = bottom[1][0];
		front[2][0] = bottom[2][0];
		bottom[0][0] = back[2][2];
		bottom[1][0] = back[1][2];
		bottom[2][0] = back[0][2];
		back[2][2] = top[0][0];
		back[1][2] = top[1][0];
		back[0][2] = top[2][0];
		top[0][0] = temp1;
		top[1][0] = temp2;
		top[2][0] = temp3;
	}
}
void rotateRight(bool clockwise) {
	char temp1 = front[0][2], temp2 = front[1][2], temp3 = front[2][2];
	if (clockwise) {
		rotateClockwise(right);
		front[0][2] = bottom[0][2];
		front[1][2] = bottom[1][2];
		front[2][2] = bottom[2][2];
		bottom[0][2] = back[2][0];
		bottom[1][2] = back[1][0];
		bottom[2][2] = back[0][0];
		back[2][0] = top[0][2];
		back[1][0] = top[1][2];
		back[0][0] = top[2][2];
		top[0][2] = temp1;
		top[1][2] = temp2;
		top[2][2] = temp3;
	}
	else {
		rotateCounterClockwise(right);
		front[0][2] = top[0][2];
		front[1][2] = top[1][2];
		front[2][2] = top[2][2];
		top[0][2] = back[2][0];
		top[1][2] = back[1][0];
		top[2][2] = back[0][0];
		back[2][0] = bottom[0][2];
		back[1][0] = bottom[1][2];
		back[0][0] = bottom[2][2];
		bottom[0][2] = temp1;
		bottom[1][2] = temp2;
		bottom[2][2] = temp3;
	}
}
void rotateFront(bool clockwise) {
	char temp1 = top[2][0], temp2 = top[2][1], temp3 = top[2][2];
	if (clockwise) {
		rotateClockwise(front);
		top[2][0] = left[2][2];
		top[2][1] = left[1][2];
		top[2][2] = left[0][2];
		left[2][2] = bottom[0][2];
		left[1][2] = bottom[0][1];
		left[0][2] = bottom[0][0];
		bottom[0][2] = right[0][0];
		bottom[0][1] = right[1][0];
		bottom[0][0] = right[2][0];
		right[0][0] = temp1;
		right[1][0] = temp2;
		right[2][0] = temp3;
	}
	else {
		rotateCounterClockwise(front);
		top[2][0] = right[0][0];
		top[2][1] = right[1][0];
		top[2][2] = right[2][0];
		right[0][0] = bottom[0][2];
		right[1][0] = bottom[0][1];
		right[2][0] = bottom[0][0];
		bottom[0][2] = left[2][2];
		bottom[0][1] = left[1][2];
		bottom[0][0] = left[0][2];
		left[2][2] = temp1;
		left[1][2] = temp2;
		left[0][2] = temp3;
	}
}
void rotateBack(bool clockwise) {
	char temp1 = top[0][0], temp2 = top[0][1], temp3 = top[0][2];
	if (clockwise) {
		rotateClockwise(back);
		top[0][0] = right[0][2];
		top[0][1] = right[1][2];
		top[0][2] = right[2][2];
		right[0][2] = bottom[2][2];
		right[1][2] = bottom[2][1];
		right[2][2] = bottom[2][0];
		bottom[2][2] = left[2][0];
		bottom[2][1] = left[1][0];
		bottom[2][0] = left[0][0];
		left[2][0] = temp1;
		left[1][0] = temp2;
		left[0][0] = temp3;
	}
	else {
		rotateCounterClockwise(back);
		top[0][0] = left[2][0];
		top[0][1] = left[1][0];
		top[0][2] = left[0][0];
		left[2][0] = bottom[2][2];
		left[1][0] = bottom[2][1];
		left[0][0] = bottom[2][0];
		bottom[2][2] = right[0][2];
		bottom[2][1] = right[1][2];
		bottom[2][0] = right[2][2];
		right[0][2] = temp1;
		right[1][2] = temp2;
		right[2][2] = temp3;
	}
}
void rotateTop(bool clockwise) {
	char temp1 = front[0][0], temp2 = front[0][1], temp3 = front[0][2];
	if (clockwise) {
		rotateClockwise(top);
		front[0][0] = right[0][0];
		front[0][1] = right[0][1];
		front[0][2] = right[0][2];
		right[0][0] = back[0][0];
		right[0][1] = back[0][1];
		right[0][2] = back[0][2];
		back[0][0] = left[0][0];
		back[0][1] = left[0][1];
		back[0][2] = left[0][2];
		left[0][0] = temp1;
		left[0][1] = temp2;
		left[0][2] = temp3;
	}
	else {
		rotateCounterClockwise(top);
		front[0][0] = left[0][0];
		front[0][1] = left[0][1];
		front[0][2] = left[0][2];
		left[0][0] = back[0][0];
		left[0][1] = back[0][1];
		left[0][2] = back[0][2];
		back[0][0] = right[0][0];
		back[0][1] = right[0][1];
		back[0][2] = right[0][2];
		right[0][0] = temp1;
		right[0][1] = temp2;
		right[0][2] = temp3;
	}
}
void rotateBottom(bool clockwise) {
	char temp1 = front[2][0], temp2 = front[2][1], temp3 = front[2][2];
	if (clockwise) {
		rotateClockwise(bottom);
		front[2][0] = left[2][0];
		front[2][1] = left[2][1];
		front[2][2] = left[2][2];
		left[2][0] = back[2][0];
		left[2][1] = back[2][1];
		left[2][2] = back[2][2];
		back[2][0] = right[2][0];
		back[2][1] = right[2][1];
		back[2][2] = right[2][2];
		right[2][0] = temp1;
		right[2][1] = temp2;
		right[2][2] = temp3;
	}
	else {
		rotateCounterClockwise(bottom);
		front[2][0] = right[2][0];
		front[2][1] = right[2][1];
		front[2][2] = right[2][2];
		right[2][0] = back[2][0];
		right[2][1] = back[2][1];
		right[2][2] = back[2][2];
		back[2][0] = left[2][0];
		back[2][1] = left[2][1];
		back[2][2] = left[2][2];
		left[2][0] = temp1;
		left[2][1] = temp2;
		left[2][2] = temp3;
	}
}
int main() {
	std::cin.tie(NULL);
	std::ios_base::sync_with_stdio(false);


	int turn, s, d;
	std::cin >> N;
	for (int t = 1; t <= N; t++) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				std::cin >> top[i][j];
			}
		}
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				std::cin >> left[i][j];
			}
			for (int j = 0; j < 3; j++) {
				std::cin >> front[i][j];
			}
			for (int j = 0; j < 3; j++) {
				std::cin >> right[i][j];
			}
			for (int j = 0; j < 3; j++) {
				std::cin >> back[i][j];
			}

		}
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				std::cin >> bottom[i][j];
			}
		}

		std::cin >> turn;
		for (int i = 0; i < turn; i++) {
			std::cin >> s >> d;
			if (s == 0) {
				rotateLeft(d > 0);
			}
			else if (s == 1) {
				rotateFront(d > 0);
			}
			else if (s == 2) {
				rotateRight(d > 0);
			}
			else if (s == 3) {
				rotateBack(d > 0);
			}
			else if (s == 4) {
				rotateTop(d > 0);
			}
			else if (s == 5) {
				rotateBottom(d > 0);
			}
		}

		std::cout << "Scenario #" << t << ":\n";
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				std::cout << "  ";
			}
			for (int j = 0; j < 3; j++) {
				std::cout << top[i][j];
				std::cout << ' ';
			}
			std::cout << '\n';
		}
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				std::cout << left[i][j];
				std::cout << ' ';
			}
			for (int j = 0; j < 3; j++) {
				std::cout << front[i][j];
				std::cout << ' ';
			}
			for (int j = 0; j < 3; j++) {
				std::cout << right[i][j];
				std::cout << ' ';
			}
			for (int j = 0; j < 3; j++) {
				std::cout << back[i][j];
				std::cout << ' ';
			}
			std::cout << '\n';
		}
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				std::cout << "  ";
			}
			for (int j = 0; j < 3; j++) {
				std::cout << bottom[i][j];
				std::cout << ' ';
			}
			std::cout << '\n';
		}

		std::cout << '\n';
	}

	return 0;
}

/*
단순 구현이다. 매우 귀찮다...
*/
#include <iostream>
#include <vector>
#include <stack>
#include <climits>
#include <algorithm>
#include <string>
#include <utility>

#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))

using namespace std;
using i2 = pair<int, int>; // (max, min)

class formula {
public:
	int len = 0, newLen = 0;
	string main = "";
	i2 nums[10] = {}, newNums[10] = {}, tempNums[10] = {};
	char operators[9] = {}, newOperators[9] = {}, tempOperators[9] = {};

	formula() : len(0), main("") {};
	formula(string _main) : main(_main) {
		len = main.length();
		for (int i = 0; i < len; i++) {
			if (i % 2 == 0) {
				nums[i / 2] = i2(main[i] - '0', main[i] - '0');
			}
			else {
				operators[i / 2] = main[i];
			}
		}
	};
	formula(i2 (&_nums)[10], char (&_operators)[9], int _len) {
		len = _len;
		copy(_nums, _nums + (len / 2 + 1), nums);
		copy(_operators, _operators + (len / 2), operators);
	}

	i2 getMaxMinOutput() {
		int cal = 0;
		i2 maxminOutput = i2(INT32_MIN, INT32_MAX);
		i2 output = i2(0, 0);
		for (int i = 0; i <= (len / 2 + 1) / 2; i++) {
			if (i == 0) {
				newLen = len;
				copy(nums, nums + (len / 2 + 1), newNums);
				copy(operators, operators + (len / 2), newOperators);
				output = calculateWithNoParen();
				maxminOutput = i2(max(maxminOutput.first, output.first),
					min(maxminOutput.second, output.second));
			}
			else {
				vector<int> combiVec;
				for (int j = 0; j < len / 2 + 1 - i * 2; j++) {
					combiVec.push_back(0);
				}
				for (int j = 0; j < i * 2; j++) {
					combiVec.push_back(1);
				}

				do {
					bool started = false;
					int openIdx = -1, closeIdx = -1, tempLen = 0;
					newLen = 0;

					if (i == 1 && combiVec[0] == 1 && combiVec[combiVec.size() - 1] == 1) {
						continue;
					}

					for (int j = 0; j < (int)combiVec.size(); j++) {
						if (started) {
							if (combiVec[j] == 0) {
								tempNums[tempLen++ / 2] = nums[j];
								tempOperators[tempLen++ / 2] = operators[j];
							}
							else {
								started = false;
								closeIdx = j;
								tempNums[tempLen++ / 2] = nums[j];

								newNums[newLen++ / 2] =
									formula(tempNums, tempOperators, tempLen).getMaxMinOutput();
								if (j < len / 2) {
									newOperators[newLen++ / 2] = operators[j];
								}
							}
						}
						else {
							if (combiVec[j] == 0) {
								newNums[newLen++ / 2] = nums[j];
								if (j < len / 2) {
									newOperators[newLen++ / 2] = operators[j];
								}
							}
							else {
								started = true;
								openIdx = j;
								tempLen = 0;
								tempNums[tempLen++ / 2] = nums[j];
								tempOperators[tempLen++ / 2] = operators[j];
							}
						}
					}

					output = calculateWithNoParen();
					maxminOutput = i2(max(maxminOutput.first, output.first),
						min(maxminOutput.second, output.second));
				} while (next_permutation(combiVec.begin(), combiVec.end()));
			}
		}
		return maxminOutput;
	}

	i2 calculateWithNoParen() {
		string postfix[19];
		stack<char> operatorStack;
		stack<i2> numStack;
		int count = 0;
		i2 n1 = i2(0, 0), n2 = i2(0, 0);
		for (int i = 0; i < newLen / 2; i++) {
			postfix[count++] = to_string(i);
			if (operatorStack.empty()) {
				operatorStack.push(newOperators[i]);
			}
			else {
				if (operatorStack.top() == '*') {
					operatorStack.pop();
					postfix[count++] = "*";
				}
				operatorStack.push(newOperators[i]);
			}
		}
		postfix[count++] = to_string(newLen / 2);
		while (!operatorStack.empty()) {
			postfix[count++] = operatorStack.top();
			operatorStack.pop();
		}

		count = 0;
		for (int i = 0; i < newLen; i++) {
			if (postfix[i].length() == 1) {
				if (postfix[i].compare("+") == 0) {
					n2 = numStack.top();
					numStack.pop();
					n1 = numStack.top();
					numStack.pop();

					int val = 0, maxVal = INT32_MIN, minVal = INT32_MAX;
					val = n1.first + n2.first;
					maxVal = max(maxVal, val);
					minVal = min(minVal, val);
					val = n1.first + n2.second;
					maxVal = max(maxVal, val);
					minVal = min(minVal, val);
					val = n1.second + n2.first;
					maxVal = max(maxVal, val);
					minVal = min(minVal, val);
					val = n1.second + n2.second;
					maxVal = max(maxVal, val);
					minVal = min(minVal, val);
					
					numStack.push(i2(maxVal, minVal));
				}
				else if (postfix[i].compare("-") == 0) {
					n2 = numStack.top();
					numStack.pop();
					n1 = numStack.top();
					numStack.pop();

					int val = 0, maxVal = INT32_MIN, minVal = INT32_MAX;
					val = n1.first - n2.first;
					maxVal = max(maxVal, val);
					minVal = min(minVal, val);
					val = n1.first - n2.second;
					maxVal = max(maxVal, val);
					minVal = min(minVal, val);
					val = n1.second - n2.first;
					maxVal = max(maxVal, val);
					minVal = min(minVal, val);
					val = n1.second - n2.second;
					maxVal = max(maxVal, val);
					minVal = min(minVal, val);

					numStack.push(i2(maxVal, minVal));
				}
				else if (postfix[i].compare("*") == 0) {
					n2 = numStack.top();
					numStack.pop();
					n1 = numStack.top();
					numStack.pop();

					int val = 0, maxVal = INT32_MIN, minVal = INT32_MAX;
					val = n1.first * n2.first;
					maxVal = max(maxVal, val);
					minVal = min(minVal, val);
					val = n1.first * n2.second;
					maxVal = max(maxVal, val);
					minVal = min(minVal, val);
					val = n1.second * n2.first;
					maxVal = max(maxVal, val);
					minVal = min(minVal, val);
					val = n1.second * n2.second;
					maxVal = max(maxVal, val);
					minVal = min(minVal, val);

					numStack.push(i2(maxVal, minVal));
				}
				else {
					numStack.push(newNums[stoi(postfix[i])]);
				}
			}
			else {
				numStack.push(newNums[stoi(postfix[i])]);
			}
		}
		return numStack.top();
	}
};

formula mainFormula;

int main() {
	int trash;
	string stringInput;
	cin >> trash >> stringInput;
	mainFormula = formula(stringInput);
	cout << mainFormula.getMaxMinOutput().first;
	return 0;
}


/*
이전 괄호 추가하기 문제와 차이점은 중첩괄호가 존재한다는 것이다.
재귀를 활용해서 중첩괄호를 해결했다.
각 수식들의 최댓값, 최솟값을 이용해서 최종적으로 최댓값을 구하면 된다.
*/

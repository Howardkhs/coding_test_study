#include <iostream>
// BOJ - 11401 Binomial Coefficient 3
#define DIV		1000000007
using namespace std;

long long temp;

long long power(long long a, long long m) {
	if (m == 0) return 1;

	temp = power(a, m / 2) % DIV;
	if (m % 2 == 1) return temp * temp % DIV * a % DIV;
	return temp * temp % DIV;
}

void solve(int n, int k) {
	if (k == 1) { cout << n; return; }
	if (k == 0 || n == k) { cout << 1; return; }
	if (n - k == 1) { cout << n; return; }

	long long A = 1, B = 1, ans;
	for (int i = n; i >= n - k + 1; i--) 
        A = (A * i) % DIV;
	for (int i = 1; i <= k; i++) 
        B = (B * i) % DIV;
	ans = ((A % DIV) * power(B, DIV - 2) % DIV) % DIV;
	cout << ans;
}

int main(void) {
	int n, k;

	cin >> n >> k;
	solve(n, k);

	return 0;
}
#include <iostream>

using namespace std;

long long a(long long n, long long k);
long long b(long long n, long long k);

long long bArr[1000][1000];

int main() {
	int n, k;
	cin >> n >> k;

	for (int i = 0; i < 1000; i++) {
		for (int j = 0; j < 1000; j++) {
			bArr[i][j] = -1;
		}
	}

	cout << a(n, k);
	return 0;
}

long long a(long long n, long long k) {
	if (n < 2 * k) {
		return 0;
	}
	return (b(n - 3, k - 1) + b(n - 1, k)) % 1000000003;
}
long long b(long long n, long long k) {
	if (bArr[n][k] != -1) {
		return bArr[n][k];
	}

	if (n < 2 * k - 1) {
		bArr[n][k] = 0;
		return 0;
	}

	if (k == 0) {
		bArr[n][k] = 1;
		return 1;
	}
	else if(k == 1) {
		bArr[n][k] = n;
		return n;
	}
	else if (k == 2) {
		bArr[n][k] = (n - 1) * (n - 2) / 2;
		return bArr[n][k];
	}

	bArr[n][k] = (b(n - 2, k - 1) + b(n - 1, k)) % 1000000003;
	return bArr[n][k];
}

/*
점화식을 잘 찾아보자.
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <queue>
#include <cmath>

using namespace std;
vector<long long> candies;

long long binarySearch(long long m, long long max)
{
	long long start = 1, end = max;
	long long answer = 0;

	while (end >= start)
	{
		long long mid = start + (end - start) / 2;

		// 각 사탕 개수를 현재 가방 개수로 나누면, 해당 가방 개수일 때 사용해야하는 각 사탕 개수를 알 수 있음.
		long long curCount = 0;
		for (int i = 0; i < candies.size(); i++)
			curCount += candies[i] / mid;
		
		if (curCount < m)		// 가방 개수 너무 많으면 한 가방 내 사탕 개수 못 채움 -> mid 이상 개수는 불가능. 그 아래 탐색
			end = mid - 1;
		else                   //  가방 개수 딱 맞거나 너무 적으면 한 가방 내 사탕 개수 채움 -> 현재 가방 개수를 answer로 설정하고 그 위 값도 탐색
		{
			answer = mid;
			start = mid + 1;
		}
	}
	return answer;
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(); cout.tie();

	int t;
	cin >> t;

	for (int i = 0; i < t; i++)
	{
		long long n, m;
		cin >> n >> m;
		long long max = 0;
		for (int j = 0; j < n; j++)
		{
			long long num;
			cin >> num;
			candies.push_back(num);

			if (max < num)
				max = num;
		}

		cout << '#' << i + 1 << ' ' << binarySearch(m, max) << endl;
		candies.clear();
	}
}

#include<iostream>

using namespace std;

int drive[200000];
int blocks[200000];

int T, N, K, t;

bool correct(int mid){
	int idx = -1;
	for (int k = 0; k < K; k++){ //
		for(int b = 0; b < blocks[k]; b++){
			idx++;
			if (idx == N)
				return false;
			if (drive[idx] > mid){
				k--;
				break;
			}
			
		}
	}
	return true;
}


int search(int start, int end){
	int answer;
	while (start <= end){
		int mid = start + (end - start) / 2;
		if(correct(mid)){
			answer = mid;
			end = mid - 1;
		}
		else{
			start = mid + 1;
		}
	}
	return answer;
}

int main(int argc, char** argv)
{	
	ios::sync_with_stdio(false);
	cin.tie(); cout.tie();
	int test_case;
	

	//freopen("input.txt", "r", stdin);
	cin>>T;
	/*
	   여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
	*/
	for(test_case = 1; test_case <= T; ++test_case)
	{
		cin >> N >> K;
		for (int i = 0; i < N; i++){
			cin >> t;
			drive[i] = t;
		}
		for (int i = 0; i < K; i++){
			cin >> t;
			blocks[i] = t;
		}

		int ret = search(0, 200000);
		cout << '#' << test_case << ' ' << ret << '\n';

	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
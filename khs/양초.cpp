
#include<iostream>
#include <cmath>

using namespace std;

int main(int argc, char** argv)
{   
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
	int test_case;
	int T, N;
    unsigned long long input;
    long double k;
	
	//freopen("input.txt", "r", stdin);
	cin>>T;
	/*
	   여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
	*/
	for(test_case = 1; test_case <= T; ++test_case)
	{
        
        cin >> input;
        if (input == 1){
            cout << "#" << test_case << " " << 1 << "\n";
            continue;
        }
        k = (-1 + sqrt(1 + 8 * input)) / 2;
        cout << k << endl;
        if (k != llround(k))
            cout << "#" << test_case << " " << -1 << "\n";
        else
            cout << "#" << test_case << " " << llround(k) << "\n";
    

	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
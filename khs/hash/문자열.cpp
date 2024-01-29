#include<iostream>
#include <unordered_map>

using namespace std;



int main(int argc, char** argv)
{   
    ios::sync_with_stdio(false);
	cin.tie(); cout.tie();
	int test_case;
	int T,N,M;
    string word;

	//freopen("input.txt", "r", stdin);
	cin>>T;

	for(test_case = 1; test_case <= T; ++test_case)
	{   
        int answer = 0;
        unordered_map<string, int> words;
        cin >> N >> M;
        while(N--){
            cin >> word;
            words[word] += 1;
        }
        while(M--){
            cin >> word;
            words[word] += 1;
            if (words[word] == 2)
                answer += 1;
        }
       
        cout<< '#' << test_case << ' ' << answer << '\n';

	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
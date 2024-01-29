#include <iostream>
#include <unordered_map>
#include <string>

using namespace std;

long long nhash(string str){
    const int p = 53;
    const int m = 1e9 + 9; //10^9 + 9
    int s_leng = str.length();
    long long hash_val = 0;
    int pow_p = 1;

    for(int i = 0; i < str.length(); i++){
        hash_val = (hash_val + (str[i] - 'a' + 1) * pow_p) % m;
        pow_p = (p * pow_p) % m;
    }
    
    return hash_val;
}

int solution(string B, string S){

    long long Shash = nhash(S);
    int s_leng = S.length();
    int idx = 0;
    int answer = 0;
    while(1){
        string sub = B.substr(idx, s_leng);

        long long Bhash = nhash(sub);
        if (Bhash == Shash)
            answer += 1;
        idx++;
        if (idx + s_leng > B.length())
            break;
    }
    return answer;

}

int main(int argc, char** argv)
{   
    ios::sync_with_stdio(false);
	cin.tie(); cout.tie();
	int test_case;
	int T,N,M;
    string B, S;
  

	//freopen("input.txt", "r", stdin);
	cin>>T;

	for(test_case = 1; test_case <= T; ++test_case)
	{   
        cin >> B >> S;  
        
       
        cout<< '#' << test_case << ' ' << solution(B, S) << '\n';

	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
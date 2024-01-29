#include<iostream>
#include <queue>
#include <algorithm>
using namespace std;

#define DIV 20171109

typedef long long ll;

int main(int argc, char** argv)
{   
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
	int test_case;
	ll T, N, A, a, b, c ,d;
	
	freopen("input.txt", "r", stdin);
	cin>>T;

	for(test_case = 1; test_case <= T; ++test_case)
	{   
        priority_queue<ll> max_q;
        priority_queue<ll, vector<ll>, greater<ll>> min_q;

        cin >> N >> A;
        min_q.push(A);  
        ll sum = 0;
        while(N--){
            cin >> a >> b; // minq가 항상 많다고 가정
            max_q.push(a);
            if(max_q.top() > min_q.top()){
                c = max_q.top();
                d = min_q.top();
                max_q.pop();
                min_q.pop();
                min_q.push(c);
                max_q.push(d);
            }

            min_q.push(b);
            if(max_q.top() > min_q.top()){
                c = max_q.top();
                d = min_q.top();
                max_q.pop();
                min_q.pop();
                min_q.push(c);
                max_q.push(d);
            }

            // cout << min_q.top() << endl;

            sum += min_q.top() % DIV;
        }
		cout << "#" << test_case << " " << sum % DIV << "\n";

	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
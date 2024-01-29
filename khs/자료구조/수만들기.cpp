#include<iostream>
#include <queue>
#include <map>


using namespace std;

typedef long long ll;
typedef pair<int, int> P; // 더한 횟수, K 값

struct compare{
    bool operator()(P &a, P &b){
        if (a.first != b.first)
            return a.first > b.first; //산을 오름
        return a.second < b.second;
    }
};

int main(int argc, char** argv)
{
	int test_case;
	int T, N, x = 0, D = 1, K;
    int time, now;
    ll a;
    ll A[10];

	//freopen("input.txt", "r", stdin);
	cin>>T;
	/*
	   여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
	*/
	for(test_case = 1; test_case <= T; ++test_case)
	{   
        priority_queue<P, vector<P>, compare> pq;
        x = 0;
        cin >> N;
        for(int i = 0; i < N; i++){
            cin >> a;
            A[i] = a;
        }
        cin >> K;
        pq.push({0, K});
        while (1){
            P cur = pq.top();
            pq.pop();
            if (cur.second == 0){
                cout << "#" << test_case << " " << cur.first << "\n";
                break;
            }
            pq.push({cur.first + cur.second, 0});
            for(int i = 0; i < N;  i++){
                pq.push({cur.first + cur.second % A[i], cur.second / A[i]});
            }
            
        }

	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
#include<iostream>
#include <queue>



using namespace std;

int main(int argc, char** argv)
{   
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
	int test_case;
	int T, N, order, a;
 
	//freopen("input.txt", "r", stdin);
	cin>>T;
	/*
	   여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
	*/
	for(test_case = 1; test_case <= T; ++test_case)
	{
        cin >> N;
        cout << "#" << test_case << " ";
        priority_queue<int> pq;
        while(N--){
            
            cin >> order;
            switch (order)
            {
                case 1:
                    cin >> a;
                    pq.push(a);
                    break;
                case 2:
                    if (pq.empty()){
                        cout << -1 << " ";
                        break;
                    }
                    auto p = pq.top();
                    cout << p << " ";
                    pq.pop();
                    break;
                
            }
        }
		

	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
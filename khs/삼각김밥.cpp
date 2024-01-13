
#include<iostream>
#include <unordered_map>
#include <string.h>

using namespace std;

#define MAX_N  10001
#define MAX_LEN  141

typedef pair<int, int> P;

unordered_map<int, P> pos;

int main(int argc, char** argv)
{	
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int test_case;
	int T;
    
	
	cin>>T;

    int graph[MAX_LEN][MAX_LEN];

    memset(graph, -1, sizeof(graph));

    int cnt, idx, num;
    cnt = 0;
    idx = 0;
    num = 1;
    while(1){
        graph[idx][cnt] = num;

        pos[num] = P(idx, cnt);
        cnt += 1;
        num += 1;
        if (idx + 1 ==cnt){
            idx += 1;
            cnt = 0;
        }
        if (num == MAX_N)
            break;
    }
    int s, e, x, y;
    int x_0, y_0, x_1, y_1, x_dis, y_dis;
	for(test_case = 1; test_case <= T; ++test_case)
	{
        cin >> s >> e;
        // s = 1;
        // e = 10000;
        cnt = 0;
        if (s > e){
            int temp = e;
            e = s;
            s = temp;
        }
        x_0 = pos[s].first;
        y_0 = pos[s].second;
        x_1 = pos[e].first;
        y_1 = pos[e].second;
        x_dis = x_1 - x_0;
        y_dis = y_1 - y_0;

        if (x_dis > 0 && y_dis > 0) {
            int fast_cnt = min(x_dis, y_dis);
            cnt += fast_cnt;
            x_dis -= fast_cnt;
            y_dis -= fast_cnt;
        }       
        cout << "#" << test_case << " "<< cnt + abs(x_dis) + abs(y_dis) << "\n";

		/////////////////////////////////////////////////////////////////////////////////////////////
		/*
			 이 부분에 여러분의 알고리즘 구현이 들어갑니다.
		 */
		/////////////////////////////////////////////////////////////////////////////////////////////


	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
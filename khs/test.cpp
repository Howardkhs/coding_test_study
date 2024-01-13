
#include <iostream>
#include <string.h>
#include <cmath>
#include <unordered_map>

using namespace std;
#define MAX_LEN  141
unordered_map<int, int> pos;

int main(int argc, char** argv)
{	
    ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int test_case;
	int T, s, e;
    
	
	cin>>T;
    int x_0, y_0, x_1, y_1, num, idx, x_dis, y_dis, cnt;
    num = 1;
    idx = 1;
    while(1){
        pos[idx] = num;
        num += idx;
        idx += 1;
        if (num >= 10200)
            break;        
    }


	for(test_case = 1; test_case <= T; ++test_case)
	{
        cin >> s >> e;

     
        if (s > e){
            int temp = e;
            e = s;
            s = temp;
        }

        x_0 = ceil((-1 + sqrt(pow(1, 2) + 8 * s * 1)) / 2);
        y_0 = s - pos[x_0] + 1;

 
        x_1 = ceil((-1 + sqrt(pow(1, 2) + 8 * e * 1)) / 2);
        y_1 = e - pos[x_1] + 1;
  

        x_dis = x_1 - x_0;
        y_dis = y_1 - y_0;
        cnt = 0;
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
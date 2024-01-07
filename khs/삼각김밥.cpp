/////////////////////////////////////////////////////////////////////////////////////////////
// 기본 제공코드는 임의 수정해도 관계 없습니다. 단, 입출력 포맷 주의
// 아래 표준 입출력 예제 필요시 참고하세요.
// 표준 입력 예제
// int a;
// float b, c;
// double d, e, f;
// char g;
// char var[256];
// long long AB;
// cin >> a;                            // int 변수 1개 입력받는 예제
// cin >> b >> c;                       // float 변수 2개 입력받는 예제 
// cin >> d >> e >> f;                  // double 변수 3개 입력받는 예제
// cin >> g;                            // char 변수 1개 입력받는 예제
// cin >> var;                          // 문자열 1개 입력받는 예제
// cin >> AB;                           // long long 변수 1개 입력받는 예제
/////////////////////////////////////////////////////////////////////////////////////////////
// 표준 출력 예제
// int a = 0;                            
// float b = 1.0, c = 2.0;               
// double d = 3.0, e = 0.0; f = 1.0;
// char g = 'b';
// char var[256] = "ABCDEFG";
// long long AB = 12345678901234567L;
// cout << a;                           // int 변수 1개 출력하는 예제
// cout << b << " " << c;               // float 변수 2개 출력하는 예제
// cout << d << " " << e << " " << f;   // double 변수 3개 출력하는 예제
// cout << g;                           // char 변수 1개 출력하는 예제
// cout << var;                         // 문자열 1개 출력하는 예제
// cout << AB;                          // long long 변수 1개 출력하는 예제
/////////////////////////////////////////////////////////////////////////////////////////////

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
    
	/*
	   아래의 freopen 함수는 input.txt 를 read only 형식으로 연 후,
	   앞으로 표준 입력(키보드) 대신 input.txt 파일로부터 읽어오겠다는 의미의 코드입니다.
	   //여러분이 작성한 코드를 테스트 할 때, 편의를 위해서 input.txt에 입력을 저장한 후,
	   freopen 함수를 이용하면 이후 cin 을 수행할 때 표준 입력 대신 파일로부터 입력을 받아올 수 있습니다.
	   따라서 테스트를 수행할 때에는 아래 주석을 지우고 이 함수를 사용하셔도 좋습니다.
	   freopen 함수를 사용하기 위해서는 #include <cstdio>, 혹은 #include <stdio.h> 가 필요합니다.
	   단, 채점을 위해 코드를 제출하실 때에는 반드시 freopen 함수를 지우거나 주석 처리 하셔야 합니다.
	*/
	//freopen("input.txt", "r", stdin);
	cin>>T;
	/*
	   여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
	*/
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
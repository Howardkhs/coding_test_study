#include <iostream>
#include <algorithm>
#include <vector>
#include <string.h>
using namespace std;
#define MAX_N 50
int a[MAX_N] = {0};
int b[MAX_N] = {0};
int c[MAX_N] = {0};
int min_abc[MAX_N] = {0};

int main(int argc, char** argv)
{	
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
	int test_case;
	int T, n, answer, _a, _b, _c, tot, temp;
    int idx_a, idx_b, idx_c;
    
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

	for(test_case = 1; test_case <= T; ++test_case)
	{	
        
        cin >> n;
      
        answer = 2111111111;
        tot = 0;
        idx_a = 0;
        idx_b = 0;
        idx_c = 0;
        
       
        for (int i = 0; i < n; i++){
            cin >> _a >> _b >> _c;
            
            a[i] = _b + _c;
            b[i] = _a + _c;
            c[i] = _a + _b;
            int min_temp[3];
            min_temp[0] = a[i];
            min_temp[1] = b[i];
            min_temp[2] = c[i];

            int minVal = *min_element(min_temp, min_temp+3);
            // min_abc[i] = min({a[i], b[i], c[i]});
            min_abc[i] = minVal;
            tot += min_abc[i];

            // if (min_abc[i] == a[i]){
            //     idx_a = 1;
            // }
            // if (min_abc[i] == b[i]){
            //     idx_b = 1;
            // }
            // if (min_abc[i] == c[i]){
            //     idx_c = 1;
            // }

        }
        if (n <= 2){
            cout << "#" << test_case << " " << -1 << "\n";
            continue;
        }
        // 50P3 (123) (12357) 05

        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                for (int k = 0; k < n; k++){
                    if (i == j || j == k || k == i)
                        continue;
                    temp = tot;
                    temp -= min_abc[i] + min_abc[j] + min_abc[k];
                    temp += a[i] + b[j] + c[k];
        
                    answer = min(answer, temp);
                }
            }
        }
        cout << "#" << test_case << " " << answer << "\n";


    }

	
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
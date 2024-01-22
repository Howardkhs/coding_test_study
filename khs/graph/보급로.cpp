#include<iostream>
#include <string>
#include <cstdlib>
#include <queue>

using namespace std;

struct pairs{
    int h;
    int x;
    int y;
};

int dx[4] = {-1, 1, 0, 0};
int dy[4] = { 0, 0,-1, 1};

int graph[101][101];
int T, N, n;


struct compare{
    bool operator()(pairs &a, pairs &b){
        return a.h >= b.h;
    }
};

int main(int argc, char** argv)
{   
    
	int test_case;
	
    char str[101];

	freopen("input.txt", "r", stdin);
	cin>>T;
	/*
	   여러 개의 테스트 케이스가 주어지므로, 각각을 처리합니다.
	*/
	for(test_case = 1; test_case <= T; ++test_case)
	{   
        priority_queue<pairs, vector<pairs>, compare> pq;
        int visited[101][101] = {0,};
        cin >> N;
        
        for (int i = 0; i < N; i++){
            cin >> str;
            for (int j = 0; j < N; j++){
                char t = str[j];
                n = atoi(&t);
                graph[i][j] = n;
            }
        }
        pairs a = {0,0,0};
        pq.push(a);

        while (!pq.empty()){
            a = pq.top();
            pq.pop();
            int h = a.h;
            int x = a.x;
            int y = a.y;
            if(x == N-1 && y == N-1){
                cout<< '#' << test_case << ' ' << h << '\n';
                break;
            }
            
            for (int i = 0; i < 4; i++){
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (nx < 0 || ny < 0 || nx >= N || ny >= N)
                    continue;
                if (visited[nx][ny] == 1)
                    continue;
                int nh = h + graph[nx][ny];
                visited[nx][ny] = 1;
                pq.push({nh, nx , ny});
            }
        }

        


	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
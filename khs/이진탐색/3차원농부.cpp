#include<iostream>
#include <algorithm>

using namespace std;

int cow[500000];
int horse[500000];

int lowerSearch(int target, int start, int end){

    int up = -1;
    while (start <= end){
        int mid = start + (end - start) / 2;
        // cout << horse[mid] << endl; 
        if (horse[mid] == target)
            return mid;
        
        if (horse[mid] < target){
            up = mid;
            start= mid + 1;
        }
        else{
            end = mid - 1;
        }
        
    }
    return up;
}// -1이면 인덱스 안에 없는거다.  결국 끝까지 탐색했읒나 그거보다 작은수를

int upperSearch(int target, int start, int end){

    int up = -1;
    while (start <= end){
        int mid = start + (end - start) / 2;
        // cout << horse[mid] << endl; 
        if (horse[mid] == target)
            return mid;
        
        if (horse[mid] < target){
            
            start= mid + 1;
        }
        else{
            end = mid - 1;
            up = mid;
        }
        
    }
    return up;
}  // -1이면 인덱스 안에 없는거다.  결국 끝까지 탐색했읒나 그거보다 큰수를 못찾은거지

int main(int argc, char** argv)
{   
    ios::sync_with_stdio(false);
	cin.tie(); cout.tie();
	int test_case;
	int T, N, M, z;
    int c_0, c_1;
	
	//freopen("input.txt", "r", stdin);
	cin>>T;
	
	for(test_case = 1; test_case <= T; ++test_case)
	{
        cin >> N >> M;
        cin >> c_0 >> c_1;
        int distance = 2*10e9;
        for(int i = 0; i < N; i++){
            cin >> z;
            cow[i] = z;
        }
        for(int i = 0; i < M; i++){
            cin >> z;
            horse[i] = z;
        }
		sort(cow, cow + N);
        sort(horse, horse + M);
        int cnt = 0;
        for (int i = 0 ; i < N; i++){
            int up = upperSearch(cow[i], 0, M-1);
            int down = lowerSearch(cow[i], 0, M-1); 
           
        

            if (up == down){
                int temp_distance = abs(c_0 - c_1) + abs(cow[i] - horse[up]);
                if (temp_distance < distance){
                    distance = temp_distance;
                    cnt = 1;
                }
                else if(temp_distance == distance){
                    cnt += 1;
                }
                continue;
            }

            if (up != -1){
                int temp_distance = abs(c_0 - c_1) + abs(cow[i] - horse[up]);
                if (temp_distance < distance){
                    distance = temp_distance;
                    cnt = 1;
                }
                else if(temp_distance == distance){
                    cnt += 1;
                }
            }

            if (down != -1){
                int temp_distance = abs(c_0 - c_1) + abs(cow[i] - horse[down]);
                if (temp_distance < distance){
                    distance = temp_distance;
                    cnt = 1;
                }
                else if(temp_distance == distance){
                    cnt += 1;
                }
            }
    
                        
        }
        cout << "#" << test_case << " " << distance << " " << cnt << "\n";
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
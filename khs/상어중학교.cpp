#include <iostream>
#include <queue>
#include <iomanip>

using namespace std;

struct P{
    int size, rainbow, x, y;
    

    bool operator<(const P& other) const{

        if (size != other.size){
            return size < other.size;
        }
        if (rainbow != other.rainbow){
            return rainbow < other.rainbow;
        }
        if (x != other.x){
            return x < other.x;
        }
        if (y!= other.y){
            return y < other.y;
        }
    }
};
typedef pair <int, int> XY;
priority_queue<P> pq; // 크기, 무지개블록, 행, 열
queue <XY> q;

int arr[21][21], visited[21][21];
int dx[] = {0,0,1,-1};
int dy[] = {1,-1,0,0};
int N, M;


void rotate(){
    int _arr[21][21];
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            _arr[i][j] = arr[j][N-1-i];
        }
    }
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            arr[i][j] = _arr[i][j];
        }
    }
}

void gravity(){

    for (int j = 0; j < N; j++){
        for (int i = 1; i < N; i++){
            if (arr[i][j] == 9){
                int i_ = i;
                while (i_ > 0){
                    if (arr[i_-1][j] == -1)
                        break;
                    int swap;
                    swap = arr[i_][j];
                    arr[i_][j] = arr[i_-1][j];
                    arr[i_-1][j] = swap;
                    i_ -= 1;
                }
            }
        }
    }
}


void popping(P top){

    int visited[21][21] = {};
    int size, rainbow, x, y;
    x = top.x;
    y = top.y;
    int color = arr[x][y];

    XY now = {x,y};
    q.push(now);
    while (!q.empty()){
        XY now = q.front();
        q.pop();
        int x = now.first;
        int y = now.second;
        visited[x][y] = -1;
        arr[x][y] = 9;

        for (int k = 0; k < 4; k++){
            int nx = x + dx[k];
            int ny = y + dy[k];
            if (nx < 0 || nx >= N || ny < 0 || ny >= N)
                continue;
            if (visited[nx][ny] == -1)
                continue;
            if (arr[nx][ny] == -1 or arr[nx][ny] == 9)
                continue;
            if (arr[nx][ny] == color or arr[nx][ny] == 0){
                XY now = {nx, ny};
                q.push(now);
                visited[nx][ny] = -1;
                

            }
        }
    }
}

void search(int color){

    int visited[21][21] = {};

    int x_;
    int y_;


    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){

            if (visited[i][j] == -1 || arr[i][j] == 0)
                continue;
            if (arr[i][j] == color){
    
                XY now = {i,j};
                x_ = i;
                y_ = j;
                q.push(now);

                int cnt = 0;
                int r_cnt = 0;
                visited[i][j] = -1;
                while (!q.empty()){
                    XY now = q.front();
                    q.pop();
                    cnt += 1;

                    int x = now.first;
                    int y = now.second;

                    if (arr[x][y] == 0)
                        r_cnt += 1;

                    for (int k = 0; k < 4; k++){
                        int nx = x + dx[k];
                        int ny = y + dy[k];
                        if (nx < 0 || nx >= N || ny < 0 || ny >= N)
                            continue;
                        if (arr[nx][ny] == -1 || visited[nx][ny] == -1)
                            continue;
                        if (arr[nx][ny] == color or arr[nx][ny] == 0){
                            XY now = {nx, ny};
                            q.push(now);
                            visited[nx][ny] = -1;
                        }
                    }
                }
                if (cnt >= 2){
                    P group = {cnt, r_cnt, x_, y_};
                    pq.push(group);
                }
            }
        }
    }
}


int main(){

    cin >> N >> M;
    int score = 0;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            cin >> arr[i][j];
        }
    }
    while (true){

        for (int i = 1; i <= M; i++){
            search(i);
        }
        if (pq.empty())
            break;
        P top = pq.top();
        score += top.size * top.size;
        popping(top);
        // cout << "after popping\n";

        // for (int i = 0; i < N; i++){
        //     for (int j = 0; j < N; j++){
        //         cout << setw(2) << arr[i][j] << " ";
        //     }   
        //     cout << endl;
        // }
        
        gravity();
        // cout << "after gravity\n";

        // for (int i = 0; i < N; i++){
        //     for (int j = 0; j < N; j++){
        //         cout << setw(2) << arr[i][j] << " ";
        //     }   
        //     cout << endl;
        // }
        rotate();
        // cout << "after swap\n";

        // for (int i = 0; i < N; i++){
        //     for (int j = 0; j < N; j++){
        //         cout << setw(2) << arr[i][j] << " ";
        //     }   
        //     cout << endl;
        // }
        gravity();
        // cout << "after gravity\n";

        // for (int i = 0; i < N; i++){
        //     for (int j = 0; j < N; j++){
        //         cout << setw(2) << arr[i][j] << " ";
        //     }   
        //     cout << endl;
        // }
        while (!pq.empty())
            pq.pop();
        
    }
    cout << score << endl;
}


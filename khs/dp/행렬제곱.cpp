#include <iostream>

using namespace std;

#define DIV 1000


long long N, B;
long long arr[5][5];
long long answer[5][5];

void dq(long long B){

    long long b = B;
    
    if (b == 1){
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                answer[i][j] = arr[i][j] % 1000;
            }
        }
        return;
    }
    long long temparr[5][5];


    if (b % 2 == 0){
        dq(b / 2);
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                temparr[i][j] = answer[i][j];
            }
        }

        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                int x, y;
                x = i;
                y = j;
                int k = 0;
                long long sum = 0;
                while (1){
                    sum += temparr[i][k] * temparr[k][j];
                    k += 1;
                    if (k == N)
                        break;
                }
                answer[i][j] = sum % DIV;
            }
        }      

    }   
    if (b % 2 == 1){
        dq(b / 2);
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                temparr[i][j] = answer[i][j];
            }
        }

        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                int x, y;
                x = i;
                y = j;
                int k = 0;
                long long sum = 0;
                while (1){
                    sum += temparr[i][k] * temparr[k][j];
                    k += 1;
                    if (k == N)
                        break;
                }
                answer[i][j] = sum % DIV;
            }
        }    
      
        long long _temparr[5][5];
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                _temparr[i][j] = answer[i][j];
            }
        }
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                temparr[i][j] = arr[i][j];
            }
        }
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                int x, y;
                x = i;
                y = j;
                int k = 0;
                long long sum = 0;
                while (1){
                    sum += _temparr[i][k] * temparr[k][j];
                    k += 1;
                    if (k == N)
                        break;
                }
                answer[i][j] = sum % DIV;
            }
        }   

    }   
  
    return;
    

}


int main(){

    cin >> N >> B;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            cin >> arr[i][j];
        }
    }
    dq(B);
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            cout << answer[i][j] << " ";
        }
        cout << endl;
    }
}
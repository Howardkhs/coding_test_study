#include <iostream>
#include <map>
#include <cmath>

using namespace std;

typedef pair<long long , long long > P;
map<long long , long long > x_log;
map<long long , long long > y_log;
int main(){
    ios_base :: sync_with_stdio(false); 
    cin.tie(NULL); 
    cout.tie(NULL);
    long long  N, K, Q;
    cin >> N >> K >> Q;
    while (Q--){
        long long  x, y;
        cin >> x >> y;
        if (K==1){
            cout << abs(y-x) << "\n";
            continue;
        }
        if (y > x){
            long long  temp = y;
            y = x;
            x = temp;
        }


        long long  n = 0;
        P x_pos, y_pos;
        long long  sum = 0;

        while (1){
            sum += pow(K, n);

            if (sum >= x){
                long long  mod = pow(K, n) - (sum-x);
                x_pos = {n, mod};
                break;
            }
            n += 1;
        }

        n = 0;
        sum = 0;

        while (1){
            sum += pow(K, n);
            if (sum >= y){
                long long  mod = pow(K, n) - (sum-y);
                y_pos = {n, mod};
       
                break;
            }
            n += 1;
        }

   
        x_log.clear();
        y_log.clear();
        x_log[x_pos.first] = x_pos.second;
        y_log[y_pos.first] = y_pos.second;

        long long  i, j;
        i = x_pos.first;
        j = x_pos.second;
 
        while (1){
      
        
            if (i == 0 && j == 1)
                break;
            i -= 1;
            if (j % K  != 0){
                j = (j / K) + 1;
                x_log[i] = j;
            }
            else{
                j = j / K;
                x_log[i] = j;
            }
        }

        i = y_pos.first;
        j = y_pos.second;

        while (1){
       
            if (i == 0 && j == 1)
                break;
            i -= 1;
            if (j % K  != 0){
                j = (j / K) + 1;
                y_log[i] = j;
            }
            else{
                j = j / K;
                y_log[i] = j;
            }
        }
        
        long long  key = 0;

        // cout << "x \n";
        // for (auto keys = y_log.rbegin(); keys != y_log.rend(); keys++){
        //     cout << keys->first << " " << keys->second << endl;
        // }
        


        for (auto keys = y_log.rbegin(); keys != y_log.rend(); keys++){
            key = keys->first;
            if(x_log[key] == y_log[key])
                break;
        }
        
        long long  x_end_key = (x_log.rbegin())->first;
        long long  y_end_key = (y_log.rbegin())->first;
     
        cout << x_end_key - key + y_end_key - key << "\n";



    }

}
#include <iostream>
#include <deque>
#include <unordered_set>
using namespace std;

struct PairHash {
    template <typename T, typename U>
    std::size_t operator()(const std::pair<T, U>& p) const {
        auto hash1 = std::hash<T>{}(p.first);
        auto hash2 = std::hash<U>{}(p.second);

        return hash1 ^ hash2;
    }
};

struct PairEqual {
    template <typename T, typename U>
    bool operator()(const std::pair<T, U>& lhs, const std::pair<T, U>& rhs) const {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }
};


typedef pair<int, int> P;
unordered_set<P, PairHash, PairEqual> answer;

int arr[2000];

int main(){
    int N;
    cin >> N;

    for (int i = 0; i < N; i++){
        cin >> arr[i];
    }

    for (int i = 0; i < N; i++){
        for (int j = 2; j < N; j+=2){
            if (i + j >= N)
                break;
            deque<int> q;
            int fail = 0;
            for (int k = i; k < i + (j / 2); k++){
                q.push_back(arr[k]);
            }
            for (int k = i + j / 2 + 1; k < i + j + 1; k++){
                int a;
                a = q.back();
                q.pop_back();
                if (a != arr[k]){
                    fail = 1;
                    break;
                }
            }
            if (fail == 0){
                P p = {i + 1, i + j + 1};
                answer.insert(p);
            }

        }
    }

    int M;
    int S, E;
    cin >> M;
    while(M--){
        cin >> S >> E;
        P p = {S,E};
        if (S == E)
            cout << 1 << "\n";
        else if (answer.find(p) != answer.end())
        {
            cout << 1 << "\n";
        }
        else
            cout << 0 << "\n";
        
    }


}

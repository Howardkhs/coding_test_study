#include <iostream>
#include <string>
#include <algorithm> 
#include <vector>

using namespace std;

bool compare(pair <int, string> a, pair <int, string> b){
    if (a.first == b.first)
        return (a.second > b.second);
    return (a.first > b.first);
}

int main(){
    vector <pair<int, string>> v;
    string s[4] = {"sort", "compare", "function" , "test"};
    for (int i = 0; i < 4; i++){
        v.push_back({s[i].size(), s[i]});
    }
    sort(v.begin(), v.end());
    cout << "단순 오름차순 \n";
    for(auto c: v)
        cout << c.first << " " << c.second << "\n";
    sort(v.begin(), v.end(), compare);
    cout << "compare 함수 구현 \n";
    for(auto c: v)
        cout << c.first << " " << c.second << "\n";
}
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

int main() {
    vector <char> v1 = { 'A','B','C' }; // 사전순으로 정렬되어있어야함
    vector <char> v2 = { 'B','C','A' };
    do {
        for (auto x : v1)
            cout << x; 
        cout << "\n"; 
    } while (next_permutation(v1.begin(), v1.end()));//계속해서 정렬
    cout << "\n"; 

    do {
        for (auto x : v2)
            cout << x;
        cout << "\n";
    } while (next_permutation(v2.begin(), v2.end()));//계속해서 정렬
    cout << "\n";
}
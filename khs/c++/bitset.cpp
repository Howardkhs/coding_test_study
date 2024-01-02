#include <iostream>
#include <bitset>
using namespace std;

int main(){
    bitset<10> test(8);
    cout << test << "\n";
    string binary = bitset<4>(8).to_string();
    cout << binary << "\n";

}
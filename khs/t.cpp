#include <iostream>
#include <algorithm>
#include <vector>
#include <string.h>
#include <unordered_map>
using namespace std;
#define MAX_N 50
int a[MAX_N] = {0};
int b[MAX_N] = {0};
int c[MAX_N] = {0};
int min_abc[MAX_N] = {0};
unordered_map<string, vector<int>> idxs;

struct P{
    int temp;
    string j;
    string idx;
    int i ;
};

int main(int argc, char** argv)
{	
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
	idxs["a"].push_back(1);
    
    string i = "a";
    cout << idxs[i][0] << endl;
    idxs[i].pop_back();

	
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
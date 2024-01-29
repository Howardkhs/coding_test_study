#include<iostream>
#include<string>
#include<unordered_map>
#include<vector>
#include<algorithm>

using namespace std;

unordered_map<string, int> word_visited;
vector<string> words;

string str;

void solution(){
    for (int i = 0; i < str.length(); i++){
        for (int j = 1; j <= str.length(); j++){
            if (i + j > str.length())
                continue;
            // cout <<  i << " " << j << endl;
            string sub = str.substr(i, j);
            
            // cout << sub << endl;
            if (word_visited[sub] == 1)
                continue;
            words.push_back(sub);
            word_visited[sub] = 1;
        }
    }
}

int main(int argc, char** argv)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
	int test_case;  

	int T, K;

	//freopen("input.txt", "r", stdin);
	cin>>T;

	for(test_case = 1; test_case <= T; ++test_case)
	{   
        words.clear();
        word_visited.clear();
        cin >> K;
        cin >> str;
        solution();

        // for (int i = 0; i < words.size(); i++){
        //     cout << words[i] << " ";
        // }
        if (words.size() < K)
            cout <<  "#" << test_case << " " << "none\n";
        else{
            sort(words.begin(), words.end());
            cout <<  "#" << test_case << " " << words[K-1] << "\n";        
        }
        
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
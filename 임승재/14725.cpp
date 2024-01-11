#include<map>
#include<set>
#include<vector>
#include<string>
#include<iostream>
#include<queue>

using namespace std;

class node
{
    public:
        map<string,node*> children;
        void insert(vector<string> v,int idx)
        {
            if(idx == v.size()) return;
            if(children.find(v[idx])==children.end())
            {
                children[v[idx]] = new node;
            }
            children[v[idx]] -> insert(v,idx+1);
        }
        void dfs(int depth)
        {
            for(auto iter=children.begin();iter!=children.end();iter++)
            {
                for(int i=0;i<depth;i++) cout << "--";
                cout << (*iter).first << '\n';
                (iter->second)->dfs(depth+1);
            }
        }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    node trie;
    int n;
    cin >> n;
    for(int i=0;i<n;i++)
    {
        int k;
        cin >> k;
        vector<string> v;
        for(int j=0;j<k;j++)
        {
            string str;
            cin >> str;
            v.push_back(str);
        }
        trie.insert(v,0);
    }
    trie.dfs(0);
}
/*
trie 자료구조
*/
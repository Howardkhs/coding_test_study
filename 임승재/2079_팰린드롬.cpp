#include<cstdio>
#include<string>
#include<vector>
#include<queue>

using namespace std;

int main()
{
	char tmp[2020];
	bool dp[2020][2020] = {0,};
	scanf("%s",tmp);
	string s=string(tmp);
	vector<vector<int>> g=vector<vector<int>>(s.length()+1,vector<int>());
	//printf("%s",s.c_str());
	for(int i=0;i<s.length();i++)
	{
		dp[i][i] = true;
		g[i].push_back(i+1);
		for(int j=1;i-j>=0 && i+j<s.length();j++)
		{
			if(s[i-j] == s[i+j])
			{
				dp[i-j][i+j] = true;
				g[i-j].push_back(i+j+1);
			}
			else break;
		}
		if(i+1<s.length() && s[i]==s[i+1])
		{
			dp[i][i+1] = true;
			g[i].push_back(i+2);
			for(int j=1;i-j>=0 && i+1+j<s.length();j++)
			{
				if(s[i-j] == s[i+1+j])
				{
					dp[i-j][i+1+j] = true;
					g[i-j].push_back(i+j+2);
				}
				else break;
			}
		}
	}
	/*
	for(int i=0;i<s.length();i++)
	{
		for(int j=0;j<s.length();j++)
		{
			printf("%d ",dp[i][j]);
		}
		printf("\n");
	}
	
	for(int i=0;i<s.length();i++)
	{
		for(int j=0;j<g[i].size();j++)
		{
			printf("%d ",g[i][j]);
		}
		printf("\n");
	}
	*/
	queue<int> q;
	bool visited[2020] = {0,};
	int dist[2020] = {0,};
	visited[0] = true;
	q.push(0);
	while(!q.empty())
	{
		int cur = q.front();
		q.pop();
		for(int i=0;i<g[cur].size();i++)
		{
			if(!visited[g[cur][i]])
			{
				visited[g[cur][i]] = true;
				dist[g[cur][i]] = dist[cur]+1;
				q.push(g[cur][i]);
			}
		}
	}
	printf("%d",dist[s.size()]);
}

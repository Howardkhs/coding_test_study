#include <iostream>
#include <malloc.h>
#include <cstring>
#include <string>
#include <vector>
using namespace std;
int T, K, tot;
vector <char> ans;
struct NODE {
	int alpha[26 + 2];
	bool isEnd;
	NODE* next[26 + 2];
};
NODE * makeNode() {
	NODE *tmp = (NODE*)malloc(sizeof(NODE));
	for (int i = 0; i < 26; i++) {
		tmp->next[i] = 0; tmp->alpha[i] = 0;
	}
	tmp->isEnd = false;
	return tmp;
};

void push(NODE *root, string str, int s, int e) {
	NODE *tmp = root;
	if (s == e) {	tmp->isEnd = true; return;}
	if (!tmp->next[str[s] - 'a']) tmp->next[str[s] - 'a']=makeNode();
	tmp->alpha[str[s] - 'a'] += 1;
	push(tmp->next[str[s] - 'a'], str, s + 1, e);//재귀 형식
}

void find(NODE *root) {
	NODE *tmp = root;
	if (tmp->isEnd)
		tot++;
	if (tot == K)
		return;
	for (int i = 0; i < 26; i++) {
		if (tmp->next[i]) {
			ans.push_back(i + 'a');
			find(tmp->next[i]);
			if (tot == K)return;
			ans.pop_back();
		}
	}
}

void del(NODE *root) {
	NODE *tmp = root;
	for (int i = 0; i < 26; i++) {
		if (tmp->next[i]) del(tmp->next[i]);
	}
	free(tmp);
}

int main() {
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		string arr; tot = 0; ans.clear();
		scanf("%d", &K);
		cin >> arr;
		int len = strlen(arr.c_str());
		//cout << arr;
	
		NODE *root = makeNode();
		for (int i = 0; i < len; i++) {
			if (!root->next[arr[i] - 'a']) root->next[arr[i] - 'a'] = makeNode();
			root->alpha[arr[i] - 'a']++;
			push(root->next[arr[i] - 'a'], arr, i + 1, len);
		}
		find(root);
		del(root);
		printf("#%d ", tc);
		for (int i = 0; i < ans.size(); i++) cout << ans[i];
		printf("\n");
	}
	
	return 0;
}
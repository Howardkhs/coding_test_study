#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

///////////////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

char OFFSET = 'a';
int del_cnt;
int ser_cnt;

int char_to_int(char a){
    return a - OFFSET + 1;
}
class Node;

vector<Node> nodevec;
int root_id = 0;
int ptr = 0; // 노드 위치 포인터

class Node{
    public:
        int count = 0;
        int child[27] = {0,};

        Node(){};

        int insert(char str[], int len){
            int now_id = root_id;
            for (int i = 0; i < len; i++){
                int alpha = char_to_int(str[i]);
                if (nodevec[now_id].child[alpha] == 0){
                    nodevec[now_id].child[alpha] = ptr; // child가 포인터를 가리킴
                    nodevec.emplace_back();
                    now_id = ptr++;
                }
                else{
                    now_id = nodevec[now_id].child[alpha];
                }
            }
            nodevec[now_id].count++;
            return nodevec[now_id].count;
        }

        void remove(char str[], int idx, int now_id){
            if (idx == strlen(str)){
                if (nodevec[now_id].count > 0){
                    del_cnt += nodevec[now_id].count;
                    nodevec[now_id].count = 0;
            
                }
                return;
            }
            if (!(str[idx] == '?')){
                Node *now_node = &nodevec[now_id];
                int alpha = char_to_int(str[idx]);
                if (now_node->child[alpha] != 0){
                    remove(str, idx+1, now_node->child[alpha]);
                }
            }
            else{
                Node *now_node = &nodevec[now_id];
                for (int i = 0; i < 27; i++){
                    if (now_node->child[i] != 0){
                        remove(str, idx+1, now_node->child[i]);
                    }
                }
            }

        }
        void search(char str[], int idx, int now_id){
            if (idx == strlen(str)){
                if (nodevec[now_id].count > 0){
                    ser_cnt += nodevec[now_id].count;
                }
                return;
            }
            if (!(str[idx] == '?')){
                Node *now_node = &nodevec[now_id];
                int alpha = char_to_int(str[idx]);
                if (now_node->child[alpha] != 0){
                    search(str, idx+1, now_node->child[alpha]);
                }
            }
            else{
                Node *now_node = &nodevec[now_id];
                for (int i = 0; i < 27; i++){
                    if (now_node->child[i] != 0){
                       search(str, idx+1, now_node->child[i]);
                    }
                }
            }
        }
        
};

void init() {
    nodevec.clear();
    Node root;
    nodevec.push_back(root);
    ptr = 0;
    ptr++;
	return;
}

int add(char str[]) {
    Node rnode = nodevec[root_id];
    
	return rnode.insert(str, strlen(str));
}

int remove(char str[]) {
    Node rnode = nodevec[root_id];
    del_cnt = 0;
    rnode.remove(str, 0, 0);
    // cout << del_cnt << endl;
	return del_cnt;
}

int search(char str[]) {
    Node rnode = nodevec[root_id];
    ser_cnt = 0;
    rnode.search(str, 0, 0);
    // cout << ser_cnt << endl;
	return ser_cnt;
}

void print_n(int node_id){
    Node a = nodevec[node_id];
    for (int i = 0; i < 27; i++){
        if (a.child[i] != 0){
            char c = i + 'a' - 1;
            cout << c;
            print_n(a.child[i]);
        }
    }
    cout << a.count;    
}


/////////////////////////////////////////////////////////////////////////

#define MAX_LEN 30
#define CMD_INIT 1
#define CMD_ADD 2
#define CMD_REMOVE 3
#define CMD_SEARCH 4

static bool run() {
	int q;
	scanf("%d", &q);

	char str[MAX_LEN + 1];
	int cmd, ans, ret = 0;
	bool okay = false;

	for (int i = 0; i < q; ++i) {
		scanf("%d", &cmd);
		switch (cmd) {
			case CMD_INIT:
				init();
				okay = true;
				break;
			case CMD_ADD:
				scanf("%s %d", str, &ans);
				ret = add(str);
				if (ans != ret)
					okay = false;
				break;
			case CMD_REMOVE:
				scanf("%s %d", str, &ans);
				ret = remove(str);
				if (ans != ret)
					okay = false;
				break;
			case CMD_SEARCH:
				scanf("%s %d", str, &ans);
				ret = search(str);
				if (ans != ret)
					okay = false;
				break;
			default:
				okay = false;
				break;
		}
        // print_n(0);
        // cout << endl;
	}
	return okay;
}

int main() {
	setbuf(stdout, NULL);
	freopen("sample_input.txt", "r", stdin);

	int T, MARK;
	scanf("%d %d", &T, &MARK);

	for (int tc = 1; tc <= T; tc++) {
		int score = run() ? MARK : 0;
		printf("#%d %d\n", tc, score);
	}

	return 0;
}
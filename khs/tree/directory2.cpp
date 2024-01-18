#ifndef _CRT_SECURE_NO_WARNINGS 
#define _CRT_SECURE_NO_WARNINGS 
#endif

#include <iostream>
#include <string>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <string.h>

using namespace std;

#define CMD_MKDIR 1
#define CMD_RM 2
#define CMD_CP 3
#define CMD_MV 4
#define CMD_FIND 5

#define NAME_MAXLEN 6
#define PATH_MAXLEN 1999

#define MAX_L 50050

int node_cnt = 0;
int node_num[MAX_L];
int node_sum[MAX_L];
string node_name[MAX_L];
vector<unordered_map<string, int>> node_v; // vector[int] ->string ->int

void init(int n){
    fill(node_num, node_num + MAX_L, 0); 
    fill(node_sum, node_sum + MAX_L, 0);
    node_sum[0] = 1;
    node_name[0] = "/";
    node_cnt = 1;
    node_v.clear();
    for (int i = 0; i < MAX_L; i++){
        unordered_map<string, int> map1; // 이걸 벡터로 바꿔보자
        node_v.push_back(map1);
    }

	return;
}

void cmd_mkdir(char path[PATH_MAXLEN + 1], char name[NAME_MAXLEN + 1]){
    
 
    int node = 0;
    char* result;
	result = strtok(path, "/");	
	while(result != NULL){
		char parsing[7];
		strcpy(parsing, result);
		if (parsing[0] =='\0')
			break;
		string str_buf(parsing);
		node = node_v[node][str_buf];
		result = strtok(NULL,"/");
	}

    string _name(name);
    node_num[node_cnt] = node;  // parent 생성 1->0
    node_v[node][_name] = node_cnt;

    int _node = node;
    int _cnode = node_cnt;
    node_sum[_cnode] = 1;
    int count = node_sum[_cnode];

    while (_cnode != 0){
        node_sum[_node] += count;
        _cnode = _node;
        _node = node_num[_node];
    }

    node_name[node_cnt] = _name; // 이름 저장
    node_cnt++;
    // cout << node_name[node_cnt];


}

void cmd_rm(char path[PATH_MAXLEN + 1]){

    int node = 0;
    char* result;
	result = strtok(path, "/");	
	while(result != NULL){
		char parsing[7];
		strcpy(parsing, result);
		if (parsing[0] =='\0')
			break;
		string str_buf(parsing);
		node = node_v[node][str_buf];
		result = strtok(NULL,"/");
	}


    int _cnode = node; // 자식
    int _node = node_num[node]; // 아빠

    // node_num[_cnode]  = 1;
    int count = node_sum[_cnode];
    while (_cnode != 0){
        node_sum[_node] -= count;
        _cnode = _node;
        _node = node_num[_node];
    }

    node_v[node_num[node]].erase(node_name[node]);
    node_num[node] = -1; // 연결 끊어버림

}

int copy(int node){
    

    int now_node = node_cnt;
    node_cnt++;
    node_sum[now_node] = node_sum[node];
    node_name[now_node] = node_name[node];
    for (auto p = node_v[node].begin(); p != node_v[node].end(); p++){
 
        int child_node = copy(p->second);
        node_num[child_node] = now_node;
        node_v[now_node][p->first] = child_node;
    }
    return now_node;
    
}


void cmd_cp(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]){
	

	int node = 0;
    char* result;
	result = strtok(srcPath, "/");	
	while(result != NULL){
		char parsing[7];
		strcpy(parsing, result);
		if (parsing[0] =='\0')
			break;
		string str_buf(parsing);
		node = node_v[node][str_buf];
		result = strtok(NULL,"/");
	}

    int c_node = copy(node);
    
    node = 0;
    result = strtok(dstPath, "/");	
    while(result != NULL){
		char parsing[7];
		strcpy(parsing, result);
		if (parsing[0] =='\0')
			break;
		string str_buf(parsing);
		node = node_v[node][str_buf];
		result = strtok(NULL,"/");
	}
    // cout << c_node << "찾는것" << endl;
    // cout << node << "붙이기" << endl;
    node_num[c_node] = node;  // parent 생성 1->0
    node_v[node][node_name[c_node]] = c_node; // child 생성 0 -> 1
    // cout << node << "의 자식들";
    // for (auto p = node_v[node].begin(); p != node_v[node].end(); p++){
    //     cout << p->first << " ";
    // }
    // cout << endl;

    int _node = node;
    int _cnode = c_node;
    int count = node_sum[_cnode];

    while (_cnode != 0){
        node_sum[_node] += count;
        _cnode = _node;
        _node = node_num[_node];
    }
    
}

void cmd_mv(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]){
	
	int node = 0;
    char* result;
	result = strtok(srcPath, "/");	
	while(result != NULL){
		char parsing[7];
		strcpy(parsing, result);
		if (parsing[0] =='\0')
			break;
		string str_buf(parsing);
		node = node_v[node][str_buf];
		result = strtok(NULL,"/");
	}

    int c_node = node;

    int _node = node_num[c_node];
    int _cnode = c_node;
    int count = node_sum[_cnode];

    while (_cnode != 0){
        node_sum[_node] -= count;
        _cnode = _node;
        _node = node_num[_node];
    }

    node_v[node_num[c_node]].erase(node_name[c_node]);
    node_num[c_node] = -1;

    node = 0;
    result = strtok(dstPath, "/");	
    while(result != NULL){
		char parsing[7];
		strcpy(parsing, result);
		if (parsing[0] =='\0')
			break;
		string str_buf(parsing);
		node = node_v[node][str_buf];
		result = strtok(NULL,"/");
	}

    node_num[c_node] = node;

    node_v[node][node_name[c_node]] = c_node;

    _node = node;
    _cnode = c_node;
    count = node_sum[_cnode];

    while (_cnode != 0){
        node_sum[_node] += count;
        _cnode = _node;
        _node = node_num[_node];
    }
    // for (auto p = node_v[node].begin(); p != node_v[node].end(); p++){
    //     cout << p->first << " ";
    // }
    // cout << endl;


}

int cmd_find(char path[PATH_MAXLEN + 1]){
	int node = 0;
    char* result;
	result = strtok(path, "/");	
	while(result != NULL){
		char parsing[7];
		strcpy(parsing, result);
		if (parsing[0] =='\0')
			break;
		string str_buf(parsing);
		node = node_v[node][str_buf];
		result = strtok(NULL,"/");
	}
    // cout << node_sum[node] - 1 << "\n";
    return node_sum[node] - 1;

}	

void print(int node){

    cout << node_name[node] << "의 자식들" << endl;
    for (auto p = node_v[node].begin(); p != node_v[node].end(); p++){
        cout << p->first << " ";
    }
    cout << endl;
    for (auto p = node_v[node].begin(); p != node_v[node].end(); p++){
        print(p->second);
    }
}

void print_P(){
    for (int i = 0; i < MAX_L; i++){
        cout << node_num[i] << " ";
    }
    cout << endl;
}

static bool run(int m) {

	bool isAccepted = true;
	int cmd;
	char name[NAME_MAXLEN + 1];
	char path1[PATH_MAXLEN + 1], path2[PATH_MAXLEN + 1];

	while (m--) {

		scanf("%d", &cmd);

		if (cmd == CMD_MKDIR) {
			scanf("%s%s", path1, name);
			cmd_mkdir(path1, name);
		}
		else if (cmd == CMD_RM) {
			scanf("%s", path1);
			cmd_rm(path1);
		}
		else if (cmd == CMD_CP) {
			scanf("%s%s", path1, path2);
			cmd_cp(path1, path2);
		}
		else if (cmd == CMD_MV) {
			scanf("%s%s", path1, path2);
			cmd_mv(path1, path2);
		}
		else {
			int ret;
			int answer;

			scanf("%s", path1);
			ret = cmd_find(path1);
			scanf("%d", &answer);

			isAccepted &= (ret == answer);
		}
        // print(0);
        // cout << endl;
        // print_P();
	}
	

	return isAccepted;
}

int main(void) {

	int test, T;
	int n, m;

	

	freopen("sample_input.txt", "r", stdin);

	setbuf(stdout, NULL);

	scanf("%d", &T);
	
	for (test = 1; test <= T; ++test) {

		scanf("%d%d", &n, &m);

		init(n);

		if (run(m)) {
			printf("#%d 100\n", test);
		}
		else {
			printf("#%d 0\n", test);
		}
		
	}

	return 0;
}
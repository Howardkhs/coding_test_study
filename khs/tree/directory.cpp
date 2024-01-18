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




class Node{

    public:
        int cnt = 1;
		string name = "/";
		Node* parent = nullptr;
		unordered_map<string, Node*> childs;

        Node(string _name){
            name = _name;
        }

		void remove(){
			if (childs.empty() && !(name == "/")){
				parent->childs.erase(this->name);
				parent = nullptr;
				delete this;
				return;
			}
			vector<string> rm_list;
			for(auto p = childs.begin(); p != childs.end(); p++){
				rm_list.push_back(p->first);
			}
			for (int i = 0; i < distance(rm_list.begin(), rm_list.end()); i++){
				childs[rm_list[i]]->remove();
			}
			if (name == "/")
				return;
			parent->childs.erase(this->name);
			parent = nullptr;
			delete this;
			return;
		}

		void print(){
			if (childs.empty()){
				cout << name << endl;
				return;
			}
			for(auto p = childs.begin(); p != childs.end(); p++){
				p->second->print();
			}
			cout << name << endl;
		}

		Node* copy(){
			Node * self = new Node(name);
			self->cnt = this->cnt;
			Node * C;
			if (childs.empty()){
				return self;
			}
			for(auto p = childs.begin(); p != childs.end(); p++){
				C = p->second->copy();
				C->parent = self;
				self->childs[C->name] = C;
			}
			return self;

		}

};

int node_cnt = 0;
vector<Node*> v;

Node *root;

extern void init(int n){
	v[50050] = {nullptr};
	root = new Node("/");
	v[0] = root;
	// root->cnt = 1;
	// root->childs.clear();
	return;
}
extern void cmd_mkdir(char path[PATH_MAXLEN + 1], char name[NAME_MAXLEN + 1]){


	Node * P = root;
	Node * C;
	char* result;
	result = strtok(path, "/");	
	while(result != NULL){
		char parsing[7];
		strcpy(parsing, result);
		if (parsing[0] =='\0')
			break;
		string str_buf(parsing);
		P = P->childs[str_buf];
		result = strtok(NULL,"/");
	}

	string _name(name);
	C = new Node(_name);
	P->childs[_name] = C;
	C->parent = P;
	
	int count = C->cnt;

	while(C->parent != nullptr){
		C->parent->cnt += count;
		C = C->parent;
	}


}
extern void cmd_rm(char path[PATH_MAXLEN + 1]){


	Node * P = root;
	Node * C;
	char* result;
	result = strtok(path, "/");	
	while(result != NULL){
		char parsing[7];
		strcpy(parsing, result);
		if (parsing[0] =='\0')
			break;
		string str_buf(parsing);
		P = P->childs[str_buf];
		result = strtok(NULL,"/");
	}



	C = P;
	int count = C->cnt;
	while(C->parent != nullptr){
		C->parent->cnt -= count;
		C = C->parent;
	}

	P->parent->childs.erase(P->name);
	P->parent = nullptr;


}
extern void cmd_cp(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]){
	

	Node * P = root;
	Node * C;
	char* result;
	result = strtok(srcPath, "/");	
	while(result != NULL){
		char parsing[7];
		strcpy(parsing, result);
		if (parsing[0] =='\0')
			break;
		string str_buf(parsing);
		P = P->childs[str_buf];
		result = strtok(NULL,"/");
	}
	
	C = P->copy();

	P = root;
	result = nullptr;
	result = strtok(dstPath, "/");	
	while(result != NULL){
		char parsing[7];
		strcpy(parsing, result);
		if (parsing[0] =='\0')
			break;
		string str_buf(parsing);
		P = P->childs[str_buf];
		result = strtok(NULL,"/");
	}
	
	
	P->childs[C->name] = C;
	C->parent = P;

	int count = C->cnt;
	while(C->parent != nullptr){
		C->parent->cnt += count;
		C = C->parent;
	}

	return;

}
extern void cmd_mv(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]){
	
	Node * C = root;
	Node * P;
	char* result;
	result = strtok(srcPath, "/");	
	while(result != NULL){
		char parsing[7];
		strcpy(parsing, result);
		if (parsing[0] =='\0')
			break;
		string str_buf(parsing);
		C = C->childs[str_buf];
		result = strtok(NULL,"/");
	}
	Node * T;
	T = C;
	int count = T->cnt;

	while(T->parent != nullptr){
		T->parent->cnt -= count;
		T = T->parent;
	}

	C->parent->childs.erase(C->name);
	C->parent = nullptr;


	P = root;
	result = nullptr;
	result = strtok(dstPath, "/");	
	while(result != NULL){
		char parsing[7];
		strcpy(parsing, result);
		if (parsing[0] =='\0')
			break;
		string str_buf(parsing);
		P = P->childs[str_buf];
		result = strtok(NULL,"/");
	}
	P->childs[C->name] = C;

	C->parent = P;
	count = C->cnt;
	while(C->parent != nullptr){
		C->parent->cnt += count;
		C = C->parent;
	}
	return;

}
extern int cmd_find(char path[PATH_MAXLEN + 1]){
	Node * C = root;
	Node * P;
	char* result;
	result = strtok(path, "/");	
	while(result != NULL){
		char parsing[7];
		strcpy(parsing, result);
		if (parsing[0] =='\0')
			break;
		string str_buf(parsing);
		C = C->childs[str_buf];
		result = strtok(NULL,"/");
	}
	return C->cnt-1;
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
	}
	

	return isAccepted;
}

int main(void) {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int test, T;
	int n, m;

	

	// freopen("sample_input.txt", "r", stdin);

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
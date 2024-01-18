#ifndef _CRT_SECURE_NO_WARNINGS 
#define _CRT_SECURE_NO_WARNINGS 
#endif



#define CMD_MKDIR 1
#define CMD_RM 2
#define CMD_CP 3
#define CMD_MV 4
#define CMD_FIND 5

#define NAME_MAXLEN 6
#define PATH_MAXLEN 1999


#include <array>

using namespace std;
class Node{
    public:
        int sub;
        long long name;
        array<int, 30> ch;
        int ch_cnt;
        int par;
        Node(){}
        Node(long long _name){
            name = _name;
            sub = 0;
        }
};

Node nodes[50050];
int ptr = 0;
int new_node(long long name){
    Node &ret = nodes[ptr++];
    ret.name = name;
    ret.sub = 0;
	ret.ch_cnt = 0;
	ret.par = -1;
    return ptr - 1;
        
}
int deep_copy(int target) {
	int d = new_node(nodes[target].name);
	nodes[d].sub = nodes[target].sub;
	nodes[d].par = -1;
	nodes[d].ch_cnt = 0;
	for (int i = 0; i < nodes[target].ch_cnt; ++i) {
		int x = deep_copy(nodes[target].ch[i]);
		nodes[d].ch[nodes[d].ch_cnt++] = x;
		nodes[x].par = d;
	}
	return d;
}
int root;
void init(int n) {
	ptr = 0;
	root = new_node(0);
}
int path_to_dir(char path[PATH_MAXLEN + 1]) {
	int ret = root;
	for (int i = 1; path[i]; ) {
		int j = i;
		long long my_name = 0;
		while (path[j] != '/') {
			my_name <<= 5;
			my_name += (path[j] - 'a' + 1);
			++j;
		}
		int lf = 0, rg = (int)nodes[ret].ch_cnt - 1;
		while (lf < rg) {
			int mid = (lf + rg) / 2;
			if (nodes[nodes[ret].ch[mid]].name >= my_name) rg = mid;
			else lf = mid + 1;
		}
		ret = nodes[ret].ch[rg];
		i = j + 1;
	}
	return ret;
}
inline void insertion(array< int, 30> &ch, int &ch_cnt, int node) {
	ch[ch_cnt++] = node;
	for (int i = (int)ch_cnt - 2; i >= 0; --i) {
		if (nodes[ch[i]].name > nodes[ch[i + 1]].name) swap(ch[i], ch[i + 1]);
		else break;
	}
}
void add_up(int node, int delta) {
	while (node != -1) {
		nodes[node].sub += delta;
		node = nodes[node].par;
	}
}
void cmd_mkdir(char path[PATH_MAXLEN + 1], char name[NAME_MAXLEN + 1]) {
	int d = path_to_dir(path);
	add_up(d, 1);
	long long my_name = 0;
	for (int i = 0; name[i]; ++i) {
		my_name <<= 5;
		my_name += (name[i] - 'a' + 1);
	}
	int nw = new_node(my_name);
	insertion(nodes[d].ch, nodes[d].ch_cnt, nw);
	nodes[nw].par = d;
}
void cmd_rm(char path[PATH_MAXLEN + 1]) {
	int node = path_to_dir(path);
	int d = nodes[node].par;
	int lf = 0, rg = nodes[d].ch_cnt - 1;
	while (lf < rg) {
		int mid = (lf + rg) / 2;
		if (nodes[nodes[d].ch[mid]].name >= nodes[node].name) rg = mid;
		else lf = mid + 1;
	}
	for (int i = rg + 1; i < nodes[d].ch_cnt; ++i) {
		nodes[d].ch[i - 1] = nodes[d].ch[i];
	}
	--nodes[d].ch_cnt;
	add_up(d, -(nodes[node].sub + 1));
}

void cmd_rm(int node) {
	int d = nodes[node].par;
	int lf = 0, rg = nodes[d].ch_cnt - 1;
	while (lf < rg) {
		int mid = (lf + rg) / 2;
		if (nodes[nodes[d].ch[mid]].name >= nodes[node].name) rg = mid;
		else lf = mid + 1;
	}
	for (int i = rg + 1; i < nodes[d].ch_cnt; ++i) {
		nodes[d].ch[i - 1] = nodes[d].ch[i];
	}
	--nodes[d].ch_cnt;
	add_up(d, -(nodes[node].sub + 1));
}

void cmd_cp(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
	int src = path_to_dir(srcPath);
	int dst = path_to_dir(dstPath);
	add_up(dst, nodes[src].sub + 1);
	int nw = deep_copy(src);
	insertion(nodes[dst].ch, nodes[dst].ch_cnt, nw);
	nodes[nw].par = dst;
}

void cmd_mv(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
	int src = path_to_dir(srcPath);
	int dst = path_to_dir(dstPath);
	add_up(dst, nodes[src].sub + 1);
	cmd_rm(src);
	insertion(nodes[dst].ch, nodes[dst].ch_cnt, src);
	nodes[src].par = dst;
}

int cmd_find(char path[PATH_MAXLEN + 1]) {
	return nodes[path_to_dir(path)].sub;
}
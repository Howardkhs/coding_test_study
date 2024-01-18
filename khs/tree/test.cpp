#define _CRT_SECURE_NO_WARNINGS 
#endif

#include< stdio.h >

#define CMD_MKDIR 1
#define CMD_RM 2
#define CMD_CP 3
#define CMD_MV 4
#define CMD_FIND 5

#define NAME_MAXLEN 6
#define PATH_MAXLEN 1999

extern void init(int n);
extern void cmd_mkdir(char path[PATH_MAXLEN + 1], char name[NAME_MAXLEN + 1]);
extern void cmd_rm(char path[PATH_MAXLEN + 1]);
extern void cmd_cp(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]);
extern void cmd_mv(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]);
extern int cmd_find(char path[PATH_MAXLEN + 1]);

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
#define NAME_MAXLEN 6
#define PATH_MAXLEN 1999

#include < bits/stdc++.h >
using namespace std;
struct directory {
	int sub;
	long long name;
	array< int, 30> ch;
	int ch_cnt;
	int par;
	directory() { }
	directory(long long name) {
		this->name = name;
		sub = 0;
	}
};

directory pool[50'050];
int ptr = 0;
int new_node(long long name) {
	directory &ret = pool[ptr++];
	ret.name = name;
	ret.sub = 0;
	ret.ch_cnt = 0;
	ret.par = -1;
	return ptr - 1;
}
int deep_copy(int target) {
	int d = new_node(pool[target].name);
	pool[d].sub = pool[target].sub;
	pool[d].par = -1;
	pool[d].ch_cnt = 0;
	for (int i = 0; i < pool[target].ch_cnt; ++i) {
		int x = deep_copy(pool[target].ch[i]);
		pool[d].ch[pool[d].ch_cnt++] = x;
		pool[x].par = d;
	}
	return d;
}
int root;
void init(int n) {
	assert(n < 50'050);
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
		int lf = 0, rg = (int)pool[ret].ch_cnt - 1;
		while (lf < rg) {
			int mid = (lf + rg) / 2;
			if (pool[pool[ret].ch[mid]].name >= my_name) rg = mid;
			else lf = mid + 1;
		}
		ret = pool[ret].ch[rg];
		i = j + 1;
	}
	return ret;
}
inline void insertion(array< int, 30> &ch, int &ch_cnt, int node) {
	ch[ch_cnt++] = node;
	for (int i = (int)ch_cnt - 2; i >= 0; --i) {
		if (pool[ch[i]].name > pool[ch[i + 1]].name) swap(ch[i], ch[i + 1]);
		else break;
	}
}
void add_up(int node, int delta) {
	while (node != -1) {
		pool[node].sub += delta;
		node = pool[node].par;
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
	insertion(pool[d].ch, pool[d].ch_cnt, nw);
	pool[nw].par = d;
}
void cmd_rm(char path[PATH_MAXLEN + 1]) {
	int node = path_to_dir(path);
	int d = pool[node].par;
	int lf = 0, rg = pool[d].ch_cnt - 1;
	while (lf < rg) {
		int mid = (lf + rg) / 2;
		if (pool[pool[d].ch[mid]].name >= pool[node].name) rg = mid;
		else lf = mid + 1;
	}
	for (int i = rg + 1; i < pool[d].ch_cnt; ++i) {
		pool[d].ch[i - 1] = pool[d].ch[i];
	}
	--pool[d].ch_cnt;
	add_up(d, -(pool[node].sub + 1));
}

void cmd_rm(int node) {
	int d = pool[node].par;
	int lf = 0, rg = pool[d].ch_cnt - 1;
	while (lf < rg) {
		int mid = (lf + rg) / 2;
		if (pool[pool[d].ch[mid]].name >= pool[node].name) rg = mid;
		else lf = mid + 1;
	}
	for (int i = rg + 1; i < pool[d].ch_cnt; ++i) {
		pool[d].ch[i - 1] = pool[d].ch[i];
	}
	--pool[d].ch_cnt;
	add_up(d, -(pool[node].sub + 1));
}

void cmd_cp(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
	int src = path_to_dir(srcPath);
	int dst = path_to_dir(dstPath);
	add_up(dst, pool[src].sub + 1);
	int nw = deep_copy(src);
	insertion(pool[dst].ch, pool[dst].ch_cnt, nw);
	pool[nw].par = dst;
}

void cmd_mv(char srcPath[PATH_MAXLEN + 1], char dstPath[PATH_MAXLEN + 1]) {
	int src = path_to_dir(srcPath);
	int dst = path_to_dir(dstPath);
	add_up(dst, pool[src].sub + 1);
	cmd_rm(src);
	insertion(pool[dst].ch, pool[dst].ch_cnt, src);
	pool[src].par = dst;
}

int cmd_find(char path[PATH_MAXLEN + 1]) {
	return pool[path_to_dir(path)].sub;
}
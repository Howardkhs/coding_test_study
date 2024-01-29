#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define CMD_INIT 100
#define CMD_DESTROY 200
#define CMD_UPDATE 300
#define CMD_UPDATE_TYPE 400
#define CMD_CALC 500


/// @brief /////////////////////////////////////////////////////////

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

class Node;

vector<Node*> nodevec;
int ptr = 0;
int rood_id = 0;
vector<int> Groad_type;
vector<int> Groad_time;
Node* node_id[100002];
double DIV = 256;

vector<vector<Node *>> nodetype(1001);

class Node{
    public:
        int start; // 도로 범위
        int end;
        int time;
        int type;
        int node_num;

        Node * lft_node = nullptr;
        Node * rgt_node = nullptr;
        Node * parent = nullptr;

        Node(){}
        Node(int _start, int _end){
            start = _start;
            end = _end;
            if (start == end)
                node_num = start;
            time = 0;
            type = 0;
   
        }

        int find(int _start, int _end){
            int ret = 0;
            if(start == _start && end == _end){
                return time;
            }
            // case 1
            int mid = start + (end - start) / 2;

            if (_start <= mid && mid < _end){
                ret += lft_node->find(_start, mid);
                ret += rgt_node->find(mid+1, _end);
                return ret;
            }
            else if(_end <= mid){
                ret += lft_node->find(_start, _end);
                return ret;
            }
            else if(mid < _start){
                ret += rgt_node->find(_start, _end);

                return ret;
            }

        }

        
};

Node* init(int start, int end, int parent_id){
    int node_num = ptr++;
    Node *A = new Node(start, end);
    A->node_num = node_num;
    nodevec.push_back(A);
    Node * p_node = nullptr;

    if (start == end){
        A->time = Groad_time[start];
        A->type = Groad_type[start];
        nodetype[A->type].push_back(A);
        p_node = nodevec[parent_id];
        node_id[start] = A;

        if (p_node != A)
            A->parent = p_node;
        // cout << p_node->node_num << endl;
        if (A->parent) // 부모 시간 올리기
            A->parent->time += A->time;
        
        return A;
    }

    if (node_num != 0) // root노드가 아니라면
        p_node = nodevec[parent_id];

    A->lft_node = init(start, start + (end - start) / 2, node_num);
    A->rgt_node = init(start + (end - start) / 2 + 1, end, node_num);

    if (p_node)
        A->parent = p_node;
    if (A->parent) // 부모 시간 올리기
        A->parent->time += A->time;
    return A;

}




void init(int N, int M, int mType[], int mTime[]) // 도로갯수 N-1
{
    nodevec.clear();
    Groad_time.clear();
    Groad_type.clear();
    for (int i = 0; i < M; i++){
        nodetype[i].clear();
    }
    ptr = 0;
    
    for (int i = 0; i < N; i++){
        Groad_type.push_back(mType[i]);
        Groad_time.push_back(mTime[i]);
    }

    init(0, N-2, 0);

}

void destroy()
{

}

void update(int mID, int mNewTime)
{
    Node* node = node_id[mID];

    int _time = node->time;
    while (node->parent){
        node->parent->time -= _time;
        node = node->parent;
    }

    // 새로 한거 초기화
    node = node_id[mID];
    node->time = mNewTime;
    _time = node->time;
    while (node->parent){
        node->parent->time += _time;
        node = node->parent;
    }


}

int update_float(double ratio, Node* node){
    int _time = node->time;
    Node* tnode = node;
    while (node->parent){
        node->parent->time -= _time;
        node = node->parent;
    }

    // 새로 한거 초기화
    node = tnode;
    node->time = floor(ratio * _time);
    _time = node->time;
    while (node->parent){
        node->parent->time += _time;
        node = node->parent;
    }
    return _time;
}


int updateByType(int mTypeID, int mRatio256)
{
    double ratio = mRatio256 / DIV;
    int answer = 0;
    for (auto p = nodetype[mTypeID].begin(); p != nodetype[mTypeID].end(); p++){
        answer += update_float(ratio, *p);
    }
    // cout << answer << endl;
	return answer;
}

int calculate(int mA, int mB)
{   
    if (mB < mA){
        int temp = mB;
        mB = mA;
        mA = temp;
    }
    Node* rnode = nodevec[0];
    int answer = rnode->find(mA, mB-1);
    // cout << answer << endl;
	return answer;
}

void print_node(int idx){
    Node *rnode = nodevec[idx];
    cout << rnode->start << " " << rnode->end << " " << rnode->time <<endl;
    
    if (rnode->lft_node)
        print_node(rnode->lft_node->node_num);
    if (rnode->rgt_node)
        print_node(rnode->rgt_node->node_num);
}

#define MAX_N 100000

static int mType[MAX_N];
static int mTime[MAX_N];

static int run()
{
	int C;
	int isOK = 0;
	int cmd, ret, chk;

	int N, M;
	int mID, mTypeID, mNewTime, mRatio;
	int mA, mB;

	scanf("%d", &C);

	for (int c = 0; c < C; ++c)
	{
		scanf("%d", &cmd);
		switch (cmd)
		{
		case CMD_INIT:
			scanf("%d %d ", &N, &M);
			for (int i = 0; i < N - 1; i++) scanf("%d", &mType[i]);				
			for (int i = 0; i < N - 1; i++) scanf("%d", &mTime[i]);
			init(N, M, mType, mTime);
			isOK = 1;
			break;

		case CMD_UPDATE:
			scanf("%d %d", &mID, &mNewTime);
			update(mID, mNewTime);			
			break;

		case CMD_UPDATE_TYPE:
			scanf("%d %d", &mTypeID, &mRatio);
			ret = updateByType(mTypeID, mRatio);
			scanf("%d", &chk);
			if (ret != chk)
				isOK = 0;
			break;

		case CMD_CALC:
			scanf("%d %d", &mA, &mB);
			ret = calculate(mA, mB);
			scanf("%d", &chk);
			if (ret != chk)
				isOK = 0;
			break;

		default:
			isOK = 0;
			break;
		}
        // print_node(0);
	}
	destroy();
	return isOK;
}

int main()
{
	setbuf(stdout, NULL);
	freopen("sample_input.txt", "r", stdin);

	int T, MARK;
	scanf("%d %d", &T, &MARK);

	for (int tc = 1; tc <= T; tc++)
	{
		if (run()) printf("#%d %d\n", tc, MARK);
		else printf("#%d %d\n", tc, 0);
	}
	return 0;
}
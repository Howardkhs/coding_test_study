
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define CMD_INIT 100
#define CMD_UPDATE_SCORE 200
#define CMD_UNION_TEAM 300
#define CMD_GET_SCORE 400
/// @brief ////////////////////////////////////////////////////////////
/// @param N 

#include <iostream>
#include <vector>
#include <memory.h>

using namespace std;

int ret = 0;
int ptr = 0;
class Node;

vector<Node*> temp;

class Node{
    public:
        int node_num;
        int mans; // 이 집합에 속한 사람수
        // int score;
        int get_score;

        Node* parent = nullptr;
        // vector<Node*> child;

        Node(int _node_num){
            node_num = _node_num;
            mans = 1;
            // score = 0;
            get_score = 0;
        }

        Node* find_parent(){
            temp.push_back(this);
            if (parent)
                return this->parent->find_parent();
            return this;
        }
        void find_ret(){
            ret += get_score;
            if (parent)
                this->parent->find_ret();
        }
};

Node* A;
Node* B;

Node* P_A;
Node* P_B;

vector<Node> nodevec;
vector<Node*> pvec;
int visited[100001];

void init(int N)
{
    nodevec.clear();
    for (int i = 0; i <= N; i++){
        nodevec.emplace_back(i);
        pvec.emplace_back();
    }
    memset(visited, 0, sizeof(int) * 100001);
}

void updateScore(int mWinnerID, int mLoserID, int mScore)
{
    // cout << "update score " << endl;
    A = &nodevec[mWinnerID];
    B = &nodevec[mLoserID];

    if (visited[A->node_num] == 1){
        P_A = pvec[A->node_num];
    }
    else 
        P_A = A;
    
    temp.clear();
    P_A = P_A->find_parent();
    for (int i = 0; i < temp.size(); i++){
        Node* p = temp[i];
        pvec[p->node_num] = P_A;
        visited[p->node_num] = 1;
    }

    if (visited[B->node_num] == 1){
        P_B = pvec[B->node_num];
    }
    else 
        P_B = B;
    temp.clear();
    P_B = P_B->find_parent();
    for (int i = 0; i < temp.size(); i++){
        Node* p = temp[i];
        pvec[p->node_num] = P_B;
        visited[p->node_num] = 1;
    }

    P_A->get_score += mScore;
    P_B->get_score -= mScore;
}

void unionTeam(int mPlayerA, int mPlayerB)
{
    
    A = &nodevec[mPlayerA];
    B = &nodevec[mPlayerB];

    if (visited[A->node_num] == 1){
        P_A = pvec[A->node_num];
    }
    else 
        P_A = A;
    temp.clear();
    P_A = A->find_parent();
    for (int i = 0; i < temp.size(); i++){
        Node* p = temp[i];
        pvec[p->node_num] = P_A;
        visited[p->node_num] = 1;
    }

    if (visited[B->node_num] == 1){
        P_B = pvec[B->node_num];
    }
    else 
        P_B = B;
    temp.clear();
    P_B = P_B->find_parent();
    for (int i = 0; i < temp.size(); i++){
        Node* p = temp[i];
        pvec[p->node_num] = P_B;
        visited[p->node_num] = 1;
    }
    
    if (P_A->mans >= P_B->mans){
        // 연결
        P_B->parent = P_A;
        P_B->get_score -= P_A->get_score;
        visited[P_B->node_num] = 1;
        pvec[P_B->node_num] = P_A;       
        visited[P_A->node_num] = 1;
        pvec[P_A->node_num] = P_A;   
    }
 
    else{
        P_A->parent = P_B;
        // P_B->child.push_back(P_A);
        P_A->get_score -= P_B->get_score;
        visited[P_A->node_num] = 1;
        pvec[P_A->node_num] = P_B;       
        visited[P_B->node_num] = 1;
        pvec[P_B->node_num] = P_B; 
        
    }
    // P_A = A->find_parent();
    // P_B = B->find_parent();
    // cout << P_A->node_num << " " << P_B->node_num << endl;    
    // cout << P_A->score  << " " << P_A->get_score << endl;
}

int getScore(int mID)
{   
    // cout << "get score " << mID << endl;
    ret = 0;
    A = &nodevec[mID];
    A->find_ret();

    // cout << ret << endl;
	return ret;
}

void print_node(){
    for(int i = 1; i < nodevec.size(); i++){
        // cout << nodevec[i].score << " ";
        cout << endl;
    }
}

static bool run()
{
	int queryCnt, cmd;
	int ans, res;
	bool okay = false;

	scanf("%d", &queryCnt);
	for (int i = 0; i < queryCnt; i++)
	{
		scanf("%d", &cmd);
		switch (cmd)
		{
		case CMD_INIT:
			int N;
			scanf("%d", &N);
			init(N);
			okay = true;
			break;
		case CMD_UPDATE_SCORE:
			int mWinnerID, mLoserID, mScore;
			scanf("%d%d%d", &mWinnerID, &mLoserID, &mScore);
			updateScore(mWinnerID, mLoserID, mScore);
			break;
		case CMD_UNION_TEAM:
			int mPlayerA, mPlayerB;
			scanf("%d%d", &mPlayerA, &mPlayerB);
			unionTeam(mPlayerA, mPlayerB);
			break;
		case CMD_GET_SCORE:
			int mID;
			scanf("%d", &mID);
			res = getScore(mID);
			scanf("%d", &ans);
			if (ans != res)
			{
				okay = false;
			}
			break;
		}
        // print_node();
	}

	return okay;
}

int main()
{
	setbuf(stdout, NULL);
	freopen("sample_input.txt", "r", stdin);

	int T, MARK;
	scanf("%d%d", &T, &MARK);

	for (int tc = 1; tc <= T; tc++)
	{
		int score = run() ? MARK : 0;
		printf("#%d %d\n", tc, score);
	}

	return 0;
}
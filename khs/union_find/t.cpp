#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define CMD_INIT 100
#define CMD_UPDATE_SCORE 200
#define CMD_UNION_TEAM 300
#define CMD_GET_SCORE 400


#include <vector>

using namespace std;

int ret = 0;
class Node{
    public:
        int node_num;
        int mans = 1; // 이 집합에 속한 사람수
        int get_score = 0;

        Node* parent = nullptr;

        Node(int _node_num){
            node_num = _node_num;
        
        }

        Node* find_parent(){
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

void init(int N)
{
    nodevec.clear();
    for (int i = 0; i <= N; i++){
        nodevec.emplace_back(i);
    }
}

void updateScore(int mWinnerID, int mLoserID, int mScore)
{

    A = &nodevec[mWinnerID];
    B = &nodevec[mLoserID];

    P_A = A->find_parent();
    P_B = B->find_parent();

    P_A->get_score += mScore;
    P_B->get_score -= mScore;
}

void unionTeam(int mPlayerA, int mPlayerB)
{
    
    A = &nodevec[mPlayerA];
    B = &nodevec[mPlayerB];

    P_A = A->find_parent();
    P_B = B->find_parent();
    
    if (P_A->mans >= P_B->mans){
        // 연결
        P_B->parent = P_A;
        P_B->get_score -= P_A->get_score;
        P_A->mans += P_B->mans;
        
    }
 
    else{
        P_A->parent = P_B;
        P_A->get_score -= P_B->get_score;
        P_B->mans += P_A->mans;
    }
   
}

int getScore(int mID)
{   

    ret = 0;
    A = &nodevec[mID];
    A->find_ret();

	return ret;
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
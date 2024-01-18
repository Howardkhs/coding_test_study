#include <iostream>
#include <array>
#include <set>


using namespace std;

class Node{

    public:
        int num;
        Node* parent = nullptr;
        int cnt = 1;
        
        Node() {}
        Node(int _num){
            num = _num;
        }

        Node* find_parent(){
            if (parent == nullptr){
                return this;
            }
            return parent->find_parent();
        }

};

Node* hometown[101];


int main(int argc, char** argv)
{   
   
	int test_case;
	int T;
    int N, M;
    int a, b;
    Node* A;
    Node* B;
	// freopen("input.txt", "r", stdin);
	cin>>T;

	for(test_case = 1; test_case <= T; ++test_case)
	{   
        array<int, 101> find = {0,};
        set<int> group;
        cin >> N >> M;

        for (int i = 1; i <= N; i++){
            A = new Node(i);
            hometown[i] = A;
        }


        while(M--){
            cin >> a >> b;
            A = hometown[a];
            B = hometown[b];
            Node * P_A;
            Node * P_B;
            P_A = A->find_parent();
            P_B = B->find_parent();
            
            if (P_A == P_B){
                continue;
            }

            if (P_A->cnt > P_B->cnt){
                P_B->parent = P_A;
                P_A->cnt += P_B->cnt;
            }
            else{
                P_A->parent = P_B;
                P_B->cnt += P_A->cnt;
            }
        
        }
        for (int i = 1; i <= N; i++){
            Node* C = hometown[i];
            Node* P = C->find_parent();
            group.insert(P->num);
        }
        cout << "#" << test_case << " " <<group.size() << endl;
	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
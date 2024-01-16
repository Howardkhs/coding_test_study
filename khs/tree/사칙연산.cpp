#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <cctype>

using namespace std;



class Node{

    public:
        string alpha;
        int node_num;
        bool is_num = false;
        bool is_cal = false;
        Node* lft_child = nullptr;
        Node* rgt_child = nullptr;

        Node(string _alpha, int _node_num){
            alpha = _alpha;
            node_num = _node_num;
        }

        int check(){
            int lft = 0, rgt = 0;
            if (lft_child == nullptr && rgt_child == nullptr)
                return is_num; // 끝까지 내려가서 숫자인지 리턴 중앙이 사칙이고 옆이 숫자면 성공    
            if (lft_child)
                lft = lft_child->check();
            if (rgt_child)
                rgt = rgt_child->check();
            if (lft && rgt && is_cal){
                is_num = true;
                return is_num;
            }
            return 0;
            
        }
};

unordered_map<int, Node*> child_dict;

int main(){
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
    // cout.tie(NULL);
    int N, lft, rgt, num;
    string alpha;
    string order;
    
    int test_case;
	int T = 10;

	freopen("input.txt", "r", stdin);
	for(test_case = 1; test_case <= T; ++test_case)
	{
        cin >> N;
        getchar();

        getline(cin, order, '\n');

        istringstream iss(order);
        string str_buf;

        N--;
        int idx = 0;  
        lft = 0;
        rgt = 0;
                
        while(getline(iss, str_buf, ' ')){
            if (idx == 0)
                num = stoi(str_buf);
            if (idx == 1)
                alpha = str_buf;
            if (idx == 2)
                lft = stoi(str_buf);
            if (idx == 3)
                rgt = stoi(str_buf);
            idx++;            

        }

        Node A(alpha, num);
        child_dict[1] = &A;
        if (isdigit(alpha[0])){
            A.is_num = true;
        }
        else{
            A.is_cal = true;
        }

        if (lft){
            Node* B = new Node("T", lft);
            child_dict[lft] = B;
            A.lft_child = B;
        }
        if (rgt){
            Node* B = new Node("T", rgt);
            child_dict[rgt] = B;
            A.rgt_child = B;
        }

        while(N--){
            getline(cin, order, '\n');
     
            istringstream iss(order);
            string str_buf;

            idx = 0;  
            lft = 0;
            rgt = 0;
                    
            while(getline(iss, str_buf, ' ')){
   
                if (idx == 0)
                    num = stoi(str_buf);
                if (idx == 1)
                    alpha = str_buf;
                if (idx == 2)
                    lft = stoi(str_buf);
                if (idx == 3)
                    rgt = stoi(str_buf);
                idx++;            

            }

            Node *A;
            if (child_dict[num]){
                A = child_dict[num];
                A->alpha = alpha;
            }
            else{
                A = new Node(alpha, num);
                child_dict[num] = A;
            }

            if (isdigit(alpha[0])){
                A->is_num = true;
            }
            else{
                A->is_cal = true;
            }

            if (lft){
                Node* B = new Node("T", lft);
                child_dict[lft] = B;
                A->lft_child = B;
            }
            if (rgt){
                Node* B = new Node("T", rgt);
                child_dict[rgt] = B;
                A->rgt_child = B;
            }

        }

        Node* top = child_dict[1];
        top->check();
        if (top->is_num && top->is_cal)
            cout << "#" << test_case << " " << top->is_num << " ";
        else
            cout << "#" << test_case << " " << 0 << " ";
        cout << '\n';

	}

}
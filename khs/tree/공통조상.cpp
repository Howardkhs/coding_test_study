#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

using namespace std;

class Node{

    public:

        int num;
        int cnt = 1;
        Node* parent = nullptr;

        Node(int _num){
            num = _num;
        }
};



int main(){


    int test_case;
	int T = 10;
    
    int V, E, a, b, p, c;
    Node* A;
    Node* B;
    freopen("input.txt", "r", stdin);
    cin >> T;
    for(test_case = 1; test_case <= T; ++test_case)
	{   
        unordered_map<int, Node*> node_dict;
        cin >> V >> E >> a >> b;
        while(E--){
            cin >> p >> c;
            if (node_dict[p]){
                A = node_dict[p];
            }
            else{
                A = new Node(p);
                node_dict[p] = A;
            }
            if (node_dict[c]){
                B = node_dict[c];
            }
            else{
                B = new Node(c);
                node_dict[c] = B;
            }
            B->parent = A;
            Node* C = A;
            while(C != nullptr){
                C->cnt += B->cnt;
                C = C->parent;
            }
        }

        A = node_dict[a];
        B = node_dict[b];
        vector<int> A_P;
        vector<int> B_P;

 
        while(A != nullptr){
            A_P.push_back(A->num);
            A = A->parent;
        }
        while(B != nullptr){
            B_P.push_back(B->num);
            B = B->parent;
        }

        for (int i = 0; i < distance(A_P.begin(), A_P.end()); i++){
            auto p = find(B_P.begin(), B_P.end(), A_P[i]);
            if (p == B_P.end())
                continue;
            else{
                cout << "#" << test_case << " " << *p << " " << node_dict[*p]->cnt <<"\n";
                break;
            }
        }
    }
}
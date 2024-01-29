#include<iostream>
#include <vector>

using namespace std;

class Node;
vector<Node*> nodevec;
int ptr = 0;
int root_id = 0;
vector<long long> num;
Node* node_id[100002];

class Node{
    public:
        int start;
        int end;
        long long n = 0;
        int node_num;

        Node * lft_node = nullptr;
        Node * rgt_node = nullptr;
        Node * parent = nullptr;

        Node(){
            n = 0;
        
        }
        Node(int _start, int _end){
            start = _start;
            end = _end;
            if (start == end)
                node_num = start;
            n = 0;
   
        }

        long long find(int _start, int _end){
            long long ret = 0;
            if(start == _start && end == _end){
                return n;
            }
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
        if (start % 2 == 0)
            A->n = num[start];
        else
            A->n = -num[start];
        p_node = nodevec[parent_id];
        node_id[start] = A;
        if (p_node != A)
            A->parent = p_node;
        if (A->parent){
            A->parent->n += A->n;
        }
        return A;
    }
    if (node_num != 0) // root노드가 아니라면
        p_node = nodevec[parent_id];
    A->lft_node = init(start, start + (end - start) / 2, node_num);
    A->rgt_node = init(start + (end - start) / 2 + 1, end, node_num);
    if (p_node)
        A->parent = p_node;
    if (A->parent){
       A->parent->n += A->n;
    }
    return A;
}

void update(int id, long long x)
{
    Node* node = node_id[id];
    long long _n = node->n;
    while (node->parent){
        node->parent->n -= _n;
        node = node->parent;
    }

    node = node_id[id];
    if (id % 2 == 0)
        node->n = x;
    else
        node->n = -x;
    _n = node->n;
    while (node->parent){
        node->parent->n += _n;
        node = node->parent;
    }

}

void print_node(int idx){
    Node *rnode = nodevec[idx];
    cout << rnode->start << " " << rnode->end << " " << rnode->n <<endl;
    
    if (rnode->lft_node)
        print_node(rnode->lft_node->node_num);
    if (rnode->rgt_node)
        print_node(rnode->rgt_node->node_num);
}

int main(int argc, char** argv)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
	int test_case;
	long long T, n, q,a,b,c;
	
	//freopen("input.txt", "r", stdin);
	cin>>T;
	
	for(test_case = 1; test_case <= T; ++test_case)
	{   
        ptr = 0;
        nodevec.clear();
        num.clear();
        
        cin >> n >> q;
        for (int i = 0; i < n; i++){
            cin >> a;
            num.push_back(a);
        }
        init(0, n-1, 0);
        Node* rnode = nodevec[0];
        
        // print_node(0);
        cout << "#" << test_case << " ";
        while(q--){
            cin >> a >> b >> c;
            switch (a)
            {
                case 0:
                    update(b, c);
                    break;
                case 1:
                    if (b % 2 == 0)
                        cout << rnode->find(b, c-1) << " ";
                    else
                        cout << -rnode->find(b, c-1) << " ";
                    break;
                default:
                    break;
                
            }
            // print_node(0);
        }
        cout << "\n";
	

	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
#include<iostream>
#include <vector>

using namespace std;

class Node;
vector<Node*> nodevec;
int ptr = 0;
int root_id = 0;
vector<int> num;
Node* node_id[100002];

class Node{
    public:
        int start;
        int end;
        int max_num;
        int min_num;
        int node_num;

        Node * lft_node = nullptr;
        Node * rgt_node = nullptr;
        Node * parent = nullptr;

        Node(){
            max_num = 0;
            min_num = 10e9;
        }
        Node(int _start, int _end){
            start = _start;
            end = _end;
            if (start == end)
                node_num = start;
            max_num = 0;
            min_num = 10e9;
        }

        int find_max(int _start, int _end){
            int ret = 0;
            if(start == _start && end == _end){
                return max_num;
            }
            int mid = start + (end - start) / 2;
            if(_start <= mid && mid < _end){
                ret = max(ret, lft_node->find_max(_start, mid));
                ret = max(ret, rgt_node->find_max(mid+1, _end));
                return ret;
            }
            else if(_end <= mid){
                ret = max(ret, lft_node->find_max(_start, _end));
                return ret;
            }
            else if(mid < _start){
                ret = max(ret, rgt_node->find_max(_start, _end));
                return ret;
            }
        }

        int find_min(int _start, int _end){
            int ret = 10e9;
            // cout << _start << " " << _end << endl;
            if(start == _start && end == _end){
                return min_num;
            }
            int mid = start + (end - start) / 2;
            if(_start <= mid && mid < _end){
                ret = min(ret, lft_node->find_min(_start, mid));
                ret = min(ret, rgt_node->find_min(mid+1, _end));
                return ret;
            }
            else if(_end <= mid){
                ret = min(ret, lft_node->find_min(_start, _end));
                return ret;
            }
            else if(mid < _start){
                ret = min(ret, rgt_node->find_min(_start, _end));
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
        A->max_num = num[start];
        A->min_num = num[start];
        p_node = nodevec[parent_id];
        node_id[start] = A;
        if (p_node != A)
            A->parent = p_node;
        if (A->parent){
            A->parent->max_num = max(A->parent->max_num, A->max_num);
            A->parent->min_num = min(A->parent->min_num, A->min_num);
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
        A->parent->max_num = max(A->parent->max_num, A->max_num);
        A->parent->min_num = min(A->parent->min_num, A->min_num);
    }
    return A;
}

void update(int id, int x)
{
    Node* node = node_id[id];
    node->max_num = x;
    node->min_num = x;
    int _max = node->max_num;
    int _min = node->min_num;
    while (node->parent){
        node->parent->max_num = max(node->parent->lft_node->max_num, node->parent->rgt_node->max_num);
        node->parent->min_num = min(node->parent->lft_node->min_num, node->parent->rgt_node->min_num);
        node = node->parent;
    }

}

void print_node(int idx){
    Node *rnode = nodevec[idx];
    cout << rnode->start << " " << rnode->end << " " << rnode->max_num << " " << rnode->min_num <<endl;
    
    if (rnode->lft_node)
        print_node(rnode->lft_node->node_num);
    if (rnode->rgt_node)
        print_node(rnode->rgt_node->node_num);
}

int main(int argc, char** argv)
{
    // ios_base::sync_with_stdio(false);
    // cin.tie(NULL);
    // cout.tie(NULL);
	int test_case;
	int T, n, q,a,b,c;
	
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
        
        print_node(0);
        cout << "#" << test_case << " ";
        while(q--){
            cin >> a >> b >> c;
            switch (a)
            {
                case 0:
                    update(b, c);
                    break;
                case 1:
                    cout << rnode->find_max(b, c-1) - rnode->find_min(b, c-1) << " ";
                    break;
                default:
                    break;
                
            }
            print_node(0);
        }
        cout << "\n";
	

	}
	return 0;//정상종료시 반드시 0을 리턴해야합니다.
}
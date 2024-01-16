#include <iostream>
#include <unordered_map>

using namespace std;

class Node{

    public:
        int num;
        int autor;
        int count = 0;
        int parent_num;
        Node* parent = nullptr;
        Node* lft_child = nullptr;
        Node* rgt_child = nullptr;
        // bool lft_alarm = true;
        // bool rgt_alarm = true;
        bool alram_on = true;
        unordered_map<int, int> autors;

        Node(int _num){
            num = _num;

        }

        Node * find_parent(Node * A){
            return A->parent;
        }

        void set_parent(Node * p, Node * c){
            c->parent = p;
            if (p->lft_child){
                p->rgt_child = c;
            }
            else{
                p->lft_child = c;
            }
            return;
        }

        void set_autor(int _autor){
            autor = _autor;
            autors[_autor] += 1;
            parent->set_autors(_autor);
        }

        
        void set_autors(int _autor){
            count++;
            _autor--;
            autors[_autor] += 1;
            if (_autor > 0 && parent){
                this->parent->set_autors(_autor);
            }
        }
        void set_up(){
            
            Node* A = this;
            for (auto p = autors.begin(); p != autors.end(); p++){
                int up = p->first;
                int cnt = p->second;
                if (cnt == 0)
                    continue;
                if (up == 0)
                    continue;
                A = this;
                while (1){
                    up--;
                    A = find_parent(A);
                    if (A == nullptr)
                        break;

                    A->autors[up] += cnt;
                    A->count += cnt;
            
                    if (up == 0)
                        break;
                }
            }
            
        }

        void set_down(){
            
            Node* A = this;

            for (auto p = autors.begin(); p != autors.end(); p++){
                int up = p->first;
                int cnt = p->second;
                if (up == 0)
                    continue;
                if (cnt == 0)
                    continue;
                A = this;
                while (1){
                    up--;
                    A = find_parent(A);
                    if (A == nullptr)
                        break;

                    A->autors[up] -= cnt;
                    A->count -= cnt;
                    if (up == 0)
                        break;
                }
            }
            
        }
        
        
        void autor_change(int power){
            Node* A = this;
            int _autor = autor;
            A->autors[_autor] -= 1;
            while(1){
                A = A->find_parent(A);
                if (A == nullptr)
                    break;
                _autor--;
                A->count--;
                A->autors[_autor] -= 1;
                if (_autor == 0)
                    break;
            }
            autor = power;
            _autor = autor;
            A = this;
            A->autors[_autor] += 1;
            while(1){
                A = A->find_parent(A);
                if (A == nullptr)
                    break;
                _autor--;
                A->count++;
                A->autors[_autor] += 1;
                if (_autor == 0)
                    break;
                
            }
        }

};

unordered_map<int, Node*> node_dict;

void alarm_on_off(int c){

    Node * A = node_dict[c];
    if ((A->alram_on == false)){
        A->parent = node_dict[A->parent_num];  
        A->alram_on == true;
        A->set_up(); // 위에 추가
        return;
    }
    A->set_down(); // 위에 제거
    A->alram_on = false;
    A->parent = nullptr;
    
}

void autor_up(int c, int power){
    Node* A = node_dict[c];
    A->autor_change(power);

}

void change_node(int c_0, int c_1){

    Node* A = node_dict[c_0];
    Node* B = node_dict[c_1];

    if (A->parent_num == B->parent_num)
        return;

    if ((A->alram_on))
        A->set_down();
    
    if ((B->alram_on))
        B->set_down();

    int temp = A->parent_num;
    A->parent_num = B->parent_num;
    B->parent_num = temp;

    A->parent = node_dict[A->parent_num];
    if (A->alram_on == false)
        A->parent = nullptr;
    B->parent = node_dict[B->parent_num];
    if (B->alram_on == false)
        B->parent = nullptr;
    if (A->alram_on)
        A->set_up();
    if (B->alram_on)
        B->set_up();

}


void print_node(int c){
    
    Node * A = node_dict[c];
    cout << c <<  "번 노드 시작" << endl;
    for (auto p = A->autors.begin(); p != A->autors.end(); p++){
        cout << p->first << "에 " << p->second << "개 " << endl;
    }
}   

int main(){

    ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

    int N, Q, order, p_num, _autor, c, power, c_0, c_1;

    cin >> N >> Q;
    Q--;
    cin >> order;
    Node * A = new Node(0);
    node_dict[0] = A;

    for (int i = 1; i < N + 1; i++){
        A = new Node(i);
        node_dict[i] = A;  
    }

    for (int i = 1; i < N + 1; i++){
        cin >> p_num;
        A = node_dict[i];
        A->set_parent(node_dict[p_num], A);
        A->parent_num = p_num;         
    }

    for (int i = 1; i < N + 1; i++){
        cin >> _autor;
        A = node_dict[i];
        A->set_autor(_autor);

    }
    // print_node(1);
    // print_node(2);
    // print_node(4);
    // print_node(8);

    while(Q--){
        cin >> order;
        if (order == 200){
            cin >> c;
            alarm_on_off(c); // 알람 끄고 키기
        }
        else if(order == 300){
            cin >> c >> power;
            autor_up(c, power);
        }
        else if(order == 400){
            cin >> c_0 >> c_1;
            change_node(c_0, c_1);
            
        }
        else if(order == 500){
            cin >> c;
            cout << node_dict[c]->count << "\n";
        }
        // print_node(1);
        // print_node(2);
        // print_node(4);
        // print_node(8);
            

    }

}   
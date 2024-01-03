#include <iostream>
#include <string>
using namespace std;

class Node{
    public:
        char alpha;
        Node* lft;
        Node* rgt;

        Node(char a = '0'){      
            this->alpha = a;
            lft = nullptr;
            rgt = nullptr;
    }   

    Node* add_right(char a){
        this->rgt = new Node(a);
        this->rgt->lft = this;
        return this->rgt;
    }

    Node* get_left(){
        return this->lft;
    }

    Node* move_left(){
        return this->lft;
    }

    Node* get_right(){
        return this->rgt;
    }

    Node* move_right(){
        return this->rgt;
    }

    char get_alpha(){
        return this->alpha;
    }

        
};


int main(){

    string str;
    string order;
    char a;
    cin >> str;
    int M;
    cin >> M;


    Node* cursor = new Node();
    Node* start = cursor;
    Node* temp;

    for (auto c = str.begin(); c < str.end(); c++){
        cursor = cursor->add_right(*c);
    }


    while(M--){
        
        cin >> order;
        if (order == "P"){
            cin >> a;
        }
        if (order[0] == 'L'){
            if (cursor->get_left() != nullptr)
                cursor = cursor->move_left();
        }

        if (order[0] == 'D'){
            if (cursor->get_right() != nullptr)
                cursor = cursor->move_right();
        }

        if (order[0] == 'B'){
            if (cursor->get_alpha() != '0'){

                temp = cursor;
                cursor->lft->rgt = cursor->rgt;
                if (cursor->rgt)
                    cursor->rgt->lft = cursor->lft;
                cursor = cursor->lft;
                temp->lft = nullptr;
                temp->rgt = nullptr;
                delete temp;
            }

        }

        if (order[0] == 'P'){
         

            Node* c = new Node(a);
            if (cursor->rgt == nullptr){
                c->lft = cursor;
                cursor->rgt = c;
                cursor = c;
                continue;
            }
            else{
                c->rgt = cursor->rgt;
                c->lft = cursor;
                c->lft->rgt = c;
                c->rgt->lft = c;
                cursor = c;
            }

        }
    }


    while(1){
        start = start->rgt;
        cout << start->alpha;
        if (start->rgt == nullptr)
            break;
    }  


}
#include <iostream>
#include <unordered_map>
#include <algorithm>

using namespace std;


class Box{
    public:
        int id;
        int w;
        Box* prv = nullptr;
        Box* nxt = nullptr;

        Box(int id, int w){
            this->id = id;
            this->w = w;
        }

};
  

int n, m;
int order;
int t;
int q;
int belts[11];
unordered_map<int, Box*> box_container;
unordered_map<int, int> belt_num;
Box* heads[11] = {nullptr};
Box* tails[11] = {nullptr};


void set_factory(int n, int m){
    int box_ids[n];
    int box_ws[n];
    int temp;
    int id, w;
    for (int i = 0; i < n; i ++){
        cin >> temp;
        box_ids[i] = temp;
    }
    for (int i = 0; i < n; i ++){
        cin >> temp;
        box_ws[i] = temp;
    }

    int belt_number = 1;
    while (1){
        if (belt_number == m + 1)
            break;
        for (int i = 0; i < n / m; i++){
            id = box_ids[n/m * (belt_number - 1)+i];
            w  = box_ws[n/m * (belt_number - 1)+i];
            Box* b = new Box(id, w);
            if (heads[belt_number] == nullptr and tails[belt_number] == nullptr){
                heads[belt_number] = b;
                tails[belt_number] = b;
                belt_num[id] = belt_number;
                box_container[id] = b;
            }
            else{
                belt_num[id] = belt_number;
                Box* tail = tails[belt_number];
                tail->nxt = b;
                b->prv = tail;
                tails[belt_number] = b;
                box_container[id] = b;
            }
        }
        belt_number++;
    }
}

void box_drop(int w_max){
    int tot_w = 0;
    for (int i = 1; i < m + 1; i++){
        Box* box = heads[i];
        if (belts[i] == -1)
            continue;
        if (box == nullptr)
            continue;
        if (box->w <= w_max){
            if (heads[i] == tails[i]){
                heads[i] = nullptr;
                tails[i] = nullptr;
                belt_num[box->id] = -1;
                tot_w += box->w;
                box_container[box->id] = nullptr;
            }
            else{
                heads[i] = box->nxt;
                box->nxt->prv = nullptr;
                box->nxt = nullptr;
                belt_num[box->id] = -1;
                tot_w += box->w;
                box_container[box->id] = nullptr;
            }
        }
        else{
            if (heads[i] == tails[i])
                continue;
            heads[i] = box->nxt;
            box->nxt->prv = nullptr;
            box->nxt = nullptr;
            Box * tail = tails[i];
            tail->nxt = box;
            box->prv = tail;
            tails[i] = box;
        }
    }
    cout << tot_w << "\n";
}

void remove_box(int r_id){
    if (box_container[r_id] == nullptr){
        cout << -1 << '\n';
        return;
    }
    int belt_number = belt_num[r_id];
    Box* box = box_container[r_id];

    if (heads[belt_number] == tails[belt_number]){
        heads[belt_number] = nullptr;
        tails[belt_number] = nullptr;
        belt_num[box->id] = -1;
        box_container[box->id] = nullptr;
    }
    else if (heads[belt_number] == box){
        heads[belt_number] = box->nxt;
        box->nxt->prv = nullptr;
        box->nxt = nullptr;
        belt_num[box->id] = -1;
        box_container[box->id] = nullptr;
    }
    else if (tails[belt_number] == box){
        tails[belt_number] = box->prv;
        box->prv->nxt= nullptr;
        box->prv = nullptr;
        belt_num[box->id] = -1;
        box_container[box->id] = nullptr;
    }
    else{
        box->nxt->prv = box->prv;
        box->prv->nxt = box->nxt;
        box->nxt = nullptr;
        box->prv = nullptr;
        belt_num[box->id] = -1;
        box_container[box->id] = nullptr;
    }

    cout << r_id << "\n";
}

void check_box(int f_id){
    if (box_container[f_id] == nullptr){
        cout << -1 << '\n';
        return;
    }
    int belt_number = belt_num[f_id];
    Box* box = box_container[f_id];
    if (heads[belt_number] == tails[belt_number]){
        cout << belt_number << '\n';
        return;
    }
    else if (heads[belt_number] == box){
        cout << belt_number << '\n';
        return;
    }
    else{
        Box* tail = tails[belt_number];
        Box* head = heads[belt_number];
        heads[belt_number] = box;
        tails[belt_number] = box->prv;
        box->prv->nxt = nullptr;
        box->prv = nullptr;
        head->prv = tail;
        tail->nxt = head;
        cout << belt_number << '\n';
        return;
    }
    // cout <<123123;
}

void broken_belt(int b_num){
    if (belts[b_num] == -1){
        cout << -1 << '\n';
        return;
    }
    int start = b_num;
    while (1){
        b_num++;
        if (b_num == m + 1)
            b_num = 1;
        if (belts[b_num] == 1){
            belts[start] = -1;
            if (heads[start] == nullptr){
                cout << start << '\n';
                return;
            }
            Box * box = heads[start];
            while( box != nullptr){
                belt_num[box->id] = b_num;
                box = box->nxt;
            }
            Box* head = heads[start];
            Box* tail = tails[start];
            head->prv = tails[b_num];
            tails[b_num]->nxt = head;
            tails[b_num] = tail;

            heads[start] = nullptr;
            tails[start] = nullptr;
            cout << start << '\n';
            return;
        }
    }
}

int main(){
    fill(belts, belts + 11, 1);
    cin >> q;
    q--;
    cin >> order >> n >> m;
    set_factory(n,m);
    while (q--){
        cin >> order >> t;
        if (order == 200)
            box_drop(t); 
        else if (order == 300)
            remove_box(t);
        else if (order == 400)
            check_box(t);
        else if (order == 500)
            broken_belt(t);

    }
}

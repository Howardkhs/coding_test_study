#include <iostream>

#define DIV 1000000007
#define MAX_N  1000001
using namespace std;
long long idx = 0;
typedef pair <long long, long long> P;

long long storage[MAX_N] = {0};


class Tree{
    public:
        Tree(long long N){
            this->N = N; //충돌 방지
            sum = 1;
            lft = nullptr;
            rgt = nullptr;
            P p = {0, N-1};
            cover = p;
            
        }

        long long make_child(){
            if (this->N == 1){
                this->sum = (storage[idx] % DIV);
                idx += 1;
                return this->sum;
            }
            else{
                if (this->N % 2 == 0){
                    this->lft = new Tree(this->N / 2); // 메모리 할당
                    this->lft->cover = {this->cover.first, this->cover.first + this->N / 2 - 1};
                    this->sum *= this->lft->make_child();
                    this->rgt = new Tree(this->N / 2);
                    this->rgt->cover = {this->cover.first + this->N / 2, this->cover.second};
                    this->sum *= this->rgt->make_child();
                    this->sum %= DIV;
                    return this->sum;
                }
                else{
                    this->lft = new Tree(this->N / 2 + 1);
                    this->lft->cover = {this->cover.first, this->cover.first + this->N / 2};
                    this->sum *= this->lft->make_child();
                    this->rgt = new Tree(this->N / 2);
                    this->rgt->cover = {this->cover.first + this->N / 2 + 1, this->cover.second};
                    this->sum *= this->rgt->make_child();
                    this->sum %= DIV;
                    return this->sum;
                }
            }

        }
        void print_cover(){
            cout << this->cover.first << ' ' <<this->cover.second << "\n";
            if (this->lft != nullptr){
                this->lft->print_cover();
            }
            if (this->rgt != nullptr){
                this->rgt->print_cover();
            }
        }
        void print_child(){
            cout << this->sum << "\n";
            if (this->lft){
                this->lft->print_child();
            }
            if (this->rgt){
                this->rgt->print_child();
            }
        }

        long long change_child(long long order, long long c){
            if (this->cover.first == order and this->cover.second == order){
                this-> sum = c % DIV;
                return this->sum;
            }
            else if (this->lft->cover.first <= order && order <= this->lft->cover.second){
                long long lft_sum = this->lft->change_child(order, c);
                this->sum = (lft_sum * this->rgt->sum) % DIV;
                return this->sum;
            }
            else{
                long long rgt_sum = this->rgt->change_child(order, c);
                this->sum = (rgt_sum * this->lft->sum) % DIV;
                return this->sum;
            }

        }

        long long print_multi(long long b, long long c){
            long long answer = 1;
            if (this->cover.first == b && this->cover.second == c){
                return this->sum;
            }
            else if (this->lft->cover.first <= b && c <= this->lft->cover.second){
                long long temp = this->lft->print_multi(b,c);
                answer = (answer * temp) % DIV;
                return answer;
            }
            else if (this->rgt->cover.first <= b && c <= this->rgt->cover.second){
                long long temp = this->rgt->print_multi(b,c);
                answer = (answer * temp) % DIV;
                return answer;
            }
            else{
                long long temp_1 = this->lft->print_multi(b, this->lft->cover.second);
                long long temp_2 = this->rgt->print_multi(this->rgt->cover.first, c);
                answer = (temp_1 * temp_2) % DIV;
                return answer;
            }
        }

    
    private:
        long long N;
        long long sum;
        Tree* lft;
        Tree* rgt;
        P cover;

};






int main(){

    ios_base :: sync_with_stdio(false); 
    cin.tie(NULL); 
    cout.tie(NULL);

    long long N, M, K;
    cin >> N >> M >> K;
    idx = 0;
    

    for (long long i = 0; i < N; i++){
        long long num;
        cin >> num;
        storage[i] = num;
    }
    Tree tree(N);
    
    tree.make_child();
    // tree.print_child();
    // tree.print_cover();
    long long t = M + K;
    long long a, b, c;
    long long score;
    while (t--){
        cin >> a >> b >> c;
        if (a == 1){
            tree.change_child(b-1,c);
        }
        else{
            score = tree.print_multi(b-1,c-1);
            cout << score << "\n";
        }
    }


}
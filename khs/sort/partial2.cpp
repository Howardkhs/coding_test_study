#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MAX_INPUT 10000
#define MAX_NUM 30000

static int input[MAX_INPUT];

static unsigned int seed = 13410;

static unsigned int pseudoRand() {
	seed = seed * 214013 + 2531011;
	return (unsigned int)(seed >> 11) % MAX_NUM;
}

static void makeInput(int inputLen) {
	for (int i = 0; i < inputLen; i++) {
		input[i] = pseudoRand();
	}
}
using namespace std;
#include <vector>
#include <iostream>
#include <list>
typedef pair<int, int> P; // 수입 id

list<P> mans;


void init()
{   
    mans.clear();
}

void addUser(int uID, int height) 
{
    if (mans.empty()){
        mans.push_back({height, uID});
        return;
    }
    int fail = 1;
    for (auto p = mans.begin(); p != mans.end(); p++){
        if (p->first < height){
            mans.insert(p, {height, uID});
            fail = 0;
            break;
        }
    
        if (p->first == height){
            if (p->second > uID){
                mans.insert(p, {height, uID});
                fail = 0;
                break;
            }
        }
    }
    if (fail)
        mans.push_back({height, uID});
   
    
}

int getTop10(int result[10]) 
{   
    if (distance(mans.begin(), mans.end()) < 10){
        for (int i = 0; i < distance(mans.begin(), mans.end()); i++){
            result[i] = mans[i].second;
            
        }
        return distance(mans.begin(), mans.end());
    }
    for (int i = 0; i < 10; i++){
        result[i] = mans[i].second;
        
    }
    return 10;
}


static int run() {
	int N, userNum, uID = 0;
	int score = 100, result[10], cnt;
	int sum, check;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &userNum);
		makeInput(userNum);
		for (int j = 0; j < userNum; j++) {
			addUser(uID++, input[j]);
		}
		cnt = getTop10(result);
		sum = 0;
		for (int j = 0; j < cnt; j++)
			sum += result[j];
		scanf("%d", &check);
		if (check != sum)
			score = 0;
	}
	return score;
}

int main(void) {vector, NULL);
	freopen("partial_sort_input.txt", "r", stdin);
	int T;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		init();
		printf("#%d %d\n", tc, run());
	}
	return 0;
}
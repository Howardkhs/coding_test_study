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

#define MAX_SIZE    100000
int heights[MAX_SIZE];
int uIDs[MAX_SIZE];
int sorted_1[MAX_SIZE];
int sorted_2[MAX_SIZE];
int ptr;

void init()
{   
    ptr = 0;
}

void addUser(int uID, int height) 
{
    heights[ptr] = height;
    uIDs[ptr++] = uID;    
}

void merge(int heights[], int uIDs[], int lft, int mid, int rgt){
    int i, j, k, l;
    i = lft;
    j = mid+1;
    k = lft;


    while(i<=mid && j<=rgt){
        if (heights[i] > heights[j]){
            sorted_1[k] = heights[i];
            sorted_2[k++] = uIDs[i++];
        }
        else if (heights[i] == heights[j]){
            if (uIDs[i] < uIDs[j]){
                sorted_1[k] = heights[i];
                sorted_2[k++] = uIDs[i++];
            }
        }
        else{
            sorted_1[k] = heights[j];
            sorted_2[k++] = uIDs[j++];
        }
    }

    // 남아 있는 값들을 일괄 복사
    if(i>mid){
        for(l=j; l<=rgt; l++){
            sorted_1[k] = heights[l];
            sorted_2[k++] = uIDs[l];
        }
    }
    // 남아 있는 값들을 일괄 복사
    else{
        for(l=i; l<=mid; l++){
            sorted_1[k] = heights[l];
            sorted_2[k++] = uIDs[l];
        }
    }

    // 배열 sorted[](임시 배열)의 리스트를 배열 list[]로 재복사
    for(l=lft; l<=rgt; l++){
        heights[l] = sorted_1[l];
        uIDs[l] = sorted_2[l];
    }
}

void merge_sort(int heights[], int uIDs[], int lft, int rgt){
    int mid;

    if (lft < rgt){
        mid = (lft + rgt) / 2;
        merge_sort(heights, uIDs, lft, mid);
        merge_sort(heights, uIDs, mid+1, rgt);
        merge(heights, uIDs, lft, mid, rgt);
    }
}


int getTop10(int result[10]) 
{   
    merge_sort(heights, uIDs, 0, ptr-1);
    if (ptr < 10){
        for (int i = 0; i < ptr; i++){
            result[i] = uIDs[i];
            
        }
        return ptr;
    }
    for (int i = 0; i < 10; i++){
        result[i] = uIDs[i];
        
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

int main(void) {
	setbuf(stdout, NULL);
	// freopen("partial_sort_input.txt", "r", stdin);
	int T;
	scanf("%d", &T);
	for (int tc = 1; tc <= T; tc++) {
		init();
		printf("#%d %d\n", tc, run());
	}
	return 0;
}
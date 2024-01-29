#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>


#define CMD_INIT    1
#define CMD_APPEND  2
#define CMD_CUT     3
#define CMD_REVERSE 4
#define CMD_COUNT   5

#include <deque>
#include <iostream>
#include <unordered_map>
#include <cstring>

using namespace std;
bool reversed = false;

deque<int> dq;
unordered_map<int, int> words;
unordered_map<int, int> rwords;

int char_to_int(char a){
    return a - 'a' + 1;
}

void make_hash(){
    int idx = 0;
    int len = dq.size();
    words.clear();
    rwords.clear();
    for (int i = 0; i < len; i++){
        int word = dq[i];
        words[word] += 1;

        if (i + 1 >= len)
            continue;
        word = word << 5;
        word |= dq[i+1];
        words[word] += 1;

        if (i + 2 >= len)
            continue;
        word = word << 5;
        word |= dq[i+2];
        words[word] += 1;

        if (i + 3 >= len)
            continue;
        word = word << 5;
        word |= dq[i+3];
        words[word] += 1;
    }

    // for (auto p = words.begin(); p != words.end(); p++){
    //     cout << p->first << " " << p->second << endl;
    // } 
    // cout << endl;

    for (int i = len - 1; i >= 0; i--){
        int word = dq[i];
        rwords[word] += 1;

        if (i - 1 == -1)
            continue;
        word = word << 5;
        word |= dq[i-1];
        rwords[word] += 1;

        if (i - 2 == -1)
            continue;
        word = word << 5;
        word |= dq[i-2];
        rwords[word] += 1;

        if (i - 3 == -1)
            continue;
        word = word << 5;
        word |= dq[i-3];
        rwords[word] += 1;
    }

    // for (auto p = rwords.begin(); p != rwords.end(); p++){
    //     cout << p->first << " " << p->second << endl;
    // } 
    // cout << endl;

}

void init(char mStr[])
{
    dq.clear();
    reversed = false;
    

    for (int i = 0; mStr[i]; i++){
        dq.push_back(char_to_int(mStr[i]));
    }
    make_hash();

}

void appendHash(int asize){
    // cout << "append " << asize << endl;
    if (dq.size() < 8) {
        make_hash();
        return;
    }
    if (reversed){
        int idx = asize + 2;
        int len = dq.size();
        for (int i = idx; i > idx - 3; i--){
            int word = dq[i];
            rwords[word] -= 1;

            if (i - 1 == idx - 3)
                continue;
            word = word << 5;
            word |= dq[i-1];
            rwords[word] -= 1;

            if (i - 2 == idx - 3)
                continue;
            word = word << 5;
            word |= dq[i-2];
            rwords[word] -= 1;
        }

        for (int i = idx; i >= 0; i--){
            int word = dq[i];
            rwords[word] += 1;

            if (i - 1 == -1)
                continue;
            word = word << 5;
            word |= dq[i-1];
            rwords[word] += 1;

            if (i - 2 == -1)
                continue;
            word = word << 5;
            word |= dq[i-2];
            rwords[word] += 1;

            if (i - 3 == -1)
                continue;
            word = word << 5;
            word |= dq[i-3];
            rwords[word] += 1;
        }

        for (int i = 0; i < asize; i++){
            int word = dq[i];
            words[word] += 1;

            if (i + 1 >= len)
                continue;
            word = word << 5;
            word |= dq[i+1];
            words[word] += 1;

            if (i + 2 >= len)
                continue;
            word = word << 5;
            word |= dq[i+2];
            words[word] += 1;

            if (i + 3 >= len)
                continue;
            word = word << 5;
            word |= dq[i+3];
            words[word] += 1;
        }

    }
    else{
        int idx = dq.size() - 3 - asize;
        int len = dq.size();
        for (int i = idx; i < idx + 3; i++){ // 앞에 3개 딕트 제거
            int word = dq[i];
            words[word] -= 1;


            if (i + 1 >= idx + 3)
                continue;
            word = word << 5;
            word |= dq[i+1];
            words[word] -= 1;

            if (i + 2 >= idx + 3)
                continue;
            word = word << 5;
            word |= dq[i+2];
            words[word] -= 1;
        }

        for (int i = idx; i < len; i++){

            int word = dq[i];
            words[word] += 1;

            if (i + 1 >= len)
                continue;
            word = word << 5;
            word |= dq[i+1];
            words[word] += 1;

            if (i + 2 >= len)
                continue;
            word = word << 5;
            word |= dq[i+2];
            words[word] += 1;

            if (i + 3 >= len)
                continue;
            word = word << 5;
            word |= dq[i+3];
            words[word] += 1;
        }
   
        for (int i = len - 1; i >= len - asize; i--){

            int word = dq[i];
            rwords[word] += 1;

            if (i - 1 == -1)
                continue;
            word = word << 5;
            word |= dq[i-1];
            rwords[word] += 1;

            if (i - 2 == -1)
                continue;
            word = word << 5;
            word |= dq[i-2];
            rwords[word] += 1;

            if (i - 3 == -1)
                continue;
            word = word << 5;
            word |= dq[i-3];
            rwords[word] += 1;
        }

        // 뒤에꺼 붙은거 처리
    }

}

void appendWord(char mWord[])
{
    if (reversed){
        int i;
        for (i = 0; mWord[i]; i++){
            dq.push_front(char_to_int(mWord[i]));
        }
        appendHash(i);
    }
    else{
        int i;
        for (i = 0; mWord[i]; i++){
            dq.push_back(char_to_int(mWord[i]));
        }
        appendHash(i);
    }    
}

void eraseWord(int start, int end)
{
    if (!(reversed)){
        if (start < 8){
            make_hash();
            return;
        }
        int idx = start - 3;
        for (int i = idx; i < idx + 3; i++){ // 앞에 3개 더하고
            int word = dq[i];
            words[word] += 1;

            if (i + 1 >= idx + 3)
                continue;
            word = word << 5;
            word |= dq[i+1];
            words[word] += 1;

            if (i + 2 >= idx + 3)
                continue;
            word = word << 5;
            word |= dq[i+2];
            words[word] += 1;
        }
        int len = end;
        for (int i = idx; i < len; i++){

            int word = dq[i];
            words[word] -= 1;

            if (i + 1 >= len)
                continue;
            word = word << 5;
            word |= dq[i+1];
            words[word] -= 1;

            if (i + 2 >= len)
                continue;
            word = word << 5;
            word |= dq[i+2];
            words[word] -= 1;

            if (i + 3 >= len)
                continue;
            word = word << 5;
            word |= dq[i+3];
            words[word] -= 1;
        }
        for (int i = len - 1; i >= start; i--){

            int word = dq[i];
            rwords[word] -= 1;

            if (i - 1 == -1)
                continue;
            word = word << 5;
            word |= dq[i-1];
            rwords[word] -= 1;

            if (i - 2 == -1)
                continue;
            word = word << 5;
            word |= dq[i-2];
            rwords[word] -= 1;

            if (i - 3 == -1)
                continue;
            word = word << 5;
            word |= dq[i-3];
            rwords[word] -= 1;
        }


    }
    else{
        if (dq.size() - end < 8){
            make_hash();
            return;
        }

        int idx = end + 2;

        for (int i = idx; i > idx - 3; i--){
            int word = dq[i];
            rwords[word] += 1;

            if (i - 1 == idx - 3)
                continue;
            word = word << 5;
            word |= dq[i-1];
            rwords[word] += 1;

            if (i - 2 == idx - 3)
                continue;
            word = word << 5;
            word |= dq[i-2];
            rwords[word] += 1;
        }
        for (int i = idx; i >= 0; i--){
            int word = dq[i];
            rwords[word] -= 1;

            if (i - 1 == -1)
                continue;
            word = word << 5;
            word |= dq[i-1];
            rwords[word] -= 1;

            if (i - 2 == -1)
                continue;
            word = word << 5;
            word |= dq[i-2];
            rwords[word] -= 1;

            if (i - 3 == -1)
                continue;
            word = word << 5;
            word |= dq[i-3];
            rwords[word] -= 1;
        }
        int len = dq.size();
        for (int i = 0; i < end; i++){
            int word = dq[i];
            words[word] -= 1;

            if (i + 1 >= len)
                continue;
            word = word << 5;
            word |= dq[i+1];
            words[word] -= 1;

            if (i + 2 >= len)
                continue;
            word = word << 5;
            word |= dq[i+2];
            words[word] -= 1;

            if (i + 3 >= len)
                continue;
            word = word << 5;
            word |= dq[i+3];
            words[word] -= 1;
        }
    }    
}

void cut(int k)
{
    if (!(reversed)){
        eraseWord(dq.size() - k, dq.size());
        dq.erase(dq.end() - k, dq.end());
    }
    else{
        eraseWord(0, k);
        dq.erase(dq.begin(), dq.begin() + k);
    }

}

void reverse()
{
    if (reversed)
        reversed = false;
    else   
        reversed = true;
}

int countOccurrence(char mWord[])
{   
    int s = 0;
    for (int i = 0; mWord[i]; i++){
        s = s << 5;
        s |= char_to_int(mWord[i]);
        
    }
    if (reversed){
        // cout << rwords[s] << endl;
        return rwords[s];
    }
    // cout << words[s] << endl;
    return words[s];
}

/////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////

void print_dq(){
    cout << "deque : " << endl;
    for (int i = 0; i < dq.size(); i++){
        char a = dq[i] + 'a' - 1;
        cout << a << " ";
    }
    cout << endl;
}

static bool run()
{
	bool correct = false;
	int queryCnt;
	scanf("%d", &queryCnt);
	static char mStr[30001], mWord[5];

	while (queryCnt--)
	{
		int cmd;
		scanf("%d", &cmd);

		if (cmd == CMD_INIT)
		{
			scanf("%s", mStr);
			init(mStr);
			correct = true;
		}
		else if (cmd == CMD_APPEND)
		{
			scanf("%s", mWord);
			
			if (correct)
			{
				appendWord(mWord);
			}
		}
		else if (cmd == CMD_CUT)
		{
			int k;
			scanf("%d", &k);
			
			if (correct)
			{
				cut(k);
			}
		}
		else if (cmd == CMD_REVERSE)
		{
			if (correct)
			{
				reverse();
			}
		}
		else if (cmd == CMD_COUNT)
		{
			scanf("%s", mWord);

			int ret = -1;
			if (correct)
			{
				ret = countOccurrence(mWord);
			}

			int ans;
			scanf("%d", &ans);
			if(ret != ans)
			{
				correct = false;
			}
		}
	}
	return correct;
}

int main()
{
	setbuf(stdout, NULL);
	freopen("sample_input.txt", "r", stdin);

	int T, MARK;
	scanf("%d %d", &T, &MARK);

	for (int tc = 1; tc <= T; tc++)
	{
		int score = run() ? MARK : 0;
		printf("#%d %d\n", tc, score);
	}
	return 0;
}
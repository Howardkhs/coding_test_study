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
        word += dq[i+1];
        words[word] += 1;

        if (i + 2 >= len)
            continue;
        word = word << 5;
        word += dq[i+2];
        words[word] += 1;

        if (i + 3 >= len)
            continue;
        word = word << 5;
        word += dq[i+3];
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
        word += dq[i-1];
        rwords[word] += 1;

        if (i - 2 == -1)
            continue;
        word = word << 5;
        word += dq[i-2];
        rwords[word] += 1;

        if (i - 3 == -1)
            continue;
        word = word << 5;
        word += dq[i-3];
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
    for (int i = 0; i < dq.size(); i++){
        cout << dq[i] << " ";
    }
    cout << endl;

    make_hash();

}

void appendHash(int asize){
    if (dq.size() < 8) {
        make_hash();
        return;
    }
    if (reversed){
        int idx = asize + 2;
        int len = dq.size();
        for (int i = idx; i > idx - 3; i--){
            int word = dq[i];
            words[word] -= 1;

            if (i - 1 == idx - 3)
                continue;
            word = word << 5;
            word += dq[i-1];
            words[word] -= 1;

            if (i - 2 >= idx - 3)
                continue;
            word = word << 5;
            word += dq[i-2];
            words[word] -= 1;
        }

        for (int i = idx; i >= 0; i--){
            int word = dq[i];
            rwords[word] += 1;

            if (i - 1 == -1)
                continue;
            word = word << 5;
            word += dq[i-1];
            rwords[word] += 1;

            if (i - 2 == -1)
                continue;
            word = word << 5;
            word += dq[i-2];
            rwords[word] += 1;

            if (i - 3 == -1)
                continue;
            word = word << 5;
            word += dq[i-3];
            rwords[word] += 1;
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
            word += dq[i+1];
            words[word] -= 1;

            if (i + 2 >= idx + 3)
                continue;
            word = word << 5;
            word += dq[i+2];
            words[word] -= 1;
        }

        for (int i = idx; i < len; i++){
            int word = dq[i];
            words[word] += 1;

            if (i + 1 >= len)
                continue;
            word = word << 5;
            word += dq[i+1];
            words[word] += 1;

            if (i + 2 >= len)
                continue;
            word = word << 5;
            word += dq[i+2];
            words[word] += 1;

            if (i + 3 >= len)
                continue;
            word = word << 5;
            word += dq[i+3];
            words[word] += 1;
        }
    }

}

void appendWord(char mWord[])
{
    if (reversed){
        for (int i = 0; mWord[i]; i++){
            dq.push_front(char_to_int(mWord[i]));
        }
        appendHash(sizeof(mWord));
    }
    else{
        for (int i = 0; mWord[i]; i++){
            dq.push_back(char_to_int(mWord[i]));
        }
        appendHash(sizeof(mWord));
    }

    

    for (int i = 0; i < dq.size(); i++){
        cout << dq[i] << " ";
    }
    cout << endl;
    
}

void cut(int k)
{
    if (!(reversed)){
        dq.erase(dq.end() - k, dq.end());
    }
    else
        dq.erase(dq.begin(), dq.begin() + k);
    make_hash();
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
        s += char_to_int(mWord[i]);
        
    }
    if (reversed){
        cout << rwords[s] << endl;
        return rwords[s];
    }
    cout << words[s] << endl;
    return words[s];
}
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

//////////////////////////////////////////////////////////////////////
#include <unordered_map>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class student{
    public:
        int mScore;
        int mId;
        int mGender;
        int mGrade;

        student(){}
        student(int _mScore, int _mId, int _mGender, int _mGrade){
            mScore = _mScore;
            mId = _mId;
            mGender = _mGender;
            mGrade = _mGrade;
        }

};

unordered_map<int, student> students;
unordered_map<int, int> check_S;
vector<vector<vector<student>>> G;

bool compare(student &a, student &b){
    if (a.mScore != b.mScore)
        return a.mScore < b.mScore;
    return a.mId < b.mId;
}


void init() {
   
    G.clear();
    check_S.clear();
    students.clear();
    for (int i = 0; i < 2;i++){
        G.emplace_back();
        for (int j = 0; j < 4; j++){
            G[i].emplace_back();
        }
    }
	return;
}

void insert(int gender, int mGrade, student S){
    int start = 0;
    int end = G[gender][mGrade].size() - 1;

    if (end == -1){
        G[gender][mGrade].push_back(S);
        return;
    }

    int target = 0;

    while (start <= end){
        int mid = start + (end - start) / 2;
        if (G[gender][mGrade][mid].mScore < S.mScore){
            start = mid + 1;
            target = start;
        }
        else if(G[gender][mGrade][mid].mScore > S.mScore){
        
            end = mid - 1;
        }
        else{
            if(G[gender][mGrade][mid].mId < S.mId){
                start = mid + 1;
                target = start;
            }
            else{
                end = mid - 1;
            }
        }
    }

    G[gender][mGrade].insert(G[gender][mGrade].begin() + target, S);
}

int add(int mId, int mGrade, char mGender[7], int mScore) {
    
    
    if (mGender[0] == 'm'){
        student S = {mScore, mId, 0, mGrade};
        students[mId] = S;
        check_S[mId] = 1;
        insert(0, mGrade, S);
        // cout << G[0][mGrade][G[0][mGrade].size() - 1].mId << endl;
        return G[0][mGrade][G[0][mGrade].size() - 1].mId;
    }
    else{
        student S = {mScore, mId, 1, mGrade};
        students[mId] = S;
        check_S[mId] = 1;
        insert(1, mGrade, S);
        // cout << G[1][mGrade][G[1][mGrade].size() - 1].mId << endl;
        return G[1][mGrade][G[1][mGrade].size() - 1].mId;
    }

	return 0;
}

int del(student S){
    int gender = S.mGender;
    int mGrade = S.mGrade;
    int mId = S.mId;

    int start = 0;
    int end = G[gender][mGrade].size() - 1;

    int target = 0;

    while (start <= end){
        int mid = start + (end - start) / 2;
        if (G[gender][mGrade][mid].mScore < S.mScore){
            start = mid + 1;
        }
        else if(G[gender][mGrade][mid].mScore > S.mScore){
            end = mid - 1;
        }
        else{
            if (G[gender][mGrade][mid].mId < mId){
                start = mid + 1;
            }
            else if(G[gender][mGrade][mid].mId > mId){
                end = mid - 1;
            }
            else{
                target = mid;
                break;
            }
        }
    }
    G[gender][mGrade].erase(G[gender][mGrade].begin() + target);
    if (G[gender][mGrade].size() == 0){
        return 0;
    }
    else{
        return G[gender][mGrade][0].mId;
    }
}
int remove(int mId) {


    if (check_S[mId] == 0)
        return 0;

    student S = students[mId];
    check_S[mId] = 0;

    int answer = del(S);
    // cout << answer << endl;
	return answer;
}

student find(int Gender, int Grade, int mScore){
    int start = 0;
    int end = G[Gender][Grade].size() - 1;

    int target = 0;
    int mId = 2000000000;

    while (start <= end){
        int mid = start + (end - start) / 2;
        if (G[Gender][Grade][mid].mScore < mScore){
            start = mid + 1;
            target = start;
        }
        else if(G[Gender][Grade][mid].mScore >= mScore){
            end = mid - 1;
        }
    }
    // cout << target << endl;
    // while (start <= end){
    //     int mid = start + (end - start) / 2;
    //     if (G[Gender][Grade][mid].mScore < mScore){
    //         start = mid + 1;
    //     }
    //     else if(G[Gender][Grade][mid].mScore > mScore){
    //         target = mid;
    //         end = mid - 1;
    //     }
    //     else{
    //         if(G[Gender][Grade][mid].mId < mId){
    //             mId = G[Gender][Grade][mid].mId;
    //             target = mid;
    //             end = mid - 1;
    //             // cout << target << endl;
    //         }
    //     }
    // }
    if (target >= G[Gender][Grade].size()){
        student answer(2000000000, 2000000000, 1, 1);
        return answer;
    }
    // cout << target << " " << G[Gender][Grade][target].mScore << endl; //.못찾을떄
    return G[Gender][Grade][target];
}

int query(int mGradeCnt, int mGrade[], int mGenderCnt, char mGender[][7], int mScore) {
    
    // for (int i = 0; i < 2; i++){
    //     for (int j = 1; j < 4; j++){
    //         sort(G[i][j].begin(), G[i][j].end(),compare);
            
    //     }
    // }
    int Gender, Grade;
    int fail = 1;
    student S, answer(2000000000, 2000000000, 1, 1);
    
    for (int i = 0; i < mGenderCnt; i++){
        if (mGender[i][0] == 'm')
            Gender = 0;
        else
            Gender = 1;
        for (int j = 0; j < mGradeCnt; j++){
            Grade = mGrade[j];
            if (G[Gender][Grade].size() == 0)
                continue;
            S = find(Gender, Grade, mScore);
            // cout << S.mId << endl;
            if (S.mScore == 2000000000)
                continue;
            if (S.mScore < answer.mScore){
                answer.mScore = S.mScore;
                answer.mId = S.mId;
            }
            else if (S.mScore == answer.mScore){
                if (S.mId < answer.mId){
                    answer.mScore = S.mScore;
                    answer.mId = S.mId;
                }
            }
            // cout << answer.mId << endl;
            
            fail = 0;
        }
        
    }
    if (fail == 1) {    
        // cout << 0 << endl;
        return 0;
    }
    else {
        // cout << answer.mId << endl;
        return answer.mId;
    }

}

void print(){
    for (int i = 0; i < 2; i++){
        for (int j = 1; j < 4; j++){
            for (int k = 0; k < G[i][j].size(); k++){
                cout << G[i][j][k].mId << " ";
            }
        }
    }
    cout << endl;

}


/////////////////////////////////////////////////////////////////////////



#define CMD_INIT 100
#define CMD_ADD 200
#define CMD_REMOVE 300
#define CMD_QUERY 400

static bool run() {
	int q;
	scanf("%d", &q);

	int id, grade, score;
	char gender[7];
	int cmd, ans, ret;
	bool okay = false;

	for (int i = 0; i < q; ++i) {
		scanf("%d", &cmd);
		switch (cmd) {
			case CMD_INIT:
				init();
				okay = true;
				break;
			case CMD_ADD:
				scanf("%d %d %s %d %d", &id, &grade, gender, &score, &ans);
				ret = add(id, grade, gender, score);
				if (ans != ret)
					okay = false;
				break;
			case CMD_REMOVE:
				scanf("%d %d", &id, &ans);
				ret = remove(id);
				if (ans != ret)
					okay = false;
				break;
			case CMD_QUERY: {
				int gradeCnt, genderCnt;
				int gradeArr[3];
				char genderArr[2][7];
				scanf("%d", &gradeCnt);
				if (gradeCnt == 1) {
					scanf("%d %d", &gradeArr[0], &genderCnt);
				} else if (gradeCnt == 2) {
					scanf("%d %d %d", &gradeArr[0], &gradeArr[1], &genderCnt);
				} else {
					scanf("%d %d %d %d", &gradeArr[0], &gradeArr[1], &gradeArr[2], &genderCnt);
				}
				if (genderCnt == 1) {
					scanf("%s %d %d", genderArr[0], &score, &ans);
				} else {
					scanf("%s %s %d %d", genderArr[0], genderArr[1], &score, &ans);
				}
				ret = query(gradeCnt, gradeArr, genderCnt, genderArr, score);
				if (ans != ret)
					okay = false;
				break;
			}
			default:
				okay = false;
				break;
		}
        if (okay == false)  {
            okay = true;
            cout << cmd << endl;
        }

        
        // print();
	}
	return okay;
}

int main() {
	setbuf(stdout, NULL);
	freopen("sample_input.txt", "r", stdin);

	int T, MARK;
	scanf("%d %d", &T, &MARK);

	for (int tc = 1; tc <= T; tc++) {
		int score = run() ? MARK : 0;
		printf("#%d %d\n", tc, score);
	}
    // print();

	return 0;
}
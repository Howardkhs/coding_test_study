#include<iostream>
#include <algorithm>

using namespace std;

int cow[500000];
int horse[10] = {0,1,2,3,4,6,7,8,9,10};

int downSearch(int target, int start, int end){

    int up = -1;
    while (start <= end){
        int mid = start + (end - start) / 2;
        // cout << horse[mid] << endl; 
        if (horse[mid] == target)
            return mid;
        
        if (horse[mid] < target){
            up = mid;
            start= mid + 1;
        }
        else{
            end = mid - 1;
        }
        
    }
    return up;
}

int upperSearch(int target, int start, int end){

    int up = -1;
    while (start <= end){
        int mid = start + (end - start) / 2;
        // cout << horse[mid] << endl; 
        if (horse[mid] == target)
            return mid;
        
        if (horse[mid] < target){
            
            start= mid + 1;
        }
        else{
            up = mid;
            end = mid - 1;
            
        }
        
    }
    return up;
}

int main(){
   cout << upperSearch(5, 0, 9) << endl;
   cout << upperSearch(0, 0, 9) << endl;
   cout << upperSearch(-1, 0, 9) << endl;
   cout << upperSearch(10, 0, 9) << endl;
   cout << upperSearch(11, 0, 9) << endl;

}
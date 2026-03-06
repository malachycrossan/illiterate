#include <iostream>
using namespace std;

int ** memo;
int * points;
int length, cuts;

int findMin(int start, int end) {
    //cout << "Start: " << start << ", End: " << end << endl;

    // (0, -1)
    if(end < start) {
        return 0;
    }
    
    // Already solved.
    if(memo[start][end] != -1) { 
        //cout << "Already solved! " << memo[start][end] << endl;
        return memo[start][end]; 
    }

    int l, r, len;
    if(start == 0) { l = 0; } else { l = points[start-1]; }
    if(end == cuts-1) { r = length; } else { r = points[end+1]; }
    len = r - l;
    //cout << "Len: " << len << endl;

    // 0 length.
    if(start == end) {
        //cout << "They are equal." << endl; 
        memo[start][end] = len;
        return len; 
    }

    int ret = 1000000; // Greater than the maximum possible cost. 

    for(int a = start; a <= end; a++) {
        int cost = len + findMin(start, a-1) + findMin(a+1, end);
        //cout << "Cost: " << cost << endl;
        ret = min(ret, cost);
    }

    memo[start][end] = ret;
    return ret;
}

/*
void printArr(int ** memo) {
    for(int o = 0; o < cuts; o++) {
        for(int t = 0; t < cuts; t++) {
            cout << "Memo[" << o << "][" << t << "] = " << memo[o][t] << endl;
        }
    }
}
*/

int main() {
    int cases;
    cin >> cases;

    // Main loop.
    for(int m = 0; m < cases; m++) {
        // Get user input.
        cin >> length >> cuts;
        points = new int[cuts];
        memo = new int*[cuts];

        for(int n = 0; n < cuts; n++) {
            // Get all split points.
            cin >> points[n];
            memo[n] = new int[cuts];
            // Initialize with -1's.
            for(int k = 0; k < cuts; k++) { memo[n][k] = -1; }
        }

        cout << findMin(0, cuts-1) << endl;

        //printArr(memo);
    }

    return 0;
}
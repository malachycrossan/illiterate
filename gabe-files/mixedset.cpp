#include <iostream>
#include <map>
#include <list>
#include <stack>
#include <algorithm>
using namespace std;

// Uses lots of global variables for less writing headache.
int c, n, s, k, subsize, currank;
int * cur;
int memo[51];

void printArr(int * cur) {
    // Just print the array.
    for(int i = 0; i < s; i++) {
        cout << cur[i] << " ";
    }
    cout << endl;
}

int findMixed(int pos, int * cur, list<int> subs) {
    // We're at the end of the set.
    if(pos >= s) { 
        currank++;
        // Print the final array when necessary.
        if(currank == k) {
            printArr(cur);
        }
        return 0; 
    }

    int curnum, pushes;
    bool works;
    // Get the previous position (if applicable) and loop through each number after that.
    // Ex: if cur[1] = 2, then we would start at 3 and loop to n.
    if(pos == 0) { curnum = 0; } else { curnum = cur[pos-1]; }
    // Main loop.
    for(int i = curnum; i < n; i++) {
        // Reset values per loop.
        works = true;
        pushes = 0;

        // Place value in current position.
        cur[pos] = i+1;
        //cout << "cur[" << pos << "] = " << i+1 <<endl;

        // Add all previous differences.
        stack<int> cursubs;
        for(int j = pos-1; j >= 0; j--) {
            // Found sub.
            if(memo[(i+1)-cur[j]]) {
                //cout << "memo[" << i-cur[j] << "] = " << memo[i-cur[j]] << endl;
                //cout << i+1 << " - " << cur[j] << " exists." << endl;
                j = -1;
                works = false;
                break; // Leave j loop.
            } else {
                // Add sub.
                memo[(i+1)-cur[j]] = 1;
                cursubs.push((i+1)-cur[j]);
                ++pushes;
            }
        }
        
        if(!works) {
            // Backtrack?
            for(int j = 0; j < pushes; j++) {
                memo[cursubs.top()] = 0;
                cursubs.pop();
            }
            continue;
        }

        // This number works, so continue.
        findMixed(pos + 1, cur, subs);

        // Backtrack.
        //cout << "Pushes: " << pushes << endl;
        //cout << "cursubs: " << cursubs.size() << endl;
        for(int j = 0; j < pushes; j++) {
            memo[cursubs.top()] = 0;
            cursubs.pop();
        }

        if(currank == k) { return 0; } // we're done.
    }

    return 0;
}

int main() {
    cin >> c;

    // Main loop.
    for(int z = 0; z < c; z++) {
        cin >> n >> s >> k;
        currank = 0;
        cur = new int[s]{};
        list<int> subs = {};
        // Set memo table to 0's.
        fill(memo, memo + 51, 0);
        cout << "memo[1] = " << memo[1] << endl;
        // Find mixed set.
        findMixed(0, cur, subs);
    }

    return 0;
}
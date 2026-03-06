#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include <valarray>
using namespace std;

static int arr[12] = { 3, 17, 15, 18, 11, 22, 12, 23, 21, 7, 9, 13 }; // Defined to save time for debugging.
static int totalsum = 171; // Defined to save time for debugging.
static int rowgoal = totalsum / 3; // 57.
static int res = 0;
static int totalsol;

static vector<array<int, 12>> solutions; 

/*

    Test Case Example:
    3  17  15  18  11  22  12  23  21  7  9  13
    ---------------------------------------------
    0  1   2   3   4   5   6   7   8   9  10 11

    Total Sum = 171
    2 * Total Sum = 342
    Total Sum / 3 = 57

    Starting Rows:
    Row 1 - 3, 17, 15, 18 = 53          // STOP HERE!!!  53 != 57
    Row 2 -  18, 11, 22, 12 = 63
    Row 3 - 12, 23, 21, 3 = 59
    Row 4 - 7, 22, 23, 13 = 65
    Row 5 - 9, 15, 11, 7 = 42
    Row 6 - 13, 21, 15, 9 = 58

    First successful row 1 - 0 + 1 + 2 + 5  |   3, 17, 15, 22

*/

void addRotations(array<int, 12> cur);

void addSolution(array<int, 12> cur) {
    solutions.push_back(cur);

    totalsol++;
}

bool hasSolution(array<int, 12> cur) {
    auto it = find(solutions.begin(), solutions.end(), cur);
    if(it != solutions.end()) {
        // Did not reach the end- we found one.
        return true;
    } else {
        return false;
    }
}

void addReflection(array<int, 12> cur) {
    array<int, 12> newcur;
    // Vertical reflection.
    newcur[0] = cur[0];
    newcur[1] = cur[8];
    newcur[2] = cur[7];
    newcur[3] = cur[6];
    newcur[4] = cur[5];
    newcur[5] = cur[4];
    newcur[6] = cur[3];
    newcur[7] = cur[2];
    newcur[8] = cur[1];
    newcur[9] = cur[9];
    newcur[10] = cur[11];
    newcur[11] = cur[10];
    totalsol++;
    solutions.push_back(newcur);
    //addRotations(newcur);

    // Horizontal reflection.
    newcur[0] = cur[9];
    newcur[1] = cur[4];
    newcur[2] = cur[2];
    newcur[3] = cur[10];
    newcur[4] = cur[1];
    newcur[5] = cur[8];
    newcur[6] = cur[11];
    newcur[7] = cur[7];
    newcur[8] = cur[5];
    newcur[9] = cur[0];
    newcur[10] = cur[3];
    newcur[11] = cur[6];
    totalsol++;
    solutions.push_back(newcur);
    //addRotations(newcur);

    // Left-right diagonal reflection.
    newcur[0] = cur[11];
    newcur[1] = cur[7];
    newcur[2] = cur[5];
    newcur[3] = cur[9];
    newcur[4] = cur[4];
    newcur[5] = cur[2];
    newcur[6] = cur[10];
    newcur[7] = cur[1];
    newcur[8] = cur[8];
    newcur[9] = cur[3];
    newcur[10] = cur[6];
    newcur[11] = cur[0];
    totalsol++;
    solutions.push_back(newcur);
    //addRotations(newcur);

    // Right-left diagonal reflection.
    newcur[0] = cur[10];
    newcur[1] = cur[1];
    newcur[2] = cur[8];
    newcur[3] = cur[11];
    newcur[4] = cur[7];
    newcur[5] = cur[5];
    newcur[6] = cur[9];
    newcur[7] = cur[4];
    newcur[8] = cur[2];
    newcur[9] = cur[6];
    newcur[10] = cur[0];
    newcur[11] = cur[3];
    totalsol++;
    solutions.push_back(newcur);
    //addRotations(newcur);

    // Extreme left-right diagonal reflection.
    newcur[0] = cur[6];
    newcur[1] = cur[5];
    newcur[2] = cur[4];
    newcur[3] = cur[3];
    newcur[4] = cur[2];
    newcur[5] = cur[1];
    newcur[6] = cur[0];
    newcur[7] = cur[8];
    newcur[8] = cur[7];
    newcur[9] = cur[10];
    newcur[10] = cur[9];
    newcur[11] = cur[11];
    totalsol++;
    solutions.push_back(newcur);
    //addRotations(newcur);

    // Extreme right-left diagonal reflection.
    newcur[0] = cur[3];
    newcur[1] = cur[2];
    newcur[2] = cur[1];
    newcur[3] = cur[0];
    newcur[4] = cur[8];
    newcur[5] = cur[7];
    newcur[6] = cur[6];
    newcur[7] = cur[5];
    newcur[8] = cur[4];
    newcur[9] = cur[11];
    newcur[10] = cur[10];
    newcur[11] = cur[9];
    totalsol++;
    solutions.push_back(newcur);
    //addRotations(newcur);
    return;
}

void addRotations(array<int, 12> cur) {
    valarray<int> innercircle = { 1, 2, 4, 5, 7, 8 };
    valarray<int> outercircle = { 0, 10, 3, 9, 6, 11 };
    int temp;
    array<int, 12> newcur;
    // Manual rotations.
    // Don't ask how long this took.

    // 60, 120, 180, 240, 300
    for(int i = 0; i < 5; i++) {
        temp = innercircle[5];
        innercircle.shift(1);
        innercircle[5] = temp;
        temp = outercircle[5];
        outercircle.shift(1);
        outercircle[5] = temp;

        newcur[0] = cur[outercircle[0]];
        newcur[1] = cur[innercircle[0]];
        newcur[2] = cur[innercircle[1]]; 
        newcur[3] = cur[outercircle[1]];
        newcur[4] = cur[innercircle[2]];
        newcur[5] = cur[innercircle[3]];
        newcur[6] = cur[outercircle[2]];
        newcur[7] = cur[innercircle[4]];
        newcur[8] = cur[innercircle[5]];
        newcur[9] = cur[outercircle[3]];
        newcur[10] = cur[outercircle[4]];
        newcur[11] = cur[outercircle[5]];
        addSolution(newcur);
        //addReflection(newcur);
    }

    /*
    newcur[0] = cur[6];
    newcur[1] = cur[5];
    newcur[2] = cur[8];
    newcur[3] = cur[11];
    newcur[4] = cur[1];
    newcur[5] = cur[2];
    newcur[6] = cur[9];
    newcur[7] = cur[7];
    newcur[8] = cur[4];
    newcur[9] = cur[0];
    newcur[10] = cur[10];
    newcur[11] = cur[3];
    addSolution(newcur);

    newcur[0] = cur[0];
    newcur[1] = cur[6];
    newcur[2] = cur[7];
    newcur[3] = cur[8];
    newcur[4] = cur[11];
    newcur[5] = cur[10];
    newcur[6] = cur[1];
    newcur[7] = cur[2];
    newcur[8] = cur[3];
    newcur[9] = cur[9];
    newcur[10] = cur[5];
    newcur[11] = cur[4];
    addSolution(newcur);
    */
    return;
}

bool arrEmpty() {
    // If all values are 0, we're done.
    for(int i = 0; i < 12; i++) {
        if(arr[i] != 0) { return false; } 
    }

    return true;
}

void getArr() {
    // Reset the total sum for new set of numbers.
    totalsum = 0;
    // Get inputs and find total sum of all numbers.
    for(int j = 0; j < 12; j++) {
        cin >> arr[j];
        totalsum += arr[j];
    }
    return;
}

bool canPrune(int index, array<int, 12> cur) {
    if(index == 3 && cur[0]+cur[1]+cur[2]+cur[3] == rowgoal) {
        //cout << "Row 1 works!" << endl;
        //cout << "Row 1: " << cur[0] << " " << cur[1] << " " << cur[2] << " " << cur[3] << " " << endl;
        // Row 1 works.
        return false;
    } else if(index == 6 && cur[3]+cur[4]+cur[5]+cur[6] == rowgoal) {
        // Row 2 works.
        return false;
    } else if(index == 8 && cur[6]+cur[7]+cur[8]+cur[0] == rowgoal) {
        // Row 3 works.
        return false;
    } else if(index == 10 && cur[10]+cur[2]+cur[4]+cur[9] == rowgoal) {
        // Row 5 works (completed before 4. yes I know that's weird but hear me out)
        return false;
    } else if(index == 11) {
        // Two row completions here.
        // Left: Row 4      Right: Row 6
        if(cur[9]+cur[5]+cur[7]+cur[11] == rowgoal && cur[11]+cur[8]+cur[1]+cur[10] == rowgoal) {
            return false;
        }
    }

    return true;
}

// Index of current array, index of value to try in arr.
int bruteForce(int index, array<int, 12> cur, bool used[12]) {

     /*
        Row # - Indexes

        Row 1 - 0, 1, 2, 3
        Row 2 - 3, 4, 5, 6
        Row 3 - 6, 7, 8, 0
        Row 4 - 9, 5, 7, 11
        Row 5 - 10, 2, 4, 9
        Row 6 - 11, 8, 1, 10

    */

    if(index >= 12 && !hasSolution(cur)) {
        cout << "Permutation found:  " << cur[0] << ", " << cur[1] << ", " << cur[2] << ", " << cur[3] << ", " << cur[4] << ", " << cur[5] << ", " << cur[6] << ", " << cur[7] << ", " << cur[8] << ", " << cur[9] << ", " << cur[10] << ", " << cur[11] << "." << endl;
        // Add this permutation to the total solutions array.
        addSolution(cur);
        // Add reflections and rotations of this solution.
        addReflection(cur);
        addRotations(cur);
        // Res -> total UNIQUE solutions.
        res++;
        return 0;
    }

    for(int i = 0; i < 12; i++) {
        if(used[i]) continue; // If number is already used, move on to the next one.

        // Number is not used.
        cur[index] = arr[i];
        
        // Prune at row-completion points.
        if(index == 3 || index == 6 || index == 8 || index == 10 || index == 11) {
            if(canPrune(index, cur)) {
                // Do not permute with proposed number.
                continue;
            } else {
                used[i] = true;
                bruteForce(index + 1, cur, used);
                used[i] = false;
            }
        } else {
            // Not a row completion point- continue like normal.
            used[i] = true;
            bruteForce(index + 1, cur, used);
            used[i] = false;
        }
    }

    return 0;
}

int main() {
    // Brute force.
    array<int, 12> cur;
    bool used[12] = { false };

    bruteForce(0, cur, used);


    cout << "Done! Total permutations: " << res << endl;
    cout << "Solutions length: " << solutions.size() << endl;
    return 0;
}
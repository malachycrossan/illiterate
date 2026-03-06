#include <iostream>
#include <valarray>
#include <minmax.h>
using namespace std;

static int total = 0;

void checkRowsCols(valarray<int> numbers, int d) {
    int m = numbers[0];
    int n = numbers[0] + numbers[1] + numbers[2];
    // Rows.
    for(int i = 0; i < 3; i++) {
        m = max(m, numbers[i] + numbers[i+1] + numbers[i+2]);
        m = min(n, numbers[i] + numbers[i+1] + numbers[i+2]);
    }
    // Columns.
    for(int j = 0; j < 3; j++) {
        m = max(m, numbers[j] + numbers[j+3] + numbers[j+6]);
        n = min(n, numbers[j] + numbers[j+3] + numbers[j+6]);
    }

    m = max(m, numbers[0] + numbers[4] + numbers[8]);
    m = max(m, numbers[2] + numbers[4] + numbers[6]);

    n = min(n, numbers[0] + numbers[4] + numbers[8]);
    n = min(n, numbers[2] + numbers[4] + numbers[6]);

    cout << "min is " << n << endl;
    cout << "is " << m-n << " less than" << d << "?" << endl;
    if(m-n <= d) {
        cout << "yes" << endl;
        total++;
        return;
    } else {
        return;
    }
}

int combinations(int ind, valarray<int> numbers, int almost) {
    for(int i = 0; i < 8; i++) {
        // Shift.
        int first = numbers[0];
        numbers = numbers.shift(1);
        numbers[8] = first;
        checkRowsCols(numbers, almost);
    }
    // Call again.
    if(ind < 8) {
        valarray<int> newnumbers = numbers;
        int temp = newnumbers[0];
        newnumbers[0] = newnumbers[8];
        newnumbers[8] = temp;
        return combinations(++ind, newnumbers, almost);
    }

    return 0;
}

int main() {
    valarray<int> numb(9);
    int almost;
    cin >> almost;

    for(int i = 0; i < 9; i++) {
        cin >> numb[i];
    }
    combinations(0, numb, almost);
    cout << total << endl;
    return 0;
}
#include <iostream>
using namespace std;

/*
    1 - 15 - 7 - 9 - 2 - 5 - 10

    Using biggest num, change of:
    14 - 0 - 8 - 6 - 8 - 5 - 0

    best answer is
    15 - 15 - 15 - 9 - 10 - 10 - 10

    Max of cow #...
    0-6 = their own number.

    (0, 1) = 15
    (1, 2) = 15
    (2, 3) = 9
    (3, 4) = 9
    (4, 5) = 5
    (5, 6) = 10

    (0, 1, 2) = 15 -> 
    (1, 2, 3) = 15 ->
    (2, 3, 4) = 9 ->
    (3, 4, 5) = 9 -> 
    (4, 5, 6) = 10 -> 


*/

int main() {
    int t, n, k;
    int * skilllevels;
    cin >> t;

    for(int i = 0; i < t; i++) {
        // Number of cows, max team size.
        cin >> n >> k;
        int teams = n - k;
        int * teamvals = new int[teams];
        skilllevels = new int[n];

        // Get the skill level of each cow.
        for(int j = 0; j < n; j++) {
            cin >> skilllevels[j];
        }
    }
    return 0;
}
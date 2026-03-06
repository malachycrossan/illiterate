#include <iostream>
using namespace std;

// Team 8 - 1/30/2026

int main() {
    int total, tests, members, before, after;
    cin >> tests;
    // Each test case.
    for(int i = 0; i < tests; i++) {
        cin >> members;
        total = 0;
        // Loop through all members.
        for(int j = 0; j < members; j++) {
            cin >> before >> after;
            if(after-before == 19) {
                total++;
            }
        }
        // Print total members with 19 pounds gained.
        cout << total << endl;
    }

    return 0;
}
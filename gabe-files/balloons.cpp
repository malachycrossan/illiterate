#include <iostream>
using namespace std;

int main() {
    int cases, n, x, y, cur;
    bool easy, hard;
    cin >> cases;


    for(int i = 0; i < cases; i++) {
        cin >> n >> x >> y;

        easy = false;
        hard = false;
        for(int j = 0; j < n; j++) {
            cin >> cur;
            if(j == 0 && cur == x) {
                easy = true;
            } else if(j == n-1 && cur == y) {
                hard = true;
            }
        }


        if(easy && hard) {
            cout << "BOTH" << endl;
        } else if(easy && !hard) {
            cout << "EASY" << endl;
        } else if(!easy && hard) {
            cout << "HARD" << endl;
        } else {
            cout << "OKAY" << endl;
        }
    }

    return 0;
}
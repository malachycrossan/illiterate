#include <iostream>
using namespace std;

int main() {
    int c, b, z, pow;
    cin >> c;

    for(int i = 0; i < c; i++) {
        cin >> b >> z;
        pow = b;

        // Increase power.
        while(pow < z) { pow *= b; }

        // Check if it is a perfect power.
        if(pow == z && b != z) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}
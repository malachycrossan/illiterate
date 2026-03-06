#include <iostream>
using namespace std;

int factorial(int num) {
    if(num == 0 || num == 1) { return 1; }
    return num * factorial(num-1);
}

int aChooseB(int a, int b) {
    int fa = factorial(a);
    int fb = factorial(b);
    return fa / (fb*(factorial(a-b)));
}

long long combinations(long long start) {
    if(start == 0) { return 0; }
    if(start == 1) { return 1; }
    long long finalans = 0;
    for(int j = 1; j <= start; j++) {
        finalans += aChooseB(start, j)*(combinations(start-j)+1);
    }
    return finalans;
}

int main() {
    int n, b;
    long long * ans = new long long[11]{};
    cin >> n;

    for(int i = 0; i < n; i++) {
        // There are b numbers.
        cin >> b;
        if(ans[b-1] != 0) {
            // We already calculated the answer.
            cout << (i+1) << " " << b << " " << ans[b-1] << endl;
        } else {
            // Calculate it.
            ans[b-1] = combinations(b);
            cout << (i+1) << " " << b << " " << combinations(b) << endl;
        }
    }
    return 0;
}
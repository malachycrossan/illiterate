#include <iostream>
#include <vector>
#include <list>
using namespace std;
long long memo[1000001];
long long totals[1000001];
long long total = 0;
int days;

int main() {
    cin >> days;
    memo[0] = 0;
    int farthest = 1;

    while(days != 0) {
        total = totals[farthest-1];
        for(int i = farthest; i < days+1; i++) { 
            memo[i] = i + memo[i-1];
            total += memo[i];
            totals[i] = total;
            farthest = i;
        }
        cout << totals[days] << endl;
        cin >> days;
    }

    return 0;
}
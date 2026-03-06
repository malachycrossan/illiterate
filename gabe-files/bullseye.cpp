#include <iostream>
#include <math.h>
#include <cmath>
using namespace std;

int main() {
    int cases;
    long long radius, paint, rings, curr; // current radius, current paint
    //long long * memo = new long long[2000000000000000001];

    cin >> cases;

    for(int i = 0; i < cases; i++) {
        cin >> radius >> paint;

        long long low = 1;
        long long high = sqrt(paint/2);
        long long mid = low + (high-low+1)/2;
        long long total = (long long)mid * ((long long)2*mid + (long long)2*radius - 1);
        // ((mid-1)/2 + 1)*(mid - radius + (2*radius))
        cout << "Total = " << total << endl;

        while(low < high) {
            cout << "While " << low << " < " << high << endl; 

            if(total > paint) {
                high = mid-1;
                cout << "High = " << mid-1 << endl;
            } else if(total <= paint) {
                low = mid;
                cout << "Low = " << mid << endl;
            }

            mid = low + (high-low+1)/2;
            cout << "Mid = " << mid << endl;
            total = (long long)mid * ((long long)2*mid + (long long)2*radius - 1);
            cout << "Total = " << total << endl;
        }

        cout << "Case #" << i+1 << ": " << low << endl;
    }

    return 0;
}
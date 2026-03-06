#include <iostream>
#include <iomanip>
using namespace std;

int main() {

    int sections;
    double smallestspd = 2000.0f;
    double t, low, mid, total, time;
    double high = 2000000.0f;
    double * dist;
    double * spd;
    // Get sections and total time.
    cin >> sections >> time;

    // Create distance and speed arrays.
    dist = new double[sections];
    spd = new double[sections];

    // Store each distance and speedometer reading.
    for(int i = 0; i < sections; i++) {
        cin >> dist[i] >> spd[i];
        // Used to set low.
        if(spd[i] < smallestspd) {
            smallestspd = spd[i];
        }
    }

    low = smallestspd*(-1);
    // Always print 9 decimal places.
    cout << fixed << setprecision(9);

    // Time = distance / (speed+c)
    // Guess for c.
    for(int j = 0; j < 100; j++) {
        
        total = 0;
        mid = (double)(high+low)/(2.0f);

        for(int k = 0; k < sections; k++) {
            total += (double)dist[k] / (double)(spd[k]+mid);
        }
        
        if(total > time) {
            //cout << total << " > " << time << endl;
            low = mid;
        } else if(total < time) {
            //cout << total << " < " << time << endl;
            high = mid;
        }
    }
    
    // Print final number.
    cout << mid << endl;
    return 0;
}
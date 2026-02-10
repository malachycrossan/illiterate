// 2026-02-06-Competition/robot.cpp
// Author: ?
#include <iostream>
#include <math.h>
#include <iomanip>
using namespace std;

struct Target {
    int x, y, penalty;
};

int n, x, y, p, curx, cury;
double * times; // Optimal times. 
Target * targets;

double timeToArrive(int x1, int y1, int x2, int y2) {
    int v = abs(y1 - y2); // Vertical line of the triangle.
    int h = abs(x1 - x2); // Horizontal line of the triangle.

    // Return hypotenuse.     c = sqrt(a^2 + b^2)
    return sqrt((v*v) + (h*h)) + 1; 
}

double cost(int targ, int curp) {
    double ti, ti2; // time
    int p = curp;
    Target cur = targets[targ];

    // We've already got the optimal time for this target.
    if(times[targ] != 0) {
        return times[targ];
    }

    if(targ == n) {
        times[targ] = timeToArrive(targets[targ].x, targets[targ].y, 100, 100); 
        return times[targ];
    } else {
        // Time from current target to next target down the list.
        ti = timeToArrive(cur.x, cur.y, targets[targ+1].x, targets[targ+1].y);
        // Add the optimal time from that target to the time.
        ti += cost(targ+1, curp);
        // Add that target's penalty for later.
        p += targets[targ+1].penalty;
    }
    
    // Find optimal time between other targets.
    for(int i = targ+2; i < n+1; i++) {
        // See if it is more optimal to skip and go to other targets.
        ti2 = timeToArrive(cur.x, cur.y, targets[i].x, targets[i].y); // Adds 1 second per extra target.
        ti2 += cost(i, curp);
        // Continue with the smallest of the two. 
        ti = min(ti, ti2+p);
        // Add penalty before moving on to next target.
        // If there are more targets, then we add previous penalties.
        p += targets[i].penalty;
    }

    // Return whether an optimal route was found or if it is more optimal to go straight to the goal.
    times[targ] = min(ti, timeToArrive(cur.x, cur.y, 100, 100)+p);
    return times[targ];
}

int main() {
    Target t;
    cin >> n; // Number of targets.
    while(n != 0) {
        // Reset values.
        curx = 0;
        cury = 0;
        targets = new Target[n+1]; // + 1 to have origin at the beginning.
        times = new double[n+1];
        targets[0] = { 0, 0, 0 };
        times[0] = 0;
        
        // Start loop.
        for(int i = 1; i < n+1; i++) {
            cin >> x >> y >> p; // x, y, and penalty of each target.
            // Create the new target.
            t = { x, y, p };
            targets[i] = t;
            // Help initialize times array to all 0's.
            times[i] = 0;
        }

        // Print the optimal cost.
        double res = cost(0, 0);
        // Why is C++ so weird with printing specific decimal places?
        cout << fixed << setprecision(3) << res << endl;
        // Get new input.
        cin >> n;
    }
    return 0;
}
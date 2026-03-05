#include <algorithm>
#include <cmath>
#include <functional>
#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;

typedef double T;
typedef long long ll;

struct P {
    T x, y;
    P() : x(0), y(0) {}
    P(T x, T y) : x(x), y(y) {}

    P operator+(P b)  const { return {x+b.x, y+b.y}; }
    P operator-(P b)  const { return {x-b.x, y-b.y}; }
    P operator*(T s)  const { return {x*s, y*s}; }
    P operator/(T s)  const { return {x/s, y/s}; }
    P& operator+=(P b)      { x+=b.x; y+=b.y; return *this; }
    P& operator-=(P b)      { x-=b.x; y-=b.y; return *this; }
    P& operator*=(T s)      { x*=s; y*=s; return *this; }
    P operator-() const     { return {-x, -y}; }

    bool operator<(P b)  const { return x<b.x || (x==b.x && y<b.y); }
    bool operator==(P b) const { return x==b.x && y==b.y; }
    bool operator!=(P b) const { return !(*this==b); }

    double mag2() const { return (double)x*x + (double)y*y; }
    double mag()  const { return sqrt(mag2()); }
};

P operator*(T s, P v) { return v * s; }

double dist(P a, P b) { return (a-b).mag(); }

double min_distance(P trees[], int t) {
    double min_distance = 100000;
    for (int i = 0; i < t; i++) {
        for (int j = i + 1; j < t; j++) {
            double distance = dist(trees[i], trees[j]);
            if (distance < min_distance) min_distance = distance;
        }
    }
    return min_distance;
}

int main () {
    int c; // test cases
    int t;
    cin >> c;
    for (int i = 1; i <= c; i++) {
        cin >> t; // trees
        P tree[t]; 
        for (int j = 0; j < t; j++) {
            int x, y;
            cin >> x;
            cin >> y;
            tree[j] = P(x,y);
        }
        double shortest_distance = min_distance(tree, t);
        double max_area = (shortest_distance/2)*(shortest_distance/2)*3.141592653589793;

        cout << fixed;
        cout << setprecision(3);
        cout << "Campus #" << i << ":" << endl << "Maximum territory area = " << max_area << endl << endl;
    }
}

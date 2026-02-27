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

pair<P,P> closest_pair(vector<P> pts) {
    sort(pts.begin(), pts.end());
    int n=pts.size();
    pair<P,P> best={pts[0],pts[1]};
    double best_d=dist(pts[0],pts[1]);
    vector<P> strip;

    function<void(int,int)> solve = [&](int lo, int hi) {
        if (hi-lo <= 3) {
            for (int i=lo; i<hi; i++)
                for (int j=i+1; j<hi; j++) {
                    double d=dist(pts[i],pts[j]);
                    if (d < best_d) { best_d=d; best={pts[i],pts[j]}; }
                }
            sort(pts.begin()+lo, pts.begin()+hi, [](P a,P b){ return a.y<b.y; });
            return;
        }
        int mid=(lo+hi)/2;
        double mx=pts[mid].x;
        solve(lo,mid);
        solve(mid,hi);
        inplace_merge(pts.begin()+lo, pts.begin()+mid, pts.begin()+hi,
                      [](P a,P b){ return a.y<b.y; });
        strip.clear();
        for (int i=lo; i<hi; i++)
            if (fabs(pts[i].x-mx) < best_d) strip.push_back(pts[i]);
        for (int i=0; i<(int)strip.size(); i++)
            for (int j=i+1; j<(int)strip.size() && strip[j].y-strip[i].y<best_d; j++) {
                double d=dist(strip[i],strip[j]);
                if (d < best_d) { best_d=d; best={strip[i],strip[j]}; }
            }
    };
    solve(0, n);
    return best;
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
        vector<P> tree_vec(tree, tree + t);
        auto pair = closest_pair(tree_vec);
        double shortest_distance = dist(pair.first, pair.second);
        double max_area = (shortest_distance/2)*(shortest_distance/2)*3.141592653589793;

        cout << fixed;
        cout << setprecision(3);
        cout << "Campus #" << i << ":" << endl << "Maximum territory area = " << max_area << endl << endl;
    }
}

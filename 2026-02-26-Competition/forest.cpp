#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

typedef double T;
typedef long long ll;

const double EPS = 1e-9;
const double PI  = acos(-1.0);

int  sgn(double a)           { return (a > EPS) - (a < -EPS); }

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


    T cross(P b) const { return x*b.y - y*b.x; }

    double mag2() const { return (double)x*x + (double)y*y; }
    double mag()  const { return sqrt(mag2()); }
};

double dist(P a, P b) { return (a-b).mag(); }

int orient(P a, P b, P c) { return sgn((double)(b-a).cross(c-a)); }


struct poly {
    vector<P> v;
    poly(vector<P> verts) : v(verts) {}
    int size() const { return (int)v.size(); }

    double signed_area() const {
        double a=0;
        for (int i=0; i<size(); i++) a += (double)v[i].cross(v[(i+1)%size()]);
        return a / 2.0;
    }
    double area() const { return fabs(signed_area()); }
};

poly convex_hull(vector<P> pts, bool keep_collinear=false) {
    int n=pts.size();
    if (n < 2) return {pts};
    sort(pts.begin(), pts.end());
    vector<P> h;
    for (int phase=0; phase<2; phase++) {
        int start=h.size();
        for (P& p : pts) {
            while ((int)h.size() >= start+2) {
                int o = orient(h[h.size()-2], h.back(), p);
                if (o<0 || (keep_collinear && o==0)) h.pop_back();
                else break;
            }
            h.push_back(p);
        }
        h.pop_back();
        reverse(pts.begin(), pts.end());
    }
    return {h};
}

int main () {
    int n, c;
    cin >> n;
    cin >> c;

    P tree[n];
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x;
        cin >> y;
        tree[i] = P(x,y);
    }
    vector<P> tree_vec(tree, tree + n);
    poly fence = convex_hull(tree_vec);

    double area = fence.area() + PI*c*c;
    double perimeter = 2*PI*c;
    for (int j = 0; j < fence.size(); j++) {
        double segment_length = dist(fence.v.at(j), fence.v.at((j + 1) % fence.size()));
        perimeter += segment_length;
        area += segment_length * c;
    }
    cout << perimeter << " " << area;
}

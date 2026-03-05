#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;

typedef double T;
typedef long long ll;

const double EPS = 1e-9;

bool leq(double a, double b) { return a <= b + EPS; }

struct P {
    T x, y;
    P() {}
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

    T dot(P b)   const { return x*b.x + y*b.y; }

    T cross(P b) const { return x*b.y - y*b.x; }

    double mag2() const { return (double)x*x + (double)y*y; }
    double mag()  const { return sqrt(mag2()); }

    P unit() const { double m=mag(); return {(T)(x/m), (T)(y/m)}; }

};

P operator*(T s, P v) { return v * s; }

double dist(P a, P b) { return (a-b).mag(); }



struct isect {
    int count = 0;
    P pt[2];
    isect() : count(0) {}
    isect(P a) : count(1), pt{a, {}} {}
    isect(P a, P b) : count(2), pt{a, b} {}
};

struct line {
    P origin, dir;

    line(P a, P b) : origin(a), dir(b-a) {}

    P at_param(double t) const { return origin + dir*(T)t; }
    P unit_dir()         const { return dir.unit(); }

    double dist_to(P p) const { return fabs((double)dir.cross(p-origin)) / dir.mag(); }

    P project(P p) const {
        double t = (double)(p-origin).dot(dir) / dir.mag2();
        return at_param(t);
    }

};

struct seg {
    P a, b;
    seg(P a, P b) : a(a), b(b) {}

    line to_line() const { return line(a, b); }
    double length() const { return dist(a, b); }

    bool contains(P p) const {
        double len = length();
        if (len < EPS) return dist(a,p) < EPS;
        if (fabs((double)(p-a).cross(b-a)) > EPS*len) return false;
        double t = (double)(p-a).dot(b-a);
        return t > -EPS && t < len*len + EPS;
    }
};

struct circle {
    P center;
    double radius;
    circle(P c, double r) : center(c), radius(r) {}

    bool contains(P p)    const { return  leq(dist(center,p), radius); }

};

isect intersect(circle c, line l) {
    double d = l.dist_to(c.center);
    if (d > c.radius+EPS) return {};
    P foot = l.project(c.center);
    double h = sqrt(max(0.0, c.radius*c.radius - d*d));
    if (h < EPS) return {foot};
    return {foot + l.unit_dir()*(T)h, foot - l.unit_dir()*(T)h};
}

isect intersect(circle c, seg s) {
    isect lh = intersect(c, s.to_line()), r;
    for (int i=0; i<lh.count; i++)
        if (s.contains(lh.pt[i])) r.pt[r.count++] = lh.pt[i];
    return r;
}

int main () {
    double x, y, r, x1, y1, x2, y2;
    while (cin.peek() != EOF){
        cin >> x;
        cin >> y;
        cin >> r;
        cin >> x1;
        cin >> y1;
        cin >> x2;
        cin >> y2;

        circle c = circle(P(x,y), r);
        seg s = seg(P(x1,y1), P(x2,y2));
        isect result = intersect(c, s);
        if (result.count > 0) cout << "The line segment intersects the circle." << endl;
        else cout << "The line segment does not intersect the circle." << endl;
    }
}

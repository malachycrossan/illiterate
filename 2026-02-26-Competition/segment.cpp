#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;

typedef double T;
typedef long long ll;

const double EPS = 1e-9;
const double PI  = acos(-1.0);

bool eq (double a, double b) { return fabs(a-b) < EPS; }
bool leq(double a, double b) { return a <= b + EPS; }
int  sgn(double a)           { return (a > EPS) - (a < -EPS); }
double to_deg(double r)      { return r * 180.0 / PI; }
double to_rad(double d)      { return d * PI / 180.0; }

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

    // cross > 0 means b is CCW from this, < 0 means CW, = 0 means parallel
    T cross(P b) const { return x*b.y - y*b.x; }

    double mag2() const { return (double)x*x + (double)y*y; }
    double mag()  const { return sqrt(mag2()); }

    P unit() const { double m=mag(); return {(T)(x/m), (T)(y/m)}; }

    // 90 degrees CCW. For CW use {y, -x}.
    P perp() const { return {-y, x}; }

    P rotate(double theta) const {
        double c=cos(theta), s=sin(theta);
        return {(T)(x*c - y*s), (T)(x*s + y*c)};
    }

    P rotate(double theta, P center) const {
        return (*this - center).rotate(theta) + center;
    }
};

P operator*(T s, P v) { return v * s; }

double dist(P a, P b) { return (a-b).mag(); }

// angle in [0, pi] between vectors a and b
double angle(P a, P b) {
    return acos(max(-1.0, min(1.0, a.dot(b) / a.mag() / b.mag())));
}

// signed area of triangle abc. positive = CCW, negative = CW.
double tri_area(P a, P b, P c) { return (b-a).cross(c-a) / 2.0; }

// +1 CCW, -1 CW, 0 collinear
int orient(P a, P b, P c) { return sgn((double)(b-a).cross(c-a)); }

// given three side lengths, returns the angle opposite to side c
double law_of_cosines(double a, double b, double c) {
    return acos(max(-1.0, min(1.0, (a*a + b*b - c*c) / (2*a*b))));
}

// is p inside triangle abc? returns true for boundary points too
bool in_triangle(P p, P a, P b, P c) {
    int d1=orient(a,b,p), d2=orient(b,c,p), d3=orient(c,a,p);
    return (d1>=0 && d2>=0 && d3>=0) || (d1<=0 && d2<=0 && d3<=0);
}

// are p and q on the same side of line ab?
bool same_side(P p, P q, P a, P b) {
    return sgn((double)(b-a).cross(p-a)) == sgn((double)(b-a).cross(q-a));
}

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
    P at_dist(double d)  const { return origin + dir.unit()*(T)d; }
    P unit_dir()         const { return dir.unit(); }

    bool contains(P p) const { return fabs((double)dir.cross(p-origin)) < EPS*dir.mag(); }

    double dist_to(P p) const { return fabs((double)dir.cross(p-origin)) / dir.mag(); }

    // foot of perpendicular from p onto this line
    P project(P p) const {
        double t = (double)(p-origin).dot(dir) / dir.mag2();
        return at_param(t);
    }

    P reflect(P p) const { return project(p)*2 - p; }
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
    while (true) {
        cin >> x; if (x == EOF) break;
        cin >> y; if (y == EOF) break;
        cin >> r; if (r == EOF) break;
        cin >> x1; if (x1 == EOF) break;
        cin >> y1; if (y1 == EOF) break;
        cin >> x2; if (x2 == EOF) break;
        cin >> y2; if (y2 == EOF) break;

        circle c = circle(P(x,y), r);
        seg s = seg(P(x1,y1), P(x2,y2));
        isect result = intersect(c, s);
        if (result.count > 0) cout << "The line segment intersects the circle." << endl;
        else cout << "The line segment does not intersect the circle." << endl;

    }
}

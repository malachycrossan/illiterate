// line.cpp
// Tests: line-line intersection, line distance, projection, reflection,
//        segment-segment intersection, segment-line intersection,
//        segment contains, segment closest point, orient, same_side

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cmath>
#include <functional>
using namespace std;

typedef double T;
typedef long long ll;
const double EPS = 1e-9;
const double PI  = acos(-1.0);
bool eq (double a, double b) { return fabs(a-b) < EPS; }
bool leq(double a, double b) { return a <= b + EPS; }
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
    bool operator<(P b)  const { return x<b.x || (x==b.x && y<b.y); }
    bool operator==(P b) const { return x==b.x && y==b.y; }
    bool operator!=(P b) const { return !(*this==b); }
    T dot(P b)   const { return x*b.x + y*b.y; }
    T cross(P b) const { return x*b.y - y*b.x; }
    double mag2() const { return (double)x*x + (double)y*y; }
    double mag()  const { return sqrt(mag2()); }
    P unit() const { double m=mag(); return {(T)(x/m), (T)(y/m)}; }
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
int orient(P a, P b, P c) { return sgn((double)(b-a).cross(c-a)); }
bool same_side(P p, P q, P a, P b) {
    return sgn((double)(b-a).cross(p-a)) == sgn((double)(b-a).cross(q-a));
}
bool in_triangle(P p, P a, P b, P c) {
    int d1=orient(a,b,p), d2=orient(b,c,p), d3=orient(c,a,p);
    return (d1>=0 && d2>=0 && d3>=0) || (d1<=0 && d2<=0 && d3<=0);
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
    P project(P p) const {
        double t = (double)(p-origin).dot(dir) / dir.mag2();
        return at_param(t);
    }
    P reflect(P p) const { return project(p)*2 - p; }
};
isect intersect(line a, line b) {
    double det = (double)a.dir.cross(b.dir);
    if (fabs(det) < EPS) return {};
    P d = b.origin - a.origin;
    double t = (double)d.cross(b.dir) / det;
    return { a.at_param(t) };
}
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
    P closest(P p) const {
        P ab = b-a;
        double len2 = ab.mag2();
        if (len2 < EPS) return a;
        double t = max(0.0, min(1.0, (double)(p-a).dot(ab) / len2));
        return a + ab*(T)t;
    }
    double dist_to(P p) const { return dist(p, closest(p)); }
};
isect intersect(seg s, seg t) {
    int d1=orient(t.a,t.b,s.a), d2=orient(t.a,t.b,s.b);
    int d3=orient(s.a,s.b,t.a), d4=orient(s.a,s.b,t.b);
    if (d1*d2 < 0 && d3*d4 < 0)
        return intersect(s.to_line(), t.to_line());
    isect r;
    auto try_add = [&](P p) {
        for (int i=0; i<r.count; i++)
            if (eq(r.pt[i].x,p.x) && eq(r.pt[i].y,p.y)) return;
        if (r.count < 2) r.pt[r.count++] = p;
    };
    if (d1==0 && t.contains(s.a)) try_add(s.a);
    if (d2==0 && t.contains(s.b)) try_add(s.b);
    if (d3==0 && s.contains(t.a)) try_add(t.a);
    if (d4==0 && s.contains(t.b)) try_add(t.b);
    return r;
}
isect intersect(seg s, line l) {
    double da = (double)l.dir.cross(s.a - l.origin);
    double db = (double)l.dir.cross(s.b - l.origin);
    if (sgn(da)*sgn(db) > 0) return {};
    if (fabs(da-db) < EPS) return {s.a, s.b};
    double t = da / (da - db);
    return { s.a + (s.b-s.a)*(T)t };
}

int main() {
    // Input format:
    // Line 1: number of test cases
    // Each test case:
    //   CMD on first line, then arguments
    //
    // LINE_ISECT ax ay bx by cx cy dx dy   -> count [px py] [px2 py2]
    // LINE_DIST  ax ay bx by px py          -> distance
    // LINE_PROJ  ax ay bx by px py          -> foot_x foot_y
    // LINE_REFL  ax ay bx by px py          -> ref_x ref_y
    // SEG_ISECT  ax ay bx by cx cy dx dy   -> count [px py] [px2 py2]
    // SEG_LINE   ax ay bx by cx cy dx dy   -> count [px py] [px2 py2]
    // SEG_DIST   ax ay bx by px py          -> distance
    // SEG_CLOSE  ax ay bx by px py          -> closest_x closest_y
    // SEG_CONT   ax ay bx by px py          -> YES/NO
    // ORIENT     ax ay bx by cx cy          -> CCW/CW/COLLINEAR
    // SAME_SIDE  px py qx qy ax ay bx by   -> YES/NO
    // IN_TRI     px py ax ay bx by cx cy   -> YES/NO

    int T; scanf("%d",&T);
    while (T--) {
        char cmd[20]; scanf("%s",cmd);
        double a1,a2,b1,b2,c1,c2,d1,d2,p1,p2;

        if (strcmp(cmd,"LINE_ISECT")==0) {
            scanf("%lf%lf%lf%lf%lf%lf%lf%lf",&a1,&a2,&b1,&b2,&c1,&c2,&d1,&d2);
            isect h = intersect(line(P(a1,a2),P(b1,b2)), line(P(c1,c2),P(d1,d2)));
            printf("%d", h.count);
            for (int i=0;i<h.count;i++) printf(" %.6f %.6f", h.pt[i].x+EPS, h.pt[i].y+EPS);
            printf("\n");
        }
        else if (strcmp(cmd,"LINE_DIST")==0) {
            scanf("%lf%lf%lf%lf%lf%lf",&a1,&a2,&b1,&b2,&p1,&p2);
            printf("%.6f\n", line(P(a1,a2),P(b1,b2)).dist_to(P(p1,p2)) + EPS);
        }
        else if (strcmp(cmd,"LINE_PROJ")==0) {
            scanf("%lf%lf%lf%lf%lf%lf",&a1,&a2,&b1,&b2,&p1,&p2);
            P f = line(P(a1,a2),P(b1,b2)).project(P(p1,p2));
            printf("%.6f %.6f\n", f.x+EPS, f.y+EPS);
        }
        else if (strcmp(cmd,"LINE_REFL")==0) {
            scanf("%lf%lf%lf%lf%lf%lf",&a1,&a2,&b1,&b2,&p1,&p2);
            P r = line(P(a1,a2),P(b1,b2)).reflect(P(p1,p2));
            printf("%.6f %.6f\n", r.x+EPS, r.y+EPS);
        }
        else if (strcmp(cmd,"SEG_ISECT")==0) {
            scanf("%lf%lf%lf%lf%lf%lf%lf%lf",&a1,&a2,&b1,&b2,&c1,&c2,&d1,&d2);
            isect h = intersect(seg(P(a1,a2),P(b1,b2)), seg(P(c1,c2),P(d1,d2)));
            printf("%d", h.count);
            // sort points for deterministic output
            if (h.count==2 && h.pt[1] < h.pt[0]) swap(h.pt[0],h.pt[1]);
            for (int i=0;i<h.count;i++) printf(" %.6f %.6f", h.pt[i].x+EPS, h.pt[i].y+EPS);
            printf("\n");
        }
        else if (strcmp(cmd,"SEG_LINE")==0) {
            scanf("%lf%lf%lf%lf%lf%lf%lf%lf",&a1,&a2,&b1,&b2,&c1,&c2,&d1,&d2);
            isect h = intersect(seg(P(a1,a2),P(b1,b2)), line(P(c1,c2),P(d1,d2)));
            printf("%d", h.count);
            if (h.count==2 && h.pt[1] < h.pt[0]) swap(h.pt[0],h.pt[1]);
            for (int i=0;i<h.count;i++) printf(" %.6f %.6f", h.pt[i].x+EPS, h.pt[i].y+EPS);
            printf("\n");
        }
        else if (strcmp(cmd,"SEG_DIST")==0) {
            scanf("%lf%lf%lf%lf%lf%lf",&a1,&a2,&b1,&b2,&p1,&p2);
            printf("%.6f\n", seg(P(a1,a2),P(b1,b2)).dist_to(P(p1,p2)) + EPS);
        }
        else if (strcmp(cmd,"SEG_CLOSE")==0) {
            scanf("%lf%lf%lf%lf%lf%lf",&a1,&a2,&b1,&b2,&p1,&p2);
            P c = seg(P(a1,a2),P(b1,b2)).closest(P(p1,p2));
            printf("%.6f %.6f\n", c.x+EPS, c.y+EPS);
        }
        else if (strcmp(cmd,"SEG_CONT")==0) {
            scanf("%lf%lf%lf%lf%lf%lf",&a1,&a2,&b1,&b2,&p1,&p2);
            printf("%s\n", seg(P(a1,a2),P(b1,b2)).contains(P(p1,p2)) ? "YES" : "NO");
        }
        else if (strcmp(cmd,"ORIENT")==0) {
            scanf("%lf%lf%lf%lf%lf%lf",&a1,&a2,&b1,&b2,&c1,&c2);
            int o = orient(P(a1,a2),P(b1,b2),P(c1,c2));
            if (o>0) printf("CCW\n");
            else if (o<0) printf("CW\n");
            else printf("COLLINEAR\n");
        }
        else if (strcmp(cmd,"SAME_SIDE")==0) {
            scanf("%lf%lf%lf%lf%lf%lf%lf%lf",&p1,&p2,&a1,&a2,&b1,&b2,&c1,&c2);
            // p, q, line_a, line_b
            printf("%s\n", same_side(P(p1,p2),P(a1,a2),P(b1,b2),P(c1,c2)) ? "YES" : "NO");
        }
        else if (strcmp(cmd,"IN_TRI")==0) {
            scanf("%lf%lf%lf%lf%lf%lf%lf%lf",&p1,&p2,&a1,&a2,&b1,&b2,&c1,&c2);
            printf("%s\n", in_triangle(P(p1,p2),P(a1,a2),P(b1,b2),P(c1,c2)) ? "YES" : "NO");
        }
    }
}

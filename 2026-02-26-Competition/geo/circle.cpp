// circle.cpp
// Tests: circle-circle intersection, circle-line intersection,
//        circle-segment intersection, circle contains, sector/segment areas,
//        closest_pair

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
};
P operator*(T s, P v) { return v * s; }
double dist(P a, P b) { return (a-b).mag(); }
int sgn2(double a) { return (a>EPS)-(a<-EPS); }
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
};
struct circle {
    P center;
    double radius;
    circle(P c, double r) : center(c), radius(r) {}
    bool contains(P p)    const { return  leq(dist(center,p), radius); }
    bool on_boundary(P p) const { return   eq(dist(center,p), radius); }
    double sector_area(double angle_rad) const { return 0.5 * radius * radius * angle_rad; }
    double triangle_area(double angle_rad) const { return 0.5 * radius * radius * sin(angle_rad); }
    double segment_area(double angle_rad) const { return sector_area(angle_rad) - triangle_area(angle_rad); }
};
isect intersect(circle c1, circle c2) {
    double d = dist(c1.center, c2.center);
    if (d > c1.radius+c2.radius+EPS) return {};
    if (d < fabs(c1.radius-c2.radius)-EPS) return {};
    double a  = (c1.radius*c1.radius - c2.radius*c2.radius + d*d) / (2*d);
    double h2 = max(0.0, c1.radius*c1.radius - a*a);
    P mid = c1.center + (c2.center-c1.center).unit()*(T)a;
    if (h2 < EPS) return {mid};
    P perp = (c2.center-c1.center).unit().perp() * (T)sqrt(h2);
    return {mid+perp, mid-perp};
}
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

int main() {
    // CMD args
    // CIRC_CIRC  cx1 cy1 r1 cx2 cy2 r2  -> count [px py] [px2 py2]  (sorted by x then y)
    // CIRC_LINE  cx cy r ax ay bx by     -> count [px py] [px2 py2]
    // CIRC_SEG   cx cy r ax ay bx by     -> count [px py] [px2 py2]
    // CIRC_CONT  cx cy r px py           -> INSIDE/BOUNDARY/OUTSIDE
    // CIRC_AREA  r angle_deg             -> sector_area segment_area
    // CLOSEST_PAIR n x1 y1 ... xn yn     -> d (distance of closest pair)

    int T; scanf("%d",&T);
    while(T--) {
        char cmd[20]; scanf("%s",cmd);
        if (strcmp(cmd,"CIRC_CIRC")==0) {
            double cx1,cy1,r1,cx2,cy2,r2;
            scanf("%lf%lf%lf%lf%lf%lf",&cx1,&cy1,&r1,&cx2,&cy2,&r2);
            isect h = intersect(circle(P(cx1,cy1),r1), circle(P(cx2,cy2),r2));
            if (h.count==2 && h.pt[1] < h.pt[0]) swap(h.pt[0],h.pt[1]);
            printf("%d", h.count);
            for (int i=0;i<h.count;i++) printf(" %.6f %.6f", h.pt[i].x+EPS, h.pt[i].y+EPS);
            printf("\n");
        }
        else if (strcmp(cmd,"CIRC_LINE")==0) {
            double cx,cy,r,ax,ay,bx,by;
            scanf("%lf%lf%lf%lf%lf%lf%lf",&cx,&cy,&r,&ax,&ay,&bx,&by);
            isect h = intersect(circle(P(cx,cy),r), line(P(ax,ay),P(bx,by)));
            if (h.count==2 && h.pt[1] < h.pt[0]) swap(h.pt[0],h.pt[1]);
            printf("%d", h.count);
            for (int i=0;i<h.count;i++) printf(" %.6f %.6f", h.pt[i].x+EPS, h.pt[i].y+EPS);
            printf("\n");
        }
        else if (strcmp(cmd,"CIRC_SEG")==0) {
            double cx,cy,r,ax,ay,bx,by;
            scanf("%lf%lf%lf%lf%lf%lf%lf",&cx,&cy,&r,&ax,&ay,&bx,&by);
            isect h = intersect(circle(P(cx,cy),r), seg(P(ax,ay),P(bx,by)));
            if (h.count==2 && h.pt[1] < h.pt[0]) swap(h.pt[0],h.pt[1]);
            printf("%d", h.count);
            for (int i=0;i<h.count;i++) printf(" %.6f %.6f", h.pt[i].x+EPS, h.pt[i].y+EPS);
            printf("\n");
        }
        else if (strcmp(cmd,"CIRC_CONT")==0) {
            double cx,cy,r,px,py;
            scanf("%lf%lf%lf%lf%lf",&cx,&cy,&r,&px,&py);
            circle c(P(cx,cy),r);
            P p(px,py);
            if (c.on_boundary(p)) printf("BOUNDARY\n");
            else if (c.contains(p)) printf("INSIDE\n");
            else printf("OUTSIDE\n");
        }
        else if (strcmp(cmd,"CIRC_AREA")==0) {
            double r, deg; scanf("%lf%lf",&r,&deg);
            double rad = deg * PI / 180.0;
            circle c(P(0,0),r);
            printf("%.6f %.6f\n", c.sector_area(rad)+EPS, c.segment_area(rad)+EPS);
        }
        else if (strcmp(cmd,"CLOSEST_PAIR")==0) {
            int n; scanf("%d",&n);
            vector<P> pts(n);
            for (int i=0;i<n;i++) scanf("%lf%lf",&pts[i].x,&pts[i].y);
            auto pr = closest_pair(pts);
            printf("%.6f\n", dist(pr.first,pr.second)+EPS);
        }
    }
}

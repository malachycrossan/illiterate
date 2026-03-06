#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <vector>
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
    P() : x(0), y(0) {}
    P(T x, T y) : x(x), y(y) {}

    P operator+(P b) const { return {x+b.x, y+b.y}; }
    P operator-(P b) const { return {x-b.x, y-b.y}; }
    P operator*(T s) const { return {x*s, y*s}; }
    P operator/(T s) const { return {x/s, y/s}; }
    P& operator+=(P b) { x+=b.x; y+=b.y; return *this; }
    P& operator-=(P b) { x-=b.x; y-=b.y; return *this; }
    P& operator*=(T s) { x*=s; y*=s; return *this; }
    P operator-() const { return {-x, -y}; }

    bool operator<(P b) const { return x<b.x || (x==b.x && y<b.y); }
    bool operator==(P b) const { return x==b.x && y==b.y; }
    bool operator!=(P b) const { return !(*this==b); }

    T dot(P b) const { return x*b.x + y*b.y; }

    T cross(P b) const { return x*b.y - y*b.x; }

    double mag2() const { return (double)x*x + (double)y*y; }
    double mag() const { return sqrt(mag2()); }

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

double angle(P a, P b) {
    return acos(max(-1.0, min(1.0, a.dot(b) / a.mag() / b.mag())));
}

double tri_area(P a, P b, P c) { return (b-a).cross(c-a) / 2.0; }

int orient(P a, P b, P c) { return sgn((double)(b-a).cross(c-a)); }

double law_of_cosines(double a, double b, double c) {
    return acos(max(-1.0, min(1.0, (a*a + b*b - c*c) / (2*a*b))));
}

bool in_triangle(P p, P a, P b, P c) {
    int d1=orient(a,b,p), d2=orient(b,c,p), d3=orient(c,a,p);
    return (d1>=0 && d2>=0 && d3>=0) || (d1<=0 && d2<=0 && d3<=0);
}

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

    double implicit_a() const { return -(double)dir.y; }
    double implicit_b() const { return  (double)dir.x; }
    double implicit_c() const { return implicit_a()*origin.x + implicit_b()*origin.y; }

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


struct circle {
    P center;
    double radius;
    circle(P c, double r) : center(c), radius(r) {}

    bool contains(P p)    const { return  leq(dist(center,p), radius); }
    bool on_boundary(P p) const { return   eq(dist(center,p), radius); }

    double sector_area(double angle_rad) const {
        return 0.5 * radius * radius * angle_rad;
    }

    double triangle_area(double angle_rad) const {
        return 0.5 * radius * radius * sin(angle_rad);
    }

    double segment_area(double angle_rad) const {
        return sector_area(angle_rad) - triangle_area(angle_rad);
    }
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



struct poly {
    vector<P> v;
    poly() {}
    poly(vector<P> verts) : v(verts) {}
    int size() const { return (int)v.size(); }

    double signed_area() const {
        double a=0;
        for (int i=0; i<size(); i++) a += (double)v[i].cross(v[(i+1)%size()]);
        return a / 2.0;
    }
    double area() const { return fabs(signed_area()); }

    ll boundary_points() const {
        ll b=0;
        for (int i=0; i<size(); i++) {
            ll dx = llabs((ll)(v[(i+1)%size()].x - v[i].x));
            ll dy = llabs((ll)(v[(i+1)%size()].y - v[i].y));
            b += __gcd(dx, dy);
        }
        return b;
    }
    ll interior_points() const {
        ll A = (ll)round(2.0 * area());
        ll B = boundary_points();
        return (A - B + 2) / 2;
    }

    int contains(P p) const {
        int cr=0;
        for (int i=0; i<size(); i++) {
            P a=v[i], b=v[(i+1)%size()];
            if (seg(a,b).contains(p)) return 0;
            if ((a.y<=p.y && b.y>p.y) || (b.y<=p.y && a.y>p.y)) {
                double t = (double)(p.y-a.y) / (double)(b.y-a.y);
                if (p.x < a.x + t*(b.x-a.x)) cr++;
            }
        }
        return (cr%2==1) ? 1 : -1;
    }

    bool is_convex() const {
        if (size() < 3) return false;
        int sign=0;
        for (int i=0; i<size(); i++) {
            int s = sgn((double)(v[(i+1)%size()]-v[i]).cross(v[(i+2)%size()]-v[(i+1)%size()]));
            if (s==0) continue;
            if (sign==0) sign=s;
            else if (s!=sign) return false;
        }
        return true;
    }

    P centroid() const {
        P c; double a=0;
        for (int i=0; i<size(); i++) {
            double cr = (double)v[i].cross(v[(i+1)%size()]);
            c += (v[i]+v[(i+1)%size()]) * (T)cr;
            a += cr;
        }
        return c / (T)(3*a);
    }
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
    int t;
    cin >> t;

    long d;
    double A, B;
    for (int i = 0; i < t; i++) {
        cin >> d;
        cin >> A;
        cin >> B;

        A = to_rad(A);
        B = to_rad(B);
        P you = P(0,0);
        P youUnit = P(cos(A),sin(A));
        P mulder = P(d,0);
        P mulderUnit = P(-cos(B),sin(B));

        line a = line(you, youUnit);
        line b = line(mulder, mulderUnit);

        cout << "A: " << A << "B: " << B << "you: " << you.x << " " << you.y << "youUnit: " << youUnit.x << " " << youUnit.y << "mulder: " << mulder.x << " " << mulder.y << "mulder: " << mulder.x << " " << mulder.y
        cout << intersect(a,b).pt[0].x << endl;
    }
}

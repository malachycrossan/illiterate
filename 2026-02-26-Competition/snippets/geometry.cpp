#include <math.h>
#include <cmath>

#define choose_a_type int // int, double, float, long long

struct point2d {
  choose_a_type x, y;
  point2d() {}
  point2d(choose_a_type x, choose_a_type y) : x(x), y(y) {}
  point2d &operator+=(const point2d &t) {
    x += t.x;
    y += t.y;
    return *this;
  }
  point2d &operator-=(const point2d &t) {
    x -= t.x;
    y -= t.y;
    return *this;
  }
  point2d &operator*=(choose_a_type t) {
    x *= t;
    y *= t;
    return *this;
  }
  point2d &operator/=(choose_a_type t) {
    x /= t;
    y /= t;
    return *this;
  }

   // Returns the vector from this to other.
	point2d getVect(point2d o) {
        // Returns a new point.
		return point2d(o.x-x, o.y-y);
	}

    // Returns the distance between this and other.
	double dist(point2d o) {
		return sqrt((o.x-x)*(o.x-x) + (o.y-y)*(o.y-y));
	}

	// Returns the magnitude ot this cross product other.
	int crossProductMag(point2d o) {
		return x*o.y - y*o.x;
	}

  point2d operator+(const point2d &t) const { return point2d(*this) += t; }
  point2d operator-(const point2d &t) const { return point2d(*this) -= t; }
  point2d operator*(choose_a_type t) const { return point2d(*this) *= t; }
  point2d operator/(choose_a_type t) const { return point2d(*this) /= t; }
};
point2d operator*(choose_a_type a, point2d b) { return b * a; }

choose_a_type dot_points(point2d a, point2d b) {
    return a.x * b.x + a.y * b.y;
}

choose_a_type dot_scalars(choose_a_type ax, choose_a_type ay, choose_a_type bx, choose_a_type by) {
    return ax * bx + ay * by;
}

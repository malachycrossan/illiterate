#include <math.h>
#include <cmath>

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


struct vect2D {

    double x;
    double y;

    vect2D(double myx, double myy) {
        x = myx;
        y = myy;
    }

    vect2D(point2d start, point2d end) {
        x = end.x - start.x;
        y = end.y - start.y;
    }

    double dot(vect2D other) {
        return x*other.x + y*other.y;
    }

    double mag() {
        return sqrt(x*x+y*y);
    }

    // Thjs formula comes from using the relationship between the dot product and
    // the cosine of the included angle.
    double angle(vect2D other) {
        return acos(dot(other)/mag()/other.mag());
    }

    double signedCrossMag(vect2D other) {
        return x*other.y-other.x*y;
    }

    double crossMag(vect2D other) {
        return abs(signedCrossMag(other));
    }
};


struct line {

    double EPSILON = 1e-9;

    point2d p;
    vect2D dir;

    line(point2d start, point2d end) {
        p = start;
        dir = vect2D(start, end);
    }

    point2d intersect(line other) {

        // This is the denominator we get when setting up our system of equations for
        // our two parametric line parameters.
        double den = det(dir.x, -other.dir.x, dir.y, -other.dir.y);
        if (abs(den) < EPSILON) return;

        // We already have the denominator, now solve for the numerator for lambda, the
        // parameter for this line. Then return the resultant point.
        double numLambda = det(other.p.x-p.x, -other.dir.x, other.p.y-p.y, -other.dir.y);
        return eval(numLambda/den);
    }

    // Returns the shortest distance from other to this line. Sets a vector from the starting
    // point of this line to other and uses the cross product with that vector and the direction
    // vector of the line.
    double distance(point2d other) {
        vect2D toPt = vect2D(p, other);
        return dir.crossMag(toPt)/dir.mag();
    }

    // Returns the point on this line corresponding to parameter lambda.
    point2d eval(double lambda) {
        return point2d(p.x+lambda*dir.x, p.y+lambda*dir.y);
    }

    double det(double a, double b, double c, double d) {
        return a*d - b*c;
    }
};
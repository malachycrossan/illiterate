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
  point2d operator+(const point2d &t) const { return point2d(*this) += t; }
  point2d operator-(const point2d &t) const { return point2d(*this) -= t; }
  point2d operator*(choose_a_type t) const { return point2d(*this) *= t; }
  point2d operator/(choose_a_type t) const { return point2d(*this) /= t; }
};
point2d operator*(choose_a_type a, point2d b) { return b * a; }

class vect implements Comparable<vect> {

	// Stores reference vect
	public static double refX;
	public static double refY;

	public double x;
	public double y;

	public vect(double myx, double myy) {
		x = myx;
		y = myy;
	}

	public vect(vect start, vect end) {
		x = end.x - start.x;
		y = end.y - start.y;
	}

	// Returns the vector from this to other.
	public vect getVect(vect other) {
		return new vect(other.x-x, other.y-y);
	}

	public double mag() {
		return Math.sqrt(x*x+y*y);
	}

	public double angle(vect other) {
		return Math.acos(this.dotProduct(other)/mag()/other.mag());
	}

	// Returns the distance between this and other.
	public double dist(vect other) {
		return Math.sqrt((other.x-x)*(other.x-x) + (other.y-y)*(other.y-y));
	}

	// Returns the magnitude ot this cross product other.
	public double crossProductMag(vect other) {
		return this.x*other.y - other.x*this.y;
	}

	public double absCrossProductMag(vect other) {
		return Math.abs(crossProductMag(other));
	}

	public double dotProduct(vect other) {
		return this.x*other.x + this.y*other.y;
	}

	// returns true iff this to mid to next is a right turn (180 degree is considered right turn).
	public boolean isRightTurn(vect mid, vect next) {
		vect v1 = getVect(mid);
		vect v2 = mid.getVect(next);
		return v1.crossProductMag(v2) >= 0; /*** Change to > 0 to skip collinear points. ***/
	}

	// Returns true iff this vect is the origin.
	public boolean isZero() {
		return x == 0 && y == 0;
	}

	public int compareTo(vect other) {

		vect myRef = new vect(refX, refY);
		vect v1 = myRef.getVect(this);
		vect v2 = myRef.getVect(other);

		// To avoid 0 issues.
		if (v1.isZero()) return -1;
		if (v2.isZero()) return 1;

		// Angles are different, we are going counter-clockwise here.
		if (v1.crossProductMag(v2) != 0)
			return -(int)v1.crossProductMag(v2);

		// This should work, smaller vectors come first.
		if (myRef.dist(v1) < myRef.dist(v2)) return -1;
		return 1;
	}

	public vect scale(double c) {
		return new vect(x*c, y*c);
	}

	public vect unitVect() {
		return new vect(x/this.mag(), y/this.mag());
	}

	public vect rotate(double angle) {
		return new vect(
			x*Math.cos(angle) - y*Math.sin(angle),
			x*Math.sin(angle) + y*Math.cos(angle)
		);
	}
}

class line {
	final public static double EPSILON = 1e09;

	public vect p1;
	public vect p2;

	public line(vect start, vect end) {
		p1 = start;
		p2 = end;
	}

	public double length() {
		return Math.sqrt((p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y));
	}

	 public vect intersect(line other) {

        // This is the denominator we get when setting up our system of equations for
        // our two parametric line parameters.
        double den = det(p2.x, -other.p2.x, p2.y, -other.p2.y);
        if (Math.abs(den) < EPSILON) return null;

        // We already have the denominator, now solve for the numerator for lambda, the
        // parameter for this line. Then return the resultant point.
        double numLambda = det(other.p.x-p.x, -other.p2.x, other.p.y-p.y, -other.p2.y);
        return eval(numLambda/den);
    }

    // Returns the shortest distance from other to this line. Sets a vector from the starting
    // point of this line to other and uses the cross product with that vector and the p2ection
    // vector of the line.
    public double distance(vect other) {
        vect toPt = new vect(p1, other);
        return p2.absCrossProductMag(toPt)/p2.mag();
    }

    // Returns the point on this line corresponding to parameter lambda.
    public vect eval(double lambda) {
        return new vect(p1.x+lambda*p2.x, p1.y+lambda*p2.y);
    }

    public static double det(double a, double b, double c, double d) {
        return a*d - b*c;
    }

	public vect direction() {
		return new vect(p2.x-p1.x, p2.y-p1.y);
	}

	public double cross() {
		return p1.crossProductMag(p2);
	}

	public double dot() {
		return p1.dotProduct(p2);
	}

	public double angle(line other) {
		vect v1 = this.direction();
		vect v2 = other.direction();

		return v1.angle(v2);
	}

	public double distFromVect(vect p) {
		double angle = -(this.angle(new line(new vect(0, 0), new vect(1, 0))));
		line tempLine = new line(p1.rotate(angle), p2.rotate(angle));
		vect rot = p.rotate(angle);

		return Math.abs(rot.y - tempLine.p1.y);
	}

	public int numIntersections(line other) {

	}
}

class polygon {
	public line[] edges;

	public polygon(line[] myedges) {
		edges = myedges.clone();
	}

	public double area() {
		double val = 0;

		for (int i = 0; i < edges.length; i++) {
			val += edges[i].cross();
		}

		return val / 2;
	}

	// -1 is outside, 0 on edge, 1 inside
	public int pointInPoly(vect p) {
		double curAngle = 0;

		for (int i = 0; i < edges.length - 1; i++) {
			vect check1 = new vect(p, edges[i].p1);
			vect check2 = new vect(p, edges[i].p2);

			curAngle += check1.angle(check2);
		}

		// Inside
		if (curAngle == 2*Math.PI) {
			return 1;
		}
		// On edge
		else if (curAngle == Math.PI) {
			return 0;
		}

		// Outside
		return -1;
	}
}
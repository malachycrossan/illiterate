import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.StringTokenizer;

public class euclid {
    public static void main(String[] args) {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;

        pt A, B, C, D, E, F;
        pt G, H;

        try {
            st = new StringTokenizer(br.readLine());

            A = new pt(Double.valueOf(st.nextToken()), Double.valueOf(st.nextToken()));
            B = new pt(Double.valueOf(st.nextToken()), Double.valueOf(st.nextToken()));
            C = new pt(Double.valueOf(st.nextToken()), Double.valueOf(st.nextToken()));
            D = new pt(Double.valueOf(st.nextToken()), Double.valueOf(st.nextToken()));
            E = new pt(Double.valueOf(st.nextToken()), Double.valueOf(st.nextToken()));
            F = new pt(Double.valueOf(st.nextToken()), Double.valueOf(st.nextToken()));

            // Continues while A != B (ABGH has area greater than 0)
            while (A.x != B.x || A.y != B.y) {
                // Gets area of DEF
                double area = Math.abs(((D.x * (E.y - F.y)) + (E.x * (F.y - D.y)) + (F.x * (D.y - E.y))) / 2);

                line AB = new line(A, B);
                double paraWidth = AB.length();
                double paraHeight = area / paraWidth;

                // Gets angle of CAB
                line AC = new line(A, C);
                double angle_CAB = AB.angle(AC);

                // Gets position of H along AC axis
                double len_AH = paraHeight / Math.sin(angle_CAB);
                double scalar = len_AH / AC.length();

                // Calcs H & G
                H = AC.ptOnLine(scalar);
                pt offset = new pt(H.x-A.x, H.y-A.y);
                G = new pt(B.x+offset.x, B.y+offset.y);

                System.out.printf("%.3f %.3f %.3f %.3f\n", G.x, G.y, H.x, H.y);

                st = new StringTokenizer(br.readLine());
                A = new pt(Double.valueOf(st.nextToken()), Double.valueOf(st.nextToken()));
                B = new pt(Double.valueOf(st.nextToken()), Double.valueOf(st.nextToken()));
                C = new pt(Double.valueOf(st.nextToken()), Double.valueOf(st.nextToken()));
                D = new pt(Double.valueOf(st.nextToken()), Double.valueOf(st.nextToken()));
                E = new pt(Double.valueOf(st.nextToken()), Double.valueOf(st.nextToken()));
                F = new pt(Double.valueOf(st.nextToken()), Double.valueOf(st.nextToken()));
            }

            br.close();
        }
        catch (Exception e) {
            System.err.println(e);
        }
    }
}

class pt {
    public double x, y;

    public pt(double myx, double myy) {
        x = myx;
        y = myy;
    }

    public pt(pt p1, pt p2) {
        x = p2.x - p1.x;
		y = p2.y - p1.y;
    }
    
    public double distance(pt other) {
        return Math.sqrt((other.x-x)*(other.x-x) + (other.y-y)*(other.y-y));
    }

    public double mag() {
        return Math.sqrt(x*x+y*y);
    }

    public double angle(pt other) {
		return Math.acos(this.dotProduct(other)/mag()/other.mag());
	}

    public double dotProduct(pt other) {
    	return this.x*other.x + this.y*other.y;
	}
}

class line {
    public pt origin, end;

    public line(pt o, pt e) {
        origin = o;
        end = e;
    }

    public pt direction() {
		return new pt(end.x-origin.x, end.y-origin.y);
	}

    public double angle(line other) {
		pt v1 = this.direction();
		pt v2 = other.direction();

		return v1.angle(v2);
	}

    public double length() {
        return origin.distance(end);
    }

    public pt ptOnLine(double c) {
        return new pt((end.x-origin.x)*c + origin.x, (end.y-origin.y)*c + origin.y);
    }
}

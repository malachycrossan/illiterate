// 2026-02-06-Competition/nametag.java
// Author: ?

import java.util.*;
public class nametag {
	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		int n;
		String s, front, back, rev;
		String[] reversed;
		
		n = scan.nextInt();
		
		for(int i = 0; i < n; i++) {
			s = scan.next();
			s = s.toUpperCase();
			reversed = new String[s.length()];
		
			for(int j = 0; j < s.length(); j++) {
				front = s.substring(0, j);
				back = s.substring(j, s.length());
				rev = back + front;
				reversed[j] = rev;
			}
		
			Arrays.sort(reversed);
			System.out.println(reversed[0]);
		}
		
		scan.close();
		return;
	}
}

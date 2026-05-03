#include <iostream>
using namespace std;
int helper (int n, int s) {
  if (n == 0) return 0;
  if (n == 1 && 0 <= s && s <= 3) return 1;
  return helper (n-1, s-0) + helper (n-1, s-1) + helper (n-1, s-2) + helper (n-1, s-3);
}
int main () {

  int t;
  cin >> t;
  for (int i = 0; i < t; i++) {
    int n, s;
    cin >> n >> s;
    cout << helper(n,s) << endl;
  }
}

#include <iostream>

using namespace std;

long stirling(long n, long k, long memo[12][12]) {
  if (n < 0) return 0;
  if (k < 0) return 0;
  if (k > n) return 0;
  if (memo[n][k] != -1) return memo[n][k];

  return k*stirling(n - 1,k, memo) + stirling(n-1, k-1, memo);
}

int main () {

  long memo[12][12];
  for (int i = 0; i < 12; i++) for (int j = 0; j < 12; j++) memo[i][j] = -1;
  memo[1][1] = 1;
  memo[2][1] = 1;
  memo[2][2] = 1;
    
  // for (int i = 0; i < 12; i++) for (int j = 0; j < 12; j++) cout << i << " " << j << " " << stirling(i,j, memo) << endl;
  long total = 0;
  int n = 2;
  for (int i = 1; i <= n; i++) total += stirling(n, i, memo);
  cout << total << endl;
}

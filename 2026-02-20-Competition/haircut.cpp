#include <iostream>
using namespace std;

int helper(long long low, long long high, int M[], int N, int B) {
  long long mid = low + (high - low) / 2;
  // cout << "Step: " << low << " " << mid << " " << high << " Total = ";
  int total = 0;
  for (int i = 0; i < B; i++) {
  //   cout << (mid + M[i] - 1)/M[i] << " + ";
    total += (mid + M[i] - 1)/M[i];
  }
  // cout << " = " << total << endl;
  long long count = 0;
  if (low == mid) for (int i = 0; i <= B; i++) {
    if (count + total == N) return count;
    if (mid % M[i] == 0) count++;
  }
  if (total < N) { return helper(mid, high, M, N, B); }
  else { return helper(low, mid - 1, M, N, B);}
}

int main () {
  int num_cases;
  cin >> num_cases;
  for (int n = 1; n <= num_cases; n++){
    int B; cin >> B;
    int N; cin >> N;
    int M[B];
    for (int i = 0; i < B; i++) cin >> M[i];
    long long low = 0; long long high = 1000000000;
  //   cout << "Barbers: " << B << endl << "Position in line: " << N << endl << "{";
  //   for (int i = 0; i < B; i++) cout << M[i] << ",";
  //   cout << "}" << endl;
    int ans = helper(low, high, M, N, B);
  cout << "Case #" << n << ": " << ans << endl;
  }
}

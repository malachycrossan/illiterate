#include <iostream>
using namespace std;

long long helper(long long low, long long high, int M[], int N, int B) {
  long long mid = ((high - low) / 2) + low;
  
  long long total = 0;
  for (int i = 0; i < B; i++) {
    total += (long long)(mid + M[i] - 1)/M[i];
  }

  long long count = 0;
  if (low == mid) {
    cout << low << " == " << mid << endl;
    for (int i = 0; i <= B; i++) {
      cout << "count + total = " << count + total << endl;
      if ((count + total) == N) { 
        //cout << count+total << " == " << N << endl;
        return count; 
      }
      
      //cout << "mid = " << mid << ", M[i] = " << M[i] << endl; 
      count++;
    }
  }

  if (total < N) { 
    return helper(mid, high, M, N, B); 
  } else { 
    return helper(low, mid - 1, M, N, B);
  }

  return 0;
}

int main() {
  int num_cases;
  cin >> num_cases;
    for (int n = 1; n <= num_cases; n++){
        int B; cin >> B;
        int N; cin >> N;
        int * M = new int[B];
        for (int i = 0; i < B; i++) { cin >> M[i]; }
        long long low = 0; long long high = 1000000000;
        //   cout << "Barbers: " << B << endl << "Position in line: " << N << endl << "{";
        //   for (int i = 0; i < B; i++) cout << M[i] << ",";
        //   cout << "}" << endl;
        long long ans = helper(low, high, M, N, B);
        cout << "Case #" << n << ": " << ans << endl;
    }
    return 0;
}
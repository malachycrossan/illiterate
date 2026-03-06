#include <iostream>
using namespace std;

long long helper(long long low, long long high, int M[], int N, int B) {
  //cout << "In helper." << endl;
  long long mid = low + (high - low) / 2;
  //cout << "Mid: " << mid << endl;
  //cout << "Step: " << low << " " << mid << " " << high << " Total = ";
  long long total = 0;
  for (int i = 0; i < B; i++) {
    //cout << (mid + M[i] - 1)/M[i] << endl;
    total += (long long)(mid + M[i] - 1)/M[i];
    //cout << "Total: " << total << endl;
  }
  //cout << "Done!" << endl;
  //cout << " = " << total << endl;
  long long count = 0;
  if (low == mid) {
    //cout << "Low = Mid: " << low << " " << mid << " " << high << endl;
    for (int i = 0; i < B; i++) {
      cout << "count + total = " << count + total << endl;
      if ((count + total) == N) { 
        //cout << "RETURN" << endl; 
        return count; 
      }
      
      //cout << "mid = " << mid << ", M[i] = " << M[i] << endl; 
      //cout << "mid % M[i] == " << (mid%M[i]) << endl;
      if ((mid % M[i]) == 0) { 
        //cout << "COUNT: " << count+1 << endl; 
        count++;
      }
    }
  }

  //cout << "Total: " << total << endl;
  if (total < N) { 
    //cout << "Low: " << mid << ", High: " << high << endl;
    return helper(mid, high, M, N, B); 
  } else { 
    //cout << "Low: " << low << ", High: " << mid-1 << endl;
    return helper(low, mid - 1, M, N, B);
  }
}

int main () {
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
}

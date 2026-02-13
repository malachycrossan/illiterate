// 2026-02-13-Competition/sticks.cpp
// Author: Malachy Crossan
#include <iostream>
using namespace std;

long long stick_cost(long long* cuts, long long left, long long right) {
long long index_length = right - left;
if (index_length < 2) return 0;
long long middle = index_length / 2 + left;
return (cuts[right] - cuts[left]) + stick_cost(cuts, left, middle) + stick_cost(cuts, middle, right);
}

int main () {
  long long num_cases;
  cin >> num_cases;

  long long num_cuts, length;
  for (long long i = 0; i < num_cases; i++) {
    cin >> length;
    cin >> num_cuts;
    long long* cuts = (long long*)malloc(sizeof(long long) * (num_cuts + 2));
    cuts[0] = 0;
    cuts[num_cuts + 1] = length;

    for (long long j = 1; j < num_cuts + 1; j++) {
      cin >> cuts[j];
    }

    cout << stick_cost(cuts, 0, num_cuts + 1) << endl;

    free(cuts);
  }

  return 0;
}

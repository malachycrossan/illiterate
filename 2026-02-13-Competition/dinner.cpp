// 2026-02-13-Competition/sticks.cpp
// Author: Malachy Crossan
#include <iostream>
using namespace std;

long dinner(int total, long* memo_table) {
  if (total < 0) return 0;
  if (total == 0) return 1;
  // for (int j = 0; j < total; j++) cout << memo_table[j] << " ";
  // cout << endl;
  if (memo_table[total] > 0) return memo_table[total];
  long count = dinner(total - 2, memo_table) + dinner(total - 5, memo_table) + dinner(total - 10, memo_table);
  memo_table[total] = count;
  // for (int j = 0; j < total; j++) cout << memo_table[j] << " ";
  // cout << endl;
  return count;
}

int main () {
  int num_cases;
  cin >> num_cases;

  int total;
  for (int i = 0; i < num_cases; i++) {
    cin >> total;
    long* memo_table = new long[total + 1];
    for (int j = 0; j < total; j++) memo_table[j] = -1;
    cout << "Dinner #" << i + 1 << ": " << dinner(total, memo_table) << endl;
  }

  return 0;
}

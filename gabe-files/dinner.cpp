#include <iostream>
using namespace std;

int dinner(long long total, long long* memo_table) {
  // for (int j = 0; j < total; j++) cout << memo_table[j] << " ";
  // cout << endl;
  if (total < 0) return 0;
  if (total == 0) return 1;
  if (memo_table[total] > 0) {
    //cout << memo_table[total];
    return memo_table[total];
  }

  long long count = 0;
  count += dinner(total - 2, memo_table);
  // cout << "Count: " << count << " ";
  count += dinner(total - 5, memo_table);
  // cout << "Count: " << count << " ";
  count += dinner(total - 10, memo_table);
  // cout << "Count: " << count << " ";
  memo_table[total] = count;
  cout << "memo[" << total << "] = " << memo_table[total] << endl;

  return count;
}

int main () {
  int num_cases;
  cin >> num_cases;

  int total;
  for (int i = 0; i < num_cases; i++) {
    cin >> total;
    // int* memo_table = (int*)calloc(total, sizeof(int));
    // int* memo_table = (int*)malloc(total * sizeof(int));
    long long* memo_table = new long long[total]{};
    for (int j = 0; j < total; j++) memo_table[j] = -1;
    cout << dinner(total, memo_table) << endl;
  }

  return 0;
}
#include <iostream>
#include <string>
using namespace std;

long long countseq(string input, string subseq, long long input_index, long long subseq_index, long long** memo_table) {
  if (subseq_index == subseq.length()) return 1;

  long long curr = input_index;

  long long lookup_result = memo_table[curr][subseq_index];
  if (lookup_result != -1) return lookup_result;

  long long total = 0;
  while (curr + 1 <= input.length()) {
    if (input[curr] == subseq[subseq_index]) {
      total += countseq(input, subseq, curr + 1, subseq_index + 1, memo_table);
    }
    curr++;
  }

  // for (long long i = 0; i < (input.length() + 1); i++) {
  //   for (long long j = 0; j < (subseq.length() + 1); j++) {
  //     cout << memo_table[i][j] << " ";
  //   }
  //   cout << endl;
  // }
  // cout << endl;

  memo_table[input_index][subseq_index] = total;
  return total;
}

int main () {
  long long num_cases;
  cin >> num_cases;
  long long solutions[num_cases];

  string input;
  string subseq;
  for (long long i = 0; i < num_cases; i++) {
    cin >> input;
    cin >> subseq;

    long long** memo_table = (long long**)malloc(sizeof(long long*) * (input.length()) + 1);
    for (long long i = 0; i < (input.length() + 1); i++) {
      memo_table[i] = (long long*)malloc(sizeof(long long) * (subseq.length()) + 1);
      for (long long j = 0; j < (subseq.length() + 1); j++){
        memo_table[i][j] = -1;
      }
    }

    // for (long long i = 0; i < (input.length() + 1); i++) {
    //   for (long long j = 0; j < (subseq.length() + 1); j++) {
    //       cout << memo_table[i][j] << " ";
    //   }
    //   cout << endl;
    // }
    // cout << endl;

    solutions[i] = countseq(input, subseq, 0, 0, memo_table);
    free(memo_table);
    // printf("%x0\n", solutions[i]);
    cout << solutions[i] << endl;
  }
  // for (long long i = 0; i < num_cases; i++) cout << solutions[i] << endl;

  return 0;
}

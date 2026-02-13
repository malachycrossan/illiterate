// 2026-02-13-Competition/sticks.cpp
// Author: Malachy Crossan
#include <iostream>
using namespace std;

int stick_cost(int* cuts, int left, int right) {
int index_length = right - left;
if (index_length < 2) return 0;
int middle = index_length / 2 + left;
return (cuts[right] - cuts[left]) + stick_cost(cuts, left, middle - 1) + stick_cost(cuts, middle + 1, right);
}

int main () {
  int num_cases;
  cin >> num_cases;

  int num_cuts;
  for (int i = 0; i < num_cases; i++) {
    cin >> num_cuts;
    int* cuts = (int*)malloc(sizeof(int) * num_cuts);

    for (int j = 0; j < num_cuts; j++) {
      cin >> cuts[j];
    }

    cout << stick_cost(cuts, 0, num_cuts);

    free(cuts);
  }

  return 0;
}

// 2026-02-13-Competition/sticks.cpp
// Author: Malachy Crossan
#include <iostream>
using namespace std;

int stick_cost(int* cuts, int length, int left, int right) {
int index_length = right - left;
if (index_length < 2) return 0;
int middle = index_length / 2 + left;
return (cuts[right] - cuts[left]) + stick_cost(cuts, length, left, middle - 1) + stick_cost(cuts, length, middle + 1, right);
}

int main () {
  int num_cases;
  cin >> num_cases;

  int num_cuts, length;
  for (int i = 0; i < num_cases; i++) {
    cin >> length;
    cin >> num_cuts;
    int* cuts = (int*)malloc(sizeof(int) * (num_cuts + 2));
    cuts[0] = 0;
    cuts[num_cuts + 1] = length;

    for (int j = 1; j < num_cuts + 1; j++) {
      cin >> cuts[j];
    }

    cout << stick_cost(cuts, length, 0, num_cuts);

    free(cuts);
  }

  return 0;
}

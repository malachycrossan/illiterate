// 2026-02-06-Competition/mine.cpp
// Author: Malachy Crossan
#include <cstdlib>
#include <iostream>
using namespace std;

int main () {
  int R, C;

  for (;;) {
  cin >> R >> C;
  if (R == 0) break;
  int** result = (int**)malloc(sizeof(int*) * R);
  for (int i = 0; i < R; i++) {
    result[i] = (int*)malloc(sizeof(int) * C);
    for (int j = 0; j < C; j++){
      result[i][j] = 0;
    }
  }

  char curr;
  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++){
      cin >> curr;
      if (curr == '.') continue;
      result[i][j] = -1;

      if (0 < j) if (result[i][j-1] != -1) result[i][j-1] += 1;
      if (j < C - 1) if (result[i][j+1] != -1) result[i][j+1] += 1;

      if (0 < i) {
        if (result[i-1][j] != -1) result[i-1][j] += 1;
        if (0 < j) if (result[i-1][j-1] != -1) result[i-1][j-1] += 1;
        if (j < C - 1) if (result[i-1][j+1] != -1) result[i-1][j+1] += 1;
      }
      if (i < R - 1) {
        if (result[i+1][j] != -1) result[i+1][j] += 1;
        if (0 < j) if (result[i+1][j-1] != -1) result[i+1][j-1] += 1;
        if (j < C - 1) if (result[i+1][j+1] != -1) result[i+1][j+1] += 1;
      }
    }
  }

  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++){
      if (result[i][j] != -1) {
        cout << result[i][j];// << " ";
      } else {
        cout << "*";
      }
    }
    cout << endl;
  } 
  }
}

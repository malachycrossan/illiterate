#include <cstdlib>
#include <iostream>
using namespace std;

int R, C;
int ** board;

void addToRow(int row, int col) {
  // Left
  if(col-1 >= 0) {
    //cout << "board[" << row << "][" << col-1 << "]++  [left]" << endl;
    board[row][col-1]++;
  }

  // Right
  if(col+1 <= C) {
    //cout << "board[" << row << "][" << col+1 << "]++  [right]" << endl;
    board[row][col+1]++;
  }

  return;
}

void displayBoard() {
  for(int r = 0; r < R; r++) {
    for(int c = 0; c < C; c++) {
      if(board[r][c] < 0) {
        cout << "*";
      } else {
        cout << board[r][c];
      }
    }
    cout << endl;
  }
}

int main () {

  cin >> R >> C;

  while(R != 0 && C != 0) {
    board = new int*[R];
    // Initialize board seperately to reduce headaches.
    for(int i = 0; i < R; i++) {
      board[i] = new int[C]{}; // {} initializes all rows with 0's.
    }

    // Main loop.
    char cur;
    for(int i = 0; i < R; i++) {
      // Go through each character.
      for(int j = 0; j < C; j++) {
        cin >> cur;
        if(cur == '*') {
          // Can I add to the top row?
          if(i-1 >= 0) {
            addToRow(i-1, j);
            board[i-1][j]++;
          }

          //cout << "Add to row " << i << " " << j << endl;
          addToRow(i, j);
          board[i][j] = -9;

          // Can I add to the row below?
          if(i+1 < R) {
            addToRow(i+1, j);
            board[i+1][j]++;
          }
        }
      }
    }

    // Display final board.
    displayBoard();

    cin >> R >> C;
  }
}

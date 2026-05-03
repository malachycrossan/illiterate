#include <iomanip>
#include <iostream>
using namespace std;
int main () {
  int t;
  cin >> t;
  for (int i = 0; i < t; i++) {
    int p, k, x;
    cin >> p >> k >> x;
    int prob[x+1+p]; 
    int probBuff[x+1+p];
    for (int j = 0; j < x+1+p; j++) {
      prob[j] = 0;
      probBuff[j] = 0;
    }
    prob[0] = 1;
    int frac = 1;
    for (int jump = 0; jump < k; jump++) {
      frac *= p;
      for (int j = 0; j < x+1+p; j++) {
        probBuff[j] = 0;
      }
      probBuff[x] = prob[x] * p;
      for (int position = 0; position < x + 1 + p; position++) {
        if (prob[position] > 0) {
          if (position < x) {
            for (int nextPosition = position + 1; nextPosition <= position + p; nextPosition++){
              probBuff[nextPosition] += prob[position];
            }
          } else if (position > x) {
            for (int nextPosition = position - 1; nextPosition >= position - p; nextPosition--){
              nextPosition = max(0, nextPosition);
              probBuff[nextPosition] += prob[position];
            }
          }
        }
      }

      for (int j = 0; j < x + 1 + p; j++) {
        // cout << prob[j] << "|" << probBuff[j] << " ";
        prob[j] = probBuff[j];
      }
      // cout << "frac" <<frac << endl;
      // memcpy(probBuff, prob, x*sizeof(double));
    }
    cout << fixed;
    cout << setprecision(6);
    cout << ((double)prob[x] / (double)frac) << endl;
  }
}

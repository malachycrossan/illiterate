#include <stdio.h>

int main() {
    int listLen, maxVal;
    scanf("%d %d", &listLen, &maxVal);
    
    unsigned long long listNum[11][2001];
    for (int i = 1; i < 2001; i++) {
        listNum[1][i] = i;
    }
    for (int i = 2; i < 11; i++) {
        listNum[i][1] = 0;
    }

    for (int i = 2; i < 11; i++) {
        for (int j = 2; j < 2001; j++) {
            listNum[i][j] = listNum[i][j-1] + listNum[i-1][j/2];
        }
    }
    
    int caseNum = 1;
    while (listLen != 0 && maxVal != 0) {
        printf("Case %d: n = %d, m = %d, # lists = %lld\n", caseNum, listLen, maxVal, listNum[listLen][maxVal]);

        scanf(" %d %d", &listLen, &maxVal);

        caseNum++;
    }
}
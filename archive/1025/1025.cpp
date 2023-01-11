
#include <math.h>

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

string arr[9][9];

int ispalin(int num) {
  int temp = sqrt(num);
  return temp * temp == num ? num : -1;
}

int main() {
  int N, M;
  int maxi = -1;
  cin >> N >> M;

  // input
  for (int i = 0; i < N; i++) {
    string tempStr;
    cin >> tempStr;
    for (int j = 0; j < M; j++) {
      arr[i][j] = tempStr[j];
    }
  }

  // brute force
  for (int i = 0; i < N; i++) {  //
    for (int j = 0; j < M; j++) {
      int flag = 1;
      for (int dx = -N + 1; dx < N; dx++) {
        for (int dy = -M + 1; dy < M; dy++) {
          if (dx == 0 && dy == 0) continue;
          int x = i;
          int y = j;
          string sum = "";
          while (x >= 0 && x < N && y >= 0 && y < M) {
            sum += arr[x][y];
            maxi = max(maxi, ispalin(stoi(sum)));
            x += dx;
            y += dy;
          }
        }
      }
    }
  }

  if (N == 1 && M == 1)
    cout << ispalin(stoi(arr[0][0])) << endl;
  else
    cout << maxi << endl;

  return 0;
}
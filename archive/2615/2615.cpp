#include <stdio.h>

int pan[19][19];

int dx[4] = {0, 1, 1, -1};  // right down rightdown rightup
int dy[4] = {1, 0, 1, 1};

/* right, down , diag*/
int check(int i, int j, int direc, int color) {
  int cnt = 1;
  // 0 <= i - dx[direc] < 19 || 0 <= j - dy[direc] < 19
  if (0 <= i - dx[direc] || i - dx[direc] < 19 || 0 <= j - dy[direc] || j - dy[direc] < 19) {
    if (pan[i - dx[direc]][j - dy[direc]] == color) return cnt;
  }
  while (true) {
    if (0 > i + dx[direc] || i + dx[direc] > 19 || 0 > j + dy[direc] || j + dy[direc] > 19) return cnt;  // out of range
    if (pan[i + dx[direc]][j + dy[direc]] != color) return cnt;                                          // not matched color
    cnt++;
    i += dx[direc];
    j += dy[direc];
  }
}

int main() {
  for (int i = 0; i < 19; i++)
    for (int j = 0; j < 19; j++)
      scanf("%d", &pan[i][j]);

  for (int j = 0; j < 19; j++) {
    for (int i = 0; i < 19; i++) {
      if (pan[i][j] != 0) {
        for (int k = 0; k < 4; k++) {
          if (check(i, j, k, pan[i][j]) == 5) {
            printf("%d\n%d %d", pan[i][j], i + 1, j + 1);
            return 0;
          }
        }
      }
    }
  }
  printf("0");
  return 0;
}
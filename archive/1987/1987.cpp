#include <stdio.h>

int R, C, ans;  // R=x Y=c
int dx[4] = {0, 0, 1, -1};
int dy[4] = {1, -1, 0, 0};
char map[20][20];
char alphabet[26];

int max(int x, int y) {
  return x < y ? y : x;
}

void backtracking(int x, int y, int step) {
  ans = max(ans, step);

  alphabet[map[x][y] - 'A'] = 1;

  for (int i = 0; i < 4; i++) {
    int nx = x + dx[i];
    int ny = y + dy[i];
    if (nx >= 0 && nx < R) {    // check x
      if (ny >= 0 && ny < C) {  // check y
        if (alphabet[map[nx][ny] - 'A'] == 0)
          backtracking(nx, ny, step + 1);
      }
    }
  }

  alphabet[map[x][y] - 'A'] = 0;
}

int main() {
  scanf("%d %d", &R, &C);

  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) {
      scanf(" %c", &map[i][j]);
    }
  }
  backtracking(0, 0, 1);
  printf("%d", ans);
  return 0;
}
#include <stdio.h>

char baseArr[3][3];
char arr[3][3];
int N, ans, tempClick;

int dx[5] = {0, 0, 1, -1, 0};
int dy[5] = {1, -1, 0, 0, 0};

int stuck = -1;

void printArr() {
  printf("------------->Array<\n");
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      printf("%c", arr[i][j]);
    }
    printf("\n");
  }
}

void click(int x, int y) {
  for (int i = 0; i < 5; i++) {
    int nx = x + dx[i];
    int ny = y + dy[i];
    if (nx < 0 || nx >= 3 || ny < 0 || ny >= 3) continue;
    if (arr[nx][ny] == '*')
      arr[nx][ny] = '.';
    else
      arr[nx][ny] = '*';
  }
  tempClick--;
}

int calc(int num) {
  // copy arr
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      arr[i][j] = baseArr[i][j];
    }
  }
  // click
  tempClick = 10;
  if (num % 2 == 1) click(0, 0);
  if (num / 2 % 2 == 1) click(0, 1);
  if (num / 4 % 2 == 1) click(0, 2);
  if (num / 8 % 2 == 1) click(1, 0);
  if (num / 16 % 2 == 1) click(1, 1);
  if (num / 32 % 2 == 1) click(1, 2);
  if (num / 64 % 2 == 1) click(2, 0);
  if (num / 128 % 2 == 1) click(2, 1);
  if (num / 256 % 2 == 1) click(2, 2);

  if (arr[0][0] == '.' && arr[0][1] == '.' && arr[0][2] == '.' &&
      arr[1][0] == '.' && arr[1][1] == '.' && arr[1][2] == '.' &&
      arr[2][0] == '.' && arr[2][1] == '.' && arr[2][2] == '.') {
    if (tempClick != 10) {
      return 10 - tempClick;
    }
  }
  return 100;
}

int main() {
  scanf("%d", &N);
  for (int iter = 0; iter < N; iter++) {
    // initialize
    ans = 100;
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        scanf(" %c", &baseArr[i][j]);
      }
    }
    // 512

    for (int i = 1; i <= 512; i++) {
      int temp = calc(i);
      if (temp < ans) ans = temp;
    }
    printf("%d\n", ans);
  }
  return 0;
}
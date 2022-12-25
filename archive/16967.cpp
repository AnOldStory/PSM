#include <stdio.h>

int arr[1100][1100];

int main() {
  int H, W, X, Y;
  scanf("%d %d %d %d", &H, &W, &X, &Y);
  int output[H][W];

  // input
  for (int i = 0; i < H + X; i++) {
    for (int j = 0; j < W + Y; j++) {
      scanf("%d", &arr[i][j]);
    }
  }

  // output initial
  for (int i = 0; i < H; i++) {
    for (int j = 0; j < W; j++) {
      output[i][j] = arr[i][j];
      if (i - X >= 0 && j - Y >= 0)
        output[i][j] -= output[i - X][j - Y];
      printf("%d ", output[i][j]);
    }
    printf("\n");
  }
}
#include <stdio.h>

#define MAX_DEPTH 500

int max(int a, int b) {
  return a < b ? b : a;
}

int main() {
  int n;
  int tree[MAX_DEPTH][MAX_DEPTH];
  // [row, column]
  int dp[MAX_DEPTH][MAX_DEPTH];
  int ans = 0;

  scanf("%d", &n);

  scanf(" %d", &tree[0][0]);      // initial tree
  ans = (dp[0][0] = tree[0][0]);  // multiple assign

  for (int i = 1; i < n; i++) {
    for (int j = 0; j <= i; j++) {
      scanf(" %d", &tree[i][j]);
      dp[i][j] = max(dp[i - 1][j], j > 0 ? dp[i - 1][j - 1] : 0);
      dp[i][j] += tree[i][j];

      ans = max(ans, dp[i][j]);
    }
  }

  printf("%d", ans);
  return 0;
}

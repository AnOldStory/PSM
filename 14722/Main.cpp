#include <iostream>

// #define MAX 2147483647

using namespace std;

// 0: 딸기 1:초코 : 바나나
int min(int a, int b) {
  return a < b ? a : b;
}

int max(int a, int b) {
  return a > b ? a : b;
}

int main() {
  int N;
  cin >> N;
  int map[N][N];
  int dp[N][N][3];

  // initial dp
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> map[i][j];
      dp[i][j][0] = 0;
      dp[i][j][1] = 0;
      dp[i][j][2] = 0;
      if (map[i][j] == 0) {
        dp[i][j][0] = 1;
      }
    }
  }
  for (int k = 0; k < 3; k++) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        cout << dp[i][j][k] << " ";
      }
      cout << endl;
    }
    cout << "=====================" << endl;
  }

  // dp[0][0][0] = 1;
  // dp[0][0][1] = 1;
  // dp[0][0][2] = 1;

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      for (int k = 0; k < 3; k++) {  // now state
        int idx = map[i][j];
        int before = (idx + 2) % 3;
        // int before2 = (idx + 1) % 3;
        // if (i == N - 1 && j == N - 1) cout << "k: " << k << "idx: " << idx << " before: " << before << " ASDASD" << dp[i - 1][j][before] << endl;
        if (i > 0) {
          if (k == idx) dp[i][j][k] = max(dp[i][j][k], dp[i - 1][j][before] + 1);
          dp[i][j][k] = max(dp[i][j][k], dp[i - 1][j][k]);
        }
        if (j > 0) {
          if (k == idx) dp[i][j][k] = max(dp[i][j][k], dp[i][j - 1][before] + 1);
          dp[i][j][k] = max(dp[i][j][k], dp[i][j - 1][k]);
        }
      }
    }
    // int up = i > 0 ? ((dp[i - 1][j] + 1) % 3 == dp[i][j] ? dp[i - 1][j] : dp[i - 1][j] + 1) : 0;
    // int left = j > 0 ? ((dp[i][j - 1] + 1) % 3 == dp[i][j] ? dp[i][j - 1] : dp[i][j - 1] + 1) : 0;
    // dp[i][j] = max(up, left);
  }

  for (int k = 0; k < 3; k++) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        cout << dp[i][j][k] << " ";
      }
      cout << endl;
    }
    cout << "=====================" << endl;
  }

  int ans = 0;
  for (int i = 0; i < 3; i++) {
    if (dp[N - 1][N - 1][i] > ans) {
      ans = dp[N - 1][N - 1][i];
    }
  }

  cout << ans << endl;

  return 0;
}
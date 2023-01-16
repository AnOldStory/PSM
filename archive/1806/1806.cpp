#include <algorithm>
#include <iostream>
using namespace std;

int main() {
  int N, S, arr[100000];

  cin >> N >> S;

  for (int i = 0; i < N; i++) {
    cin >> arr[i];
  }

  int low = 0, high = 0, sum = arr[0], len = N + 1;

  while (low <= high && high < N) {
    if (sum < S) {
      sum += arr[++high];
    } else {
      len = min(len, high - low + 1);
      sum -= arr[low++];
    }
  }

  if (len == N + 1) len = 0;
  cout << len << endl;

  return 0;
}
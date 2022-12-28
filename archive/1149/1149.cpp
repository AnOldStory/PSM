#include <stdio.h>

int memo[1000][3];
//[N][color-r0,g1,b2]

int min(int a, int b)
{
    return a < b ? a : b;
}

int main()
{
    int N;
    int r, g, b;

    scanf(" %d", &N);
    scanf(" %d %d %d", &r, &g, &b);
    memo[0][0] = r;
    memo[0][1] = g;
    memo[0][2] = b;
    for (int i = 1; i < N; i++)
    {
        scanf(" %d %d %d", &r, &g, &b);
        memo[i][0] = min(memo[i - 1][1], memo[i - 1][2]) + r;
        memo[i][1] = min(memo[i - 1][0], memo[i - 1][2]) + g;
        memo[i][2] = min(memo[i - 1][0], memo[i - 1][1]) + b;
    }

    printf("%d", min(min(memo[N - 1][0], memo[N - 1][1]), memo[N - 1][2]));
    return 0;
}

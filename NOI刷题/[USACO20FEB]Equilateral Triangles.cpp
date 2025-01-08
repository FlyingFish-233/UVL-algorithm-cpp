// P6143 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 610;

int n;
char c[NR][NR], save[NR][NR];
int sum[NR][NR];

int calc()
{
    for (int k = 2; k <= 2 * n; k++)
        for (int i = 1; i <= k - 1; i++)
            sum[i][k - i] = sum[i - 1][k - i + 1] + (c[i][k - i] == '*');
    int ans = 0;
    for (int k = 3; k <= 2 * n - 1; k++)
        for (int i = max(1, k - n); i <= min(k - 1, n); i++) if (c[i][k - i] == '*')
            for (int j = 1; j <= min(n - i, k - i - 1); j++) if (c[i + j][k - i - j] == '*')
                ans += sum[i + 2 * j][k - i] - sum[i + j][k - i + j];
    return ans;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%s", c[i] + 1);
    int ans = 0;
    for (int t = 1; t <= 4; t++) {
        ans += calc();
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                save[n - j + 1][i] = c[i][j];
        memcpy(c, save, sizeof(save));
    }
    printf("%d\n", ans);
    return 0;
}
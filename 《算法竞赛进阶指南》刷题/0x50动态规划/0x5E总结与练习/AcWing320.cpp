# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 210;

int n;
int a[NR];
int f[NR][NR];

int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]), a[i + n] = a[i];
    for (int len = 2; len <= n; len++)
        for (int l = 1; l <= 2 * n - len; l++) {
            int r = l + len - 1;
            for (int i = l; i < r; i++)
                f[l][r] = max(f[l][r], f[l][i] + f[i + 1][r] + a[l] * a[i + 1] * a[r + 1]);
        }
    int ans = 0;
    for (int i = 1; i <= n; i++)
        ans = max(ans, f[i][i + n - 1]);
    printf("%d\n", ans);
    return 0;
}
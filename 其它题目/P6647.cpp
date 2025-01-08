# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 2e6 + 10;

int n, k;
int a[NR];
long long f[2][NR];

int a_max[NR];
long long f_max[NR];

int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    if (n % k == 0) {
        long long ans = 0; int now = 0;
        for (int i = 1; i <= n; i++) {
            now = max(now, a[i]);
            if (i % k == 0) ans += now, now = 0;
        }
        printf("%lld\n", ans);
        return 0;
    }
    int num = n / k + 1, m = k * num - n;
    for (int i = 1; i <= k - m; i++)
        f[0][m] = max(f[0][m], 1ll*a[i]);
    for (int i = m - 1; i >= 0; i--)
        f[0][i] = max(f[0][i + 1], 1ll*a[k - i]);

    for (int i = 2; i <= num; i++) {
        f_max[0] = f[0][0];
        for (int j = 1; j <= m; j++)
            f_max[j] = max(f_max[j - 1], f[0][j]);
        a_max[0] = 0;
        for (int j = (i - 1) * k + 1; j <= i * k - m; j++)
            a_max[0] = max(a_max[0], a[j]);
        f[1][0] = f[0][0] + a_max[0];
        for (int j = 1; j <= m; j++) {
            a_max[j] = max(a_max[j - 1], a[(i - 1) * k - j + 1]);
            f[1][j] = max(f[1][j - 1], f[0][j] + a_max[j]);
        }
        int r = 0, now = a_max[0];
        for (int j = m; j >= 0; j--) {
            if (a[i * k - j] > now) {
                now = a[i * k - j];
                while (r < m && a_max[r + 1] <= now) r++;
            }
            f[1][j] = max(f[1][j], f_max[min(r, j)] + now);
        }
        for (int j = 0; j <= m; j++)
            f[0][j] = f[1][j];
    }
    printf("%lld\n", f[0][m]);
    return 0;
}

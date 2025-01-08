# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 60, MR = 1260;
const int mod = 1e9 + 7;

int n, m;
long long c[NR][NR], pow2[MR];
long long h[NR], f[NR][NR], g[NR][NR][NR];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= n; i++)
        c[i][0] = 1;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            c[i][j] = (c[i - 1][j] + c[i - 1][j - 1]) % mod;
    pow2[0] = 1;
    for (int i = 1; i <= n * (n - 1) / 2; i++)
        pow2[i] = pow2[i - 1] * 2 % mod;
    g[0][0][0] = 1;
    for (int i = 1; i <= n; i++) {
        h[i] = pow2[i * (i - 1) / 2];
        for (int j = 1; j <= i - 1; j++)
            h[i] = (h[i] - h[j] * c[i - 1][j - 1] % mod * pow2[(i - j) * (i - j - 1) / 2]) % mod;

        for (int j = 1; j <= i - 1; j++)
        for (int k = 1; k <= i - 1; k++) {
            long long sum = 0, k_x = 1;
            for (int x = 1; x <= min(i - k, j); x++)
                k_x = k_x * k % mod, sum = (sum + g[i - k][j - x][x] * k_x) % mod;
            f[i][j] = (f[i][j] + f[k][0] * c[i - 1][k - 1] % mod * sum) % mod;
        }

        f[i][0] = h[i];
        for (int j = 1; j <= i - 1; j++)
            f[i][0] = (f[i][0] - f[i][j]) % mod;

        for (int j = 0; j <= i - 1; j++)
        for (int k = 1; k <= i; k++)
        for (int p = 1; p <= i; p++)
        for (int q = 0; q <= j; q++)
            g[i][j][k] = (g[i][j][k] + f[p][q] * c[i - 1][p - 1] % mod * p % mod * g[i - p][j - q][k - 1]) % mod;
    }
    long long ans = 0;
    for (int i = 0; i <= min(m, n - 1); i++)
        ans = (ans + f[n][i]) % mod;
    printf("%lld\n", (ans + mod) % mod);
    return 0;
}
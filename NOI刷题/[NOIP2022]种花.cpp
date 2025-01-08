# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 1e3 + 10;
const int mod = 998244353;

int n, m, c, f;
char a[NR][NR];
int r[NR][NR], d[NR][NR];

int main()
{
    int T, id;
    scanf("%d%d", &T, &id);
    while (T--) {
        scanf("%d%d%d%d", &n, &m, &c, &f);
        for (int i = 1; i <= n; i++)
            scanf("%s", a[i] + 1);

        memset(r, -1, sizeof(r));
        memset(d, -1, sizeof(d));
        for (int j = m; j >= 1; j--)
            for (int i = 1; i <= n; i++)
                if (a[i][j] == '0') r[i][j] = r[i][j + 1] + 1;
        for (int i = n; i >= 1; i--)
            for (int j = 1; j <= m; j++)
                if (a[i][j] == '0') d[i][j] = d[i + 1][j] + 1;

        int ans1 = 0, ans2 = 0;
        for (int j = m - 1; j >= 1; j--)
            for (int i = 1, sum = 0; i <= n; i++) {
                if (a[i][j] == '1') { sum = 0; continue; }
                if (i >= 3 && a[i - 1][j] == '0' && a[i - 2][j] == '0') sum += r[i - 2][j];
                (ans1 += 1ll * sum * r[i][j] % mod) %= mod;
                (ans2 += 1ll * sum * r[i][j] % mod * d[i][j] % mod) %= mod;
            }
        printf("%d %d\n", ans1 * c, ans2 * f);
    }
    return 0;
}
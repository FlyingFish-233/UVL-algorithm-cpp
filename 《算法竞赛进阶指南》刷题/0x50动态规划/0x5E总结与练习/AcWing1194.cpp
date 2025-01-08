# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 13, MR = 1e4 + 10;

int n, m, lim;
int a[NR];
bool g[NR][NR];
int f[NR][NR][MR], cnt[NR][NR][MR];

int main()
{
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m), lim = (1 << n) - 1;
        for (int i = 0; i < n; i++)
            scanf("%d", &a[i]);
        memset(g, false, sizeof(g));
        for (int i = 1, x, y; i <= m; i++)
            scanf("%d%d", &x, &y), x--, y--, g[x][y] = g[y][x] = true;
        memset(f, -0x3f, sizeof(f));
        memset(cnt, 0, sizeof(cnt));
        for (int i = 0; i < n; i++)
            f[i][i][1 << i] = a[i], cnt[i][i][1 << i] = 1;
        for (int sta = 0; sta < lim; sta++)
            for (int i = 0; i < n; i++) if (sta >> i & 1)
                for (int j = 0; j < n; j++) if (f[i][j][sta] > -1e9)
                    for (int k = 0; k < n; k++) if (!(sta >> k & 1) && g[j][k]) {
                        int delta = a[k] + a[j] * a[k];
                        if (i != j && g[k][i]) delta += a[i] * a[j] * a[k];
                        if (f[j][k][sta | (1 << k)] < f[i][j][sta] + delta)
                            f[j][k][sta | (1 << k)] = f[i][j][sta] + delta, cnt[j][k][sta | (1 << k)] = cnt[i][j][sta];
                        else if (f[j][k][sta | (1 << k)] == f[i][j][sta] + delta)
                            cnt[j][k][sta | (1 << k)] += cnt[i][j][sta];
                    }
        int ans = -1e9, tot = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                if (ans < f[i][j][lim])
                    ans = f[i][j][lim], tot = cnt[i][j][lim];
                else if (ans == f[i][j][lim]) tot += cnt[i][j][lim];
            }
        if (ans == -1e9) printf("0 0\n");
        else printf("%d %d\n", ans, tot / 2);
    }
    return 0;
}
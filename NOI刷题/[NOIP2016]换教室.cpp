// P1850 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 2010, VR = 310;

int n, m, v, e;
int c[NR], d[NR]; double k[NR];
int g[VR][VR];
double f[NR][NR][2];

int main()
{
    scanf("%d%d%d%d", &n, &m, &v, &e);
    for (int i = 1; i <= n; i++)
        scanf("%d", &c[i]);
    for (int i = 1; i <= n; i++)
        scanf("%d", &d[i]);
    for (int i = 1; i <= n; i++)
        scanf("%lf", &k[i]);
    memset(g, 0x3f, sizeof(g));
    for (int i = 0; i <= v; i++) g[0][i] = g[i][i] = 0;
    for (int i = 1, x, y, w; i <= e; i++)
        scanf("%d%d%d", &x, &y, &w), g[x][y] = g[y][x] = min(g[x][y], w);
    for (int k = 1; k <= v; k++)
        for (int i = 1; i <= v; i++)
            for (int j = 1; j <= v; j++)
                g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
    for (int i = 0; i <= n; i++)
        for (int j = 0; j <= m; j++)
            f[i][j][0] = f[i][j][1] = 2e9;
    f[0][0][0] = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 0; j <= m; j++) {
            f[i][j][0] = f[i - 1][j][0] + g[c[i - 1]][c[i]];
            f[i][j][0] = min(f[i][j][0], f[i - 1][j][1] + k[i - 1] * g[d[i - 1]][c[i]] + (1 - k[i - 1]) * g[c[i - 1]][c[i]]);
            if (j == 0) continue;
            f[i][j][1] = f[i - 1][j - 1][0] + k[i] * g[c[i - 1]][d[i]] + (1 - k[i]) * g[c[i - 1]][c[i]];
            double save = k[i] * k[i - 1] * g[d[i - 1]][d[i]] + k[i] * (1 - k[i - 1]) * g[c[i - 1]][d[i]];
            save += (1 - k[i]) * k[i - 1] * g[d[i - 1]][c[i]] + (1 - k[i]) * (1 - k[i - 1]) * g[c[i - 1]][c[i]];
            f[i][j][1] = min(f[i][j][1], f[i - 1][j - 1][1] + save);
        }
    double ans = 2e9;
    for (int i = 0; i <= m; i++)
        ans = min(ans, min(f[n][i][0], f[n][i][1]));
    printf("%.2f\n", ans);
    return 0;
}

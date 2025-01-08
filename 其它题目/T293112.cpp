# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 110;

int n, m, c_max, T;
int p[NR], c[NR];
int dis[NR][NR][20], w[NR][NR], save[NR];
int f[NR][NR * NR];

int main()
{
    scanf("%d%d%d%d", &n, &m, &c_max, &T);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &p[i], &c[i]), c[i] = min(c[i], c_max);
    memset(dis, -0x3f, sizeof(dis));
    for (int i = 1; i <= n; i++) dis[i][i][0] = 0;
    for (int i = 1, x, y, w; i <= m; i++)
        scanf("%d%d%d", &x, &y, &w), dis[x][y][0] = max(dis[x][y][0], w);
    for (int i = 1; (1 << i) <= c_max; i++)
        for (int x = 1; x <= n; x++)
            for (int y = 1; y <= n; y++)
                for (int z = 1; z <= n; z++)
                    dis[x][y][i] = max(dis[x][y][i], dis[x][z][i - 1] + dis[z][y][i - 1]);
    memset(w, -0x3f, sizeof(w));
    for (int i = 1; i <= n; i++) w[i][i] = 0;
    for (int x = 1; x <= n; x++)
        for (int i = 0; (1 << i) <= c[x]; i++) if (c[x] >> i & 1) {
            memset(save, -0x3f, sizeof(save));
            for (int y = 1; y <= n; y++)
                for (int z = 1; z <= n; z++)
                    save[y] = max(save[y], w[x][z] + dis[z][y][i]);
            memcpy(w[x], save, sizeof(save));
        }
    for (int i = 0; i <= n * n; i++)
        for (int x = 1; x <= n; x++) if (i >= p[x])
            for (int y = 1; y <= n; y++)
                f[x][i] = max(f[x][i], f[y][i - p[x]] + w[x][y]);
    while (T--) {
        int s, q, d;
        scanf("%d%d%d", &s, &q, &d);
        printf("%d\n", q - (lower_bound(f[s] + 1, f[s] + q + 1, d) - f[s]));
    }
    return 0;
}
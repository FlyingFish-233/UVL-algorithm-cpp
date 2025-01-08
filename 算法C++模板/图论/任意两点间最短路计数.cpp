// P2047 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 110;
const int INF = 0x3f3f3f3f;

int n, m;
int f[NR][NR];
long long cnt[NR][NR];

int main()
{
    scanf("%d%d", &n, &m);
    memset(f, 0x3f, sizeof(f));
    for (int i = 1, x, y, w; i <= m; i++) {
        scanf("%d%d%d", &x, &y, &w);
        if (f[x][y] > w) f[x][y] = f[y][x] = w, cnt[x][y] = cnt[y][x] = 1;
        else if (f[x][y] == w) cnt[x][y]++, cnt[y][x]++;
    }
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) {
                int w = f[i][k] + f[k][j];
                if (f[i][j] > w) f[i][j] = w, cnt[i][j] = cnt[i][k] * cnt[k][j];
                else if (f[i][j] == w) cnt[i][j] += cnt[i][k] * cnt[k][j];
            }
    for (int k = 1; k <= n; k++) {
        double ans = 0;
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) if (i != j && j != k && k != i)
                if (f[i][k] + f[k][j] == f[i][j])
                    ans += 1.0 * cnt[i][k] * cnt[k][j] / cnt[i][j];
        printf("%.3f\n", ans);
    }
    return 0;
}
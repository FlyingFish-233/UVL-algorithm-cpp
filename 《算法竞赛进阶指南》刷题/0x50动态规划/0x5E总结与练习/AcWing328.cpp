# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int MR = 6e4 + 10;

int n, m;
bool a[160][20];
int p[20], f[2][MR];

void dfs(int x, int y, int sta, int sta0, int delta)
{
    if (y == m) { f[x & 1][sta0] = max(f[x & 1][sta0], f[(x & 1) ^ 1][sta] + delta); return; }
    int t = sta / p[y] % 3;
    if (t >= 1) { dfs(x, y + 1, sta, sta0 + (t - 1) * p[y], delta); return; }
    dfs(x, y + 1, sta, sta0, delta);
    if (x + 2 <= n && y + 1 < m && !a[x][y] && !a[x][y + 1] && !a[x + 1][y] && !a[x + 1][y + 1]
        && !a[x + 2][y] && !a[x + 2][y + 1] && sta / p[y + 1] % 3 == 0)
        dfs(x, y + 2, sta, sta0 + 2 * p[y] + 2 * p[y + 1], delta + 1);
    if (x + 1 <= n && y + 2 < m && !a[x][y] && !a[x][y + 1] && !a[x][y + 2] && !a[x + 1][y]
        && !a[x + 1][y + 1] && !a[x + 1][y + 2] && sta / p[y + 1] % 3 == 0 && sta / p[y + 2] % 3 == 0)
        dfs(x, y + 3, sta, sta0 + p[y] + p[y + 1] + p[y + 2], delta + 1);
}

int main()
{
    p[0] = 1;
    for (int i = 1; i <= 10; i++)
        p[i] = p[i - 1] * 3;
    int T;
    scanf("%d", &T);
    while (T--) {
        int tmp;
        scanf("%d%d%d", &n, &m, &tmp);
        memset(a, false, sizeof(a));
        for (int i = 1, x, y; i <= tmp; i++)
            scanf("%d%d", &x, &y), a[x][--y] = true;
        memset(f, -1, sizeof(f)), f[0][0] = 0;
        for (int i = 1; i <= n; i++) {
            memset(f[i & 1], -1, sizeof(f[i & 1]));
            for (int sta = 0; sta < p[m]; sta++)
                if (f[(i & 1) ^ 1][sta] != -1) dfs(i, 0, sta, 0, 0);
        }
        int ans = 0;
        for (int sta = 0; sta < p[m]; sta++)
            ans = max(ans, f[n & 1][sta]);
        printf("%d\n", ans);
    }
    return 0;
}
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 210;

int n, m;
bool g[NR][NR];

bool vis[NR];
int opp[NR];

bool find(int x)
{
    if (vis[x]) return false;
    vis[x] = true;
    for (int y = 1; y <= n; y++) if (g[x][y])
        if (opp[y] == 0 || find(opp[y]))
            { opp[y] = x; return true; }
    return false;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1, x, y; i <= m; i++)
        scanf("%d%d", &x, &y), g[x][y] = true;
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                g[i][j] |= g[i][k] && g[k][j];
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        memset(vis, false, sizeof(vis));
        ans += find(i);
    }
    printf("%d\n", n - ans);
    return 0;
}
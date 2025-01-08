# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 150;

struct Edge
{
    int to, next;
};

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
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        memset(g, false, sizeof(g));
        for (int i = 1, x, y; i <= m; i++)
            scanf("%d%d", &x, &y), g[x][y] = true;
        memset(opp, 0, sizeof(opp));
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            memset(vis, false, sizeof(vis));
            ans += find(i);
        }
        printf("%d\n", n - ans);
    }
    return 0;
}
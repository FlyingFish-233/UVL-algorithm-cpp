# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>

using namespace std;

const int NR = 60, MR = 3e4 + 10;

struct Edge
{
    int to, next;
};

int n, m;
char c[NR][NR];
int tot, a[NR][NR], b[NR][NR];

int gsz, fte[MR];
Edge g[MR];

void addEdge(int x, int y)
{
    g[++gsz] = (Edge) {y, fte[x]};
    fte[x] = gsz;
}

bool vis[MR];
int opp[MR];

bool find(int x)
{
    if (vis[x]) return false;
    vis[x] = true;
    for (int i = fte[x]; i; i = g[i].next) {
        int y = g[i].to;
        if (opp[y] == 0 || find(opp[y]))
            { opp[y] = x; return true; }
    }
    return false;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%s", c[i] + 1);
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (c[i][j] == '*') a[i][j] = (c[i][j - 1] == '*') ? tot : ++tot;
    for (int j = 1; j <= m; j++)
        for (int i = 1; i <= n; i++)
            if (c[i][j] == '*') b[i][j] = (c[i - 1][j] == '*') ? tot : ++tot;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++)
            if (c[i][j] == '*') addEdge(a[i][j], b[i][j]);
    int ans = 0;
    for (int i = 1; i <= tot; i++) {
        memset(vis, false, sizeof(vis));
        ans += find(i);
    }
    printf("%d\n", ans);
    return 0;
}
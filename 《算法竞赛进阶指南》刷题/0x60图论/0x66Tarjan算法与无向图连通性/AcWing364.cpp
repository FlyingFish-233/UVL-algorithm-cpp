# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

using namespace std;

const int NR = 1e5 + 10, MR = 4e5 + 10;

struct Edge
{
    int to, next;
};

int n, m;
int gsz = 1, fte[NR];
Edge g[MR];

void addEdge(int x, int y)
{
    g[++gsz] = (Edge) {y, fte[x]};
    fte[x] = gsz;
}

int now, dfn[NR], low[NR];
bool bridge[MR];

void tarjan(int x, int in_edge)
{
    dfn[x] = low[x] = ++now;
    for (int i = fte[x]; i; i = g[i].next) {
        int y = g[i].to;
        if ((i ^ 1) == in_edge) continue;
        if (dfn[y] != 0) { low[x] = min(low[x], dfn[y]); continue; }
        tarjan(y, i), low[x] = min(low[x], low[y]);
        if (dfn[x] < low[y]) bridge[i] = bridge[i ^ 1] = true;
    }
}

int tot, c[NR];

void color(int x)
{
    c[x] = tot;
    for (int i = fte[x]; i; i = g[i].next) {
        int y = g[i].to;
        if (c[y] == 0 && !bridge[i]) color(y);
    }
}

vector<int> G[NR];
int dep[NR], father[NR];

void dfs(int x, int dad)
{
    father[x] = dad, dep[x] = dep[dad] + 1;
    for (int i = 0; i < (int) G[x].size(); i++) {
        int y = G[x][i];
        if (y != dad) dfs(y, x);
    }
}

int fa[NR];

int find(int x)
{
    if (fa[x] == x) return x;
    return fa[x] = find(fa[x]);
}

void merge(int x, int y)
{
    fa[find(x)] = find(y);
}

int main()
{
    for (int cnt = 1; scanf("%d%d", &n, &m) && !(n == 0 && m == 0); cnt++) {
        memset(fte, 0, sizeof(fte)), gsz = 1;
        for (int i = 1, x, y; i <= m; i++)
            scanf("%d%d", &x, &y), addEdge(x, y), addEdge(y, x);

        memset(bridge, false, sizeof(bridge));
        memset(dfn, 0, sizeof(dfn)), now = 0;
        memset(low, 0, sizeof(low));
        tarjan(1, 0);

        memset(c, 0, sizeof(c)), tot = 0;
        for (int i = 1; i <= n; i++)
            if (c[i] == 0) ++tot, color(i);

        for (int i = 1; i <= tot; i++)
            G[i].clear();
        for (int x = 1; x <= n; x++)
            for (int i = fte[x]; i; i = g[i].next) {
                int y = g[i].to;
                if (c[x] != c[y])
                    G[c[x]].push_back(c[y]);
            }

        memset(father, 0, sizeof(father));
        memset(dep, 0, sizeof(dep));
        dfs(1, 0);

        for (int i = 1; i <= tot; i++)
            fa[i] = i;
        int ans = tot - 1, T;
        scanf("%d", &T);
        printf("Case %d:\n", cnt);
        while (T--) {
            int x, y;
            scanf("%d%d", &x, &y);
            x = c[x], y = c[y];
            while (find(x) != find(y)) {
                if (dep[find(x)] < dep[find(y)]) swap(x, y);
                x = find(x), merge(x, father[x]);
                x = father[x], ans--;
            }
            printf("%d\n", ans);
        }
        puts("");
    }
    return 0;
}
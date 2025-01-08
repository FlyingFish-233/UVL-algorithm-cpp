// P6626 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

# define id first
# define k second

using namespace std;

const int NR = 1e5 + 10;

struct Edge
{
    int to, next;
};

int n, m;
int gsz, fte[NR];
Edge g[NR << 1];

void addEdge(int x, int y)
{
    g[++gsz] = (Edge) {y, fte[x]}, fte[x] = gsz;
    g[++gsz] = (Edge) {x, fte[y]}, fte[y] = gsz;
}

vector< pair<int, int> > q[NR];
int ans[NR];

int root, all, sz[NR], f[NR];
bool vis[NR];

void getRoot(int x, int fa)
{
    sz[x] = 1, f[x] = 0;
    for (int i = fte[x]; i; i = g[i].next) {
        int y = g[i].to;
        if (y == fa || vis[y]) continue;
        getRoot(y, x);
        sz[x] += sz[y];
        f[x] = max(f[x], sz[y]);
    }
    f[x] = max(f[x], all - sz[x]);
    if (f[x] < f[root]) root = x;
}

int dep[NR], buc[NR];

void modify(int x, int fa, int d)
{
    dep[x] = dep[fa] + 1, buc[dep[x]] += d;
    for (int i = fte[x]; i; i = g[i].next) {
        int y = g[i].to;
        if (y != fa && !vis[y]) modify(y, x, d);
    }
}

void change(int x, int fa)
{
    for (int i = 0; i < (int) q[x].size(); i++)
        if (q[x][i].k >= dep[x]) ans[q[x][i].id] += buc[q[x][i].k - dep[x]];
    for (int i = fte[x]; i; i = g[i].next) {
        int y = g[i].to;
        if (y != fa && !vis[y]) change(y, x);
    }
}

void solve(int x)
{
    dep[x] = 0, buc[0]++;
    for (int i = fte[x]; i; i = g[i].next)
        if (!vis[g[i].to]) modify(g[i].to, x, 1);
    for (int i = 0; i < (int) q[x].size(); i++)
        ans[q[x][i].id] += buc[q[x][i].k];
    for (int i = fte[x]; i; i = g[i].next) {
        int y = g[i].to;
        if (vis[y]) continue;
        modify(y, x, -1);
        change(y, x);
        modify(y, x, 1);
    }
    buc[0]--;
    for (int i = fte[x]; i; i = g[i].next)
        if (!vis[g[i].to]) modify(g[i].to, x, -1);
}

void dfs(int x)
{
    vis[x] = true, solve(x);
    for (int i = fte[x]; i; i = g[i].next) {
        int y = g[i].to;
        if (vis[y]) continue;
        all = sz[y], root = 0;
        getRoot(y, x), dfs(root);
    }
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n, &m);
        memset(fte, 0, sizeof(fte)), gsz = 0;
        for (int i = 1; i <= n; i++) q[i].clear();
        for (int i = 1, x, y; i <= n - 1; i++)
            scanf("%d%d", &x, &y), addEdge(x, y);
        for (int i = 1, x, y; i <= m; i++)
            scanf("%d%d", &x, &y), q[x].push_back(make_pair(i, y));
        memset(ans, 0, sizeof(ans));
        memset(vis, false, sizeof(vis));
        all = n, f[0] = 2e9;
        getRoot(1, 0), dfs(root);
        for (int i = 1; i <= m; i++)
            printf("%d\n", ans[i]);
    }
    return 0;
}

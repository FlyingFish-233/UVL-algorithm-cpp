// AcWing397 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <stack>
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
stack<int> s;
int tot, c[NR];

void tarjan(int x, int in_edge)
{
    dfn[x] = low[x] = ++now, s.push(x);
    for (int i = fte[x]; i; i = g[i].next) {
        int y = g[i].to;
        if ((i ^ 1) == in_edge) continue;
        if (dfn[y] != 0) { low[x] = min(low[x], dfn[y]); continue; }
        tarjan(y, i), low[x] = min(low[x], low[y]);
        if (dfn[x] < low[y]) bridge[i] = bridge[i ^ 1] = true;
    }
    if (dfn[x] != low[x]) return;
    c[x] = ++tot;
    while (s.top() != x)
        c[s.top()] = tot, s.pop();
    s.pop();
}

vector<int> G[NR];
int dep[NR], fa[NR][30];

void build(int x, int dad)
{
    dep[x] = dep[fa[x][0] = dad] + 1;
    for (int i = 1; (1 << i) <= dep[x]; i++)
        fa[x][i] = fa[fa[x][i - 1]][i - 1];
    for (int i = 0; i < (int) G[x].size(); i++)
        if (G[x][i] != dad) build(G[x][i], x);
}

int lca(int x, int y)
{
    if (dep[x] > dep[y]) swap(x, y);
    for (int i = 20; i >= 0; i--)
        if (dep[fa[y][i]] >= dep[x]) y = fa[y][i];
    if (x == y) return x;
    for (int i = 20; i >= 0; i--)
        if (fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
    return fa[x][0];
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1, x, y; i <= m; i++)
        scanf("%d%d", &x, &y), addEdge(x, y), addEdge(y, x);
    for (int i = 1; i <= n; i++)
        if (dfn[i] == 0) tarjan(i, 0);
    for (int x = 1; x <= n; x++)
        for (int i = fte[x]; i; i = g[i].next) {
            int y = g[i].to;
            if (c[x] != c[y]) G[c[x]].push_back(c[y]);
        }
    dep[1] = 0, build(1, 0);
    int T;
    scanf("%d", &T);
    while (T--) {
        int a, b;
        scanf("%d%d", &a, &b);
        a = c[a], b = c[b];
        printf("%d\n", dep[a] + dep[b] - 2 * dep[lca(a, b)]);
    }
    return 0;
}
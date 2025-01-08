# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>

using namespace std;

const int NR = 5e5 + 10;

struct Edge
{
    int to, next, w;
};

int n, m;
int to[NR];
int gsz, fte[NR], deg[NR];
Edge g[NR << 1];

void addEdge(int x, int y)
{
    g[++gsz] = (Edge) {y, fte[x]}, fte[x] = gsz, deg[x]++;
    g[++gsz] = (Edge) {x, fte[y]}, fte[y] = gsz, deg[y]++;
}

int tot, c[NR];
vector<int> block;

void color(int x)
{
    c[x] = tot, block.push_back(x);
    for (int i = fte[x]; i; i = g[i].next)
        if (c[g[i].to] == 0) color(g[i].to);
}

int q[NR];
bool vis[NR];
int len[NR], loop[NR], s[NR];

void get_loop()
{
    int l = 1, r = 0;
    for (int i = 0; i < (int) block.size(); i++)
        if (deg[block[i]] == 1) q[++r] = block[i];
    while (l <= r) {
        int x = q[l++];
        vis[x] = true;
        for (int i = fte[x]; i; i = g[i].next) {
            int y = g[i].to;
            if (!vis[y] && --deg[y] == 1) q[++r] = y;
        }
    }
    int x;
    for (int i = 0; i < (int) block.size(); i++)
        if (!vis[block[i]]) { x = block[i]; break; }
    loop[++len[tot]] = x, s[x] = len[tot];
    for (int i = to[x]; i != x; i = to[i])
        loop[++len[tot]] = i, s[i] = len[tot];
}

int RT, root[NR];
int dep[NR], fa[NR][30];

void build(int x, int dad)
{
    fa[x][0] = dad, root[x] = RT, dep[x] = dep[dad] + 1;
    for (int i = 1; (1 << i) <= dep[x]; i++)
        fa[x][i] = fa[fa[x][i - 1]][i - 1];
    for (int i = fte[x]; i; i = g[i].next)
        if (g[i].to != dad && vis[g[i].to]) build(g[i].to, x);
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

bool cmp(int a1, int b1, int a2, int b2)
{
    if (max(a1, b1) != max(a2, b2)) return max(a1, b1) < max(a2, b2);
    if (min(a1, b1) != min(a2, b2)) return min(a1, b1) < min(a2, b2);
    return a1 >= b1;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int x = 1; x <= n; x++)
        scanf("%d", &to[x]), addEdge(x, to[x]);
    for (int i = 1; i <= n; i++) if (c[i] == 0) {
        block.clear(), ++tot, color(i);
        get_loop();
        for (int j = 1; j <= len[tot]; j++)
            dep[loop[j]] = 1, build(RT = loop[j], 0);
    }
    while (m--) {
        int x, y;
        scanf("%d%d", &x, &y);
        if (c[x] != c[y]) { printf("-1 -1\n"); continue; }
        if (root[x] == root[y]) { printf("%d %d\n", dep[x] - dep[lca(x, y)], dep[y] - dep[lca(x, y)]); continue; }
        int a1 = dep[x] - 1 + (s[root[y]] - s[root[x]] + len[c[x]]) % len[c[x]], b1 = dep[y] - 1;
        int a2 = dep[x] - 1, b2 = dep[y] - 1 + (s[root[x]] - s[root[y]] + len[c[x]]) % len[c[x]];
        if (cmp(a1, b1, a2, b2)) printf("%d %d\n", a1, b1);
        else printf("%d %d\n", a2, b2);
    }
    return 0;
}
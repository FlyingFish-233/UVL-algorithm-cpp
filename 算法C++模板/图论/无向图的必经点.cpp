// AcWing398 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <stack>
# include <vector>

using namespace std;

const int NR = 2e4 + 10, MR = 1e5 + 10;

struct Edge
{
    int to, next;
};

int n, m;
int gsz = 1, fte[NR];
Edge g[MR << 1];

void addEdge(int x, int y)
{
    g[++gsz] = (Edge) {y, fte[x]};
    fte[x] = gsz;
}

int now, root;
int dfn[NR], low[NR];
bool cut[NR];

int tot, all, c[NR], ce[MR];
stack<int> s, se;
vector<int> dcc[NR];

void tarjan(int x, int dad)
{
    dfn[x] = low[x] = ++now, s.push(x);
    if (x == root && fte[x] == 0) { dcc[++tot].push_back(x); return; }
    int tmp = 0;
    for (int i = fte[x]; i; i = g[i].next) {
        int y = g[i].to, z;
        if (dfn[y] != 0) { 
            low[x] = min(low[x], dfn[y]);
            if (y != dad) se.push(i >> 1);
            continue;
        }
        se.push(i >> 1), tarjan(y, x), low[x] = min(low[x], low[y]);
        if (dfn[x] <= low[y]) {
            tmp++;
            if (x != root || tmp > 1) cut[x] = true;
            dcc[++tot].push_back(x);
            do {
                z = s.top(), s.pop();
                dcc[tot].push_back(z);
            } while (z != y);
            do {
                z = se.top(), se.pop();
                ce[z] = tot;
            } while (z != i >> 1);
        }
    }
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

void init()
{
    memset(fte, 0, sizeof(fte)), gsz = 1;
    memset(dfn, 0, sizeof(dfn)), now = 0;
    memset(low, 0, sizeof(low));
    memset(cut, false, sizeof(cut));
    memset(c, 0, sizeof(c)), tot = 0;
    memset(ce, 0, sizeof(ce));
    memset(dep, 0, sizeof(dep));
    memset(fa, 0, sizeof(fa));
}

int main()
{
    while (scanf("%d%d", &n, &m) && !(n == 0 && m == 0)) {
        init();
        for (int i = 1, x, y; i <= m; i++)
            scanf("%d%d", &x, &y), addEdge(x, y), addEdge(y, x);
        for (int i = 1; i <= n; i++)
            if (dfn[i] == 0) tarjan(root = i, 0);
        all = tot;
        for (int i = 1; i <= n; i++)
            if (cut[i]) c[i] = ++all;
        for (int i = 1; i <= tot; i++)
            for (int j = 0; j < (int) dcc[i].size(); j++) {
                int x = dcc[i][j];
                if (cut[x]) G[c[x]].push_back(i), G[i].push_back(c[x]);
                else c[x] = i;
            }
        dep[1] = 0, build(1, 0);
        int T;
        scanf("%d", &T);
        while (T--) {
            int a, b;
            scanf("%d%d", &a, &b);
            a = ce[a], b = ce[b];
            printf("%d\n", (dep[a] + dep[b] - 2 * dep[lca(a, b)]) / 2);
        }
        for (int i = 1; i <= tot; i++) dcc[i].clear();
        for (int i = 1; i <= all; i++) G[i].clear();
    }
    return 0;
}
// P3387 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>
# include <vector>

using namespace std;

const int NR = 1e4 + 10;

int n, m;
int a[NR];
vector<int> g[NR];

int now, dfn[NR], low[NR];
int top, st[NR]; bool ins[NR];
int tot, c[NR], v[NR];

void tarjan(int x)
{
    low[x] = dfn[x] = ++now;
    ins[x] = true, st[++top] = x;
    for (int i = 0; i < (int) g[x].size(); i++) {
        int y = g[x][i];
        if (dfn[y] == 0) tarjan(y), low[x] = min(low[x], low[y]);
        else if (ins[y]) low[x] = min(low[x], dfn[y]);
    }
    if (dfn[x] != low[x]) return;
    c[x] = ++tot, v[tot] += a[x];
    while (st[top] != x) {
        int y = st[top--]; ins[y] = false;
        c[y] = tot, v[tot] += a[y];
    }
    top--, ins[x] = false;
}

int in[NR];
vector<int> G[NR];
queue<int> q;
int f[NR];

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
        scanf("%d", &a[i]);
    for (int i = 1, x, y; i <= m; i++)
        scanf("%d%d", &x, &y), g[x].push_back(y); 
    for (int i = 1; i <= n; i++)
        if (dfn[i] == 0) tarjan(i);
    for (int x = 1; x <= n; x++)
        for (int i = 0; i < (int) g[x].size(); i++) {
            int y = g[x][i];
            if (c[x] != c[y]) G[c[x]].push_back(c[y]), in[c[y]]++;
        }
    for (int i = 1; i <= tot; i++)
        if (in[i] == 0) q.push(i);
    int ans = 0;
    while (!q.empty()) {
        int x = q.front(); q.pop();
        f[x] += v[x], ans = max(ans, f[x]);
        for (int i = 0; i < G[x].size(); i++) {
            int y = G[x][i];
            f[y] = max(f[y], f[x]);
            if (--in[y] == 0) q.push(y);
        }
    }
    printf("%d\n", ans);
    return 0;
}
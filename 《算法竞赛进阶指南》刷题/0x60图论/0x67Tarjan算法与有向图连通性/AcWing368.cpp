# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <vector>
# include <stack>
# include <queue>

using namespace std;

const int NR = 1e5 + 10;

struct Edge
{
    int to, w;
};

int n, m;
vector<Edge> g[NR];

void addEdge(int x, int y, int w)
{
    g[x].push_back((Edge) {y, w});
}

int now, dfn[NR], low[NR];
bool ins[NR];
stack<int> s;

int tot, c[NR], sz[NR];

void tarjan(int x)
{
    dfn[x] = low[x] = ++now;
    ins[x] = true, s.push(x);
    for (int i = 0; i < (int) g[x].size(); i++) {
        int y = g[x][i].to;
        if (dfn[y] == 0) tarjan(y), low[x] = min(low[x], low[y]);
        else if (ins[y]) low[x] = min(low[x], dfn[y]);
    }
    if (dfn[x] != low[x]) return;
    c[x] = ++tot, sz[tot] = 1;
    while (s.top() != x) {
        int y = s.top();
        c[y] = tot, sz[tot]++;
        ins[y] = false, s.pop();
    }
    ins[x] = false, s.pop();
}

int in[NR];
vector<Edge> G[NR];

int f[NR];
queue<int> q;

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int type, x, y;
        scanf("%d%d%d", &type, &x, &y);
        switch (type) {
            case 1: addEdge(x, y, 0), addEdge(y, x, 0); break;
            case 2: addEdge(x, y, 1); break;
            case 3: addEdge(y, x, 0); break;
            case 4: addEdge(y, x, 1); break;
            case 5: addEdge(x, y, 0); break;
        }
    }
    for (int i = 1; i <= n; i++)
        if (dfn[i] == 0) tarjan(i);
    for (int x = 1; x <= n; x++)
        for (int i = 0; i < (int) g[x].size(); i++) {
            int y = g[x][i].to;
            if (c[x] == c[y] && g[x][i].w == 1) return printf("-1\n"), 0;
            if (c[x] != c[y]) G[c[x]].push_back((Edge) {c[y], g[x][i].w}), in[c[y]]++;
        }
    for (int i = 1; i <= tot; i++)
        if (in[i] == 0) q.push(i);
    long long ans = 0;
    while (!q.empty()) {
        int x = q.front(); q.pop();
        ans += 1ll * (f[x] + 1) * sz[x];
        for (int i = 0; i < (int) G[x].size(); i++) {
            int y = G[x][i].to;
            f[y] = max(f[y], f[x] + G[x][i].w);
            if (--in[y] == 0) q.push(y);
        }
    }
    printf("%lld\n", ans);
    return 0;
}
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <stack>

using namespace std;

const int NR = 5e3 + 10, MR = 2e4 + 10;

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
int tot, c[NR], deg[NR];

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

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1, x, y; i <= m; i++)
        scanf("%d%d", &x, &y), addEdge(x, y), addEdge(y, x);
    for (int i = 1; i <= n; i++)
        if (dfn[i] == 0) tarjan(i, 0);
    for (int x = 1; x <= n; x++)
        for (int i = fte[x]; i; i = g[i].next)
            if (c[x] != c[g[i].to]) deg[c[x]]++;
    int cnt = 0;
    for (int i = 1; i <= tot; i++)
        if (deg[i] == 1) cnt++;
    printf("%d\n", (cnt + 1) / 2);
    return 0;
}
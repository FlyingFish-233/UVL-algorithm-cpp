// P3376 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

using namespace std;

const int NR = 210, MR = 5e3 + 10;

struct Edge
{
    int to, next, w;
};

int n, m, s, t;
int gsz = 1, fte[NR];
Edge g[MR << 1];

void addEdge(int x, int y, int w)
{
    g[++gsz] = (Edge) {y, fte[x], w}, fte[x] = gsz;
    g[++gsz] = (Edge) {x, fte[y], 0}, fte[y] = gsz;
}

bool vis[NR];
int incf[NR], pre[NR];
queue<int> q;

bool bfs()
{
    while (!q.empty()) q.pop();
    memset(vis, false, sizeof(vis));
    vis[s] = true, q.push(s), incf[s] = (1ll << 31) - 1;
    while (!q.empty()) {
        int x = q.front(); q.pop();
        for (int i = fte[x]; i; i = g[i].next) {
            int y = g[i].to;
            if (g[i].w == 0 || vis[y]) continue;
            incf[y] = min(incf[x], g[i].w), pre[y] = i;
            vis[y] = true, q.push(y);
            if (y == t) return true;
        }
    }
    return false;
}

int update()
{
    int x = t;
    while (x != s) {
        int i = pre[x];
        g[i].w -= incf[t];
        g[i ^ 1].w += incf[t];
        x = g[i ^ 1].to;
    }
    return incf[t];
}

int main()
{
    scanf("%d%d%d%d", &n, &m, &s, &t);
    for (int i = 1, x, y, w; i <= m; i++)
        scanf("%d%d%d", &x, &y, &w), addEdge(x, y, w);
    long long ans = 0;
    while (bfs()) ans += update();
    printf("%lld\n", ans);
    return 0;
}
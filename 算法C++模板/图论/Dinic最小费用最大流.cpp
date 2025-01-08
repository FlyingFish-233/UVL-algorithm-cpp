// P3381 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

using namespace std;

const int NR = 5e3 + 10, MR = 5e4 + 10;
const long long INF = 0x3f3f3f3f3f3f3f3f;

struct Edge
{
    int to, next, w, c;
};

int n, m, s, t;
int gsz = 1, fte[NR];
Edge g[MR << 1];

queue <int> q;
int head[NR];
long long dis[NR];
bool already[NR], flag[NR];

void addEdge(int x, int y, int w, int c)
{
    g[++gsz] = (Edge) {y, fte[x], w, c}, fte[x] = gsz;
    g[++gsz] = (Edge) {x, fte[y], 0, -c}, fte[y] = gsz;
}

bool spfa()
{
    memset(dis, 0x3f, sizeof(dis));
    memcpy(head, fte, sizeof(fte));
    q.push(s), dis[s] = 0, already[s] = true;
    while (!q.empty()) {
        int x = q.front(); q.pop();
        already[x] = false;
        for (int i = fte[x]; i; i = g[i].next) {
            int y = g[i].to;
            if (g[i].w == 0 || dis[y] <= dis[x] + g[i].c) continue;
            dis[y] = dis[x] + g[i].c;
            if (!already[y]) q.push(y), already[y] = true;
        }
    }
    return dis[t] < INF;
}

long long dinic(int x, long long lim)
{
    if (x == t) return lim;
    int flow = 0;
    flag[x] = true;
    for (int i = head[x]; i && flow < lim; i = g[i].next) {
        int y = g[i].to;
        if (flag[y] || g[i].w == 0 || dis[y] != dis[x] + g[i].c) continue;
        int delta = dicnic(y, min(lim - flow, 1ll * g[i].w));
        if (delta == 0) dis[y] = INF;
        else g[i].w -= delta, g[i ^ 1].w += delta, flow += delta;
        head[x] = i;
    }
    flag[x] = false;
    return flow;
}

int main()
{
    scanf("%d%d%d%d", &n, &m, &s, &t);
    for (int i = 1, x, y, w, c; i <= m; i++)
        scanf("%d%d%d%d", &x, &y, &w, &c), addEdge(x, y, w, c);
    long long maxflow = 0, ans = 0;
    while (spfa()) {
        int save = dicnic(s, INF);
        maxflow += save, ans += dis[t] * save;
    }
    printf("%lld %lld\n", maxflow, ans);
}
// P3381 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

using namespace std;

const int NR = 5e3 + 10, MR = 5e4 + 10;
long long INF = 0x3f3f3f3f3f3f3f3f;

struct Edge
{
    int to, next, w, c;
};

int n, m, s, t;
int gsz = 1, fte[NR];
Edge g[MR << 1];

void addEdge(int x, int y, int w, int c)
{
    g[++gsz] = (Edge) {y, fte[x], w, c}, fte[x] = gsz;
    g[++gsz] = (Edge) {x, fte[y], 0, -c}, fte[y] = gsz;
}

bool already[NR];
long long dis[NR];
int incf[NR], pre[NR];
queue<int> q;

bool spfa()
{
    memset(dis, 0x3f, sizeof(dis));
    q.push(s), dis[s] = 0, already[s] = true, incf[s] = INF;
    while (!q.empty()) {
        int x = q.front(); q.pop();
        already[x] = false;
        for (int i = fte[x]; i; i = g[i].next) {
            int y = g[i].to;
            if (g[i].w == 0 || dis[y] <= dis[x] + g[i].c) continue;
            dis[y] = dis[x] + g[i].c;
            incf[y] = min(incf[x], g[i].w), pre[y] = i;
            if (!already[y]) q.push(y), already[y] = true;
        }
    }
    return dis[t] < INF;
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
    for (int i = 1, x, y, w, c; i <= m; i++)
        scanf("%d%d%d%d", &x, &y, &w, &c), addEdge(x, y, w, c);
    long long maxflow = 0, ans = 0;
    while (spfa()) {
        int save = update();
        maxflow += save, ans += dis[t] * save;
    }
    printf("%lld %lld\n", maxflow, ans);
    return 0;
}
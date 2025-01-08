// P5905 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

using namespace std;

const int NR = 3e3 + 10, MR = 1e4 + 10;
const long long INF = 1e17;

struct Edge
{
    int to, next, w;
};

int n, m;
int gsz, fte[NR];
Edge g[MR];

void addEdge(int x, int y, int w)
{
    g[++gsz] = (Edge) {y, fte[x], w};
    fte[x] = gsz;
}

long long h[NR]; int len[NR];
bool already[NR];

bool spfa(int s)
{
    queue<int> q;
    for (int i = 1; i <= n; i++) h[i] = 1;
    h[s] = 0, q.push(s), already[s] = true;
    while (!q.empty()) {
        int x = q.front(); q.pop();
        already[x] = false;
        for (int i = fte[x]; i; i = g[i].next) {
            int y = g[i].to;
            if (h[y] <= h[x] + g[i].w) continue;
            h[y] = h[x] + g[i].w, len[y] = len[x] + 1;
            if (len[y] >= n + 1) return false;
            if (!already[y]) q.push(y), already[y] = true;
        }
    }
    return true;
}

struct Node
{
    int x; long long d;
    bool operator < (const Node &cmp) const {
        return d > cmp.d;
    }
};

long long dis[NR][NR];
bool flag[NR];

// h[y] <= h[x] + g[i].w => g[i].w + h[x] - h[y] >= 0 使边权非负
void heap_dijkstra(int s)
{
    priority_queue<Node> q;
    for (int i = 1; i <= n; i++) dis[s][i] = INF;
    memset(flag, false, sizeof(flag));
    q.push((Node) {s, dis[s][s] = 0});
    while (!q.empty()) {
        int x = q.top().x; q.pop();
        if (flag[x]) continue;
        flag[x] = true;
        for (int i = fte[x]; i; i = g[i].next) {
            int y = g[i].to;
            if (dis[s][y] > dis[s][x] + g[i].w + h[x] - h[y] && !flag[y])
                q.push((Node) {y, dis[s][y] = dis[s][x] + g[i].w + h[x] - h[y]});
        }
    }
    for (int i = 1; i <= n; i++)
        if (dis[s][i] < INF) dis[s][i] += h[i] - h[s];
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1, x, y, w; i <= m; i++)
        scanf("%d%d%d", &x, &y, &w), addEdge(x, y, w);
    for (int i = 1; i <= n; i++) addEdge(0, i, 0);
    if (!spfa(0)) return printf("-1\n"), 0;
    for (int i = 1; i <= n; i++) {
        heap_dijkstra(i);
        long long ans = 0;
        for (int j = 1; j <= n; j++)
            ans += j * (dis[i][j] < INF ? dis[i][j] : 1e9);
        printf("%lld\n", ans);
    }
    return 0;
}
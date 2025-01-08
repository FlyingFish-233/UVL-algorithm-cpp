// P4779 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <climits>
# include <queue>

using namespace std;

const int NR = 1e5 + 10, MR = 2e5 + 10;
const int INF = 0x3f3f3f3f;

struct Edge
{
    int to, next, w;
};

int n, m, s0;
int gsz, fte[NR];
Edge g[MR];

void addEdge(int x, int y, int w)
{
    g[++gsz] = (Edge) {y, fte[x], w};
    fte[x] = gsz;
}

struct Node
{
    int x, d;
    bool operator < (const Node &cmp) const {
        return d > cmp.d;
    }
};

int dis[NR];
priority_queue<Node> q;
bool flag[NR];

void heap_dijkstra(int s)
{
    memset(dis, 0x3f, sizeof(dis));
    q.push((Node) {s, dis[s] = 0});
    while (!q.empty()) {
        int x = q.top().x; q.pop();
        if (flag[x]) continue;
        flag[x] = true;
        for (int i = fte[x]; i; i = g[i].next) {
            int y = g[i].to;
            if (dis[y] > dis[x] + g[i].w)
                q.push((Node) {y, dis[y] = dis[x] + g[i].w});
        }
    }
}

int main()
{
    scanf("%d%d%d", &n, &m, &s0);
    for (int i = 1, x, y, w; i <= m; i++)
        scanf("%d%d%d", &x, &y, &w), addEdge(x, y, w);
    heap_dijkstra(s0);
    for (int i = 1; i <= n; i++)
        printf("%d ", (dis[i] == INF) ? INT_MAX : dis[i]);
    puts("");
    return 0;
}
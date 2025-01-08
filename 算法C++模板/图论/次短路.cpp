// POJ3255 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <queue>

using namespace std;

const int NR = 5e3 + 10, MR = 1e5 + 10;

struct Edge
{
    int to, next, w;
};

int n, m;
int gsz, fte[NR];
Edge g[MR << 1];

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

int dis[2][NR];
priority_queue<Node> q;

void dijkstra(int s)
{
    memset(dis, 0x3f, sizeof(dis)), dis[0][s] = 0;
    q.push((Node) {s, 0});
    while (!q.empty()) {
        int x = q.top().x, d = q.top().d; q.pop();
        if (dis[1][x] < d) continue;
        for (int i = fte[x]; i; i = g[i].next) {
            int y = g[i].to, w = d + g[i].w;
            if (dis[0][y] > w) q.push((Node) {y, w}), swap(dis[0][y], w);
            if (dis[1][y] > w && dis[0][y] < w) q.push((Node) {y, w}), dis[1][y] = w;
        }
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1, x, y, w; i <= m; i++)
        scanf("%d%d%d", &x, &y, &w), addEdge(x, y, w), addEdge(y, x, w);
    dijkstra(1);
    printf("%d\n", dis[1][n]);
    return 0;
}
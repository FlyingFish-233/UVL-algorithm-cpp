// P2661 (60 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <climits>
# include <queue>

using namespace std;

const int NR = 2e5 + 10, MR = 2e5 + 10;
const int INF = 0x3f3f3f3f;

struct Edge
{
    int to, next, w;
};

int n;
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

int dijkstra(int s)
{
    memset(dis, 0x3f, sizeof(dis));
    memset(flag, false, sizeof(flag));
    q.push((Node) {s, dis[s] = 0});
    while (!q.empty()) {
        int x = q.top().x; q.pop();
        if (x == s && dis[s] > 0) return dis[s];
        if (flag[x]) continue;
        flag[x] = true;
        for (int i = fte[x]; i; i = g[i].next) {
            int y = g[i].to;
            if (dis[y] > dis[x] + g[i].w)
                q.push((Node) {y, dis[y] = dis[x] + g[i].w});
        }
        if (x == s && dis[s] == 0) dis[s] = INF;
    }
    return INF;
}

int main()
{
    scanf("%d", &n);
    for (int i = 1, x; i <= n; i++)
        scanf("%d", &x), addEdge(i, x, 1);
    int ans = INF;
    for (int i = 1; i <= n; i++)
        ans = min(ans, dijkstra(i));
    printf("%d\n", ans);
    return 0;
}
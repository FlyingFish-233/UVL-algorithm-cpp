// P1144 (100 pts)
# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <climits>
# include <queue>

using namespace std;

const int NR = 1e6 + 10, MR = 2e6 + 10;
const int mod = 1e5 + 3;

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

struct Node
{
    int x, d;
    bool operator < (const Node &cmp) const {
        return d > cmp.d;
    }
};

int dis[NR], cnt[NR];
priority_queue<Node> q;
bool flag[NR];

void dijkstra(int s)
{
    memset(dis, 0x3f, sizeof(dis));
    dis[s] = 0, cnt[s] = 1;
    q.push((Node) {s, 0});
    while (!q.empty()) {
        int x = q.top().x; q.pop();
        if (flag[x]) continue;
        flag[x] = true;
        for (int i = fte[x]; i; i = g[i].next) {
            int y = g[i].to;
            if (dis[y] > dis[x] + g[i].w)
                q.push((Node) {y, dis[y] = dis[x] + g[i].w}), cnt[y] = cnt[x];
            else if (dis[y] == dis[x] + g[i].w)
                (cnt[y] += cnt[x]) %= mod;
        }
    }
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1, x, y; i <= m; i++)
        scanf("%d%d", &x, &y), addEdge(x, y, 1), addEdge(y, x, 1);
    dijkstra(1);
    for (int i = 1; i <= n; i++)
        printf("%d\n", cnt[i]);
    return 0;
}
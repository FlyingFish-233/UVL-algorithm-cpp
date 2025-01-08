# include <cstdio>
# include <algorithm>
# include <cmath>
# include <cstring>
# include <climits>
# include <queue>

using namespace std;

const int NR = 2e4 + 10, MR = 1e5 + 10;
const int INF = 0x3f3f3f3f;

struct Edge
{
    int to, next, w;
};

int n, m, c[NR];
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

void dijkstra(int s)
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
    scanf("%d%d", &n, &m);
    int pos;
    for (int i = 1; i <= m; i++) {
        scanf("%d", &c[i]);
        if (c[i] == 0) pos = i;
    }
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            if (j - 1 >= 1) addEdge((i - 1) * m + j, (i - 1) * m + j - 1, 1);
            if (j + 1 <= m) addEdge((i - 1) * m + j, (i - 1) * m + j + 1, 1);
            if (i + c[j] >= 1 && i + c[j] <= n) addEdge((i - 1) * m + j, (i + c[j] - 1) * m + j, 2 * abs(c[j]));
        }
    dijkstra((1 - 1) * m + pos);
    int ans = INF;
    for (int i = 1; i <= m; i++)
        ans = min(ans, dis[(n - 1) * m + i]);
    printf("%d\n", (ans == INF) ? -1 : ans);
    return 0;
}